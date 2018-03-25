'use strict';

module.exports = function(Plant) {
    Plant.validatesInclusionOf('type', {in: ['dry', 'medium', 'wet']});
};
