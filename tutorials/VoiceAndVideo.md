---
  topics:
  - title: Creating Outgoing Call
    body: In this section you will learn how to start an outgoing call using $KANDY$ Mobile SDK.
  - title: Receiving Incoming Call
    body: In this section you will learn how to receive an incoming call using $KANDY$ Mobile SDK.
  - title: Managing Call Events
    body: In this section you will learn how to manage call events using $KANDY$ Mobile SDK.
  - title: Anonymous Calls
    body: In this section you will learn how to establish anonymous calls using $KANDY$ Mobile SDK.
---
# Voice and Video Calls

Voice and Video calls are managed by the Call Service which can be called from `CPaaS` instance. In order to receive and send events, `CPaaS` instance should be connected first. To see how to connect and set configurations, check **Login** and **Configurations** sections.

## Creating Outgoing Call

You can create **Outgoing Call Object** by calling `createOutgoingCall` method in Call Service.

Terminator should be defined by using `CPUriAddress` object.

For video calls, remote video view and local video views should be set to `UIView` objects where they want to be appear.

*Swift Code:*

```swift
import CPaaSSDK

let term = CPUriAddress(username: "username", withDomain: "domain")
// or let term = CPUriAddress(primaryContact: "username@domain")

let service = cpaas.callService
service?.createOutGoingCall(<CallApplicationDelegate>, andTerminator: term, completion: { (call, error) in
    if let error = error {
        print("Call Couldn't be created - Error: \(error.localizedDescription)")
        return
    }

    call?.localVideoView = <localVideoView>
    call?.remoteVideoView = <remoteVideoView>

    // For Video call
    call?.establishCall(true)

    // For Double M-Line Audio Call
    call?.establishCall(false)

    // For Single M-Line Audio Call
    call?.establishAudioCall()
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

CPUriAddress *term = [[CPUriAddress alloc] initWithUsername:@"username" withDomain:@"domain"]];
// or CPUriAddress *term = [[CPUriAddress alloc] initWithPrimaryContact:@"username@domain"];

CPCallService *service = cpaas.callService;
[service createOutGoingCall:<CPCallApplicationDelegate> andTerminator:terminator completion:^(id<CPOutgoingCallDelegate> call, CPError * error) {
    if (error) {
        NSLog(@"Call Couldn't be created - Error: %@", error.localizedDescription);
        return;
    }

    call.localVideoView = <localVideoView>;
    call.remoteVideoView = <remoteVideoView>;

    // For Video call
    [call establishCall:YES];

    // For Double M-Line Audio Call
    [call establishCall:NO];

    // For Single M-Line Audio Call
    [call establishAudioCall];
}];
```

Call Application Delegate will be notified when any changes occurred during the call and can be managed by listening its protocol stubs.

## Receiving Incoming Call

When $KANDY$ Mobile SDK receives an incoming call, it calls incomingCall: method in the Call Application Delegate. Thus, `CallApplicationDelegate` should be implemented to the class where managed. Now, the application should receive incoming call events if any occurs.

*Swift Code:*

```swift
import CPaaSSDK

cpaas.callService?.setCallApplication(self)
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

[cpaas.callService setCallApplication:self];
```

### Managing Incoming Call

When incomingCall: method is notified with the received incoming call, call can be accepted with videoEnabled option, rejected or ignored. Application will be informed about success or fail via the callback methods on `CallApplicationDelegate` which are related to the operation.

#### Accepting Incoming Call

An incoming call can be accepted by calling the acceptCall: method on the incoming call instance which is received from `CallApplicationListener`.

*Swift Code:*

```swift
import CPaaSSDK

func incomingCall(_ call: CPIncomingCallDelegate!) {
    call.localVideoView = <localVideoView>
    call.remoteVideoView = <remoteVideoView>

    // For Video Call
    call.acceptCall(true)

    // For Audio Call
    call.acceptCall(false)
}
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

- (void)incomingCall:(id<CPIncomingCallDelegate>)call {
    call.localVideoView = <localVideoView>;
    call.remoteVideoView = <remoteVideoView>;

    // For Video Call
    [call acceptCall:YES];

    // For Audio Call
    [call acceptCall:NO];
}
```

#### Rejecting Incoming Call

An incoming call can be rejected by calling the rejectCall: method on the incoming call instance.

*Swift Code:*

