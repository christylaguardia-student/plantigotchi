// eslint-disable-next-line no-console
function getErrorHandler(log = console.log) {

  // eslint-disable-next-line no-unused-vars
  return function errorHandler(err, req, res, next) {
      let code, error;

      if (err.name === 'ValidationError') {
          code = 400;
          error = Object.values(err.errors).map(v => v.message);
      } else if (err.code) {
          code = err.code;
          error = err.error;
      } else {
          code = 500;
          error = 'Internal Server Error';

      }
      log(err);
      res.status(code).send({ error });
  };
}

module.exports = getErrorHandler;
