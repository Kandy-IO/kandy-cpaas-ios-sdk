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
#import <UIKit/UIKit.h>
#import "CPErrorType.h"

#define MOBILE_ERROR_DOMAIN @"MobileErrorDomain"
#define CPaaS_ERROR_DOMAIN  @"CPaaSErrorDomain"

NS_ASSUME_NONNULL_BEGIN

/**
 *  Defines the cause of an error
 *
 * @since 1.0.0
 **/
@interface CPError : NSError

/**
 * Time(second) value for retrying erroneous action
 * @return CGFloat
 * @since 1.0.0
 */
@property(nonatomic) CGFloat retryAfter;

/**
 * Creates an error message with specified description message
 * 
 * @param domain specific error domain of the object
 * @param code specific error code of the error
 * @param descriptionString specify error with this message string
 *
 * @return New CPError object
 *
 * @since 1.0.0
 */
- (CPError *)initWithDomain:(NSString *)domain code:(CPErrorType)code description:(NSString *) descriptionString;
- (CPError *)initWithDomain:(NSString *)domain genericCode:(NSInteger)code description:(NSString *) descriptionString;


@end

NS_ASSUME_NONNULL_END
