const aedes = require('aedes')();
const server = require('net').createServer(aedes.handle);
const port = 1883;

server.listen(port, function () {
    console.log(`MQTT broker started and listening on port ${port}`);
});

// Задаем значения по умолчанию для топиков
const defaultTopics = {
    'outputState/Scenario_1': false,
    'outputState/Scenario_2': false,
    'outputState/Scenario_1_flag': false,
    'outputState/Scenario_2_flag': false,
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
    'functionState/Balcon': true,
    'functionState/Remote_2': true
};

// Публикуем значения по умолчанию
Object.keys(defaultTopics).forEach(topic => {
    aedes.publish({
        topic: topic,
        payload: JSON.stringify(defaultTopics[topic]),
        qos: 0,
        retain: true
    }, () => {
        console.log(`Default value published for topic: ${topic}`);
    });
});

// Обработка событий подключения клиентов
aedes.on('client', function (client) {
    console.log(`Client connected: ${client.id}`);
});

// Обработка событий отключения клиентов
aedes.on('clientDisconnect', function (client) {
    console.log(`Client disconnected: ${client.id}`);
});

// Обработка событий подписки на топики
aedes.on('subscribe', function (subscriptions, client) {
    console.log(`Client ${client.id} subscribed to: ${subscriptions.map(s => s.topic).join(', ')}`);
});

// Обработка событий отписки от топиков
aedes.on('unsubscribe', function (subscriptions, client) {
    console.log(`Client ${client.id} unsubscribed from: ${subscriptions.join(', ')}`);
});

// Обработка событий публикации сообщений
aedes.on('publish', function (packet, client) {
    if (client) {
        console.log(`Client ${client.id} published to ${packet.topic}: ${packet.payload.toString()}`);
    }
});