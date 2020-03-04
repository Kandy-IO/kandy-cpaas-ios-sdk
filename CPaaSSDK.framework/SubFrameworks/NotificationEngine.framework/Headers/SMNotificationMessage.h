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

#import <Foundation/Foundation.h>
#import "SMNotificationParamsDelegate.h"
@class CPError;

typedef void(^PushCallback)(CPError* _Nullable error);

typedef NS_ENUM(NSInteger, SMNotificationComingType) {
    NOTIFICATION_COMING_PUSH,
    NOTIFICATION_COMING_WS,
};

/**
 *  Utility class for NotificationMessage.
 * Global notification message object which includes the data of notifications coming from socket.
 **/
@interface SMNotificationMessage : NSObject <SMNotificationParamsDelegate, NSCopying>
/**
 * Notification eventType.
 **/
@property(nonatomic, strong) NSString * eventType;
/**
 * Notification notificationType.
 **/
@property(nonatomic, strong) NSString * notificationType;
/**
 * Channel Id for notification.
 **/
//@property(nonatomic, strong) NSString * notificationChannelId;
/**
 * active.
 **/
//@property(nonatomic, strong) NSString * active;
/**
 * time.
 **/
//@property(nonatomic, strong) NSString * time;
/**
 * statusCode.
 **/
//@property(nonatomic, retain) NSNumber * statusCode;
/**
 * eventId.
 **/
@property(nonatomic, strong) NSString * eventId;
/**
 * params.
 **/
@property(nonatomic, strong) PushCallback completionCallback;
@property(nonatomic, strong) NSMutableDictionary * params;
@property(nonatomic) SMNotificationComingType notificationComingType;

@end
