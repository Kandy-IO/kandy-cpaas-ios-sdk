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
#import "SMNotificationParamsDelegate.h"

@class CPLogManager;

@interface SMNotificationParamsFactory : NSObject
{
    CPLogManager *logManager;
    NSString *TAG;
}
typedef enum paramTypes {ntfctn, im, call, callDispose, session, presence, imResp, incomingCall, offer, linkType } ParamType;

+ (id<SMNotificationParamsDelegate>) notificationParams: (NSDictionary *) params forType: (ParamType) paramType ;

@end
