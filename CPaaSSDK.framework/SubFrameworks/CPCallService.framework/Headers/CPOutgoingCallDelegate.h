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
 * Call object, which is used for outgoing calls.
 *
 * - Since: 1.0.0
 */
@protocol CPOutgoingCallDelegate <CPCallDelegate>

/**
 * Establishes an outgoing call. The related call backs are done through the
 * application listener interface instance defined in the call service
 * 
 * @param isVideoEnabled indicates local video sending is enabled or not
 *
 * - Since: 1.0.0
 */
- (void) establishCall :(BOOL) isVideoEnabled;

/**
 * Establishes an outgoing call with custom parameters dictionary
 *
 * @param isVideoEnabled indicates local video sending is enabled or not
 * @param customParameters indicates custom call properties like emergency etc.
 *
 * - Since: 1.0.0
 */
- (void) establishCall:(BOOL)isVideoEnabled withCustomParameters:(NSDictionary<NSString *, NSString *> *_Nullable)customParameters;

/**
 * Establishes an outgoing call with single audio m-line.
 *
 * - Since: 1.0.0
 */
- (void) establishAudioCall;

/**
 * Establishes an outgoing call with single audio m-line and custom parameters dictionary
 *
 * @param customParameters indicates custom call properties like emergency etc.
 *
 * - Since: 1.0.0
 */
- (void) establishAudioCallWithCustomParameters:(NSDictionary<NSString *, NSString *> *_Nullable)customParameters;

@end
