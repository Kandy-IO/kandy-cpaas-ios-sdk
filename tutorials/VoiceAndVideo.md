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

Note that, In order to be able to call PSTN destinations, your user/project should have at least one telephone number assigned. For WebRTC destinations telephone number assignment is not required.

## Creating Outgoing Call

You can create **Outgoing Call Object** by calling `createOutgoingCall` method in Call Service.

Terminator should be defined by using `CPUriAddress` object.

For video calls, remote video view and local video views should be set to `UIView` objects where they want to be appear.

<!-- tabs:start -->

#### ** Swift Code **

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

#### ** Objective-C Code **

```objectivec
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
<!-- tabs:end -->

Call Application Delegate will be notified when any changes occurred during the call and can be managed by listening its protocol stubs.

## Receiving Incoming Call

When $KANDY$ Mobile SDK receives an incoming call, it calls incomingCall: method in the Call Application Delegate. Thus, `CallApplicationDelegate` should be implemented to the class where managed. Now, the application should receive incoming call events if any occurs.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

cpaas.callService?.callApplicationDelegate = self
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

[cpaas.callService setCallApplicationDelegate:self];
```
<!-- tabs:end -->

### Managing Incoming Call

When incomingCall: method is notified with the received incoming call, call can be accepted with videoEnabled option, rejected or ignored. Application will be informed about success or fail via the callback methods on `CallApplicationDelegate` which are related to the operation.

#### Accepting Incoming Call

An incoming call can be accepted by calling the acceptCall: method on the incoming call instance which is received from `CallApplicationListener`.

<!-- tabs:start -->

#### ** Swift Code **

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

#### ** Objective-C Code **

```objectivec
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
<!-- tabs:end -->

#### Rejecting Incoming Call

An incoming call can be rejected by calling the rejectCall: method on the incoming call instance.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

func incomingCall(_ call: CPIncomingCallDelegate!) {
    call.rejectCall()
}
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

- (void)incomingCall:(id<CPIncomingCallDelegate>)call {
    [call rejectCall];
}
```
<!-- tabs:end -->

#### Ignoring Incoming Call

An incoming call can be ignored by calling the ignoreCall: method on the incoming call instance.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

func incomingCall(_ call: CPIncomingCallDelegate!) {
    call.ignoreCall()
}
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

- (void)incomingCall:(id<CPIncomingCallDelegate>)call {
    [call ignoreCall];
}
```
<!-- tabs:end -->

#### Forwarding Incoming Call

An incoming call can be forwarded to another user by calling the forwardCall: method on the incoming call instance. After a successful invokation of the forward operation, call will be ended on the client which invoked the operation, the user whose address is given to forward operation will receive an incoming call from the originator side.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

func incomingCall(_ call: CPIncomingCallDelegate!) {
    let targetAddress = CPUriAddress(primaryContact: "username@domain")
    call.forwardCall(targetAddress)
}
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

- (void)incomingCall:(id<CPIncomingCallDelegate>)call {
    CPUriAddress *targetAddress = [[CPUriAddress alloc] initWithPrimaryContact:@"username@domain"];
    [call forwardCall:targetAddress];
}
```
<!-- tabs:end -->

## Managing Call Events

Methods implemented in the Call Application Delegate are notified with the events occurred during the call, or `callStatusChanged` when state of the call is changed. By listening these methods, call events can be managed directly. To see all methods implemented in the **Call Application Delegate** see API Reference Documents.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

func callStatusChanged(_ call: CPCallDelegate!, with callState: CPCallState!) {
    print("Call Status changed to \(callState.type)")
}
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

