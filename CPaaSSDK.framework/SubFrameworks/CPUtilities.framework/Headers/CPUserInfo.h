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

#import <AVFoundation/AVFoundation.h>

@class CPTurnCredential;

NS_ASSUME_NONNULL_BEGIN

/**
 *  Utility class for user configuration management.
 * - Since: 1.0.0
 **/
@interface CPUserInfo : NSObject 

/**
 * Name value of the user in UDID format.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (nonatomic, strong, readonly) NSString *username;

/**
 * Domain value of the user .
 * - Returns: String
 * - Since: 2.1.0
 */
@property (nonatomic, strong, readonly) NSString *domain;

/**
 * Name value of the user ID to be used in services.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (nonatomic, strong, readonly) NSString *servicesIdentity;

/**
 * Assigned Sms DIDs of the user.
 * - Returns: Array
 * - Since: 1.2.0
 */
- (nonnull NSArray<NSString *> *)getSmsDIDList;

/**
 * Id token of user in encoded format.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (nonatomic, strong, setter=setIdToken:) NSString *idToken;

/**
 * Access token which is used when communicating server.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSString *accessToken;

/**
 * Websocket channel url that comes from server.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSString *webSocketChannelUrl;

/**
 * Turn server credentials for the user.
 * - Returns: CPTurnCredential
 * - Since: 1.0.0
 */
@property (nonatomic, strong) CPTurnCredential *turnCredentials;

NS_ASSUME_NONNULL_END

@end
