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
#import "CPCallDelegate.h"

/**
 *  Call object, which is used for incoming calls.
 * - Since: 1.0.0
 */
@protocol CPIncomingCallDelegate <CPCallDelegate>

/**
 *  Accepts the incoming call
 * @param isVideoEnabled indicates if video is allowed or not
 * - Since: 1.0.0
 */
- (void) acceptCall: (BOOL)isVideoEnabled;

/**
 *  Ignores the incoming call
 * - Since: 1.0.0
 */
- (void) ignoreCall;

/**
 *  Rejects the incoming call
 * - Since: 1.0.0
 */
- (void) rejectCall;

@end
