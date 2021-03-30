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
/**
 * Class of IMNotificationParams
 */
@interface SMIMNotificationParams : NSObject <SMNotificationParamsDelegate>
/**
 * Full Name of Instant Message
 **/
@property(nonatomic,strong) NSString * fullName;
/**
 * Type of Instant Message
 **/
@property(nonatomic,strong) NSString * type;
/**
 * msgText of Instant Message
 **/
@property(nonatomic,strong) NSString * msgText;
/**
 * Charset of Instant Message
 **/
@property(nonatomic,strong) NSString * charset;
/**
 * PrimaryContact of Instant Message
 **/
@property(nonatomic,strong) NSString * primaryContact;

@end
