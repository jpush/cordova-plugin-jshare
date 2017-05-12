var exec = require('cordova/exec')

var JShare = function () {}



if (!window.plugins) {
  window.plugins = {}
}

if (!window.plugins.jshare) {
  window.plugins.jshare = new JShare()
}

module.exports = new JShare()
