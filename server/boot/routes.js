const bodyParser = require('body-parser').json();

module.exports = function(app) {
  const SensorReading = require('../src/sensorReadings');
  var router = app.loopback.Router();



  // app.get('/', (req, res) => {
    //   res.sendFile(__dirname + '/index.html');
    // });

    app.get('/plant', bodyParser, (req, res) => {
      res.send('plantigotchi received get request');
    });

    app.post('/plant', bodyParser, (req, res) => {
      console.log('plantigotchi received post request', req.body);

      const moistureReading = new SensorReading(req.body);
      console.log('moistureReading', moistureReading);

      moistureReading.save()
      .then(saved => res.send(saved))

    });
    app.use(router);
  }