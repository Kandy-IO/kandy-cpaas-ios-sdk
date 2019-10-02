/*
 * Copyright © 2014 GENBAND. All Rights Reserved.
 *
 * GENBAND CONFIDENTIAL. All information, copyrights, trade secrets
 * and other intellectual property rights, contained herein are the property
 * of GENBAND. This document is strictly confidential and must not be
 * copied, accessed, disclosed or used in any manner, in whole or in part,
 * without GENBAND's express written authorization.
 *
 */


// SPiDR events for Call
#define EVENT_TYPE_CALL_NOTIFICATION @"wrtcsEventNotification"
#define EVENT_TYPE_ANSWER_CALL @"wrtcsAnswerNotification"
#define EVENT_TYPE_INVITATION_CALL @"wrtcsSessionInvitationNotification"
#define EVENT_TYPE_ACCEPT_CALL @"wrtcsAcceptanceNotification"
#define EVENT_TYPE_ICE_CANDIDATE @"wrtcsIceNotification"
#define EVENT_TYPE_IP_CHANGE @"ipChanged"
#define EVENT_TYPE_OFFER @"wrtcsOfferNotification"

#define EVENT_TYPE_RINGING @"Ringing"
#define EVENT_TYPE_CALL_END @"SessionEnded"
#define EVENT_TYPE_CALL_CANCEL @"Cancelled"
#define EVENT_TYPE_TRANSFER_COMPLETED @"TransferCompleted"
#define EVENT_TYPE_TRANSFER_FAILED @"TransferFailed"

// SPiDR events for IM
#define EVENT_TYPE_IM @"IM"
#define EVENT_TYPE_IM_RESPONSE @"IMResponse"


// SPiDR events for Presence
#define EVENT_TYPE_PRESENCE_WATCHER @"presenceWatcher"


//Application State Events
#define EVENT_TYPE_BACKGROUND @"enteredBackGround";
#define EVENT_TYPE_FOREGROUND @"comesForeGround";

#define EVENT_TYPE_NOTIFICATION_DISCONNECTED @"notificationDisconnected"
#define EVENT_TYPE_NOTIFICATION_CONNECTED @"notificationConnected"

// Registration Service Events
#define EVENT_TYPE_DEVICE_REGISTER_GONE @"gone"
#define EVENT_TYPE_NOTIFICATION_PING @"ping"
#define EVENT_TYPE_INTERNAL_ERROR @"internalError"
#define EVENT_TYPE_CHANNELLIFETIME_REFRESHED @"channelLifetimeRefreshed"

// SMS Service Events
#define EVENT_TYPE_SMS_INBOUND_MESSAGE_RECEIVED @"inboundSMSMessageNotification"
#define EVENT_TYPE_SMS_OUTBOUND_MESSAGE_SENT @"outboundSMSMessageNotification"
#define EVENT_TYPE_SMS_OUTBOUND_DELIVERY_STATUS @"deliveryInfoNotification"

// Chat Service Events
#define EVENT_TYPE_CHAT_MESSAGE_NOTIFY @"chatMessageNotification"
#define EVENT_TYPE_CHAT_STATUS_NOTIFY @"chatMessageStatusNotification"
#define EVENT_TYPE_CHAT_MULTIMEDIA_NOTIFY @"multimediaChatMessageNotification"
#define EVENT_TYPE_CHAT_GROUP_INVITATION_NOTIFY @"groupChatSessionInvitationNotification"
#define EVENT_TYPE_CHAT_GROUP_PARTICIPANT_STATUS_NOTIFY @"chatParticipantStatusNotification"
#define EVENT_TYPE_CHAT_GROUP_NOTIFY @"chatEventNotification"

// Presence Service Events
#define EVENT_TYPE_PRESENCE_NOTIFY @"presenceNotification"
#define EVENT_TYPE_PRESENCE_LIST_NOTIFY @"presenceListNotification"

// Application State Change Events
#define EVENT_TYPE_APPLICATION_WILL_RESIGN_ACTIVE @"applicationWillResignActive"
#define EVENT_TYPE_APPLICATION_DID_BECOME_ACTIVE @"applicationDidBecomeActive"
#define EVENT_TYPE_APPLICATION_WILL_ENTER_FOREGROUND @"applicationWillEnterForeGround"
#define EVENT_TYPE_APPLICATION_WILL_ENTER_BACKGROUND @"applicationWillEnterBackground"
#define EVENT_TYPE_APPLICATION_WILL_TERMINATE @"applicationWillTerminate"

// Connection Reachibityy Change Events
#define EVENT_TYPE_REACHIBILITY_RESUCCESS @"reachibiltyRessuccess"


// Push Message Injetion Events
#define EVENT_TYPE_CPAAS_PUSH_MESSAGE @"cpaasPushMessage"

