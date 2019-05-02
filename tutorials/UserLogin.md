# User Login

To receive events or start $KANDY$ services, user login should be completed successfully. Events are received to $KANDY$ Mobile SDK by websocket or push channel. Each time the application wakes up, user login must connect websocket.

A connection can be established with different methods. How to use each method is explained and shown below. Channel lifetime is specified with the `lifetime` value. $KANDY$ Mobile SDK extends the lifetime automatically, however that doesn't guarantee connection will last indefinitely. Note that, server related configurations should be set before calling `connect`.

When a connection is established, $KANDY$ Mobile SDK uses the given Authentication Token to communicate with services. If the `Authentication Token` is invalidated or expired, service requests will fail. In these cases, `Authentication Token` should be renewed with the valid one.

## Configurations

The first step for any application that will use the $KANDY$ Mobile SDK is setting the configurations. When doing this, you can customize certain features by providing a configurations object. All feature configurations can be set with instance of the `CPConfig` class. Developers should set server related configurations before using any functionality of the SDK and all other customizations are optional.

*Swift Code:*
```swift
import CPaaSSDK

let configuration = CPConfig.sharedInstance()
configuration.restServerUrl = "cpaasapi.example.com"
configuration.useSecureConnection = true
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

CPConfig *configuration = [CPConfig sharedInstance];
configuration.restServerUrl = @"cpaasapi.example.com";
configuration.useSecureConnection = YES;
```

### Example Configurations

#### Call

The Call configs are used to initialize call/network settings and to set the starting behavior of a call.

*Swift Code:*
```swift
import CPaaSSDK

let configuration = CPConfig.sharedInstance()
configuration.earlyMediaEnabled = false
configuration.auditFrequency = 30
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

CPConfig *configuration = [CPConfig sharedInstance];
[configuration setEarlyMediaEnabled:NO];
[configuration setAuditFrequence:30];
```

#### WebRTC

The WebRTC configs are used to customize the advanced behavior of the SDK, like providing ICE Servers and corresponding options, setting a custom set of video and audio codecs, enabling or disabling encryption options of the WebRTC etc.

*Swift Code:*
```swift
import CPaaSSDK

let configuration = CPConfig.sharedInstance()
configuration.dtlsEnabled = true
configuration.iceOption = ICE_TRICKLE
configuration.iceCollectionTimeout = 1

// Setting custom ICE Servers
let iceServers: CPICEServers = CPICEServers()
iceServers.addICEServer("turns:turn-example.com:443?transport=tcp")
iceServers.addICEServer("turn:turn-example.com:3535?transport=udp")
configuration.iceServers = iceServers

// Setting specific codecs, by default all codecs are in use
let audioCodecSet = [NSNumber(value: AC_G722.rawValue), NSNumber(value: AC_OPUS.rawValue)]
let videoCodecSet = [NSNumber(value: VC_H264.rawValue), NSNumber(value: VC_VP9.rawValue)]
let codecSet = CPCodecSet.codecSet(withAudioCodecs: audioCodecSet, videoCodecs: videoCodecSet)
configuration.preferredCodecSet = codecSet
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

CPConfig *configuration = [CPConfig sharedInstance];
[configuration setDtlsEnabled:YES];
[configuration setIceOption:ICE_TRICKLE];
[configuration setICECollectionTimeout:1];

// Setting custom ICE Servers
CPICEServers *iceServers = [[CPICEServers alloc] init];
[iceServers addICEServer:@"turns:turn-example.com:443?transport=tcp"];
[iceServers addICEServer:@"turn:turn-example.com:3535?transport=udp"];
[configuration setICEServers:iceServers];

// Setting specific codecs, by default all codecs are in use
NSArray *audioCodecSet = @{@(AC_G722),@(AC_OPUS)};
NSArray *videoCodecSet = @{@(VC_H264),@(VC_VP9)};
CPCodecSet *set = [CPCodecSet codecSetWithAudioCodecs:audioCodecSet videoCodecs:videoCodecSet];
[configuration setPreferredCodecSet:set];
```

#### Capturing Logs and Troubleshooting Problems

The log level configs are used to change the severity of logging output from $KANDY$ Mobile SDK. This allows for more logged messages, such as debug information, warnings, and errors, which can help to explain what SDK is doing.

$KANDY$ Mobile SDK also provides application developers to set their customized logger implementation into Mobile SDK.

*Swift Code:*
```swift
import CPaaSSDK

let configuration = CPConfig.sharedInstance()
// Set the log level to 'TRACE_WEBRTC' to output more detailed logs. Default is 'TRACE'.
configuration.logManager.logLevel = TRACE_WEBRTC
configuration.logManager.delegate = self
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

CPConfig *configuration = [CPConfig sharedInstance];
// Set the log level to 'TRACE_WEBRTC' to output more detailed logs. Default is 'TRACE'.
[configuration.logManager setLogLevel:TRACE_WEBRTC];
[configuration.logManager setDelegate:self];
```

## connect(idToken: String, lifetime: Int, completion: ConnectionBlock)

