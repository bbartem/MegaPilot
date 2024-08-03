<template>
    <div>
      <h1>Smart Home Control</h1>
      <div v-for="(state, index) in outputStates" :key="index">
        <h2>Output {{ index }}</h2>
        <button @click="toggleOutput(index)">
          {{ state ? 'Turn OFF' : 'Turn ON' }}
        </button>
      </div>
      <div v-for="(state, index) in functionStates" :key="'func-' + index">
        <h2>Function {{ index }}</h2>
        <button @click="toggleFunction(index)">
          {{ state ? 'Turn OFF' : 'Turn ON' }}
        </button>
      </div>
    </div>
  </template>
  
  <script>
  import mqtt from 'mqtt';
  
  export default {
    data() {
      return {
        client: null,
        outputStates: Array(16).fill(false),
        functionStates: Array(16).fill(false),
        mqttServer: 'ws://YOUR_MQTT_SERVER_ADDRESS:PORT',
      };
    },
    created() {
      this.connectMQTT();
    },
    methods: {
      connectMQTT() {
        this.client = mqtt.connect(this.mqttServer);
        this.client.on('connect', () => {
          console.log('Connected to MQTT server');
          this.client.subscribe('outputState');
          this.client.subscribe('functionState');
        });
        this.client.on('message', (topic, message) => {
          const index = parseInt(message.toString(), 10);
          if (topic === 'outputState') {
            this.$set(this.outputStates, index, !this.outputStates[index]);
          } else if (topic === 'functionState') {
            this.$set(this.functionStates, index, !this.functionStates[index]);
          }
        });
      },
      toggleOutput(index) {
        const newState = !this.outputStates[index];
        this.outputStates[index] = newState;
        this.client.publish('outputState', index.toString());
      },
      toggleFunction(index) {
        const newState = !this.functionStates[index];
        this.functionStates[index] = newState;
        this.client.publish('functionState', index.toString());
      },
    },
  };
  </script>
  
  <style scoped>
  button {
    margin: 5px;
  }
  </style>
  