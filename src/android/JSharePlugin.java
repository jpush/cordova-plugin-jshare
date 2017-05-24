package cn.jpush.phonegap.share;


import android.content.Context;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.List;

import cn.jiguang.share.android.api.JShareInterface;
import cn.jiguang.share.android.api.PlatActionListener;
import cn.jiguang.share.android.api.Platform;
import cn.jiguang.share.android.api.ShareParams;
import cn.jiguang.share.qqmodel.QQ;
import cn.jiguang.share.qqmodel.QZone;
import cn.jiguang.share.wechat.Wechat;
import cn.jiguang.share.wechat.WechatFavorite;
import cn.jiguang.share.wechat.WechatMoments;
import cn.jiguang.share.weibo.SinaWeibo;

public class JSharePlugin extends CordovaPlugin {

    private static final String MSG_ERROR = "Parameter error.";

    private Context mContext;

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        mContext = cordova.getActivity().getApplicationContext();
    }

    void init(JSONArray data, CallbackContext callback) {
        JShareInterface.init(mContext);
    }

    void setDebugMode(JSONArray data, CallbackContext callback) {
        try {
            boolean enable = data.getBoolean(0);
            JShareInterface.setDebugModel(enable);
            callback.success();
        } catch (JSONException e) {
            e.printStackTrace();
            callback.error(MSG_ERROR);
        }
    }

    void getPlatformList(JSONArray data, CallbackContext callback) {
        List<String> platformList = JShareInterface.getPlatformList();
        JSONArray jsonArr = new JSONArray();
        for (int i = 0; i < platformList.size(); i++) {
            jsonArr.put(platformList.get(i));
        }
        callback.success(jsonArr);
    }

    void isPlatformValid(JSONArray data, CallbackContext callback) {
        try {
            String platform = data.getString(0);
            boolean isValid = JShareInterface.isClientValid(platform);
            callback.success(String.valueOf(isValid));
        } catch (JSONException e) {
            e.printStackTrace();
            callback.error(MSG_ERROR);
        }
    }

    void share(JSONArray data, final CallbackContext callback) {
        String platform;
        String shareParamsJsonStr;
        JSONObject shareParamsJson;
        try {
            platform = data.getString(0);
            shareParamsJsonStr = data.getString(1);
            shareParamsJson = new JSONObject(shareParamsJsonStr);
        } catch (JSONException e) {
            e.printStackTrace();
            callback.error(MSG_ERROR);
            return;
        }

        try {
            platform = getPlatformName(platform);
        } catch (IllegalArgumentException e) {
            callback.error(e.getMessage());
            return;
        }

        ShareParams shareParams = new ShareParams();
        try {
            shareParams.setShareType(shareParamsJson.getInt("shareType"));
            shareParams.setTitle(shareParamsJson.getString("title"));
            shareParams.setText(shareParamsJson.getString("text"));
            shareParams.setImagePath(shareParamsJson.getString("imagePath"));
            shareParams.setMusicUrl(shareParamsJson.getString("musicUrl"));
            shareParams.setUrl(shareParamsJson.getString("url"));
            shareParams.setFilePath(shareParamsJson.getString("filePath"));
        } catch (JSONException e) {
            e.printStackTrace();
            callback.error("ShareParams error.");
        }

        final JSONObject result = new JSONObject();
        JShareInterface.share(platform, shareParams, new PlatActionListener() {
            @Override
            public void onComplete(Platform platform, int action, HashMap<String, Object> hashMap) {
                try {
                    result.put("result", "success");
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callback.success(result);
            }

            @Override
            public void onError(Platform platform, int action, int errCode, Throwable throwable) {
                callback.error(errCode);
            }

            @Override
            public void onCancel(Platform platform, int action) {
                try {
                    result.put("result", "cancel");
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                callback.success(result);
            }
        });
    }

    private String getPlatformName(String platform) {
        if (platform == null) {
            throw new IllegalArgumentException("Platform error");
        } else if (platform.equals("WeChat")) {
            return Wechat.Name;
        } else if (platform.equals("WeChatMoments")) {
            return WechatMoments.Name;
        } else if (platform.equals("WeChatFavorite")) {
            return WechatFavorite.Name;
        } else if (platform.equals("SinaWeibo")) {
            return SinaWeibo.Name;
        } else if (platform.equals("QQ")) {
            return QQ.Name;
        } else if (platform.equals("QZone")) {
            return QZone.Name;
        } else {
            throw new IllegalArgumentException("Platform error");
        }
    }
}
