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

@class CPRestResponseHandler;
@class CPRestRequest;

@interface SMRestConnection : NSObject
/**
 *  protocol of RestConnection.
 */
@property(strong, nonatomic) CPRestResponseHandler * restResponseHandler;

/**
 * This methods open asynchronous NSURLConnection
 * @param request \link RestRequest \endlink
 */
- (void) execute:(CPRestRequest*) request;

@end
