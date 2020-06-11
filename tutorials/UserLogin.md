# User Login

To receive events or start $KANDY$ services, user login should be completed successfully. Events are received to $KANDY$ Mobile SDK by websocket or push channel. Each time the application wakes up, user login must connect websocket.

A connection can be established with different methods. How to use each method is explained and shown below. Channel lifetime is specified with the `lifetime` value. $KANDY$ Mobile SDK extends the lifetime automatically, however that doesn't guarantee connection will last indefinitely. Note that, server related configurations should be set before calling `connect`.

When a connection is established, $KANDY$ Mobile SDK uses the given Authentication Token to communicate with services. If the `Authentication Token` is invalidated or expired, service requests will fail. In these cases, `Authentication Token` should be renewed with the valid one.

## Configurations

The first step for any application that will use the $KANDY$ Mobile SDK is setting the configurations. When doing this, you can customize certain features by providing a configurations object. All feature configurations can be set with instance of the `CPConfig` class. Developers should set server related configurations before using any functionality of the SDK and all other customizations are optional.Note that,config should be set before creating a service provider.


## Base URL

This is the API Marketplace HTTPS entry point that you will use for authentication, REST services and WebSocket notifications.

```
$KANDYFQDN$
```

## ICE Servers

Use these primary and secondary URIs as the ICE Servers in the JavaScript, iOS or Android SDKs configuration when connecting and making calls. This is needed in order to ensure that calls can be established even the call peers are on different networks, behind firewalls. When the ICE server connects, it will try the Primary URL first. If that fails, it will try the Secondary URL.

#### Primary URL:

```
$KANDYTURN1$

$KANDYSTUN1$
```

#### Secondary URL:

```
$KANDYTURN2$

$KANDYSTUN2$
```

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

let configuration = CPConfig.sharedInstance()
configuration.restServerUrl = "$KANDYFQDN$"
configuration.useSecureConnection = true

// Setting ICE Servers
let iceServers: CPICEServers = CPICEServers()
iceServers.addICEServer("$KANDYTURN1$")
iceServers.addICEServer("$KANDYTURN2$")
iceServers.addICEServer("$KANDYSTUN1$")
iceServers.addICEServer("$KANDYSTUN2$")
configuration.iceServers = iceServers
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

CPConfig *configuration = [CPConfig sharedInstance];
configuration.restServerUrl = @"$KANDYFQDN$";
configuration.useSecureConnection = YES;

// Setting ICE Servers
CPICEServers *iceServers = [[CPICEServers alloc] init];
[iceServers addICEServer:@"$KANDYTURN1$"];
[iceServers addICEServer:@"$KANDYTURN2$"];
[iceServers addICEServer:@"$KANDYSTUN1$"];
[iceServers addICEServer:@"$KANDYSTUN2$"];
[configuration setICEServers:iceServers];
```
<!-- tabs:end -->

#### Capturing Logs and Troubleshooting Problems

The log level configs are used to change the severity of logging output from $KANDY$ Mobile SDK. This allows for more logged messages, such as debug information, warnings, and errors, which can help to explain what SDK is doing.

$KANDY$ Mobile SDK also provides application developers to set their customized logger implementation into Mobile SDK.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

let configuration = CPConfig.sharedInstance()
// Set the log level to 'TRACE_WEBRTC' to output more detailed logs. Default is 'TRACE'.
configuration.logManager.logLevel = TRACE_WEBRTC
configuration.logManager.delegate = self
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

CPConfig *configuration = [CPConfig sharedInstance];
// Set the log level to 'TRACE_WEBRTC' to output more detailed logs. Default is 'TRACE'.
[configuration.logManager setLogLevel:TRACE_WEBRTC];
[configuration.logManager setDelegate:self];
```
<!-- tabs:end -->

## connect(idToken: String, lifetime: Int, completion: ConnectionBlock)

Establishes a connection for the user with given ID Token, which will last until the time given with lifetime is elapsed.

Authentication needs access token in order to get and establish Websocket subscription. So before using this method, access token should be given to the Authentication with calling setToken method.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

var cpaas: CPaaS!

//Initialization of the CPaaS instance
cpaas = CPaaS(services:[CPServiceInfo(type: .sms, push: true), CPServiceInfo(type: .chat, push: true),CPServiceInfo(type: .call, push: true), CPServiceInfo(type: .presence, push: false), CPServiceInfo(type: .addressbook, push: false)])
    

