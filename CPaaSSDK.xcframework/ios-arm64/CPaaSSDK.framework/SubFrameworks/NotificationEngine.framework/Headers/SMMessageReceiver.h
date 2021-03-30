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
#import "CPNotificationEngineDelegate.h"

@class CPLogManager;

#define NOTIFICATION_MESSAGE_KEY @"notificationMessage"
/**
 * Abstract class for Message Receiving from Notification Engine
 * Classes in Service should extend this class for Message Receiving from NotificationEngine
 */
@interface SMMessageReceiver : NSObject <CPNotificationEngineDelegate>

@property(strong, nonatomic) CPLogManager *logManager;

@property (strong, nonatomic) NSString *TAG;

// Name of the topic (message channel)
@property(strong, nonatomic) NSString *_topic;

// Names of the topic (message channel)
@property(strong, nonatomic) NSArray *topics;

//Service whose methods will be called
@property (weak, nonatomic) id service;

- (id) initWithService:(id)service;

/**
 * Subscribes to Topic (Mesage Channel)
 */
- (void) subscribe;

/**
 * Unsubscribes from Topic (Message Channel)
 */
-(void) unsubsribe;

@end
