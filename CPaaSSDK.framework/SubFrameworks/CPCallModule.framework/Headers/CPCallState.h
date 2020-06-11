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
#import "CPCallStates.h"

// Reason codes defined on MobileSDK
#define STATUS_CODE_NOT_PROVIDED 9900
#define ENDED_BY_LOCAL 9901
#define REJECTED_BY_LOCAL 9902
#define IGNORED_BY_LOCAL 9903
#define RESPONDED_FROM_ANOTHER_DEVICE 9904
#define SESSION_COMPLETED 9905
#define ENDED_BY_ERROR 9906
#define ENDED_BY_UNREGISTER 9907

NS_ASSUME_NONNULL_BEGIN

/**
 * Contains status information of the call.
 * - Since: 1.0.0
 */
@interface CPCallState : NSObject

/**
 *  Enum type of CallState
 * - Returns: CPCallStates
 * - Since: 1.0.0
 */
@property (nonatomic, readonly) CPCallStates type;

/**
 *  Reason of state transition
 * - Returns: String
 * - Since: 1.0.0
 */
@property (strong, nonatomic, readonly) NSString *reason;

/**
 *  HTTP status code
 * - Returns: NSInteger
 * - Since: 1.0.0
 */
@property (nonatomic, readonly) NSInteger statusCode;

/**
 * Creates an CallState oject with specified type
 *
 * @param type Type of state as CPCallStates
 * - Returns: CPCallState object
 * - Since: 1.0.0
 */
- (id) initWithType:(CPCallStates) type;

/**
 * Creates an CallState oject with specified type and reson
 *
 * @param type Type of state as CPCallStates
 * @param reason Reason of CallState transition as String
 * - Returns: CPCallState object
 * - Since: 1.0.0
 */
- (id) initWithType:(CPCallStates) type andReason:(NSString *) reason;

/**
 * Creates an CallState oject with specified type and reson and http code
 *
 * @param type Type of state as CPCallStates
 * @param reason Reason of CallState transition as String
 * @param statusCode HTTP code comes from CPaaS for state transition
 * - Returns: CPCallState object
 * - Since: 1.0.0
 */
- (id) initWithType:(CPCallStates) type andReason:(NSString *) reason andStatusCode: (NSInteger) statusCode;

@end

NS_ASSUME_NONNULL_END
