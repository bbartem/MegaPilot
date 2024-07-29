<template>
  <div id="app">
    <template v-if="authenticated">
      <h1>MegaPilot_v5.1</h1>
      <div v-for="relay in relays" :key="relay.id">
        <button @click="toggleRelay(relay.id)" class="buttonMQTT">Реле {{ relay.id }}: {{ relay.state }}</button>
      </div>
    </template>
    <template v-else>
      <div class="pin-container">
        <h2>Введите PIN-код</h2>
        <input type="password" v-model="pin" @keyup.enter="checkPin"/>
        <button @click="checkPin">Войти</button>
        <p v-if="error">{{ error }}</p>
      </div>
    </template>
  </div>
</template>

<script>
import mqtt from 'mqtt';

export default {
  data() {
    return {
      relays: [
        { id: 0, state: 'OFF' },
        { id: 1, state: 'OFF' },
        { id: 2, state: 'OFF' },
        { id: 3, state: 'OFF' },
        { id: 4, state: 'OFF' },
        { id: 6, state: 'OFF' },
        { id: 7, state: 'OFF' },
        { id: 8, state: 'OFF' },
        { id: 9, state: 'OFF' },
        { id: 10, state: 'OFF' },
        { id: 11, state: 'OFF' },
        { id: 12, state: 'OFF' },
        { id: 13, state: 'OFF' },
        { id: 14, state: 'OFF' },
        { id: 15, state: 'OFF' },
      ],
      client: null,
      authenticated: false,
      pin: '',
      error: ''
    };
  },
  mounted() {
    this.client = mqtt.connect('ws://192.168.1.40:1883');
    this.client.on('connect', () => {
      console.log('Connected to MQTT broker');
      this.client.subscribe('home/relay');
    });

    this.client.on('message', (topic, message) => {
      if (topic === 'home/relay') {
        const relay = parseInt(message.toString());
        this.relays[relay].state = this.relays[relay].state === 'OFF' ? 'ON' : 'OFF';
      }
    });
  },
  methods: {
    toggleRelay(relayId) {
      this.client.publish('home/relay', relayId.toString());
    },
    checkPin() {
      const correctPin = '1234'; // Задайте правильный PIN-код
      if (this.pin === correctPin) {
        this.authenticated = true;
        this.error = '';
      } else {
        this.error = 'Неверный PIN-код';
      }
    }
  }
};
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  text-align: center;
  color: #2c3e50;
}

.pin-container {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.buttonMQTT {
  width: 120px;
  height: 30px;
  margin: 10px;
}

input {
  margin: 10px;
  padding: 5px;
  font-size: 16px;
}
</style>