Establishes a connection for the user with given ID Token, which will last until the time given with lifetime is elapsed.

Authentication needs access token in order to get and establish Websocket subscription. So before using this method, access token should be given to the Authentication with calling setToken method.

*Swift Code:*
```swift
import CPaaSSDK

cpaas.authentication.setToken("<ACCESS-TOKEN>")
cpaas.authentication.connect(idToken: "<ID-TOKEN>", lifetime: 3600) {
(error, channelInfo) in
    if let error = error {
        print(error.localizedDescription)
        return
    }
    print(“Connected successfully”)
    print(“ChannelInfo: \(channelInfo)”)
}
```
*Objective-C Code:*
```Objective-C
@import CPaaSSDK;

[cpaas.authentication setToken: @"<ACCESS-TOKEN>"];
[cpaas.authentication connectWithIdToken:@"<ID-TOKEN>" lifetime:3600 completion:^(CPError * _Nullable error, NSString * _Nullable channelInfo) {
    if (error) {
        NSLog(error.localizedDescription);
        return;
    }
    NSLog(“Connected successfully”);
    NSLog(“ChannelInfo: %@", channelInfo);
}
```

## connect(idToken: String, accessToken: String, lifetime: Int, completion: ConnectionBlock)

Establishes a connection for the user with given ID Token, which will last until the time given with lifetime is elapsed, using given accessToken. Access Token will be set internally and then connection will be established just like the connect method in (a).

*Swift Code:*
```swift
import CPaaSSDK

cpaas.authentication.connect(idToken: "<ID-TOKEN>", accessToken: "<ACCESS-TOKEN>", lifetime: 3600) {
(error, channelInfo) in
    if let error = error {
        print(error.localizedDescription)
        return
    }
    print(“Connected successfully”)
    print(“ChannelInfo: \(channelInfo)”)
}
```
*Objective-C Code:*
```Objective-C
@import CPaaSSDK;

[cpaas.authentication connectWithIdToken:@"<ID-TOKEN>" accessToken: @"<ACCESS-TOKEN>" lifetime:3600 completion:^(CPError * _Nullable error, NSString * _Nullable channelInfo) {
    if (error) {
        NSLog(error.localizedDescription);
        return;
    }
    NSLog(“Connected successfully”);
    NSLog(“ChannelInfo: %@", channelInfo);
}
```

## connect(idToken: String, lifetime: Int, channelInfo: String, completion: ConnectionBlock)

Channel-info consists of information about lifetime and channel URL of the Websocket channel. Instead of getting new channel URL, this method can be called if channel-info is known in order to connect specified channel URL. If lifetime information doesn't expired in the channel-info, Authentication uses lifetime and channel URL information in the channel-info in order to connect and returns new channel-info in the ConnectionBlock. If lifetime is expired, then a new connection is established by given ID Token.

*Swift Code:*
```swift
import CPaaSSDK

cpaas.authentication.setToken("<ACCESS-TOKEN>")
cpaas.authentication.connect(username: "<ID-TOKEN>", lifetime: 3600, channelInfo: "<CHANNEL-INFO>") {
(error, channelInfo) in
    if let error = error {
        print(error.localizedDescription)
        return
    }
    print(“Connected successfully”)
    print(“ChannelInfo: \(channelInfo)”)
}
```
*Objective-C Code:*
```Objective-C
@import CPaaSSDK;

[cpaas.authentication setToken: @"<ACCESS-TOKEN>"];
[cpaas.authentication connectWithIdToken:@"<ID-TOKEN>" lifetime:3600 channelInfo: @"<CHANNEL-INFO>" completion:^(CPError * _Nullable error, NSString * _Nullable channelInfo) {
    if (error) {
        NSLog(error.localizedDescription);
        return;
    }
    NSLog(“Connected successfully”);
    NSLog(“ChannelInfo: %@", channelInfo);
}
```

## connect(idToken: String, accessToken: String, lifetime: Int, channelInfo: String, completion: ConnectionBlock)

Similar to the previous method, access token can be also given within the same method. Method will set the access token internally.

*Swift Code:*
```swift
import CPaaSSDK

cpaas.authentication.connect(idToken: "<ID-TOKEN>", accessToken: "<ACCESS-TOKEN>", lifetime: 3600, channelInfo: "<CHANNEL-INFO>") {
(error, channelInfo) in
    if let error = error {
        print(error.localizedDescription)
        return
    }
    print(“Connected successfully”)
    print(“ChannelInfo: \(channelInfo)”)
}
```
*Objective-C Code:*
```Objective-C
@import CPaaSSDK;

[cpaas.authentication connectWithIdToken:@"<ID-TOKEN>" accessToken:@"<ACCESS-TOKEN>" lifetime:3600 channelInfo: @"<CHANNEL-INFO>" completion:^(CPError * _Nullable error, NSString * _Nullable channelInfo) {
    if (error) {
        NSLog(error.localizedDescription);
        return;
    }
    NSLog(“Connected successfully”);
    NSLog(“ChannelInfo: %@", channelInfo);
}
```
