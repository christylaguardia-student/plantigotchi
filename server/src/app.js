// require('dotenv').config();
const express = require('express');
const router = express.Router();
const morgan = require('morgan');
const bodyParser = require('body-parser');
const errorHandler = require('./error-handler');
const app = express();

app.use(morgan('dev'));
app.use(bodyParser.json());
app.use(express.static('../public'));

const images = require('./routes/images');

app.use('/api', images);

module.exports = app;
