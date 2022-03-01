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

@class SMRestResponse;
@class CPError;

/**
 * Base Class for Handling Call Request Responses
 */
@interface CPRestResponseHandler :  NSObject

/**
 * Initialization of a network response handler. Completion block will be triggered when network request end.
 *
 * @param responseBodyName every responses uses its own response body names
 * @param tag identifier for log manager
 * @param completion Network request completion block
 */
- (id)initWithResponseBodyName:(NSString *)responseBodyIdentifier
                           tag:(NSString *)tag
             completionHandler:(void (^)(CPError *error, NSDictionary *responseBody))completion;

/**
 * Triggred when response body is gathered successfully
 * @param response RestResponse
 **/
- (void)onFinish:(SMRestResponse *)response;

/**
 * Triggred when response body could not be gathered
 * @param error MobileError
 **/
- (void)onFailed:(CPError *)error;

/**
 * Init is unavailable method for this class
 */
- (id)init __attribute__((unavailable("init is not a supported initializer for this class.")));

@end


