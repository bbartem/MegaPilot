const express = require('express');
const http = require('http');
const { Server } = require('socket.io');
const mqtt = require('mqtt');
const ping = require('ping');
const TuyaDevice = require('tuyapi');

const app = express();
const server = http.createServer(app);
const io = new Server(server);

app.use(express.static('public'));

const mqttClient = mqtt.connect('mqtt://127.0.0.1');

// Tuya device configurations
const tuyaDevices = {
  'tuya/Podsvetka': {
    id: 'bf577538662ed7a91elury',
    key: ':T]r_me$X;]edL!4',
    command: 'switch'
  },
  'tuya/TV': {
    id: 'bfa369e38afbb8bb20mjju',
    key: '607fe8adf10116bf',
    command: 'Power'
  }
};

const topics = {
  'outputState/Scenario_1': 'Сценарий_1',
  'outputState/Scenario_1_flag': 'Сценарий_1_flag',
  'outputState/Scenario_2': 'Сценарий_2', // Fixed typo
  'outputState/Scenario_2_flag': 'Сценарий_2_flag',
  'outputState/Remote_1': 'Пульт_1',
  'outputState/Camera': 'Камера',
  'outputState/Stage': 'Сцена',
  'outputState/Microphones': 'Микрофоны',
  'outputState/Switching': 'Коммутация',
  'outputState/Broadcast': 'Трансляция',
  'outputState/Monitors': 'Мониторы',
  'outputState/Portal': 'Портал',
  'outputState/Light(lectern)': 'Свет(кафедра)',
  'outputState/Light(choir)': 'Свет(Хор)',
  'outputState/Light(piano)': 'Свет(рояль)',
  'outputState/Light(1)': 'Свет(1)',
  'outputState/Light(2)': 'Свет(2)',
  'outputState/Screen': 'Экран',
  'functionState/Room': 'Подсобка',
  'functionState/Balcon': 'Балкон',
  'functionState/Remote_2': 'Пульт_2',
  'tuya/Podsvetka': 'Подсветка сцена',
  'tuya/TV': 'Телевизор'
};

const state = {};

mqttClient.on('connect', () => {
  console.log('Connected to MQTT broker');
  mqttClient.subscribe(Object.keys(topics));
});

mqttClient.on('message', (topic, message) => {
  const value = message.toString() === '1' || message.toString().toLowerCase() === 'true';
  state[topic] = value;
  io.emit('stateUpdate', { topic, value });
});

async function checkPing() {
  const target = '192.168.1.52';
  try {
    const res = await ping.promise.probe(target, {
      timeout: 1,
      extra: ['-c', '1'],
    });
    io.emit('pingStatus', { 
      status: res.alive,
      type: res.alive ? 'success' : 'error'
    });
    return res.alive;
  } catch (error) {
    console.error('Ping error:', error);
    io.emit('pingStatus', {
      status: false,
      type: 'error'
    });
    return false;
  }
}

setInterval(checkPing, 2000);

io.on('connection', (socket) => {
  console.log('Client connected');
  socket.emit('initialState', state);

  socket.on('toggle', async (topic) => {
    const newValue = !state[topic];
    state[topic] = newValue;

    if (topic.startsWith('tuya/')) {
      const deviceConfig = tuyaDevices[topic];
      if (deviceConfig) {
        try {
          const device = new TuyaDevice({
            id: deviceConfig.id,
            key: deviceConfig.key
          });
          await device.connect();
          await device.set({ set: newValue, dps: deviceConfig.command === 'switch' ? 1 : 20 }); // DPS 1 for switch, 20 for Power (common for TVs)
          await device.disconnect();
          io.emit('stateUpdate', { topic, value: newValue });
        } catch (error) {
          console.error(`Tuya error for ${topic}:`, error);
        }
      }
    } else {
      mqttClient.publish(topic, newValue ? 'true' : 'false', { retain: true });
    }
  });
});

server.listen(4561, () => {
  console.log('Server running on http://192.168.1.51:4561');
});