const mqtt = require('mqtt');
const topics = {
    'outputState/Scenario_1': 'Сценарий_1',
    'outputState/Scenario_1_flag': 'Сценарий_1_flag',
    'outputState/Scenario_2': 'Сценарий_2',
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
    'functionState/Led': 'Лампочка'
};

// Подключение к MQTT брокеру
const client = mqtt.connect('mqtt://127.0.0.1');

// Состояния устройств
const deviceStates = {};

// Флаг выполнения любого сценария
let anyScenarioRunning = false;

let scenarioCooldown = false;

// Функция для форматирования даты и времени
function getCurrentDateTime() {
    const now = new Date();
    return now.toISOString().replace('T', ' ').replace(/\.\d+Z$/, '');
}

// Сохраняем предыдущие состояния для обнаружения изменений
const previousStates = {};

client.on('connect', () => {
    console.log(`[${getCurrentDateTime()}] Connected to MQTT broker`);
    
    // Подписываемся на все топики
    const topicList = Object.keys(topics);
    client.subscribe(topicList, (err) => {
        if (err) {
            console.error(`[${getCurrentDateTime()}] Subscription error:`, err);
        } else {
            console.log(`[${getCurrentDateTime()}] Subscribed to topics:`, topicList);
        }
    });
});

client.on('message', (topic, message) => {
    const messageStr = message.toString();
    const topicName = topics[topic] || topic;
    
    // Логируем входящее сообщение
    console.log(`[${getCurrentDateTime()}] Received MQTT message: ${topicName} = ${messageStr}`);
    
    // Сохраняем предыдущее состояние перед обновлением
    previousStates[topic] = deviceStates[topic];
    // Сохраняем текущее состояние устройства
    deviceStates[topic] = messageStr;
    
    // Если какой-то сценарий уже выполняется, игнорируем новые проверки
    if (anyScenarioRunning || scenarioCooldown) {
        console.log(`[${getCurrentDateTime()}] - `);
        return;
    }
    
    // Проверяем условия для сценариев
    checkScenarios();
});

// Функция для логирования исходящих сообщений
function publishWithLog(topic, message) {
    const topicName = topics[topic] || topic;
    console.log(`[${getCurrentDateTime()}] Sending MQTT message: ${topicName} = ${message}`);
    client.publish(topic, message, { retain: true });
}

function checkScenarios() {
    // Проверяем условия для сценария 3 (имеет приоритет)
    if (deviceStates['outputState/Scenario_1'] === 'true' && 
        deviceStates['outputState/Scenario_1_flag'] === 'true'
    ) {
        console.log(`[${getCurrentDateTime()}] Scenario 3 conditions met (Scenario_1)`);
        executeScenario3();
        return;
    }

    if (deviceStates['outputState/Scenario_2'] === 'true' && 
    deviceStates['outputState/Scenario_2_flag'] === 'true'
    ) {
        console.log(`[${getCurrentDateTime()}] Scenario 3 conditions met (Scenario_2)`);
        executeScenario3();
        return;
    }

    // Проверяем условия для сценария 1
    if (deviceStates['outputState/Scenario_1'] === 'true' && 
        deviceStates['outputState/Scenario_1_flag'] === 'false'
    ) {
        console.log(`[${getCurrentDateTime()}] Scenario 1 conditions met`);
        executeScenario1();
        return;
    }

    // Проверяем условия для сценария 2
    if (deviceStates['outputState/Scenario_2'] === 'true' && 
        deviceStates['outputState/Scenario_2_flag'] === 'false'
    ) {
        console.log(`[${getCurrentDateTime()}] Scenario 2 conditions met`);
        executeScenario2();
        return;
    }

    // Проверяем условия для сценария Room
    if (deviceStates['functionState/Room'] === 'false' && 
        (previousStates['functionState/Room'] === undefined || 
         previousStates['functionState/Room'] !== deviceStates['functionState/Room'])) {
        console.log(`[${getCurrentDateTime()}] Room door opened (false received)`);
        executeScenarioRoom();
        return;
    }

    // Проверяем условия для сценария Balcon
    if (deviceStates['functionState/Balcon'] === 'false' && 
        (previousStates['functionState/Balcon'] === undefined || 
         previousStates['functionState/Balcon'] !== deviceStates['functionState/Balcon'])) {
        console.log(`[${getCurrentDateTime()}] Balcon door opened (false received)`);
        executeScenarioBalcon();
        return;
    }
}

