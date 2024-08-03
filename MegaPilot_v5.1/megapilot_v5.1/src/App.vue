<template>
  <div id="app">
    <MqttControl />
  </div>
</template>

<script>
import MqttControl from './components/MqttControl.vue';

export default {
  name: 'App',
  components: {
    MqttControl,
  },
};
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