- (void)callStatusChanged:(id<CPCallDelegate>)call withState:(CPCallState *)callState {
    NSLog(@"Call Status changed to :%@", callState.type);
}
```
<!-- tabs:end -->

### Starting Call Events

Both incoming call (`CPIncomingCallDelegate`) and outgoing call (`CPOutgoingCallDelegate`) protocols are inherited from `CPCallDelegate` protocol. Except particular properties and methods defined in incoming call and outgoing call delegates, all methods and properties defined in `CPCallDelegate` are suitable for both call type.

Note that, an application may not start an event while any other operation is in progress.

Furthermore, when a mid-call operation finishes which is called by the user, its *success* or *fail* method is triggered depending on result of the operation.

Because audio of the call is managed by `AVAudioSession`, you can change route of the sound by changing mode and options of the `AVAudioSession` shared instance, $KANDY$ doesn't expose any API for audio route changes.

#### To end call

To end an incoming or outgoing call, endCall: method on call instance can be called.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

call.endCall()
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

[call endCall];
```
<!-- tabs:end -->

#### To hold or unhold call

While in a call, a participant may be placed on hold by calling `holdCall` method. When operation succeeds, media transfer between participants stops, and call state will change to `On Hold` state. Remote participant will see this call session in `Remotely Held` state.

To resume to the call, `unholdCall` method should be called. Note that, these operations take some time, thus listening operation results from `CallApplicationDelegate`, and acting accordingly is recommended.

Note that a call already in `On Hold` state may not be placed on hold. Similarly, attempting to `unhold` a call that is not in `On Hold` state will fail.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

call.holdCall()
call.unholdCall()
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

[call holdCall];
[call unholdCall];
```
<!-- tabs:end -->

#### To start or stop sending video

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

call.videoStart()
call.videoStop()
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

[call videoStart];
[call videoStop];
```
<!-- tabs:end -->

#### To mute or unmute call

To stop sending audio from the microphone, `mute` method can be called. Until unmuting the call, participants cannot hear the voice from the device.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

call.mute()
call.unmute()
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

[call mute];
[call unmute];
```
<!-- tabs:end -->

## Anonymous Calls

$KANDY$ offers to make voice and video calls even if the application user does not have a $KANDY$ account to login. This functionality is called as Anonymous Call on $KANDY$ system. Anonymous call feature can be useful for applications such as customer service support. Since the application user does not have a $KANDY$ account, only an outgoing call can be made to a registered $KANDY$ user. An anonymous user cannot receive and incoming call with this feature.

Please refer to [Anonymous Calls](/developer/quickstarts/rest-api/voice-and-video-calls#anonymous-calls) section to learn about how to implement anonymous calls solution.

### Creating an Anonymous Call

A server-side component is suggested to be used for logging in to $KANDY$ along with Mobile SDK for an anonymous call scenario. Once the application establishes the login, application should be able create outgoing calls using the Call Service on $KANDY$ Mobile SDK. Creating an anonymous outgoing call follows the same procedure as if it is a regular outgoing call. The main difference is an anonymous user cannot receive an incoming call, so application will not receive and incoming call notification on $KANDY$ Mobile SDK.

## Advanced Usage of Call Service

### Retrieve Audio and Video RTP/RTCP Statistics

$KANDY$ can retrieve audio and video RTP/RTCP statistics providing information including:

* Number of packets lost
* Number of packets sent/received
* Number of bytes sent/received
* Call Jitter received
* RTT (round trip delay)
* Local/Remote network addresses and ports
* Audio/Video codec names

**Note:** $KANDY$ does not keep the statistics after the call ends.It is application developer's responsibility to keep them. Since the statistics could be too long to log due to character limitation, it is adviced to write them to a file instead of logging for further usage. You can use the following class to see how to write it to a file :

<!-- tabs:start -->

#### ** Objective-C Code **

```objectivec
#import "DemoRTPLogger.h"

void RTPLog(NSString *format, ...){
    va_list args;
    va_start(args, format);
    NSString *logString = [[NSString alloc] initWithFormat:format arguments:args];
    [[DemoRTPLogger getInstance] writeLogToFile:logString];
    va_end(args);
}

@interface DemoRTPLogger(){
    
    NSFileHandle *myHandle;
}

@end

@implementation DemoRTPLogger

__strong static id _instance = nil;


+(instancetype)getInstance{
    @synchronized (self) {
        if(!_instance){
            _instance = [[self alloc]init];
        };
    }
    return _instance;
}
- (id)init
{
    self = [super init];
    if (self) {
        [self initLogFile];
    }
    return self;
}

