const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const schema = new Schema({
  moisture: Number,
  time: { type: Date, default: Date.now }
});

module.exports = mongoose.model('SensorReading', schema);