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

#import <UIKit/UIKit.h>

//! Project version number for NotificationEngine.
FOUNDATION_EXPORT double NotificationEngineVersionNumber;

//! Project version string for NotificationEngine.
FOUNDATION_EXPORT const unsigned char NotificationEngineVersionString[];

#import <NotificationEngine/SMMessageReceiver.h>
#import <NotificationEngine/CPNotificationEngineDelegate.h>

#import <NotificationEngine/SMTopicNameDefs.h>
#import <NotificationEngine/SMEventTypeDefs.h>
#import <NotificationEngine/SMNotificationMessage.h>
#import <NotificationEngine/SMIMNotificationParams.h>
#import <NotificationEngine/SMIMResponseParams.h>
#import <NotificationEngine/SMNotificationParamsFactory.h>
#import <NotificationEngine/SMPresenceWatcherNotificationParams.h>

@class CPUserInfo;
@class CPNotificationComponent;
@class SMNotificationMessage;
/**
 *  Utility class for NotificationEngine.
 **/
@interface CPNotificationEngine : NSObject {
    CPLogManager *logManager;
}

- (id)initWithUserInfo:(CPUserInfo *)userInfo;

/**
 * Static singleton instance method
 *
 * @return shared singleton instance
 */
+ (instancetype)getInstance;

/**
 * Sets static singleton instance method
 *
 */
+ (void) setInstance:(CPNotificationEngine *)instance;

/**
 * Opens the connection to SPiDR server
 **/
-(BOOL) start;

/**
 * Closes socket connection from SPiDR server
 **/
-(BOOL) stop;

/**
 * Broadcasts message to subscribers of  topic
 *
 * @param message data that will be published
 * @param topic name of the message channel
 */
+ (void) publishMessage:(SMNotificationMessage *) message toTopic:(NSString *) topic;

/**
 * Broadcasts message to subscribers
 *
 * @param messageData message data that will be published
 * @param completion Completion Block if message has PushCallBack
 */
+ (void) onNotificationMessageReceived:(NSData *) messageData completion:(PushCallback)completion;

/**
* Broadcasts message to subscribers
*
* @param messageData message data that will be published
* @param comingType Notification Coming Type SMNotificationComingType
* @param completion Completion Block if message has PushCallBack
*/
+ (void) onNotificationMessageReceived:(NSData *) messageData comingType:(SMNotificationComingType)comingType completion:(PushCallback)completion;

/**
 * Checks socket connection
 **/
-(BOOL)isConnected;

/**
 * Returns disconnected time duration in seconds
 */
+ (NSTimeInterval) disconnectedTime;

@end