async function executeScenarioRoom() {
    anyScenarioRunning = true;
    console.log(`[${getCurrentDateTime()}] Executing Room scenario - closing door after delay`);
    
    try {
        await delay(1000);
        publishWithLog('functionState/Room', 'true');
        await delay(100);
        publishWithLog('functionState/Led', 'false');
        await delay(500);
        publishWithLog('functionState/Led', 'true');
        
    } catch (err) {
        console.error(`[${getCurrentDateTime()}] Error executing Room scenario:`, err);
    } finally {
        anyScenarioRunning = false;
        console.log(`[${getCurrentDateTime()}] Room scenario execution completed`);
    }
}

async function executeScenarioBalcon() {
    anyScenarioRunning = true;
    console.log(`[${getCurrentDateTime()}] Executing Balcon scenario - closing door after delay`);
    
    try {
        await delay(3000);
        publishWithLog('functionState/Balcon', 'true');
        await delay(100);
        publishWithLog('functionState/Led', 'false');
        await delay(500);
        publishWithLog('functionState/Led', 'true');
        await delay(500);
        publishWithLog('functionState/Led', 'false');
        await delay(500);
        publishWithLog('functionState/Led', 'true');
        await delay(500);
        publishWithLog('functionState/Led', 'false');
        await delay(500);
        publishWithLog('functionState/Led', 'true');
        
    } catch (err) {
        console.error(`[${getCurrentDateTime()}] Error executing Balcon scenario:`, err);
    } finally {
        anyScenarioRunning = false;
        console.log(`[${getCurrentDateTime()}] Balcon scenario execution completed`);
    }
}

async function executeScenario1() {
    anyScenarioRunning = true;
    console.log(`[${getCurrentDateTime()}] Executing Scenario 1`);
    
    try {
        publishWithLog('functionState/Led', 'false');
        await delay(100);
        // Устанавливаем флаг сценария
        publishWithLog('outputState/Scenario_1_flag', 'true');
        publishWithLog('outputState/Remote_1', 'true');
        await delay(500);
        publishWithLog('outputState/Camera', 'true');
        await delay(500);
        publishWithLog('outputState/Stage', 'true');
        await delay(500);
        publishWithLog('outputState/Microphones', 'true');
        await delay(500);
        publishWithLog('outputState/Switching', 'true');
        await delay(1000);
        publishWithLog('outputState/Broadcast', 'true');
        await delay(500);
        publishWithLog('outputState/Monitors', 'true');
        await delay(500);
        publishWithLog('outputState/Portal', 'true');
        await delay(500);
        publishWithLog('outputState/Light(1)', 'true');
        publishWithLog('outputState/Light(2)', 'true');
        await delay(1000);
        publishWithLog('outputState/Light(lectern)', 'true');
        await delay(1000);
        publishWithLog('outputState/Light(piano)', 'true');
        await delay(500);
        // Завершаем сценарий
        publishWithLog('outputState/Scenario_1', 'false');
        await delay(100);
        publishWithLog('functionState/Led', 'true');
        
    } catch (err) {
        console.error(`[${getCurrentDateTime()}] Error executing Scenario 1:`, err);
    } finally {
        // Активируем защиту от повторного запуска
        scenarioCooldown = true;
        setTimeout(() => {
            scenarioCooldown = false;
            console.log(`[${getCurrentDateTime()}] Scenario cooldown ended`);
        }, 1000); // 1 секунда защиты

        anyScenarioRunning = false;
        console.log(`[${getCurrentDateTime()}] Scenario 1 execution completed`);
    }
}

