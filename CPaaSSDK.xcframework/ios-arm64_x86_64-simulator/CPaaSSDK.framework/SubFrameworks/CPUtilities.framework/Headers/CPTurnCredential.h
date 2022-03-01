/*
 * Copyright © 2018 GENBAND. All Rights Reserved.
 *
 * GENBAND CONFIDENTIAL. All information, copyrights, trade secrets
 * and other intellectual property rights, contained herein are the property
 * of GENBAND. This document is strictly confidential and must not be
 * copied, accessed, disclosed or used in any manner, in whole or in part,
 * without GENBAND's express written authorization.
 *
 */

#import <Foundation/Foundation.h>

@interface CPTurnCredential: NSObject

/**
 * Initializer with the username, password and expiry date.
 * - Returns: String
 * - Since: 1.0.0
 */
- (id) initWithUsername:(NSString *)username password:(NSString *)password andExpiryDate:(NSInteger)expiryDate;

/**
 * The username of ICE Server.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (nonatomic, strong, readonly) NSString *iceUsername;

/**
 * The password of ICE Server.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (nonatomic, strong, readonly) NSString *icePassword;

/**
 * The expiry date in millis for the ICE Server credentials.
 * - Returns: NSInteger
 * - Since: 1.0.0
 */
@property (readonly) NSInteger iceExpiryDate;

@end
