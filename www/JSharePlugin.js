var exec = require('cordova/exec')
var PLUGIN_NAME = 'JSharePlugin'

var JShare = {
  init: function (cb) {
    exec(cb, null, PLUGIN_NAME, 'init', [])
  },
  setDebugMode: function (enable, cb) {
    exec(cb, null, PLUGIN_NAME, 'setDebugMode', [enable])
  },
  getPlatformList: function (cb) {
    exec(cb, null, PLUGIN_NAME, 'getPlatformList', [])
  },
  isPlatformValid: function (platform, cb) {
    exec(cb, null, PLUGIN_NAME, 'isPlatformValid', [platform])
  },
  share: function (platform, shareParams, cb) {
    var shareParamsJson = JSON.stringify(shareParams)
    exec(cb, null, PLUGIN_NAME, 'share', [platform, shareParamsJson])
  }
}

var Platform = {
  WeChat: 'WeChat',
  WeChatMoments: 'WeChatMoments',
  WeChatFavorite: 'WeChatFavorite',
  SinaWeibo: 'SinaWeibo',
  QQ: 'QQ',
  QZone: 'QZone'
}

var ShareParams = {
  shareType: null,
  text: null,
  title: null,
  imagePath: null,
  musicUrl: null,
  url: null,
  filePath: null
}

var ShareType = {
  SHARE_TEXT: 1,
  SHARE_IMAGE: 2,
  SHARE_WEBPAGE: 3,
  SHARE_MUSIC: 4,
  SHARE_VIDEO: 5,
  SHARE_APPS: 6,
  SHARE_FILE: 7,
  SHARE_EMOJI: 8
}

module.exports = new JShare()
