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

@class SMNotificationMessage;

@protocol CPNotificationEngineDelegate<NSObject>

/**
 * NotificationHandleDelegate function
 * This method will be triggered when a new message is received
 * @param notificationMessage received message
 **/
- (void) notificationReceived:(SMNotificationMessage *) notificationMessage;
@end

