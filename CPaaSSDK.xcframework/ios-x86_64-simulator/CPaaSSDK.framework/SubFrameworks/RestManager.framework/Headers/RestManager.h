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

#import <UIKit/UIKit.h>

//! Project version number for RestManager.
FOUNDATION_EXPORT double RestManagerVersionNumber;

//! Project version string for RestManager.
FOUNDATION_EXPORT const unsigned char RestManagerVersionString[];

#import <Foundation/Foundation.h>

#import <RestManager/CPRestResponseHandler.h>
#import <RestManager/CPRestDeleteRequest.h>
#import <RestManager/CPRestGetRequest.h>
#import <RestManager/CPRestPutRequest.h>
#import <RestManager/CPRestPostRequest.h>
#import <RestManager/SMRestDefines.h>
#import <RestManager/SMRestConnection.h>
#import <RestManager/SMRestHeader.h>
#import <RestManager/SMRestResponse.h>
#import <RestManager/CPRestRequestHttpParameters.h>
#import <RestManager/CPRestBody.h>

@interface CPRestManager : NSObject
{
    CPLogManager  *logManager;
    NSString *TAG;
}

@property(nonatomic, readonly) SMRestResponse *restResponse;

/*
 ** Handles Call Request Responses
 */
@property(nonatomic, readonly) CPRestResponseHandler *restResponseHandler;

/**
 * Static singleton instance method
 * @return \link RestManager \endlink
 */
+(instancetype) getInstance;

/**
 * Sets static singleton instance method
 *
 */
+ (void) setInstance:(CPRestManager *)instance;
 
/**
 * This method sets headerParameters of \link RestRequest \endlink 
 * and opens a \link NSURLConnection  \endlink
 **/
- (void) execute:(CPRestRequest *)restRequest andHandler:(CPRestResponseHandler *)handler;

@end
