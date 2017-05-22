/*
 *	| |    | |  \ \  / /  | |    | |   / _______|
 *	| |____| |   \ \/ /   | |____| |  / /
 *	| |____| |    \  /    | |____| |  | |   _____
 * 	| |    | |    /  \    | |    | |  | |  |____ |
 *  | |    | |   / /\ \   | |    | |  \ \______| |
 *  | |    | |  /_/  \_\  | |    | |   \_________|
 *
 * Copyright (c) 2011 ~ 2017 Shenzhen HXHG. All rights reserved.
 */


#define JSHARE_VERSION_NUMBER 1.0.0

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, JSHAREPlatform) {
    JSHAREPlatformWechatSession = 1,
    JSHAREPlatformWechatTimeLine = 2,
    JSHAREPlatformWechatFavourite = 3,
    
    JSHAREPlatformQQ = 4,
    JSHAREPlatformQzone = 5,
    
    JSHAREPlatformSinaWeibo = 6,
};

typedef NS_ENUM(NSUInteger,JSHAREState){
    JSHAREStateSuccess = 1,
    JSHAREStateFail = 2,
    JSHAREStateCancel = 3,
    JSHAREStateUnknown = 4,
};

typedef NS_ENUM(NSUInteger,JSHAREMediaType){
    JSHAREText = 1,
    JSHAREImage = 2,
    JSHARELink = 3,
    JSHAREAudio = 4,
    JSHAREVideo = 5,
    JSHAREApp = 6,
    JSHAREFile = 7,
    JSHAREEmoticon = 8,
    JSHAREUndefined = 100,
};


typedef void(^JSHAREStateHandler)(JSHAREState state,NSError *error);

@interface JSHARELaunchConfig : NSObject

/**
 appKey 一个 JIGUANG 应用必须的,唯一的标识. 请参考 JIGUANG 相关说明文档来获取这个标识。
 */
@property (nonatomic, copy) NSString *appKey;

/**
 channel 发布渠道. 可选。
 */
@property (nonatomic, copy) NSString *channel;

/**
 advertisingIdentifier 广告标识符（IDFA). 可选，IDFA能帮助您更准确的统计。
 */
@property (nonatomic, copy) NSString *advertisingId;

/**
 isProduction 是否生产环境. 如果为开发状态,设置为NO; 如果为生产状态,应改为 YES.默认为NO。
 */
@property (nonatomic, assign) BOOL isProduction;

/**
 设置微信的应用标识。
 */
@property (nonatomic, copy) NSString *WeChatAppId;

/**
 设置微信的应用密匙。
 */
@property (nonatomic, copy) NSString *WeChatAppSecret;

/**
 设置QQ应用标识。
 */
@property (nonatomic, copy) NSString *QQAppId;

/**
 设置QQ应用Key。
 */
@property (nonatomic, copy) NSString *QQAppKey;

/**
 设置新浪微博应用标识。
 */
@property (nonatomic, copy) NSString *SinaWeiboAppKey;

/**
 设置新浪微博应用密匙。
 */
@property (nonatomic, copy) NSString *SinaWeiboAppSecret;

/**
 设置新浪微博应用回调地址。
 */
@property (nonatomic, copy) NSString *SinaRedirectUri;

@end

@interface JSHAREMessage : NSObject

/**
 标题：长度每个平台的限制而不同。
 微信好友：最大 512 字符。
 微信朋友圈：最大 512 字符。
 微信收藏：最大 512 字符。
 QQ：最大 128 字符。
 QQ空间：最大 128 字符。
 新浪微博：分享链接类型，最大 1 K字符。
 */
@property (nonatomic,strong) NSString *title;

/**
 文本：文本内容，长度每个平台的限制而不同。
 在分享非文本类型时，此字段作为分享内容的描述使用。
 
 微信好友：分享文本类型时，最大 10 K字符。分享非文本类型，最大 1 K字符。
 微信朋友圈：分享文本类型时，最大 10 K字符。分享非文本类型，最大 1 K字符。
 微信收藏：分享文本类型时，最大 10 K字符。分享非文本类型，最大 1 K字符。
 QQ：分享文本类型时，最大 1536 字符。分享非文本类型，最大 512 字符。
 QQ空间：分享文本类型时，最大 128 字符。分享非文本类型，最大 512 字符。
 新浪微博：最大 140 汉字。
 
 */
@property (nonatomic,strong) NSString *text;

/**
 链接：根据媒体类型填入链接，长度每个平台的限制不同。分享非文本及非图片类型时，必要！
 微信好友：最大 10 K字符。
 微信朋友圈：最大 10 K字符。
 微信收藏：最大 10 K字符。
 QQ：最大 512 字符。
 QQ空间：最大 512 字符。
 新浪微博：最大 512 字符。
 
 */
@property (nonatomic,strong) NSString *url;