async function executeScenario2() {
    anyScenarioRunning = true;
    console.log(`[${getCurrentDateTime()}] Executing Scenario 2`);
    
    try {
        publishWithLog('functionState/Led', 'false');
        await delay(100);
        // Устанавливаем флаг сценария
        publishWithLog('outputState/Scenario_2_flag', 'true');
        
        publishWithLog('outputState/Remote_1', 'true');
        await delay(500);
        publishWithLog('outputState/Stage', 'true');
        await delay(500);
        publishWithLog('outputState/Microphones', 'true');
        await delay(500);
        publishWithLog('outputState/Switching', 'true');
        await delay(1000);
        publishWithLog('outputState/Monitors', 'true');
        await delay(1000);
        publishWithLog('outputState/Portal', 'true');
        // Завершаем сценарий
        publishWithLog('outputState/Scenario_2', 'false');

        await delay(100);
        publishWithLog('functionState/Led', 'true');
        
    } catch (err) {
        console.error(`[${getCurrentDateTime()}] Error executing Scenario 2:`, err);
    } finally {
        // Активируем защиту от повторного запуска
        scenarioCooldown = true;
        setTimeout(() => {
            scenarioCooldown = false;
            console.log(`[${getCurrentDateTime()}] Scenario cooldown ended`);
        }, 1000); // 1 секунда защиты

        anyScenarioRunning = false;
        console.log(`[${getCurrentDateTime()}] Scenario 2 execution completed`);
    }
}

async function executeScenario3() {
    anyScenarioRunning = true;
    console.log(`[${getCurrentDateTime()}] Executing Scenario 3`);
    
    try {
        publishWithLog('functionState/Led', 'false');
        await delay(100);
        // Сбрасываем флаги сценариев
        publishWithLog('outputState/Scenario_1_flag', 'false');
        publishWithLog('outputState/Scenario_2_flag', 'false');
        
        publishWithLog('outputState/Broadcast', 'false');
        await delay(500);
        publishWithLog('outputState/Monitors', 'false');
        await delay(500);
        publishWithLog('outputState/Portal', 'false');
        await delay(500);
        publishWithLog('outputState/Remote_1', 'false');
        await delay(500);
        publishWithLog('outputState/Camera', 'false');
        await delay(500);
        publishWithLog('outputState/Microphones', 'false');
        await delay(500);
        publishWithLog('outputState/Stage', 'false');
        await delay(500);
        publishWithLog('outputState/Switching', 'false');
        await delay(500);
        publishWithLog('outputState/Light(1)', 'false');
        publishWithLog('outputState/Light(2)', 'false');
        await delay(500);
        publishWithLog('outputState/Light(choir)', 'false');
        await delay(500);
        publishWithLog('outputState/Light(piano)', 'false');
        await delay(500);
        publishWithLog('outputState/Light(lectern)', 'false');
        await delay(500);
        // Завершаем сценарии
        publishWithLog('outputState/Scenario_1', 'false');
        publishWithLog('outputState/Scenario_2', 'false');

        await delay(100);
        publishWithLog('functionState/Led', 'true');
        
    } catch (err) {
        console.error(`[${getCurrentDateTime()}] Error executing Scenario 3:`, err);
    } finally {
        // Активируем защиту от повторного запуска
        scenarioCooldown = true;
        setTimeout(() => {
            scenarioCooldown = false;
            console.log(`[${getCurrentDateTime()}] Scenario cooldown ended`);
        }, 1000); // 1 секунда защиты

        anyScenarioRunning = false;
        console.log(`[${getCurrentDateTime()}] Scenario 3 execution completed`);
    }
}

// Функция задержки
function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

// Обработка ошибок
client.on('error', (err) => {
    console.error(`[${getCurrentDateTime()}] MQTT error:`, err);
});

process.on('SIGINT', () => {
    console.log(`[${getCurrentDateTime()}] Shutting down...`);
    client.end();
    process.exit();
});

console.log(`[${getCurrentDateTime()}] Automation server started`);