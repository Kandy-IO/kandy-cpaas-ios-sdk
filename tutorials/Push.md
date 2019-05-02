# Push Notifications

When $KANDY$ cannot reach to the device using websocket channel, message will be sent through APNS if implemented. Using the mobile push mechanism, communication between $KANDY$ and the device can be maintained even while the application is not awake or in the case of websocket connection failure. In order to register device to the push channel and pass the message to the $KANDY$ Mobile SDK, see  [**Registering Device**](#registering-device) and [**Receiving Push Notification**](#receiving-push-notification) sections.

## Registering Application For Push Services

Application should be registered with its bundle ID first to be able to receive push notifications from $KANDY$. Necessary information for registration step for iOS applications are listed below, please contact with system administrator and share them when needed.

* Application Bundle ID
* APNS Key in `p8` format. (Can be found in Apple Developer Account Page - Certificates, Identifiers & Profiles)
* Team ID (Can be found in Apple Developer Account Page - Membership)

Please refer to [Notification Channels](/developer/quickstarts/rest-api/get-started#notification-channels) section to learn more about how to register for push services.

## Registering Device

In order to receive push notifications, **PushKit** framework should be implemented correctly. For details about **PushKit**, please visit https://developer.apple.com/documentation/pushkit

Open the `AppDelegate` file of the project and add `import PushKit`. Then, add the code below to the `application(:didFinishLaunchingWithOptions:)`. Note that AppDelegate should conform `PKPushRegistryDelegate` protocol.

*Swift Code:*
```swift
class AppDelegate: UIResponder, UIApplicationDelegate, PKPushRegistryDelegate {

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {

        // Other implementations...
        var pushRegistry = PKPushRegistry(queue: DispatchQueue.main)
        pushRegistry.delegate = self
        pushRegistry.desiredPushTypes = [PKPushType.voIP]

        return true
    }

...
```

*Objective-C Code:*
```objective-c
@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Other implementations...
    PKPushRegistry *registry = [[PKPushRegistry alloc] initWithQueue:dispatch_get_main_queue()];
    [registry setDelegate:self];
    [registry setDesiredPushTypes:[NSSet setWithObject:PKPushTypeVoIP]];

    return YES;
}

...
```

Desired push type is set as VoIP, which is considered high-priority notifications and is delivered without delay, recommended for VoIP applications. When device is registered to the APNS, `PKPushRegistryDelegate` will inform through its delegate and gives push token which later will be used by $KANDY$ to send notifications. This token should be sent to $KANDY$, later on when $KANDY$ subscribes to services, user will also subscribe to push channels of the services. However, device token must be aligned correctly. Different implementations than shown below, do not guarentee successful registration.

Add new `String` property  with name `deviceToken` in the `AppDelegate`, to make reachable device token on other classes when needed. Next, implement methods of the `PKPushRegistryDelegate` protocol as described in below.

*Swift Code:*
```swift
import CPaaSSDK

func pushRegistry(_ registry: PKPushRegistry, didUpdate pushCredentials: PKPushCredentials, for type: PKPushType) {
    // Get Device token
    let token = pushCredentials.token.reduce("", {$0 + String(format: "%02X", $1)})
    print("voip token: \(token)")

    // If device token is different than the previous one, change it with the new one.
    if CPConfig.sharedInstance().deviceToken == nil || CPConfig.sharedInstance().deviceToken != token {

        // Save device token to Configuration.
        CPConfig.sharedInstance().deviceToken = token

        // cpaas is the CPaaS instance of the app. Subscribe to Push Service using device token.
        // This operation can be done in another place, for example if cpaas instance not yet configured or initialized.
        cpaas.pushService.subscribe(completion: { (error, result) in
            if let error = error {
                print("Couldn't subscribe for push - Error: \(error.localizedDescription)")
                return
            }

            print("Services are subscribed to push successfuly")
        })
    }
}


@available(iOS, introduced: 10, deprecated: 11)
func pushRegistry(_ registry: PKPushRegistry, didReceiveIncomingPushWith payload: PKPushPayload, for type: PKPushType) {
    // Will be implemented in next sections.
}

@available(iOS 11, *)
func pushRegistry(_ registry: PKPushRegistry, didReceiveIncomingPushWith payload: PKPushPayload, for type: PKPushType, completion: @escaping () -> Void) {
    // Will be implemented in next sections.
}

func pushRegistry(_ registry: PKPushRegistry, didInvalidatePushTokenFor type: PKPushType) {
    print("Device token is invalidated")
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

- (void)pushRegistry:(nonnull PKPushRegistry *)registry didUpdatePushCredentials:(nonnull PKPushCredentials *)pushCredentials forType:(nonnull PKPushType)type {
    // Get Device token
    NSString *token = [pushCredentials.token.description stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"<>"]];
    token = [token stringByReplacingOccurrencesOfString:@" " withString:@""];

    // If device token is different than the previous one, change it with the new one.
    if ([CPConfig sharedInstance].deviceToken == nil || [CPConfig sharedInstance].deviceToken != token) {

        // Save device token to Configuration.
        [CPConfig sharedInstance].deviceToken = token;

        // cpaas is the CPaaS instance of the app. Subscribe to Push Service using device token.
        // This operation can be done in another place, for example if cpaas instance not yet configured or initialized.
        [cpaasHandler.CPaaS.pushService subscribeWithCompletion:^(CPError * _Nullable error, NSString * _Nullable result) {
            if (error) {
                NSLog(@"Couldn't subscribe for push - Error: %@", error.localizedDescription);
                return;
            }

            NSLog(@"Services are subscribed to push successfuly");
        }];
    }
}

#if __IPHONE_OS_VERSION_MIN_REQUIRED >= 11000
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type withCompletionHandler:(void (^)(void))completion {
    // Will be implemented in next sections.
}
#else
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type {
    // Will be implemented in next sections.
}
#endif

-(void)pushRegistry:(PKPushRegistry *)registry didInvalidatePushTokenForType:(PKPushType)type {
    NSLog("Device token is invalidated");
}
```

## Receiving Push Notification

If push registration is completed successfully and subscribed to push channels with the correct device push token, device now should receive push notifications.

When device receives push notification, `PKPushRegistryDelegate` informs its delegate via `pushRegistry(:didReceiveIncomingPushWith:for:)` which is available for  iOS10 devices, and `pushRegistry(:didReceiveIncomingPushWith:for:completion:)` for iOS11 and later devices. Because very similar implementation will be done for both methods, creating new method and executing operations inside on that method is recommended.

*Swift Code:*
```swift
import CPaaSSDK

@available(iOS, introduced: 10, deprecated: 11)
func pushRegistry(_ registry: PKPushRegistry, didReceiveIncomingPushWith payload: PKPushPayload, for type: PKPushType) {
    // Push Notification is received. Inform the SDK.
    self.sendPushMessage(payload: payload, completion: nil)
}

@available(iOS 11, *)
func pushRegistry(_ registry: PKPushRegistry, didReceiveIncomingPushWith payload: PKPushPayload, for type: PKPushType, completion: @escaping () -> Void) {
    // Push Notification is received. Inform the SDK.
    self.sendPushMessage(payload: payload, completion: completion)
}

func sendPushMessage(payload: PKPushPayload, completion: (()->())?) {
    // cpaas is the CPaaS instance of the app.
    // Before these operations, instance should be created and logged in to the user if it is available, and valid access token should be given.
    cpaas.pushService.injectPushMessage(pushMessage: payload.dictionaryPayload){ (error) in
        completion?()
    })
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

#if __IPHONE_OS_VERSION_MIN_REQUIRED >= 11000
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type withCompletionHandler:(void (^)(void))completion {
    // Push Notification is received. Inform the SDK.
    [self sendPushMessageWithPayload:payload completion:completion];
}
#else
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type {
    // Push Notification is received. Inform the SDK.
    [self sendPushMessageWithPayload:payload completion:nil];
}
#endif

- (void)sendPushMessageWithPayload: (PKPushPayload *)payload completion:(void (^)(void))completion {
    // cpaas is the CPaaS instance of the app.
    // Before these operations, instance should be created and logged in to the user if it is available, and valid access token should be given.
    [cpaas.pushService injectPushMessageWithPushMessage:payload.dictionaryPayload completion:^(CPError * _Nullable error) {
        if (completion) completion();
    }];
}
```