/**
 本地视频AssetURL:分享本地视频到 QQ 空间的必填参数，可传ALAsset的ALAssetPropertyAssetURL，或者PHAsset的localIdentifier。
 */
@property (nonatomic,strong) NSString *videoAssetURL;

/**
 缩略图：大小限制根据平台不同而不同。
 微信好友：最大 32 K。
 微信朋友圈：最大 32 K。
 微信收藏：最大 32 K。
 QQ：最大 1 M。
 QQ空间：最大 1 M。
 新浪微博：最大 32 K。
 */
@property (nonatomic,strong) NSData *thumbnail;

/**
 图片：分享JSHAREImage类型，大小限制根据平台不同而不同，当分享JSHARELink类型时没有提供缩略图时，若此参数不为空，JSHARE将会裁剪此参数提供的图片去适配缩略图。
 微信好友：最大 10 M。
 微信朋友圈：最大 10 M。
 微信收藏：最大 10 M。
 QQ：最大 5 M。
 QQ空间：最大 5 M。
 新浪微博：最大 10 M。

 */
@property (nonatomic,strong) NSData *image;

/**
 图片数组：分享到 QQ 空间支持多张图片，图片数组的元素需要为 NSData 类型，图片数量限制为20张。若只分享单张图片至 QQ 空间使用 image 字段即可。
 */
@property (nonatomic,strong) NSArray *images;

/**
 分享的媒体类型。必要！
 */
@property (nonatomic,assign) JSHAREMediaType mediaType;

/**
 分享的目标平台。必要！
 */
@property (nonatomic,assign) JSHAREPlatform platform;

/**
 分享JSHAREAudio类型至微信平台或QQ平台时，音乐数据url地址。
 微信好友：最大 10 K字符。
 微信朋友圈：最大 10 K字符。
 微信收藏：最大 10 K字符。
 QQ：最大 512 字符。
 QQ空间：最大 512 字符。
 新浪微博：最大 512 字符。
 */
@property (nonatomic,strong) NSString *mediaDataUrl;

/**
 分享JSHAREApp类型至微信平台时，第三方程序自定义的简单数据。
 */
@property (nonatomic,strong) NSString *extInfo;

/**
 分享JSHAREFile类型或者JSHAREApp类型至微信平台时，对应的File数据以及App数据，最大 10 M。
 */
@property (nonatomic,strong) NSData *fileData;

/**
 分享JSHAREFile类型至微信平台时，对应的文件后缀名，分享文件必填，否则会导致分享到微信平台出现不一致的文件类型,最大 64 字符。
 */
@property (nonatomic,strong) NSString *fileExt;

/**
 分享JSHAREEmoticon类型至微信平台时，对应的表情数据，最大 10 M。
 */
@property (nonatomic,strong) NSData *emoticonData;

/**
 分享至新浪微博平台时，分享参数的一个标识符，默认为 “objectId”。最大 255 字符。
 */
@property (nonatomic,strong) NSString *sinaObjectID;

/**
 返回一个 JShareMessage 实例
 
 @return 返回一个 JShareMessage 实例
 */
+ (JSHAREMessage *)message;
@end


@interface JSHAREService : NSObject

/**
 启动SDK,必要!
 
 @param config SDK启动参数模型，不可为nil。
 */
+ (void)setupWithConfig:(JSHARELaunchConfig *)config;


/**
 处理平台回调,必要！
 
 @param url 回调的url，在 Appdelegate 的 application:handleOpenURL: 中调用。不调用此接口 JSHARE 将无法提供分享回调。
 @return 处理结果 YES为处理成功，NO为不处理。
 */
+ (BOOL)handleOpenUrl:(NSURL *)url;

/**
 分享
 
 @param message  分享参数
 @param handler  分享之后的回调
 */
+ (void)share:(JSHAREMessage *)message
      handler:(JSHAREStateHandler)handler;


/**
 检查是否安装微信客户端
 
 @return 返回结果
 */
+ (BOOL)isWeChatInstalled;

/**
 检查是否存在QQ客户端
 
 @return 返回结果
 */
+ (BOOL)isQQInstalled;


/**
 检查是否存在新浪微博客户端
 
 @return 返回结果
 */
+ (BOOL)isSinaWeiBoInstalled;


/**
 @abstract 设置是否打印sdk产生的Debug级log信息, 默认为NO(不打印log)
 
 SDK 默认开启的日志级别为: Info. 只显示必要的信息, 不打印调试日志.
 
 请在SDK启动后调用本接口，调用本接口可打开日志级别为: Debug, 打印调试日志.
 请在发布产品时改为NO，避免产生不必要的IO
 
 此接口必须在"setupWithConfig:"之后调用才会生效.
 @param enable 是否打印
 */
+ (void)setDebug:(BOOL)enable;

@end
