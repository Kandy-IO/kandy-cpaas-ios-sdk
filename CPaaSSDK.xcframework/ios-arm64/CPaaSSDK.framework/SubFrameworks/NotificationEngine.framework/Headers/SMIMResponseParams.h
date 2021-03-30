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
 * Class of IMResponseParams
 */
@interface SMIMResponseParams : NSObject <SMNotificationParamsDelegate>
/**
 * Response Code of Instant Message
 **/
@property(nonatomic,strong) NSString * responseCode;
/**
 * Call id of Instant Message
 **/
@property(nonatomic,strong) NSString * callid;
/**
 * Name of the User who sends the Instant Message
 **/
@property(nonatomic,strong) NSString * username;
/**
 * 
 **/
@property(nonatomic,strong) NSString *remoteParty;

@end
