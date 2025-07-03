const aedes = require('aedes')();
const net = require('net');
const WebSocket = require('ws');
const http = require('http');
const fs = require('fs');

const MQTT_PORT = 1883;
const WS_PORT = 4444;

// Объект для хранения состояний
let stateStorage = {};

// Запуск MQTT-сервера
const mqttServer = net.createServer(aedes.handle);
mqttServer.listen(MQTT_PORT, () => {
  console.log(`MQTT broker started on port ${MQTT_PORT}`);
});

// Запуск WebSocket-сервера
const wsServer = new WebSocket.Server({ port: WS_PORT });
console.log(`WebSocket server started on port ${WS_PORT}`);

const clients = new Set();
wsServer.on('connection', (ws) => {
  clients.add(ws);
  ws.on('close', () => clients.delete(ws));
});

// Отправка данных во все WebSocket-клиенты
function broadcast(data) {
  const message = JSON.stringify(data);
  clients.forEach((ws) => ws.send(message));
}

// Функции для работы с состояниями
function updateState(topic, payload) {
  stateStorage[topic] = payload;
  broadcast({ type: 'update', topic, payload });
}

function getState(topic) {
  return stateStorage[topic] || null;
}

// Обработка событий Aedes
function logEvent(type, data) {
  console.log(`[${type}]`, data);
  broadcast({ type, data });
}

aedes.on('client', (client) => logEvent('client_connected', client.id));
aedes.on('clientDisconnect', (client) => logEvent('client_disconnected', client.id));
aedes.on('subscribe', (subscriptions, client) => logEvent('subscribed', { client: client.id, subscriptions }));
aedes.on('publish', (packet, client) => {
  const topic = packet.topic;
  const payload = packet.payload.toString();

  // Сохраняем состояние
  updateState(topic, payload);

  if (client) {
    logEvent('message', { client: client.id, topic, payload });
  }
});

// Веб-сервер для HTML-страницы
const webServer = http.createServer((req, res) => {
  fs.readFile('index.html', (err, data) => {
    if (err) {
      res.writeHead(500);
      res.end('Error loading index.html');
    } else {
      res.writeHead(200, { 'Content-Type': 'text/html' });
      res.end(data);
    }
  });
});
webServer.listen(8080, () => console.log('Web server running on http://localhost:8080'));
