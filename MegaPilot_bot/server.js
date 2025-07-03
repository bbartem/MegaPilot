const TelegramBot = require('node-telegram-bot-api');
const mqtt = require('mqtt');
const fs = require('fs');

const TOKEN = '7276815810:AAHxX0CCWXFPdoUzxfETGteDCItu2eZpfHU';
const MQTT_BROKER = 'mqtt://192.168.0.31';
const LOG_FILE = 'bot_logs.txt';

const bot = new TelegramBot(TOKEN, { polling: true });
const client = mqtt.connect(MQTT_BROKER);

const topics = {
    'outputState/Scenario_1': 'Сценарий_1',
    'outputState/Scenario_2': 'Сценарий_2',
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
    'functionState/Remote_2': 'Пульт_2'
};

let states = {};
let chatIds = new Set();

client.on('connect', () => {
    console.log('Connected to MQTT broker');
    Object.keys(topics).forEach(topic => client.subscribe(topic));
});

client.on('message', (topic, message) => {
    const key = topics[topic];
    const newState = message.toString() === 'true' ? 'ON' : 'OFF';
    
    if (states[key] !== newState) {
        states[key] = newState;
        console.log(`Updated: ${key} -> ${newState}`);
        updateAllKeyboards(key, newState);
    }
});

const generateKeyboard = () => {
    return [
        ['Сценарий_1', 'Сценарий_2'],
        ['Пульт_1', 'Подсобка'],
        ['Камера', 'Балкон'],
        ['Сцена', 'Пульт_2'],
        ['Микрофоны', ' '],
        ['Коммутация', ' '],
        ['Трансляция', ' '],
        ['Мониторы', ' '],
        ['Портал', ' '],
        ['Свет(кафедра)', ' '],
        ['Свет(Хор)', ' '],
        ['Свет(рояль)', ' '],
        ['Свет(1)', ' '],
        ['Свет(2)', ' '],
        ['Экран', ' '],
        ['Show Logs'],
        ['Restart Bot'],
    ].map(row => row.map(name => name.trim() ? `${name} ${states[name] || 'OFF'}` : ' '));
};

const logAction = (user, command) => {
    const logEntry = `${new Date().toISOString()} - ${user}: ${command}\n`;
    fs.appendFileSync(LOG_FILE, logEntry);
};

const updateAllKeyboards = (changedKey, newState) => {
    const updateMessage = `Обновлено ✅ ${changedKey} -> ${newState}`;
    chatIds.forEach(chatId => {
        bot.sendMessage(chatId, updateMessage, {
            reply_markup: { keyboard: generateKeyboard(), resize_keyboard: true }
        });
    });
};

bot.onText(/\/start/, (msg) => {
    chatIds.add(msg.chat.id);
    bot.sendMessage(msg.chat.id, 'Выберите команду: (◕‿◕)', {
        reply_markup: { keyboard: generateKeyboard(), resize_keyboard: true }
    });
});

bot.on('message', (msg) => {
    const chatId = msg.chat.id;
    const button = msg.text.split(' ')[0];

    if (button === 'Show') {
        fs.readFile(LOG_FILE, 'utf8', (err, data) => {
            bot.sendMessage(chatId, err ? 'Ошибка чтения логов. ❌' : `📜 Логи:\n${data || 'Нет записей'}`);
        });
        return;
    }

    if (button === 'Restart') {
        logAction(msg.from.username || msg.from.first_name, 'Restart Bot');
        bot.sendMessage(chatId, '🔄 Перезапускаю бота...', {
            reply_markup: { keyboard: generateKeyboard(), resize_keyboard: true }
        });
        // Отправляем команду /start как новое сообщение от имени пользователя
        const startMsg = {
            ...msg,
            text: '/start',
            entities: [{
                type: 'bot_command',
                offset: 0,
                length: 6
            }]
        };
        bot.processUpdate({ message: startMsg });
        return;
    }

    const topic = Object.keys(topics).find(t => topics[t] === button);
    if (topic) {
        const newState = states[button] === 'ON' ? 'false' : 'true';

        if (states[button] !== (newState === 'true' ? 'ON' : 'OFF')) {
            client.publish(topic, newState, { retain: true });
            logAction(msg.from.username || msg.from.first_name, `${button} -> ${newState}`);
        }
    }
});
