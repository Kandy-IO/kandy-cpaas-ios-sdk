---
  topics:
  - title: Fetching SMS Messages
    body: In this section you will learn how to fetch SMS messages using $KANDY$ Mobile SDK.
  - title: Sending SMS Messages
    body: In this section you will learn how to send an SMS messages using $KANDY$ Mobile SDK.
  - title: Receiving SMS Messages
    body: In this section you will learn how to receive an SMS messages using $KANDY$ Mobile SDK.
---
# SMS Messaging

SMS messaging is managed by the SMS Service which can be called from the `CPaaS` instance. In order to receive and send events, the `CPaaS` instance should be connected first. To see how to connect and set configurations, check **Login** and **Configurations** sections.

### Initialize the SMS Service

In order to use the SMS service, the service provider object must be properly initialized. When properly initialized, the application will be registered to receive SMS notifications from the server.

*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

func initProvider() {
    // select the services that will be used by the application. Specify .sms for SMS service
    // to be enabled. If the application should receive notifcations via the APN push service
    // set push parameter to 'true'.
    let servicesToEnable = [CPServiceInfo(type: .chat, push: true),
                            CPServiceInfo(type: .sms, push: true)]

    // initialize a CPaaS service provider object with the
    // services that it should provide
    self.cpaas = CPaaS(services: servicesToEnable)
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

@interface AppModel : NSObject <SmsDelegate>
@end

@implementation AppModel

- (void) initProvider {
    // Initiating configuration and assigning required parameters
    CPConfig* configuration = [CPConfig new];
    configuration.useSecureConnection = YES;
    configuration.restServerUrl = @"cpaas.rbbn.com";

    // select the services that will be used by the application. Specify .sms for SMS service
    // to be enabled. If the application should receive notifications via the APN push service
    // set push parameter to 'true'.
    NSArray<CPServiceInfo*>* cpaasServices= @[[CPServiceInfo buildWithType:CPServiceTypeSms push:true],
                              [CPServiceInfo buildWithType:CPServiceTypeCall push:false]];

    // initialize a CPaaS service provider object with the
    // services that it should provide
    self.cpaas = [[CPaaS alloc] initWithConfig:config services: cpaasServices];
 }
```

### Implement and Set Sms Delegate

In order for the CPaaS SDK to notify the application of notifications received from the server, an SMS delegate must be set.

*Swift Code:*
```swift
import CPaaSSDK

class AppModel: CPSmsDelegate {

    init() {
        self.cpaas.smsService!.delegate = self
    }

    // ... application model methods ... //

    // MARK: SmsDelegate methods
    func inboundMessageReceived(message:CPInboundMessage) {
        // save inbound message to the application model
        self.saveMessage(message)
    }

    func deliveryStatusChanged(status: CPMessageStatus) {
        // update message delivery status in application model
        self.updateMessage(status)
    }

    func outboundMessageSent(message: CPOutboundMessage) {
        // save outbound message to the application model
        self.saveMessage(message)
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

-(id)init {
    self = [super init];
    [self initProvider];

    // initialize the sms service delegate
    self.cpaas.smsService!.delegate = self;
}

// ... application model methods ... //

#pragma mark SmsDelegate methods

- (void)inboundMessageReceivedWithMessage:(CPInboundMessage * _Nonnull)message {
    // save inbound message to the application model
    [self saveMessage: message];
}

- (void)deliveryStatusChangedWithMessage:(CPOutboundMessage *)message {
    // update message delivery status in application model
    [self updateMessageWithStatus: status];
}

- (void)outboundMessageSentWithMessage:(CPOutboundMessage * _Nonnull)message {
    // save outbound message to the application model
    [self saveMessage: message];
}
@end
```

## Fetching SMS Messages
SMS messages are grouped into conversations with other users. A list of established conversations can be fetched from the server. For each conversation, the messages within that conversation may be fetched.

### Fetch all conversations from the server

Retrieve a list of all conversation objects from the server. Use this list to populate the application model with existing conversations.

*Swift Code:*
```swift
import CPaaSSDK

self.cpaas.smsService!.fetchConversations(){
    (error :CPError?, fetchResult: FetchResult?) -> Void in
    if (error == nil) {
        for conversation in fetchResult.result {
            // save conversations to application model
        }
    } else {
        // an error occurred
        print("Couldn't fetch conversations: \(error.localizedDescription)");
    }
}];
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

[self.cpaas.smsService fetchConversationsWithCompletion:^(CPError * _Nullable error, FetchResult * _Nonnull fetchResult) {
    if (error == nil) {
        for (CPConversation* conversation in fetchResult.result) {
            // save conversations to application model
        }
    } else {
        // an error occurred
        NSLog(@"Couldn't fetch conversations: %@", error.localizedDescription);
    }
}];
```

### Fetch conversations by criteria from the server

Retrieve a list of relevant conversation objects from the server. Using FetchCriteria, users can filter the participant, sender phone number and options.
Options filter has provided search parameters; max, last message time and is a new message.

*Swift Code:*
```swift
import CPaaSSDK

let criteria : FetchCriteria = FetchCriteria()
criteria.fetchOptions = FetchOptions()
criteria.fetchOptions.max = 10;

self.cpaas.smsService.fetchConversations(criteria:FetchCriteria){
    (error, fetchResult) -> Void in {
    if (error == nil) {
        for (CPConversation* conversation in fetchResult.result) {
            // save conversations to application model
			// Check if the result has more items (fetchResult.hasNext)
        }
    } else {
        // an error occurred
        print(@"Couldn't fetch conversations: %@", error.localizedDescription);
    }
}];
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

FetchCriteria *criteria = [[FetchCriteria alloc] init];
criteria.fetchOptions = [[FetchOptions alloc] init];
criteria.fetchOptions.max = 10;

[self.cpaas.smsService fetchConversationsWithFetchCriteria:criteria completion:^(CPError * _Nullable error, FetchResult  * _Nullable fetchResult) {
    if (error == nil) {
        for (CPConversation* conversation in fetchResult.result) {
            // save conversations to application model
        }
    } else {
        // an error occurred
        NSLog(@"Couldn't fetch conversations: %@", error.localizedDescription);
    }
}];
```

### Fetch all messages from the server

Retrieve a list of all message objects from the server.

*Swift Code:*
```swift
import CPaaSSDK

let destination: String = "18882223333"
if let conversation = self.getSavedConversation(withParticipant: destination) {
    conversation?.fetchMessages() {
        (error: CPError?, fetchResult:FetchResult?) -> Void in
        if (error == nil){
            // update the application model
            self.saveMessages(messages)
        } else {
          // an error occurred
          print("Couldn't fetch messages: \(error!.localizedDescription)");
        }
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

NSString* destination = @"18882223333";
CPConversation* conversation = [self getSavedConversationWithParticpant: destination];
[conversation fetchMessagesWithCompletion:^(CPError * _Nullable error, FetchResult * _Nullable fetchResult) {
    if (error == nil) {
        for (CPMessage* message in fetchResult.result) {
            // update the application model
        }
    } else {
        // an error occurred
        NSLog(@"Couldn't fetch messages: %@", error.localizedDescription);
    }
}];
```

### Fetch a number of messages from the server

Retrieve a list of message objects by filter from the server.

*Swift Code:*
```swift
import CPaaSSDK

let destination: String = "18882223333"
let options : FetchOptions = FetchOptions()
options.max = 10
if let conversation = self.getSavedConversation(withParticipant: destination) {
    conversation?.fetchMessages(options:options) {
        (error: CPError?, fetchResult:FetchResult?) -> Void in
        if (error == nil){
            // update the application model
            self.saveMessages(messages)
        } else {
          // an error occurred
          print("Couldn't fetch messages: \(error!.localizedDescription)");
        }
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

NSString* destination = @"18882223333";
CPConversation* conversation = [self getSavedConversationWithParticpant: destination];

FetchOptions * options = [[FetchOptions alloc] init];
options.max = 10;

[conversation fetchMessagesWithFetchOptions:options completion:^(CPError * _Nullable error, FetchResult * _Nullable fetchResult) {
    if (error == nil) {
      for (CPMessage* message in fetchResult.result) {
          // update the application model
      }
    } else {
        // an error occurred
        NSLog(@"Couldn't fetch messages: %@", error.localizedDescription);
    }
}];
```

## Sending SMS Messages
The Mobile SDK provides the ability to send SMS text messages.

### Send an SMS message to a single destination.

Send an SMS message from a local address specified by the SMS Service within a list of available numbers to a single destination specified as the conversation participant with message content specified by withText. An implementer should specify a completion block to handle any response whether error or successful response.

*Swift Code:*
```swift
import CPaaSSDK

let destination: String = "18882223333"
let localAddressList = self.cpaas.smsService!.localAddressList
let localAddress = //choose one address from the list above
if let conversation = self.cpaas.smsService!.createConversation(fromAddress: localAddress, withParticipant: destination) {

    // save conversation to application model
    self.saveConversation(conversation)

    let msg = self.cpaas.smsService!.createMessage(withText: "Hello world")
    conversation.send(message: msg){
        (error, newMessage) in
        if error != nil {
            print("SmsService.send failed. destination: \(destination). Error desc:\(error!.description)")
        } else {
            print("SMS message sent to \(destination)!")
            // save message to application model
            self.saveMessage(newMessage)
        }
    }

}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

[self.cpaas.smsService setSenderWithName:@"User Name" andAddress:@"user@domain.com"];

NSString* destination = @"18882223333";
NSArray * localAddressList = self.cpaas.smsService.localAddressList;
NSString * localAddress = //choose one address from the list above
Conversation* conversation = [self.cpaas.smsService  createConversationFromAddress:localAddress withParticipant:destination];

// save conversation to application model
[self saveConversation: conversation];

CPOutboundMessage* msg = [conversation createMessageWithText:@"Hello world"];

[conversation sendWithMessage:msg :
    ^(CPError * _Nullable error, CPOutboundMessage * _Nullable newMessage){
        if (error != nil) {
            NSLog(@"SmsService.send failed. Error desc:%@", destination , error.localizedDescription);
        } else {
            NSLog(@"SMS message sent to %@!", destination);
            // save message to application model
            [self saveMessage:newMessage];
        }
    }
];
```

## Receiving SMS Messages
Receiving SMS messages is an event driven process for new messages. See the application delegate method [**inboundMessageReceived**](#implement-and-set-smsdelegate) from the initialization procedure for receiving new SMS messages via notifications.
