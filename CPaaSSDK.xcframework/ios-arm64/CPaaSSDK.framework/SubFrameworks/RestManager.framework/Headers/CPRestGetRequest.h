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
#import "CPRestRequest.h"

@class CPRestRequestHttpParameters;

/**
 *  Class for Get Request.
 **/
@interface CPRestGetRequest : CPRestRequest

/**
 * messageBody created from JSONObject.
 **/
@property(nonatomic,copy) CPRestRequestHttpParameters *httpParameters;

/**
 * Constructor with messageHeader, httpParameters and serviceUrl
 *
 * @param messageHeader includes headers of rest request
 * @param httpParameters includes HTTP parameters
 * @param serviceUrl rest service url
 **/
- (id) init: (SMRestHeader *)messageHeader
            andHttpParameters:(CPRestRequestHttpParameters *)httpParameters
            andServiceUrl:(NSString*)serviceUrl;

/**
 * Constructor with httpParameters, serviceUrl and default RestHeader
 *
 * @param httpParameters includes HTTP parameters
 * @param serviceUrl rest service url
 **/
- (id) init:(CPRestRequestHttpParameters *)httpParameters andServiceUrl:(NSString *)serviceUrl;

@end
