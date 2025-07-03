const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const pug = require('pug');
const mqtt = require('mqtt');

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

app.set('view engine', 'pug');
app.set('views', './views');

app.use(express.static('public'));

app.get('/', (req, res) => {
    res.render('index');
});

// Определяем значения по умолчанию для топиков
const defaultTopics = {
    'outputState/Scenario_1': false,
    'outputState/Scenario_2': false,
    'outputState/Remote_1': false,
    'outputState/Camera': false,
    'outputState/Stage': false,
    'outputState/Microphones': false,
    'outputState/Switching': false,
    'outputState/Broadcast': false,
    'outputState/Monitors': false,
    'outputState/Portal': false,
    'outputState/Light(lectern)': false,
    'outputState/Light(choir)': false,
    'outputState/Light(piano)': false,
    'outputState/Light(1)': false,
    'outputState/Light(2)': false,
    'outputState/Screen': true,
    'functionState/Room': true,
    'functionState/Remote_2': true,
    'functionState/Balcon': true
};

// Подключение к MQTT брокеру
const mqttClient = mqtt.connect('mqtt://localhost:1883');

mqttClient.on('connect', () => {
    console.log('Connected to MQTT broker');
    mqttClient.subscribe('#', (err) => {
        if (!err) {
            console.log('Subscribed to all topics');
        }
    });

    // Запрашиваем текущие значения топиков
    Object.keys(defaultTopics).forEach(topic => {
        mqttClient.publish(topic, JSON.stringify(defaultTopics[topic]), { qos: 0, retain: true });
    });
});

mqttClient.on('message', (topic, message) => {
    io.emit('mqtt-message', { topic, message: message.toString() });
});

io.on('connection', (socket) => {
    console.log('A client connected to the web interface');

    socket.on('disconnect', () => {
        console.log('A client disconnected from the web interface');
    });
});

server.listen(3001, () => {
    console.log('Web server started on http://localhost:3001');
});