cpaas.authenticationService.setToken("<YOUR_ACCESS_TOKEN>")
cpaas.authenticationService.connect(idToken: "<YOUR_ID_TOKEN>", lifetime: 3600) {
(error, channelInfo) in
    if let error = error {
        print(error.localizedDescription)
        return
    }
    print(“Connected successfully”)
    print(“ChannelInfo: \(channelInfo)”)
}
```
#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

//Initialization of the CPaaS instance
NSArray* cpaasServices= @[[CPServiceInfo buildWithType:ServiceTypeSms push:YES],
                              [CPServiceInfo buildWithType:ServiceTypeChat push:YES],
                              [CPServiceInfo buildWithType:ServiceTypeCall push:YES],
                              [CPServiceInfo buildWithType:ServiceTypePresence push:YES],
                              [CPServiceInfo buildWithType:ServiceTypeAddressbook push:NO]];
cpaas = [[CPaaS alloc] initWithServices:cpaasServices];

[cpaas.authenticationService setToken: @"<YOUR_ACCESS_TOKEN>"];
[cpaas.authenticationService connectWithIdToken:@"<YOUR_ID_TOKEN>" lifetime:3600 completion:^(CPError * _Nullable error, NSString * _Nullable channelInfo) {
    if (error) {
        NSLog(error.localizedDescription);
        return;
    }
    NSLog(“Connected successfully”);
    NSLog(“ChannelInfo: %@", channelInfo);
}
```
<!-- tabs:end -->

## connect(idToken: String, accessToken: String, lifetime: Int, completion: ConnectionBlock)

Establishes a connection for the user with given ID Token, which will last until the time given with lifetime is elapsed, using given accessToken. Access Token will be set internally and then connection will be established just like the connect method in (a).

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

cpaas.authenticationService.connect(idToken: "<YOUR_ID_TOKEN>", accessToken: "<YOUR_ACCESS_TOKEN>", lifetime: 3600) {
(error, channelInfo) in
    if let error = error {
        print(error.localizedDescription)
        return
    }
    print(“Connected successfully”)
    print(“ChannelInfo: \(channelInfo)”)
}
```
#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

[cpaas.authenticationService connectWithIdToken:@"<YOUR_ID_TOKEN>" accessToken: @"<YOUR_ACCESS_TOKEN>" lifetime:3600 completion:^(CPError * _Nullable error, NSString * _Nullable channelInfo) {
    if (error) {
        NSLog(error.localizedDescription);
        return;
    }
    NSLog(“Connected successfully”);
    NSLog(“ChannelInfo: %@", channelInfo);
}
```
<!-- tabs:end -->

## connect(idToken: String, lifetime: Int, channelInfo: String, completion: ConnectionBlock)

Channel-info consists of information about lifetime and channel URL of the Websocket channel. Instead of getting new channel URL, this method can be called if channel-info is known in order to connect specified channel URL. If lifetime information doesn't expired in the channel-info, Authentication uses lifetime and channel URL information in the channel-info in order to connect and returns new channel-info in the ConnectionBlock. If lifetime is expired, then a new connection is established by given ID Token.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

cpaas.authenticationService.setToken("<YOUR_ACCESS_TOKEN>")
cpaas.authenticationService.connect(username: "<YOUR_ID_TOKEN>", lifetime: 3600, channelInfo: "<CHANNEL-INFO>") {
(error, channelInfo) in
    if let error = error {
        print(error.localizedDescription)
        return
    }
    print(“Connected successfully”)
    print(“ChannelInfo: \(channelInfo)”)
}
```
#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

[cpaas.authenticationService setToken: @"<YOUR_ACCESS_TOKEN>"];
[cpaas.authenticationService connectWithIdToken:@"<YOUR_ID_TOKEN>" lifetime:3600 channelInfo: @"<CHANNEL-INFO>" completion:^(CPError * _Nullable error, NSString * _Nullable channelInfo) {
    if (error) {
        NSLog(error.localizedDescription);
        return;
    }
    NSLog(“Connected successfully”);
    NSLog(“ChannelInfo: %@", channelInfo);
}
```
<!-- tabs:end -->

## connect(idToken: String, accessToken: String, lifetime: Int, channelInfo: String, completion: ConnectionBlock)

Similar to the previous method, access token can be also given within the same method. Method will set the access token internally.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

cpaas.authenticationService.connect(idToken: "<YOUR_ID_TOKEN>", accessToken: "<YOUR_ACCESS_TOKEN>", lifetime: 3600, channelInfo: "<CHANNEL-INFO>") {
(error, channelInfo) in
    if let error = error {
        print(error.localizedDescription)
        return
    }
    print(“Connected successfully”)
    print(“ChannelInfo: \(channelInfo)”)
}
```
#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

[cpaas.authenticationService connectWithIdToken:@"<YOUR_ID_TOKEN>" accessToken:@"<YOUR_ACCESS_TOKEN>" lifetime:3600 channelInfo: @"<CHANNEL-INFO>" completion:^(CPError * _Nullable error, NSString * _Nullable channelInfo) {
    if (error) {
        NSLog(error.localizedDescription);
        return;
    }
    NSLog(“Connected successfully”);
    NSLog(“ChannelInfo: %@", channelInfo);
}
```
<!-- tabs:end -->