```swift
import CPaaSSDK

func incomingCall(_ call: CPIncomingCallDelegate!) {
    call.rejectCall()
}
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

- (void)incomingCall:(id<CPIncomingCallDelegate>)call {
    [call rejectCall];
}
```

#### Ignoring Incoming Call

An incoming call can be ignored by calling the ignoreCall: method on the incoming call instance.

```swift
import CPaaSSDK

func incomingCall(_ call: CPIncomingCallDelegate!) {
    call.ignoreCall()
}
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

- (void)incomingCall:(id<CPIncomingCallDelegate>)call {
    [call ignoreCall];
}
```

## Managing Call Events

Methods implemented in the Call Application Delegate are notified with the events occurred during the call, or `callStatusChanged` when state of the call is changed. By listening these methods, call events can be managed directly. To see all methods implemented in the **Call Application Delegate** see API Reference Documents.

*Swift Code:*

```swift
import CPaaSSDK

func callStatusChanged(_ call: CPCallDelegate!, with callState: CPCallState!) {
    print("Call Status changed to \(callState.type)")
}
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

- (void)callStatusChanged:(id<CPCallDelegate>)call withState:(CPCallState *)callState {
    NSLog(@"Call Status changed to :%@", callState.type);
}
```

### Starting Call Events

Both incoming call (`CPIncomingCallDelegate`) and outgoing call (`CPOutgoingCallDelegate`) protocols are inherited from `CPCallDelegate` protocol. Except particular properties and methods defined in incoming call and outgoing call delegates, all methods and properties defined in `CPCallDelegate` are suitable for both call type.

Note that, an application may not start an event while any other operation is in progress.

Furthermore, when a mid-call operation finishes which is called by the user, its *success* or *fail* method is triggered depending on result of the operation.

Because audio of the call is managed by `AVAudioSession`, you can change route of the sound by changing mode and options of the `AVAudioSession` shared instance, $KANDY$ doesn't expose any API for audio route changes.

#### To end call

To end an incoming or outgoing call, endCall: method on call instance can be called.

*Swift Code:*

```swift
import CPaaSSDK

call.endCall()
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

[call endCall];
```

#### To hold or unhold call

While in a call, a participant may be placed on hold by calling `holdCall` method. When operation succeeds, media transfer between participants stops, and call state will change to `On Hold` state. Remote participant will see this call session in `Remotely Held` state.

To resume to the call, `unholdCall` method should be called. Note that, these operations take some time, thus listening operation results from `CallApplicationDelegate`, and acting accordingly is recommended.

Note that a call already in `On Hold` state may not be placed on hold. Similarly, attempting to `unhold` a call that is not in `On Hold` state will fail.

*Swift Code:*

```swift
import CPaaSSDK

call.holdCall()
call.unholdCall()
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

[call holdCall];
[call unholdCall];
```

#### To start or stop sending video

*Swift Code:*

```swift
import CPaaSSDK

call.videoStart()
call.videoStop()
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

[call videoStart];
[call videoStop];
```

#### To mute or unmute call

To stop sending audio from the microphone, `mute` method can be called. Until unmuting the call, participants cannot hear the voice from the device.

*Swift Code:*

```swift
import CPaaSSDK

call.mute()
call.unmute()
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

[call mute];
[call unmute];
```


## Anonymous Calls

$KANDY$ offers to make voice and video calls even if the application user does not have a $KANDY$ account to login. This functionality is called as Anonymous Call on $KANDY$ system. Anonymous call feature can be useful for applications such as customer service support. Since the application user does not have a $KANDY$ account, only an outgoing call can be made to a registered $KANDY$ user. An anonymous user cannot receive and incoming call with this feature.

Please refer to [Anonymous Calls](/developer/quickstarts/rest-api/voice-and-video-calls#anonymous-calls) section to learn about how to implement anonymous calls solution.

### Creating an Anonymous Call

A server-side component is suggested to be used for logging in to $KANDY$ along with Mobile SDK for an anonymous call scenario. Once the application establishes the login, application should be able create outgoing calls using the Call Service on $KANDY$ Mobile SDK. Creating an anonymous outgoing call follows the same procedure as if it is a regular outgoing call. The main difference is an anonymous user cannot receive an incoming call, so application will not receive and incoming call notification on $KANDY$ Mobile SDK.
