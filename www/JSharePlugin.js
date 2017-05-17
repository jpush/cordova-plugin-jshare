var exec = require('cordova/exec')
var PLUGIN_NAME = 'JSharePlugin'

var JShare = {
  init: function(cb) {
    exec(cb, null, PLUGIN_NAME, 'init', [])
  },
  setDebugModel: function(enable, cb) {
    exec(cb, null, PLUGIN_NAME, 'setDebugModel', [enable])
  },
  getPlatformList: function(cb) {
    exec(cb, null, PLUGIN_NAME, 'getPlatformList', [])
  },
  isClientValid: function(platform, cb) {
    exec(cb, null, PLUGIN_NAME, 'isClientValid', [platform])
  },
  share: function(platform, shareParams, cb) {
    exec(cb, null, PLUGIN_NAME, 'share', [platform, shareParams])
  }
}

var Platform = {
  WeChat: "Wechat.Name",
  WeChatMoments: "WechatMoments.Name",
  WeChatFavorite: "WechatFavorite.Name",
  SinaWeibo: "SinaWeibo.Name",
  QQ: "QQ.Name",
  QZone: "QZone.Name"
}

var ShareParams = {
  shareType: null,
  text: null,
  imagePath: null,
  title: null,
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