- (void) initLogFile{
    if(myHandle) [myHandle closeFile];
    
    if(![[NSFileManager defaultManager] fileExistsAtPath:CONSOLE_RTP_LOG_PATH])
        [@"" writeToFile:CONSOLE_RTP_LOG_PATH atomically:YES encoding:NSUTF8StringEncoding error:nil];
    
    NSLog(@"Log File Path: %@", CONSOLE_RTP_LOG_PATH);
    myHandle = [NSFileHandle fileHandleForUpdatingAtPath:CONSOLE_RTP_LOG_PATH];
}

- (void) writeLogToFile:(NSString *)log {
    
    NSString *dateString = [NSDateFormatter localizedStringFromDate:[NSDate date]
                                                          dateStyle:NSDateFormatterShortStyle
                                                          timeStyle:NSDateFormatterMediumStyle];
    [myHandle seekToEndOfFile];
    [myHandle writeData:[[dateString stringByAppendingFormat:@": %@\n", log] dataUsingEncoding:NSUTF8StringEncoding]];
}
-(void)clearLogs{
    [@"" writeToFile:CONSOLE_RTP_LOG_PATH atomically:YES encoding:NSUTF8StringEncoding error:nil];
    [self initLogFile];
    RTPLog(@"RTP Logs Cleaned");
}
-(void)closeFile{
    [myHandle closeFile];
}
@end
```

#### ** Swift Code **

```swift
import Foundation

class CallStatistics: NSObject {
    
    public static let sharedInstance = CallStatistics()
    private var handler: FileHandle?
    
    override init() {
        super.init()
        initLogFile()
    }
    
    private func initLogFile() {
        let destPath = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true).first!
        let fullDestPath = NSURL(fileURLWithPath: destPath).appendingPathComponent("CallStatistics.log")
        let fullDestPathString = fullDestPath!.path
        if !FileManager.default.fileExists(atPath: fullDestPathString) {
            do {
                try "".write(toFile: fullDestPathString, atomically: true, encoding: String.Encoding.utf8)
            } catch {
                NSLog("Can't write to file to device directory - Error: \(error.localizedDescription)")
            }
        }
        handler = FileHandle.init(forUpdatingAtPath: fullDestPathString)
    }
    
    fileprivate func writeLogToFile(file: String, function: String, line: Int, queue: String, _ format: String, _ args: CVarArg...) {
        let dateStr = DateFormatter.localizedString(from: Date(), dateStyle: .short, timeStyle: .medium)
        let fileNameArr = file.components(separatedBy: "/")
        let onlyTheFileName = fileNameArr.last ?? ""
        let logStr = String(format: "[\(dateStr)]: [FUNCTION: \(function) AT \(onlyTheFileName).\(line) QUEUE: \(queue)] \(format) \n", args)
        handler?.seekToEndOfFile()
        if let logData = logStr.data(using: String.Encoding.utf8) {
            handler?.write(logData)
        }
        let willLogged = String(format: format, args)
        print(willLogged)
    }
    
    func createZipFile() -> String {
        let destPath = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true).first!
        let fullDestPath = NSURL(fileURLWithPath: destPath).appendingPathComponent("CallStatistics.log")
        let fullDestPathString = fullDestPath!.path
        let zipDest = fullDestPathString.appending(".zip")
        SSZipArchive.createZipFile(atPath: zipDest, withFilesAtPaths: [fullDestPathString])
        return zipDest
    }
    
    func clearLogs() {
        let destPath = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true).first!
        let fullDestPath = NSURL(fileURLWithPath: destPath).appendingPathComponent("CallStatistics.log")
        let fullDestPathString = fullDestPath!.path
        do {
            try "".write(toFile: fullDestPathString, atomically: true, encoding: String.Encoding.utf8)
        } catch {
            NSLog("Can't write to file to device directory - Error: \(error.localizedDescription)")
        }
        initLogFile()
        logWith("RTP Logs Cleaned")
    }
    func closeFile(){
        handler?.closeFile()
    }
}

