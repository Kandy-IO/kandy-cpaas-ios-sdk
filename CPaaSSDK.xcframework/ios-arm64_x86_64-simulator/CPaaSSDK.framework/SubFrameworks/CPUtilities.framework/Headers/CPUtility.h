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

#define REST_SERVICE_PROTOCOL_HTTP @"http://"
#define REST_SERVICE_PROTOCOL_HTTPS @"https://"

#define serviceVersion @"v1"
#define projectName @"cpaas"

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CPError;
/**
 * Contains basic utility functions needed in the execution flow of SDK layer implementation
**/
@interface CPUtility : NSObject

/**
 * Returns current epoch time in ms
 */
+(long) currentTimeinMs;

/**
 *  Adds Component string to Mobile Error message.
 *  - Since: 1.0.0
 */
+(CPError*) addComponentTagToMobileError:(NSString*)component mobileError:(CPError*) error;

/**
 *  Creates dictionary template for Internal Error Message.
 *  - Since: 1.0.0
 */
+(NSDictionary*) createInternalErrorDictionary:(NSString*)component mobileError:(CPError*) error;

/**
 *  Generates client correlator.
 *  - Since: 1.0.0
 */
+ (NSString *) correlatorWithUsername:(NSString *)username;

/**
 *  Encodes connection token
 *  - Since: 1.0.0
 */
+ (nullable NSString *) encodeChannelInfoWithChannelUrl:(NSString *)channelUrl lifetime:(NSInteger) lifeTime;

/**
 *  Decodes connection token
 *  - Since: 1.0.0
 */
+ (nullable NSDictionary<NSString *, NSString *> *) decodeConnectionToken:(NSString *) connectionToken;

/**
 *  Decodes id token
 *  - Since: 1.0.0
 */
+ (NSDictionary<NSString *, id> *) decodeIdToken:(NSString *) idtoken;

/**
 * This method gets base url (server_ip:server_port) to be used in HTTP based requests
 * - Returns: String
 * - Since: 1.0.0
 */
+ (NSString *) getBaseUrl;

/**
 * This method creates required service url with given info
 * - Returns: NSString
 * - Since: 1.0.1
 */
+ (NSString *)getServiceUrlWithServiceName:(NSString *)serviceName userName:(NSString *)userName suffix:(NSString *)suffix;
@end

NS_ASSUME_NONNULL_END
