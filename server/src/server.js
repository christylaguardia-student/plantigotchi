const express = require('express');
const app = express();
const bodyParser = require('body-parser').json();

const connect = require('./lib/databaseConnect');
const dbUri = process.env.MONGODB_URI || 'mongodb://localhost:27017/plantigotchi'; //'mongodb://plant:igotchi@ds155080.mlab.com:55080/plantigotchi'
connect(dbUri);

const PORT = process.env.PORT || 3000;

// connect adatafruit to ip address "http://10.0.12.192:3000/"

const SensorReading = require('./lib/sensorReadings');

// app.get('/', (req, res) => {
//   res.sendFile(__dirname + '/index.html');
// });

app.get('/', bodyParser, (req, res) => {
  res.send('plantigotchi received get request');
});

app.post('/', bodyParser, (req, res) => {
  console.log('plantigotchi received post request', req.body);

  const moistureReading = new SensorReading(req.body);
  console.log('moistureReading', moistureReading);

  moistureReading.save()
    .then(saved => res.send(saved))

});

app.listen(PORT, () => {
  console.log(`Server started on port ${PORT}!`);
});