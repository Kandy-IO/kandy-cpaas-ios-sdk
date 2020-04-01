# Push Notifications

When $KANDY$ cannot reach to the device using websocket channel, message will be sent through APNS if implemented. Using the mobile push mechanism, communication between $KANDY$  and the device can be maintained even while the application is not awake or in the case of websocket connection failure. In order to register device to the push channel and pass the message to the $KANDY$ Mobile SDK, see [**Registering Device for Push Notifications**](#registering-device-for-push-notifications) and [**Receiving Push Notifications**](#receiving-push-notifications) sections.

Starting April 30, 2020, all iPhone apps submitted to the App Store must be built with the iOS 13 SDK or later. This restricts how VoIP Push can be used. Therefore $KANDY$ Mobile SDK iOS support both VoIP([PushKit](https://developer.apple.com/documentation/pushkit)) and Standard([UserNotifications](https://developer.apple.com/documentation/usernotifications)) Push in order to support Call, SMS, Chat Message, and Gone notifications. `PushKit` notifications can wake up or launch your app and wait for app to inform `CallKit` about incoming call, which provides VoIP app developers to present incoming VoIP calls like native GSM/CDMA incoming call. With iOS 13 SDK built app it is mandatory to inform `CallKit` when app receives a VoIP push. Failure to do so, iOS 13 will kill the app and after a couple of failures iOS 13 will block the app from receiving any further VoIP push notifications which means incoming calls will be blocked but outgoing calls can still be made while application is open.

For more information and restrictions about using VoIP notifications, please refer [Responding to VoIP notifications](https://developer.apple.com/documentation/pushkit/responding_to_voip_notifications_from_pushkit).

## Registering Application For Push Services

Application should be registered with its bundle ID first to be able to receive push notifications from $KANDY$. Necessary information for registration step for iOS applications are listed below, please contact with system administrator and share them when needed.

-   Application Bundle ID
-   APNS "Auth Key" in `p8` format. (Can be found in Apple Developer Account Page - Certificates, Identifiers & Profiles)
-   Key ID (ID of the APNs key)
-   Team ID (Can be found in Apple Developer Account Page - Membership)

Please refer to [Notification Channels](/developer/quickstarts/rest-api/get-started#notification-channels) section to learn more about how to register for push services.

## Registering Device for Push Notifications

In order to receive **VoIP push notifications**, `PushKit` framework should be implemented correctly. For more information please refer [PushKit](https://developer.apple.com/documentation/pushkit). Please note that in order to receive silent `gone` notifications which are related to call subscription expiration, standard notifications should also be implemented. This means that even if you have a call-only app, you need to use standard notifications if you want to keep track of call subscription expiration.

Open the `AppDelegate` file of the project and add `import PushKit`. Note that `AppDelegate` should conform `PKPushRegistryDelegate` protocol.

In order to receive **Standard push notifications** which will enable chat, sms, gone etc notifications, `UserNotifications` framework should be implemented correctly. For more information please refer [UserNotifications](https://developer.apple.com/documentation/usernotifications).

In order to register and for VoIP and Standard push, open the `AppDelegate` file of the project and `import UserNotifications and PushKit.` Then, add the code below to the `application(:didFinishLaunchingWithOptions:)`. Note that `AppDelegate` should conform `PKPushRegistryDelegate and` `UNUserNotificationCenterDelegate` protocol.

Please note that VoIP Push registration does not require user confirmation but UserNotifications require user confirmation. For more information please refer [Asking Permission to Use Notifications](https://developer.apple.com/documentation/usernotifications/asking_permission_to_use_notifications).

Registrations should be performed every time when app has launched. Do not cache the tokens. If the device token hasn't changed, registering with `APNs` and returning the token happens quickly.

Registration can be done in two steps.

1. Registering for tokens via iOS APIs.

2. After iOS API invokes the callbacks, send them to $KANDY$ system via refreshDeviceToken API of $KANDY$ Mobile SDK.

### Registering for tokens from iOS APIs

_Swift Code:_

```swift
...
import PushKit
import UserNotifications

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, PKPushRegistryDelegate, UNUserNotificationCenterDelegate {
    
    ...
 
    var pushRegistry : PKPushRegistry!

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        ...
        //Register for VoIP Pushes
        registerForVoIPNotifications()
        //Request And Register for Standard Push (UserNotifications)
        requestAndRegisterForPushNotifications()
        ...
        return true
    }
 
    func registerForVoIPNotifications() {
        pushRegistry = PKPushRegistry(queue: DispatchQueue.main)
        pushRegistry.delegate = self 
        pushRegistry.desiredPushTypes = [PKPushType.voIP]
    }
 
    func requestAndRegisterForPushNotifications() {
        UNUserNotificationCenter.current().delegate = self 
        //Request user authorization.
        UNUserNotificationCenter.current().requestAuthorization(options: [.alert, .sound]) { granted, error in
            if granted {
                //User granted permission for local notifications.  
            }
        }
        //Register for Standard Push Notifications.
        DispatchQueue.main.async {
            UIApplication.shared.registerForRemoteNotifications()
        }
    }
 
    ...
}
```

_Objective-C Code:_

```objective-c
...
@import PushKit;
@import UserNotifications;

@interface AppDelegate : UIResponder <UIApplicationDelegate, PKPushRegistryDelegate, UNUserNotificationCenterDelegate>
...
@end

@implementation AppDelegate {
    PKPushRegistry *registry;
}
...

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    ...
    //Register for VoIP Pushes
    [self registerVoipPushNotification];
    //Request And Register for Standard Push (UserNotifications)
    [self registerStandardPushNotification];
    ...
    return YES;
}

- (void)registerVoipPushNotification {
    registry = [[PKPushRegistry alloc] initWithQueue: dispatch_get_main_queue()];
    [registry setDelegate:self];
    [registry setDesiredPushTypes:[NSSet setWithObject:PKPushTypeVoIP]];
}

- (void)registerStandardPushNotification {
    [[UNUserNotificationCenter currentNotificationCenter] setDelegate:self];
    //Request user authorization.
    [[UNUserNotificationCenter currentNotificationCenter] requestAuthorizationWithOptions:(UNAuthorizationOptionSound | UNAuthorizationOptionAlert | UNAuthorizationOptionBadge) completionHandler:^(BOOL granted, NSError * _Nullable error) {
        if (granted == YES) {
            //User granted permission for local notifications.
        }
    }];
    //Register for Standard Push Notifications.
    dispatch_async(dispatch_get_main_queue(), ^{
        [[UIApplication sharedApplication] registerForRemoteNotifications];
    });  
}

...
@end
```

### Push Service Subscription

When device is registered to the APNS, `PKPushRegistryDelegate` and `UNUserNotificationCenterDelegate` will inform through delegate methods and gives push tokens which later will be used by $KANDY$ to in order send notifications. This token should be sent to $KANDY$, later on when $KANDY$ Mobile SDK subscribes to services, user will also subscribe to push channels of the services. Please note that, VoIP token and Standard token can not be used interchangeably.

To be able to receive push notifications, applications must subscribe to push channels by using the  `refreshDeviceToken`  API of the  `CPPushService`. Fail and success calls will be transmitted through the completion block. If the registration is successful, a  `callbackURL`  will be returned.

_Swift Code:_

```swift
...
import PushKit
import UserNotifications
import CPaaSSDK

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, PKPushRegistryDelegate, UNUserNotificationCenterDelegate {
    ...
    var cpaas : CPaaS!
    var voipPushToken : String?
    var standardPushToken : String?
 
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        ...
        //Init CPaaS services
        cpaas = CPaaS(services:[CPServiceInfo(type: .chat, push: true),CPServiceInfo(type: .call, push: true)])
        ...
        return true
    }
 
    func pushRegistry(_ registry: PKPushRegistry, didUpdate pushCredentials: PKPushCredentials, for type: PKPushType) {
        // Get Device token.
        voipPushToken = pushCredentials.token.reduce("", {$0 + String(format: "%02X", $1)})
        //Inform Kandy CPaaS for token
        sendTokensToCPaas()
        
    }
    
    func application(_ application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: Data) {
        // Get Device token.
        standardPushToken = deviceToken.reduce("", {$0 + String(format: "%02.2hhx", $1)})
    
        //Inform Kandy CPaaS for token
        sendTokensToCPaas()
    }
     
    func sendTokensToCPaas() {
        if let standardToken = standardPushToken, let voipToken = voipPushToken 
        {
            cpaas.pushService.refreshDeviceToken(standardToken, voipDeviceToken: voipToken) { (error, result) in
                if let error = error {
                    print("Couldn't refresh tokens - Error: \(error.localizedDescription)")
                } else {
                    print("Tokens for Push Services refreshed")
                }
            }
        }
    }
    
    ...
}
```
 
_Objective-C Code:_

```objective-c
...
@import PushKit;
@import UserNotifications;
@import CPaaSSDK;
 
@interface AppDelegate : UIResponder <UIApplicationDelegate, PKPushRegistryDelegate, UNUserNotificationCenterDelegate>
...
@end
 
@implementation AppDelegate {
    CPaaS *cpaas;
    NSString *voipPushToken;
    NSString *standardPushToken;
}
...
 
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
     
    ...
    //Init CPaaS services
    NSArray* cpaasServices= @[[CPServiceInfo buildWithType:ServiceTypeChat push:YES],
                              [CPServiceInfo buildWithType:ServiceTypeCall push:YES]];  
    cpaas = [[CPaaS alloc] initWithServices:cpaasServices];
    ...
    return YES;
}


- (void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(nonnull NSData *)deviceToken{
    // Get Device token.
    standardPushToken = [self hexadecimalStringFromData:deviceToken];
    //Inform Kandy CPaaS for token
    [self sendTokensToCpaaS];
}


- (void)pushRegistry:(nonnull PKPushRegistry *)registry didUpdatePushCredentials:(nonnull PKPushCredentials *)pushCredentials forType:(nonnull PKPushType)type {
    // Get Device token.
    voipPushToken = [self hexadecimalStringFromData:pushCredentials.token];
    //Inform Kandy CPaaS for token
    [self sendTokensToCpaaS];
}

-(void)sendTokensToCpaaS {
    if(voipPushToken != nil && standardPushToken != nil) {
        [[cpaas pushService] refreshDeviceToken:standardPushToken voipDeviceToken:voipPushToken completion:^(CPError * _Nullable error, NSString * _Nullable result) {
            if (error) {
                NSLog(@"Couldn't refresh VoIP token - Error: %@", error.localizedDescription);
            } else {
                NSLog(@"Tokens for Push Services refreshed");
            }
        }];
    }
}

- (NSString *)hexadecimalStringFromData:(NSData *)data {
    NSUInteger dataLength = data.length;
    if (dataLength == 0) {
        return nil;
    }
    const unsigned char *dataBuffer = data.bytes;
    NSMutableString *hexString  = [NSMutableString stringWithCapacity:(dataLength * 2)];
    for (int i = 0; i < dataLength; ++i) {
        [hexString appendFormat:@"%02x", dataBuffer[i]];
    }
    return [hexString copy];
}
 
...
@end
```

### Updating Push Subscription

iOS can update the push credentials (a.k.a device token) in some cases. The new credentials must be updated on the push server, so that the Mobile SDK can continue receiving push notifications.

_Swift Code:_

```swift
...
import CPaaSSDK

class PushModule {
    func updatePushSubscription(standardToken: String, voipToken: String) {

        let cpaas = CPaaS(services:[CPServiceInfo(type: .chat, push: true),CPServiceInfo(type: .call, push: true)])
        cpaas?.pushService.refreshDeviceToken(standardToken, voipDeviceToken: voipToken) { (error, result) in
            if let error = error {
                print("Couldn't refresh tokens - Error: \(error.localizedDescription)")
            } else {
                print("Tokens for Push Services refreshed")
            }
        }
    }
}
```

_Objective-C Code:_

```objective-c
...
@import CPaaSSDK

@interface PushModule ()
@end

@implementation PushModule

- (void) updatePushSubscriptionWithStandardPushToken:(nonnull NSString*)standardToken
                                    andVoipPushToken:(nonnull NSString*)voipToken {

    NSArray* cpaasServices= @[[CPServiceInfo buildWithType:ServiceTypeChat push:YES],
                              [CPServiceInfo buildWithType:ServiceTypeCall push:YES]];  
    CPaaS *cpaas = [[CPaaS alloc] initWithServices:cpaasServices];
    [[cpaas pushService] refreshDeviceToken:standardPushToken voipDeviceToken:voipPushToken completion:^(CPError * _Nullable error, NSString * _Nullable result) {
        if (error) {
            NSLog(@"Couldn't refresh VoIP token - Error: %@", error.localizedDescription);
        } else {
            NSLog(@"Tokens for Push Services refreshed");
        }
    }];
}

@end

```

### Removing Push Subscription

In order to stop receiving push notifications, app should remove the push subscription. Otherwise, app will continue to receive push notifications until the application removed from the device.

_Swift Code:_

```swift
...
import CPaaSSDK

class PushModule {
    func removePushSubscription() {
        let cpaas = CPaaS(services:[CPServiceInfo(type: .chat, push: true),CPServiceInfo(type: .call, push: true)])
        cpaas?.pushService.unsubscribe(completion: { (error) in
            if let error = error {
                print("Couldn't unsubscribe from server - Error: \(error.localizedDescription)")
            } else {
                print("Subscription completed.")
            }
        })
    }
}

```

_Objective-C Code:_

```objective-c
...
@import CPaaSSDK

@interface PushModule ()
@end

@implementation PushModule

- (void) removePushSubscription {
    NSArray* cpaasServices= @[[CPServiceInfo buildWithType:ServiceTypeChat push:YES],
                              [CPServiceInfo buildWithType:ServiceTypeCall push:YES]];
    CPaaS *cpaas = [[CPaaS alloc] initWithServices:cpaasServices];
    [[cpaas pushService] unsubscribeWithCompletion:^(CPError * _Nullable error) {
        if (error) {
            NSLog(@"Couldn't unsubscribe from server. - Error: %@", error.localizedDescription);
        } else {
            NSLog(@"Subscription completed.");
        }
    }];
}

@end

```

## Receiving Push Notifications

### VoIP Push Notification Callback

If VoIP push registration is completed successfully and subscribed to push channels with the correct device push token, device now should receive VoIP push notifications for incoming calls.

When device receives VoIP push notification, `PKPushRegistryDelegate` informs its delegate via `pushRegistry(:didReceiveIncomingPushWith:for:)` which is available for iOS10 devices, and `pushRegistry(:didReceiveIncomingPushWith:for:completion:)` for iOS11 and later devices. Because very similar implementation will be done for both methods, creating new method and executing operations inside on that method is recommended. With Xcode11 compiled app it has been mandatory to inform `CallKit`. For more information please refer [pushRegistry](https://developer.apple.com/documentation/pushkit/pkpushregistrydelegate/2875784-pushregistry). Informing CallKit with appropriate Caller ID and Caller Name requires parsing the incoming VoIP push Notification. $KANDY$ Mobile SDK provide API for parsing notification which is shown in below code.

Please note that in order to inject push payload, app should wait until SDK has been subscribed and connected.  

_Swift Code:_

```swift
...
import CPaaSSDK
import PushKit
...


@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, PKPushRegistryDelegate, UNUserNotificationCenterDelegate {
    ...
    var cpaas : CPaaS!
 
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        ...
        //Init CPaaS services
        cpaas = CPaaS(services:[CPServiceInfo(type: .chat, push: true),CPServiceInfo(type: .call, push: true)])
        ...
        return true
    }
 
    // Will be invoked when VoIP push notification is received.
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
        //Parsing push notification 
        var callKitInfo = cpaas.pushService.parsePushNotification(payload.dictionaryPayload)
        if (callKitInfo.error == nil) {
            //Inform CallKit about the incoming call with callKitInfo.callUUID and callKitInfo.callerDisplayInfo 
            // CXProvider reportNewIncomingCall(with:update:completion:) 
            //Failure to inform CallKit a couple of times and iOS 13 will block app from receiving VoIP push.
 
            //Inject push payload after SDK has been subscribed and connected.
            cpaas.pushService.injectPushMessage(pushMessage: payload.dictionaryPayload){ (error) in
                completion?()
            }
        } else {
            //Inform CallKit about the failed incoming call.
            // 1- CXProvider reportNewIncomingCall(with:update:completion:)
            // 2- CXProvider reportCall(with:endedAt:reason:) with reason CXCallEndedReason.failed
            //Failure to inform CallKit a couple of times and iOS 13 will block app from receiving VoIP push.
        }
    }

    ...
}
```

_Objective-C Code:_

```objective-c
...
@import CPaaSSDK;
@import PushKit;
  
@interface AppDelegate : UIResponder <UIApplicationDelegate, PKPushRegistryDelegate, UNUserNotificationCenterDelegate>
...
@end
  
@implementation AppDelegate {
    ...
    CPaaS *cpaas;
}
...
  
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
      
    ...
    //Init CPaaS services
    NSArray* cpaasServices= @[[CPServiceInfo buildWithType:ServiceTypeChat push:YES],
                              [CPServiceInfo buildWithType:ServiceTypeCall push:YES]]; 
    cpaas = [[CPaaS alloc] initWithServices:cpaasServices];
    ...
    return YES;
}
 
#if __IPHONE_OS_VERSION_MIN_REQUIRED >= 11000
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type withCompletionHandler:(void (^)(void))completion {
    [self sendPushMessageWithPayload:payload completion:completion];
}
#else
- (void)pushRegistry:(PKPushRegistry *)registry didReceiveIncomingPushWithPayload:(PKPushPayload *)payload forType:(PKPushType)type {
    [self sendPushMessageWithPayload:payload completion:nil];
}
#endif

- (void)sendPushMessageWithPayload: (PKPushPayload *)payload completion:(void (^)(void))completion {
    //Parsing push notification
    CPCKInfo *callKitInfo = [pushService parsePushNotification:payload.dictionaryPayload];
    if (!callKitInfo.error) {
        //Inform CallKit about the incoming call with callKitInfo.callUUID and callKitInfo.callerDisplayInfo
        // CXProvider reportNewIncomingCall(with:update:completion:)
        //Failure to inform CallKit a couple of times and iOS 13 will block app from receiving VoIP push.
 
        //Inject push payload after SDK has been subscribed and connected.
        [[cpaas pushService] injectPushMessageWithPushMessage:payload.dictionaryPayload completion:^(CPError * _Nullable error) {
            if (completion) {
                completion();
            }
        }];
    } else {
        //Inform CallKit about the failed incoming call.
        // 1- CXProvider reportNewIncomingCall(with:update:completion:)
        // 2- CXProvider reportCall(with:endedAt:reason:) with reason CXCallEndedReason.failed
        //Failure to inform CallKit a couple of times and iOS 13 will block app from receiving VoIP push.
    }
} 
...
@end
```

### Standard Push Notification Callback

If Standard push registration is completed successfully and subscribed to push channels with the correct device push token, device now should receive Standard push notifications. Standard push notifications include SMS, Chat Message and, special type Silent notifications. SMS and Chat Message notifications are received as alert notifications. Gone notifications are silent notifications.

Alert notifications will be handled by iOS when app is not in foreground, but will be delivered to app when app is on foreground. Silent notifications are low priority and needs to be handled by app. Silent notifications which will not provide any alert on iOS device to end-user, include Call subscription cancellation and SMS subscription cancellation.

Even though Standard notifications with alert type will be handled by iOS, app needs to provide localized content in app bundle. More information will be covered in next section.

SMS, and Chat Message notifications that will be received on foreground can be handled by implementing by `userNotificationCenter(_:willPresent:withCompletionHandler:)`  . When notification received calling completionHandler with no option `[]` will not inform user about the incoming notification.

Silent notifications needs to handled by implementing `application(_:didReceiveRemoteNotification:fetchCompletionHandler:)`. If the user opens your app from the system-displayed alert, the system may call this method again when your app is about to enter the foreground so that you can update your user interface and display information pertaining to the notification. Parsing notification first and acting accordingly is important.

For more information please refer [handling notifications](https://developer.apple.com/documentation/usernotifications/handling_notifications_and_notification-related_actions).

_Swift Code:_

```swift
...
import CPaaSSDK
import UserNotifications
...

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, PKPushRegistryDelegate, UNUserNotificationCenterDelegate {
    ...
    //App received notification foreground.
    func userNotificationCenter(_ center: UNUserNotificationCenter, willPresent notification: UNNotification, withCompletionHandler completionHandler: @escaping (UNNotificationPresentationOptions) -> Void) {
        completionHandler([])
    }
 
    //User clicked a notification. Present UI accordingly.
    func userNotificationCenter(_ center: UNUserNotificationCenter, didReceive response: UNNotificationResponse, withCompletionHandler completionHandler: @escaping () -> Void) {
        switch response.actionIdentifier {
        case UNNotificationDefaultActionIdentifier:
            //User opened the app from the notification interface.
            //Inject push payload after SDK has been subscribed and connected.
            break
        default:
            break
        }
        completionHandler()
    }
    // Will be invoked when a silent notification comes. 
    func application(_ application: UIApplication, didReceiveRemoteNotification userInfo: [AnyHashable : Any], fetchCompletionHandler completionHandler: @escaping (UIBackgroundFetchResult) -> Void) {
        //Inject push payload after SDK has been subscribed and connected.
        //Implement necessary business logic like deleting user subscription or re-subscribe.
        completionHandler(.newData)
    }
    ...
}
```

_Objective-C Code:_

```objective-c
 ...
@import CPaaSSDK;
@import UserNotifications;
  
@interface AppDelegate : UIResponder <UIApplicationDelegate, PKPushRegistryDelegate, UNUserNotificationCenterDelegate>
...
@end
  
@implementation AppDelegate 
...
//App received notification foreground.
- (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler {
    completionHandler(UNNotificationPresentationOptionNone);
}

- (void) userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void (^)(void))completionHandler {
    if ([response.actionIdentifier isEqualToString:UNNotificationDefaultActionIdentifier]) {
        //User opened the app from the notification interface.
        //Inject push payload after SDK has been subscribed and connected.
    }
    completionHandler();
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    //Inject push payload after SDK has been subscribed and connected.
    //Implement necessary business logic like deleting user subscription or re-subscribe.
    completionHandler(UIBackgroundFetchResultNewData);
}
...
@end
```

### Standard Push Notification Localization

$KANDY$ will send the alert notifications with the following keys which can be used in notification payload for localization.
| Key | Value Type| Comment|
|--|--|--|
| `title-loc-key` | String or `null` | The key to a title string in the `Localizable.strings` file for the current localization. The key string can be formatted with `%@` and `%n$@` specifiers to take the variables specified in the `title-loc-args` array. See [Localizing the Content of Your Remote Notifications](https://developer.apple.com/library/archive/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/CreatingtheNotificationPayload.html#//apple_ref/doc/uid/TP40008194-CH10-SW9) for more information. This key was added in iOS 8.2. |
| `title-loc-args` | Array of strings or `null` | Variable string values to appear in place of the format specifiers in `title-loc-key`. See [Localizing the Content of Your Remote Notifications](https://developer.apple.com/library/archive/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/CreatingtheNotificationPayload.html#//apple_ref/doc/uid/TP40008194-CH10-SW9) for more information. This key was added in iOS 8.2. |
| `loc-key` | String | A key to an alert-message string in a `Localizable.strings` file for the current localization (which is set by the user’s language preference). The key string can be formatted with `%@` and `%n$@` specifiers to take the variables specified in the `loc-args` array. See [Localizing the Content of Your Remote Notifications](https://developer.apple.com/library/archive/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/CreatingtheNotificationPayload.html#//apple_ref/doc/uid/TP40008194-CH10-SW9) for more information.|
| `loc-args` | Array of strings | Variable string values to appear in place of the format specifiers in `loc-key`. See [Localizing the Content of Your Remote Notifications](https://developer.apple.com/library/archive/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/CreatingtheNotificationPayload.html#//apple_ref/doc/uid/TP40008194-CH10-SW9) for more information.|
| `body` | String | The text of the alert message.|

When an alert notification received and includes above keys the local system searches the app’s `Localizable.strings` files for a key string matching the value. App bundle Localizable.strings should include `title-loc-key` and `loc-key` for the supported languages.

$KANDY$ keys will include below key value pairs :

 **SMS**
| Key | Value | Localizable.strings | Result Title | Result Body
|--|--|--|--|--|
| `title-loc-key` | inboundSMSMessageNotification_title | inboundSMSMessageNotification_title = "%@ sent you a SMS" | senderAdress sent you a SMS | msg |
| `title-loc-args` | ["senderAdress"] | 
| `body` | "msg" |

  **Chat**
| Key | Value | Localizable.strings | Result Title | Result Body
|--|--|--|--|--|
| `title-loc-key` | chatMessageNotification_title | chatMessageNotification_title = "%@ sent you a message" | senderAdress sent you a message | msg |
| `title-loc-args`| ["senderAdress"] |  
| `body`| "msg"|

**Group Chat Invitation**

| Key | Value | Localizable.strings | Result Title | Result Body
|--|--|--|--|--|
| `title-loc-key` | groupChatSessionInvitationNotification_title | groupChatSessionInvitationNotification_title = "Group Invitation" |  Group Invitation | Please join to groupName |
| `loc-key`| groupChatSessionInvitationNotification_body | groupChatSessionInvitationNotification_body = "Please join to %@" |
| `loc-args` | ["groupName"] |

For more information please refer [storing localized content in your app bundle](https://developer.apple.com/library/archive/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/CreatingtheNotificationPayload.html) .
