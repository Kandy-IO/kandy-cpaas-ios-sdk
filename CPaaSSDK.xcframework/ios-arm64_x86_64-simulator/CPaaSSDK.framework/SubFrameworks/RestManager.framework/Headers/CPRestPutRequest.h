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

/**
 *  Class for Put Request.
 **/
@interface CPRestPutRequest : CPRestRequest

/**
 * messageBody created from JSONObject.
 **/
@property(nonatomic,copy) CPRestBody *messageBody;

/**
 * Constructor with messageHeader, messageBody and serviceUrl
 *
 * @param messageHeader includes headers of rest request
 * @param messageBody which will be converted to String, and includes String body entity of RestRequest
 * @param serviceUrl rest service url
 **/
- (id) init:(SMRestHeader *)messageHeader andMessageBody:(CPRestBody *)messageBody andServiceUrl:(NSString *)serviceUrl;

/**
 * Constructor with messageBody, serviceUrl and default RestHeader
 *
 * @param messageBody which will be converted to String, and includes String body entity of RestRequest
 * @param serviceUrl rest service url
 **/
- (id) init:(CPRestBody *)messageBody andServiceUrl:(NSString *)serviceUrl;

@end
