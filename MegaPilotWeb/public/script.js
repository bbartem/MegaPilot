const socket = io();
const grid1 = document.getElementById('buttonGrid');
const grid2 = document.getElementById('buttonGrid2');
const statusIndicator = document.getElementById('statusIndicator');

// Иконки для кнопок
const iconMap = {
  'outputState/Remote_1': 'fa-sliders-h',
  'outputState/Camera': 'fa-video',
  'outputState/Stage': 'fa-theater-masks',
  'outputState/Microphones': 'fa-microphone',
  'outputState/Switching': 'fa-project-diagram',
  'outputState/Broadcast': 'fa-radio',
  'outputState/Monitors': 'fa-volume-low',
  'outputState/Portal': 'fa-volume-high',
  'outputState/Light(lectern)': 'fa-lightbulb',
  'outputState/Light(piano)': 'fa-lightbulb',
  'outputState/Light(1)': 'fa-lightbulb',
  'outputState/Light(2)': 'fa-lightbulb',
  'outputState/Light(choir)': 'fa-lightbulb',
  'outputState/Screen': 'fa-users-rectangle',
  'outputState/Scenario_1': 'fa-scroll',
  'outputState/Scenario_2': 'fa-scroll',
  'functionState/Room': 'fa-door-open',
  'functionState/Balcon': 'fa-door-open',
  'functionState/Remote_2': 'fa-sliders-h',
  'tuya/Podsvetka': 'fa-lightbulb',
  'tuya/TV': 'fa-tv'
};

const buttonConfigs = {
  'outputState/Remote_1': { label: 'Пульт 1', color: 'green', panel: 1 },
  'outputState/Camera': { label: 'Камера', color: 'green', panel: 1 },
  'outputState/Stage': { label: 'Сцена', color: 'green', panel: 1 },
  'outputState/Microphones': { label: 'Микрофоны', color: 'green', panel: 1 },
  'outputState/Switching': { label: 'Коммутация', color: 'green', panel: 1 },
  'outputState/Broadcast': { label: 'Трансляция', color: 'green', panel: 1 },
  'outputState/Monitors': { label: 'Мониторы', color: 'green', panel: 1 },
  'outputState/Portal': { label: 'Портал', color: 'green', panel: 1 },
  'outputState/Light(lectern)': { label: 'Кафедра', color: 'green', panel: 1 },
  'outputState/Light(piano)': { label: 'Рояль', color: 'green', panel: 1 },
  'outputState/Light(1)': { label: 'Свет(1)', color: 'green', panel: 1 },
  'outputState/Light(2)': { label: 'Свет(2)', color: 'green', panel: 1 },
  'outputState/Light(choir)': { label: 'Свет(Хор)', color: 'green', panel: 1 },
  'outputState/Screen': { label: 'Экран', color: 'green', panel: 1 },
  'outputState/Scenario_1': { label: 'Сценарий 1', color: 'red', flag: 'outputState/Scenario_1_flag', panel: 1 },
  'outputState/Scenario_2': { label: 'Сценарий 2', color: 'red', flag: 'outputState/Scenario_2_flag', panel: 1 },
  'functionState/Room': { label: 'Подсобка', color: 'green', panel: 2 },
  'functionState/Balcon': { label: 'Балкон', color: 'green', panel: 2 },
  'functionState/Remote_2': { label: 'Пульт_2', color: 'green', panel: 2 },
  'tuya/Podsvetka': { label: 'Подсветка сцена', color: 'green', panel: 2, tuya: { id: 'bf577538662ed7a91elury', command: 'switch' } },
  'tuya/TV': { label: 'Телевизор', color: 'green', panel: 2, tuya: { id: 'bfa369e38afbb8bb20mjju', command: 'Power' } }
};

const buttons = {};
let currentPanel = 0;

function renderButtons() {
  for (const topic in buttonConfigs) {
    const config = buttonConfigs[topic];
    const grid = config.panel === 2 ? grid2 : grid1;
    const container = document.createElement('div');
    container.classList.add('button-container');

    const btn = document.createElement('div');
    btn.classList.add('button', 'gray');

    const btnInner = document.createElement('div');
    btnInner.classList.add('button-inner');

    const icon = document.createElement('i');
    icon.classList.add('fas', iconMap[topic], 'button-icon');

    const label = document.createElement('div');
    label.classList.add('button-label');
    label.innerText = config.label;

    btnInner.appendChild(icon);
    btn.appendChild(btnInner);
    container.appendChild(btn);
    container.appendChild(label);

    btn.onclick = () => socket.emit('toggle', topic);
    grid.appendChild(container);
    buttons[topic] = btn;
  }
}

function updateButtonState(topic, value) {
  for (const key in buttonConfigs) {
    const config = buttonConfigs[key];
    if (config.flag && config.flag === topic) {
      const btn = buttons[key];
      btn.className = 'button';
      btn.classList.add(value ? config.color : config.color + '-outline');
    } else if (topic === key && !config.flag) {
      const btn = buttons[key];
      btn.className = 'button';
      btn.classList.add(value ? config.color : 'gray');
    }
  }
}

function slidePanel(direction) {
  currentPanel = Math.max(0, Math.min(1, currentPanel + direction));
  const panels = document.querySelector('.panels');
  panels.style.transform = `translateX(-${currentPanel * 50}%)`;
}

// Обработчик статуса ping
socket.on('pingStatus', ({ status, type }) => {
  statusIndicator.classList.remove('active', 'error');
  if (status) {
    statusIndicator.classList.add('active');
  } else {
    statusIndicator.classList.add('error');
  }
  setTimeout(() => {
    statusIndicator.classList.remove('active', 'error');
  }, 500);
});

renderButtons();

socket.on('initialState', (states) => {
  for (const topic in states) {
    updateButtonState(topic, states[topic]);
  }
});

socket.on('stateUpdate', ({ topic, value }) => {
  updateButtonState(topic, value);
});