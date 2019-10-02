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
 *  Class for Delete Request.
 **/
@interface CPRestDeleteRequest : CPRestRequest

/**
 * Constructor with messageHeader and serviceUrl
 *
 * @param messageHeader includes headers of rest request
 * @param serviceUrl rest service url
 **/
- (id) init:(SMRestHeader *)messageHeader andServiceUrl:(NSString *)serviceUrl;

/**
 * Constructor with serviceUrl and default RestHeader
 *
 * @param serviceUrl rest service url
 **/
- (id) init:(NSString *)serviceUrl;

@end
