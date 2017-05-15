var exec = require('cordova/exec')

var JShare = function () {}

function isAndroid () {
  if (device.platform === 'Android') {
    return true
  }
  return false
}

if (!window.plugins) {
  window.plugins = {}
}

if (!window.plugins.jshare) {
  window.plugins.jshare = new JShare()
}

module.exports = new JShare()
