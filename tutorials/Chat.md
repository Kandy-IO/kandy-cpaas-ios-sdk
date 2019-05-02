---
  topics:
  - title: Fetching Chat Messages
    body: In this section you will learn how to fetch chat messages from $KANDY$ using $KANDY$ Mobile SDK.
  - title: Sending Chat Messages
    body: In this section you will learn how to send a chat message using $KANDY$ Mobile SDK.
  - title: Receiving Chat Messages
    body: In this section you will learn how to receive a chat message using $KANDY$ Mobile SDK.
  - title: Deleting Chat Messages
    body: In this section you will learn how to delete a chat message using $KANDY$ Mobile SDK.
  - title: Group Chat
    body: In this section you will learn how to manage group chat conversations using $KANDY$ Mobile SDK.
---
# Chat

Chat messaging is managed by the Chat Service which can be called from the `CPaaS` instance. In order to receive and send events, the `CPaaS` instance should be connected first. To see how to connect and set configurations, check **Login** and **Configurations** sections.

### Initialize the Chat Service

In order to use the Chat service, the service provider object must be properly initialized. When properly initialized, the application will be registered to receive Chat notifications from the server.

*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

func initProvider() {
    // select the services that will be used by the application. Specify .chat for Chat service
    // to be enabled. If the application should receive notifications via the APN push service
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

@interface AppModel : NSObject <CPChatDelegate>
@end

@implementation AppModel

- (void) initProvider {
    // select the services that will be used by the application. Specify '.chat' for Chat service
    // to be enabled. If the application should receive notifications via the APN push service
    // set push parameter to 'true'.
    NSArray<CPServiceInfo*>* cpaasServices= @[[CPServiceInfo buildWithType:CPServiceTypeSms push:true],
                              				[CPServiceInfo buildWithType:CPServiceTypeChat push:true]];

    // initialize a CPaaS service provider object with the
    // services that it should provide
    self.cpaas = [[CPaaS alloc] initWithServices: cpaasServices];
 }
```

### Implement and Set ChatDelegate

In order for the Mobile SDK to notify the application of notifications received from the server, a Chat delegate must be set.

*Swift Code:*
```swift
import CPaaSSDK

class AppModel: CPChatDelegate {

    init() {
        self.cpaas.chatService!.delegate = self
    }

	// ... application model methods ... //

    // MARK: ChatDelegate methods
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

    func isComposing(message: CPIsComposingMessage) {
        if message.active {
            print("\(message.sender) is typing...")
        } else {
            print("\(message.sender) stopped typing.")			}
        }
	}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

-(id)init {
    self = [super init];
    [self initProvider];

    // initialize the chat service delegate
    self.cpaas.chatService!.delegate = self;
}

// ... application model methods ... //

#pragma mark ChatDelegate methods

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

- (void)isComposingWithMessage:(CPIsComposingMessage * _Nonnull)message {
    if (message.active) {
        NSLog(@"%@ is typing...", message.sender);
    } else {
        NSLog(@"%@ stopped typing.", message.sender);
    }
}

@end
```

## Fetching Chat Messages
Chat messages are grouped into conversations with other users. A list of established conversations can be fetched from the server. For each conversation, the messages within that conversation may be fetched.

### Fetch all conversations from the server

Retrieve a list of all conversation objects from the server. Use this list to populate the application model with existing conversations.

*Swift Code:*
```swift
import CPaaSSDK

self.cpaas.chatService!.fetchConversations(){
    (error, conversations) -> Void in
    if (error == nil){
        // save conversations to application model
        self.saveConversationList(conversations)
    } else {
        // an error occurred
        print("Couldn't fetch conversations: \(error!.localizedDescription)")
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

[self.cpaas.chatService fetchConversationsWithCompletion:^(CPError * _Nullable error, NSArray<CPConversation *> * _Nonnull newConversations) {
    if (error == nil) {
        // save conversations to application model
        [self saveConversationList: conversations];
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

let destination: String = "user_b@domain.com"
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

NSString* destination = @"user_b@domain.com";
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

let destination: String = "user_b@domain.com"
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

NSString* destination = @"user_b@domain.com";
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

## Sending Chat Messages
The Mobile SDK provides the ability to send text messages as well as messages with file attachments.

### Send a Chat message to a single destination

Send a Chat message to a single destination specified as the conversation participant with message content specified by withText. An implementer should specify a completion block to handle any response whether error or successful response.

*Swift Code:*
```swift
import CPaaSSDK

let destination: String = "user_b@domain.com"
if let conversation = self.cpaas.chatService!.createConversation(withParticipant: destination) {

    // save conversation to application model
    self.saveConversation(conversation)

    conversation.send(withText: "Hello world"){
        (error, newMessage) in
        if error != nil {
            print("ChatService.send failed. destination: \(destination).Error desc:\(error!.localizedDescription)")
        } else {
            print("Chat message sent to \(destination)!")
            // save message to application model
            self.saveMessage(newMessage)
        }
    }

}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

NSString* destination = @"user_b@domain.com";
CPConversation* conversation = [self.cpaas.chatService  createConversationWithParticipant:destination];

// save conversation to application model
[self saveConversation: conversation];

[conversation sendWithText:@"Hello world" :
    ^(CPError * _Nullable error, CPOutboundMessage * _Nullable newMessage){
        if (error != nil) {
            NSLog(@"ChatService.send failed. destination %@. Error desc:%@", destination , error.description);
        } else {
            NSLog(@"Chat message sent to %@!", destination);
            // save message to application model
            [self saveMessage:newMessage];
        }
    }
];
```

### Send a Chat message with a file attachment

Send a Chat message with a file attachment to a single destination specified as the conversation participant with message content specified by "text" and attachment specified by "withFile". An implementer may specify a code block for indicating progress to the user. An implementer should specify a completion block to handle any response whether error or successful response.

*Swift Code:*
```swift
import CPaaSSDK

let destination: String = "user_b@domain.com"
if let conversation = self.cpaas.chatService!.createConversation(withParticipant: destination) {

    // save conversation to application model
    self.saveConversation(conversation)

    // let user pick a file
    let userFile = self.chooseFile()

    self.uploadHandle = conversation.send(text: "Hello world", withFile: userFile,
	 progress: {
		(bytesSent, totalBytes) in
		self.updateProgressIndicator(bytesSent, totalBytes)
	 },
	 completion: {
        (error, newMessage) in
        if error != nil {
            print("ChatService.send failed. destination: \(destination). Error desc:\(error!.localizedDescription)")
        } else {
            print("Chat message sent to \(destination)!")
            // save message to application model
            self.saveMessage(newMessage)
        }
    }

}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

NSString* destination = @"user_b@domain.com";
CPConversation* conversation = [self.cpaas.chatService  createConversationWithParticipant:destination];

// save conversation to application model
[self saveConversation: conversation];

// let user pick a file
NSURL* userFile = [self chooseFile];

[conversation sendWithText:@"Hello world", withFile: userFile,
 progress:
	^(NSInteger bytesTx, NSInteger totalTx){
		[self updateProgressIndicatorBytes: bytesTx ofTotal: totalTx];
 	},
 completion:
    ^(CPError * _Nullable error, CPOutboundMessage * _Nullable newMessage){
        if (error != nil) {
            NSLog(@"ChatService.send failed. destination %@. Error desc:%@", destination , error.localizedDescription);
        } else {
            NSLog(@"Chat message sent to %@!", destination);
            // save message to application model
            [self saveMessage:newMessage];
        }
    }
];
```

### Download a file attachment from the server

After receiving or fetching a chat message with an attachment download the attachment file. The application may implement a progress handling code block for the purposes of indicating download progress to the user. An implementer should appropriately handle the downloaded file in the completion handler.

*Swift Code:*
```swift
import CPaaSSDK

if let attachment = message.files.first {
	// Get destination to save the file
	let localFileUrl = self.getLocalFileName()
	let remoteFileUrl = URL(string: attachment.link)

	// cast the service as ChatService to access methods specific to chat service
	let chatService = self.cpaas.chatService as! ChatService

	self.downloadHandle = chatService.download(fromUrl: remoteFileUrl, toFile: localFileUrl,
		progress: { (bytesReceived, totalBytes) in
			self.updateProgressIndicator(bytesReceived, totalBytes)
		},
		completion: { (error, fileUrl) in
          if error != nil {
              print("ChatService.download failed. Error desc:\(error!.localizedDescription)")
          } else {
              print("Downloaded attachment to \(fileUrl)!")
              // use the file
              self.showFile(fileUrl)
          }
		}
	)
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

CPFilePart* attachment = [message.files firstObject];
if (attachment != nil) {
	// Get destination to save the file
	NSURL* localFileUrl = [self getLocalFileName];
	NSURL* remoteFileUrl = [NSURL URLWithString:attachment.link];

	// cast the service as ChatService to access methods specific to chat service
	CPChatService* chatService = (CPChatService*)self.cpaas.chatService;

	self.downloadHandle = [chatService downloadFromUrl: remoteFileUrl, toFile: localFileUrl,
		progress: ^(NSInteger bytesReceived, NSInteger totalBytes) {
			[self updateProgressIndicatorBytes: bytesReceived ofTotal: totalBytes];
		},
		completion: ^(CPError * _Nullable error, NSURL * _Nullable fileUrl) {
	        if (error != nil) {
	            NSLog(@"ChatService.download failed. Error desc:%@", error.description);
	        } else {
	            NSLog(@"Downloaded attachment to %@", fileUrl);
	            // use the file
	            [self showFile: fileUrl];
	        }
		}
	)

}
```

## Receiving Chat Messages
Receiving chat messages is an even driven process for new messages and an application requested event for message history. See the application delegate method [**inboundMessageReceived**](#implement-and-set-chatdelegate) from the initialization procedure for receiving new chat messages via notifications. See the Conversation [**fetchMessages**](#fetching-chat-messages) method from the fetching chat messages procedure.

## Deleting Chat Messages
An application may find it necessary to delete historical chat conversations. Messages can be deleted individually or an entire conversation may be deleted.

### Delete a conversation from the server

Delete an entire message thread from the server. This method will delete all messages associated with a particular participant.

*Swift Code:*
```swift
import CPaaSSDK

let destination: String = "user_b@domain.com"
self.cpaas.chatService!.deleteConversation(withParticipant: destination) {
    (error) -> Void in
    if (error == nil){
        // remove the conversation from the application model
        self.removeConversation(withParticipant: destination)
    } else {
        // an error occurred
        print("Couldn't delete conversation: \(error!.localizedDescription)")
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

NSString* destination = @"user_b@domain.com";
[self.cpaas.chatService deleteConversationWithParticipant:destination completion:^(CPError * _Nullable error) {
    if (error == nil) {
        // remove the conversation from the application model
        [self removeConversationWithParticipant: destination];
    } else {
        // an error occurred
        NSLog(@"Couldn't delete conversation: %@", error.localizedDescription);
    }
}];
```

### Delete a message from the server

Delete a single message from a message thread. Each message has a unique identifier which can be used for deleting the message.

*Swift Code:*
```swift
import CPaaSSDK

let destination: String = "user_b@domain.com"
let messageID: String = messageToDelete.messageID
if let conversation = self.getSavedConversation(withParticipant: destination) {
    conversation?.deleteMessage(withId: messageID) {
        (error) -> Void in
        if (error == nil){
            // remove the message from the application model
            self.removeMessage(withId: messageID)
        } else {
            // an error occurred
            print("Couldn't delete message: \(error!.localizedDescription)")
        }
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

NSString* destination = @"user_b@domain.com";
NSString* messageID = messageToDelete.messageID;
Conversation* conversation = [self getConversationWithParticipant:destination];
[conversation deleteMessageWithId:messageID completion:^(CPError * _Nullable error) {
    if (error == nil) {
        // remove the message from the application model
        [self removeMessageWithId: messageID];
    } else {
        // an error occurred
        NSLog(@"Couldn't delete message: %@", error.localizedDescription);
    }
}];
```

## Group Chat
Group Chat messaging is managed by the Chat Service which can be called from the `CPaaS` instance.In order to receive and send events, the `CPaaS` instance should be connected first. To see how to connect and set configurations, check **Login** and **Configurations** sections.



### Receiving joined groups list
After the app succesfully connected to backend and authenticated, already joined groups can be pulled from backend


*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

func fetchGroupConversations(_ completion: @escaping (_ error: CPError?) -> () ) {

    if  refreshGroups { //Variable to check refreshing groups(Optional)
        let chatService = self.service as! CPChatService  //Initiated chat service
        chatService.fetchGroupConversations() {
        (error, newConversations) in
            if error == nil {
                // Conversations fetched successfully
            }
            completion(error)
        }
    }

}

```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

- (void) fetchGroupConversationsWithCompletion:(void (^)(CPError * _Nullable))completion {
    CPChatService* chatService = (CPChatService*)self.service;
    [chatService fetchGroupConversationsWithCompletion:^(CPError * _Nullable error, NSArray<CPConversation *> * _Nonnull newConversations) {
        if (error == nil) {
            // Conversations fetched successfully
        }
        completion(error);
    }];
}
```

### Receiving joined groups icons
After successfully receiving the list of groups which user has joined, the app can download the icons of the related groups from backend server


*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

func downloadGroupChatIcon(remote:URL, local:URL, completion: @escaping DownloadCompletionBlock) {
    let chatService = self.service as! ChatService
    chatService.download(fromUrl: remote, toFile: local,progress: { (bytesRx, totalRx) in }, // No need to track progress
        completion: completion
    )
}

```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

- (void) downloadIconFromRemote:(NSURL*)remote toLocal:(NSURL*)local completion:(void (^ _Nonnull)(CPError * _Nullable, NSURL * _Nullable))completion {
    CPChatService* chatService = (CPChatService*)self.service;
    [chatService downloadFromUrl:remote toFile:local progress:^(NSInteger x, NSInteger y) {} completion:completion];
}
```


### Upload Group Chat Image
If the creator of the group wants to add an image before creating the group, the image file needs to be uploaded to server by using chat service.

*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

chatService.upload(withFile: imageURL, progress: { (_, _) in }) {
(error, filePart) in
    var remoteURL:URL? = nil
    if let fileLink = filePart?.link {
        remoteURL = URL(string: fileLink)
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

[chatService uploadWithFile:image progress:^(NSInteger x, NSInteger y) {} completion:^(CPError * _Nullable error, FilePart * _Nullable filePart) {
    NSURL* remoteURL = nil;
    if (filePart != nil) {
        NSString* fileLink = filePart.link;
        remoteURL = [NSURL URLWithString:fileLink];
    }
}];
```


### Create a Chat Group
When group name and subject is decided, createGroupChat method of ChatGroup service must be called in order to create the groupchat and invite the participants.
Upon succesfull creation of group, user creates the group conversation

*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

let address = //Address is the userId of the participant
let participant = CPChatGroupParticipant(address: address!, admin: isAdmin)
participants.append(participant) //Participants array is filled with ChatGroupParticipant objects

chatService.createChatGroup(name: self.groupNameText.text!, type: "closed", subject: self.subjectText.text, image: self.inProgressChatIcon, participants: participants) {
(error, newChatGroup) in
    if let newChatGroup = newChatGroup {
        self.chatGroup = newChatGroup //chatGroup object is initialized here
        self.chatGroups[chatGroup.name] = chatGroup
        // also create group conversation
        if let conversation = chatService.createConversation(withGroup: chatGroup){
            self.groupConversations[chatGroup.groupID!] = ConversationModel(conversation, self)
        }
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

[chatService createChatGroupWithName:name type:@"closed" subject:subject image:remoteURL participants:participants completion:^(CPError * _Nullable error, ChatGroup * _Nullable newChatGroup) {
    // Add new chat group to local collection
    if (newChatGroup != nil) {
        newChatGroup.icon = [UIImage imageWithContentsOfFile:image.path];
        self.chatGroups[newChatGroup.name] = newChatGroup;
    }
    completion(error, newChatGroup);
}];
```



### Add Participants To Already Created Group
When the admin priviliged user wanted to add member to a current group, groupChat object's add method can be called. GroupChat object is initialized by Mobile SDK when createGroupChat method is called

*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

let address = //Address is the userId of the participant
let participant = ChatGroupParticipant(address: address!, admin: isAdmin)
self.chatGroup?.add(participant: participant) { (error) in
    if error == nil {
        // Success case
    } else {
        // Error case
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

NSString * address;
CPChatGroupParticipant * participant = [[CPChatGroupParticipant alloc] initWithAddress:address admin:isAdmin];
[chatGroup addWithParticipant:participant completion:^(CPError * _Nullable error) {
    if (error) {
        // Error case
    } else {
        // Success case
    }
}];
```

### Remove Participants From Already Created Group
When the admin priviliged user wants to remove a member from a current group, groupChat object's remove method must be called.
GroupChat object is initialized by Mobile SDK when createGroupChat method is called

*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

// attempt delete from backend server
let index = 2; //Index of member to remove from participants list
let memberArray = Array(self.chatGroup!.participants)
let member = memberArray[index];
self.chatGroup?.remove(participant: member) {
(error) in
    if error == nil {
        //Success case
    } else {
        //Error case
    }
}

```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

// attempt delete from backend server
NSUInteger index = 2;
NSArray *memberArray = newChatGroup.participants.allObjects;
ChatGroupParticipant * member = [memberArray objectAtIndex:index];
[chatGroup removeWithParticipant:participant completion:^(CPError * _Nullable error) {
    if (error) {
        // Error case
    } else {
        // Success case
    }
}];
```

### Delete chat group permanently
If an admin privileged user wants to delete the chat group, deleteChatGroup method must be called

*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

let chatService = self.service as! CPChatService
chatService.deleteChatGroup(groupID: <GROUP_ID>) { (error) in
    if error == nil {
        chatGroup.icon = nil
        self.chatGroups.removeValue(forKey: name)
    }
    // This applications chooses to also delete chat conversation for this group
    guard let conversation = chatGroup.conversation?.conversation else {
        completion(error)
        return
    }
    chatService.delete(conversation: conversation) { (deleteConversationError) in
        if deleteConversationError == nil {
            self.groupConversations.removeValue(forKey: chatGroup.groupID!)
        }
        completion(deleteConversationError)
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

[chatService deleteWithConversation:<GROUP_ID> completion:^(CPError * _Nullable deleteConversationError) {
    if (deleteConversationError == nil) {
        [self.groupConversations removeObjectForKey:chatGroup.groupID];
    }
    completion(deleteConversationError);
}];
```

### Receiving invitations
When the current user added to a group, this delegate method will be triggered.
Invitation parameter contains an invitation object that contains a copy of the group to be joined. The invitation object has methods for accept and decline.


*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

func groupInvitationReceived(invitation:CPChatGroupInvitation) {
    if (userWantsToAccept) {
        invitation.accept() { error in
            //If there is no error that means invitation accepted succesfully
        }
    } else {
        invitation.decline() { error in
        //If there is no error that means invitation declined succesfully
        }
    }
}

```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

- (void)groupInvitationReceivedWithInvitation:(CPChatGroupInvitation * _Nonnull)invitation {
    if (userWantsToAccept) {
        [invitation accept ^{ (error) in
            //If there is no error that means invitation accepted succesfully
        }];
    } else {
        [invitation decline ^{ (error) in
            //If there is no error that means invitation declined succesfully
        }];
    }
}
```


### Accept invitation from a group
When a user is added to a group an invitation message is sent. Upon receiving the invitation, user either accepts it and joins the group or decline it remove self from the group.
For accepting the invitation call the Mobile SDK group chat accept method

*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

chatGroup.accept { (error) in
    ChatHandler.sharedInstance.fetchChatGroup(withKey: group.groupID!) { (error, chatGroup) in //Receive the groups after accept
        DispatchQueue.main.async {
            //Do the related reload stuff
        }
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

[chatGroup acceptWithCompletion:^(CPError * _Nullable error) {
    [[ChatHandler getInstance] fetchChatGroupWithKey:group.groupID completion:^(CPError * _Nullable error, ChatGroup * _Nullable chatGroup) { //Receive the groups
        dispatch_async(dispatch_get_main_queue(), ^{
            //Do the related reload stuff
        });
    }];
}];

```

### Decline invitation from a group
User can decline the invitation, then user will be removed from the group.

*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

chatGroup.decline{
(error) in
    if error == nil {
        self.chatGroups.removeValue(forKey: chatGroup.name) //remove the group from your list
    }
    completion(error)
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

[chatGroup declineWithCompletion:^(CPError * _Nullable error) {
    if (error == nil) {
        [self.chatGroups removeObjectForKey:chatGroup.name]; //remove the group from your list
    }
    completion(error);
}];

```


### Receiving group participants status
When a new user added to a group or removed from group, or any other status update happened about a group participant. This method will be trigered
Participants parameter contains an array of chat group members that have updated status


*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

func groupParticipantStatus(participants:[ChatGroupParticipant]) {
     //Get the info of the participants
}

```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

- (void)groupParticipantStatusWithParticipants:(NSArray<CPChatGroupParticipant *> * _Nonnull)participants {
    //Get the info of the participants
}

```


### Group chat ended
This delegate method is called when a group chat has ended. groupID parameter containts  the groupID of the group chat that ended.

*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

func groupChatEnded(groupID:String) {

}

```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

- (void)groupChatEndedWithGroupID:(NSString * _Nonnull)groupID {

}

```
