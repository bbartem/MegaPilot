const express = require('express');
const mqtt = require('mqtt');
const http = require('http');
const socketIo = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = socketIo(server);
const port = 3000;

// Подключение к MQTT брокеру
const mqttClient = mqtt.connect('mqtt://192.168.0.27');

// Состояние кнопок
let buttonStates = new Array(21).fill(false);

// Использование EJS для рендеринга HTML
app.set('view engine', 'ejs');
app.use(express.static('public'));

// Подписка на топик MQTT
mqttClient.on('connect', () => {
    console.log('Connected to MQTT broker');
    mqttClient.subscribe('arduino/status');
});

mqttClient.on('message', (topic, message) => {
    try {
        if (topic === 'arduino/status') {
            const data = JSON.parse(message.toString());
            const button = data.button !== undefined ? data.button : data.index; // Поддержка обоих вариантов
            if (button !== undefined && button >= 0 && button < 21) {
                buttonStates[button] = data.state;
                io.emit('updateButtons', buttonStates); // Обновляем кнопки у всех клиентов
            }
        }
    } catch (error) {
        console.error('Error parsing MQTT message:', error);
    }
});

// Маршрут для главной страницы
app.get('/', (req, res) => {
    res.render('index', { buttonStates });
});

// Маршрут для обработки нажатий кнопок
app.post('/toggle/:button', (req, res) => {
    const button = parseInt(req.params.button);
    if (button >= 0 && button < 21) {
        buttonStates[button] = !buttonStates[button];
        mqttClient.publish('arduino/control', JSON.stringify({ button, state: buttonStates[button] }));
        io.emit('updateButtons', buttonStates); // Обновляем кнопки у всех клиентов
    }
    res.redirect('/');
});

// Запуск сервера
server.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});
