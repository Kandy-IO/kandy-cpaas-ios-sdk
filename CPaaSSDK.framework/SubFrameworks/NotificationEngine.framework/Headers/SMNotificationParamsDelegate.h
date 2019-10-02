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

@protocol SMNotificationParamsDelegate <NSObject>

/**
 * Parse params and assign them to related attributes
 *
 * @param params which will be parsed
 */
- (void) fillParams: (NSDictionary *) params;

@end