func logRTP(_ format: String, file: String = #file, function: String = #function, line: Int = #line, args: CVarArg...) {
    let queueName = OperationQueue.current?.name ?? ""
    CallStatistics.sharedInstance.writeLogToFile(file: file, function: function, line: line, queue: queueName, format, args)
    
}
```
<!-- tabs:end -->


Use the "getRTPStatistics" method in an Call object to retrieve a string in the JSON format containing RTP/RTCP statistics. The JSON-String includes objects of the RTCStatsReport class—a class which stores statistic details. This class has the following public variables:


 * timestamp -- Indicates the time at which the sample was taken for this statistics object.
 * type      -- Indicates the type of statistics the object contains. Types are listed below.
 * id        -- Uniquely identifies the object.


 ```javascript
type {
    "codec",            
    "inbound-rtp",
    "outbound-rtp",
    "remote-inbound-rtp",
    "remote-outbound-rtp",
    "media-source",
    "csrc",
    "peer-connection",
    "data-channel",
    "stream",
    "track",
    "transceiver",
    "sender",
    "receiver",
    "transport",
    "sctp-transport",
    "candidate-pair",
    "local-candidate",
    "remote-candidate",
    "certificate",
    "ice-server"
}
```

#### Example: Retrieving statistics

It is recommended to call this method every 10 seconds as long as call continues.

<!-- tabs:start -->

#### ** Objective-C Code **

```objectivec
  [call getRTPStatistics:^(NSString * _Nullable statistics) {
                if([call getCallState].type != CALLSTATES_ENDED && call != nil){
                    RTPLog(statistics);
            }
                }];
```

#### ** Swift Code **

```swift
    call.getRTPStatistics { (stat) in
            if(call.getCallState().type != .ended && (call != nil)) {
                logRTP(stat!)
            }
        }
```
<!-- tabs:end -->


#### Ringing feedback

If the receiving party prefers the information that it has successfully received the call, it can notify the calling party by the `ringingFeedbackOption` method. 

The default value of this method is CLIENT. If you want to change this value, you must do so before registration.

Possible values of the ringingFeedbackOption configuration parameter are NONE and CLIENT.

* NONE: There will be no ringing feedback.

* CLIENT: Client based ringing feedback.

When ringingFeedbackOption is NONE, CPaaS SDK will not send ringing feedback.

<div class="page-break"></div>

###### Example: Setting ringing feedback feature

<!-- tabs:start -->

#### ** Objective-C Code **

```objectivec
// There will be no ringing feedback.
[[CPConfig sharedInstance] setRingingFeedbackOption:NONE];
// Client based ringing feedback.
[[CPConfig sharedInstance] setRingingFeedbackOption:CLIENT];
//User can register now
```

#### ** Swift Code **

```swift
// There will be no ringing feedback.
CPConfig.getInstance().ringingFeedbackOption = .none
// Client based ringing feedback.
CPConfig.getInstance().ringingFeedbackOption = .client
//User can register now
```
<!-- tabs:end -->

###### Example: Sending ringing feedback

<!-- tabs:start -->

#### ** Objective-C Code **

```objectivec
- (void) incomingCall:(id<CPIncomingCallDelegate>)call
{
    [call sendRingingFeedback];
    // Perform actions related to the incoming call
}

- (void) sendRingingFeedbackSucceed:(id<CPIncomingCallDelegate>)call
{
    NSLog(@"Send ringing feedback succeeded");
}
- (void) sendRingingFeedbackFailed:(id<CPIncomingCallDelegate>)call withError:(CPError *)error{
    NSLog(@"Send ringing feedback failed");
}
```

#### ** Swift Code **

```swift
func incomingCall(_ call: CPIncomingCallDelegate) {
    call.sendRingingFeedback()
}

func sendRingingFeedbackSucceed(_ call: CPCallDelegate) {
    NSLog("Send ringing feedback succeeded")
}

func sendRingingFeedbackFailed(_ call: CPCallDelegate, withError error: CPError) {
    NSLog("Send ringing feedback failed")
}
```
<!-- tabs:end -->
