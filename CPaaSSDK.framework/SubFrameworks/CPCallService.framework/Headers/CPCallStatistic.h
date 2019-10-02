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

/**
 * Gives statistics of the call.
 * - Since: 1.0.0
 */
@interface CPCallStatistic : NSObject

/**
 * Unique identifier of the report.
 * - Returns: String
 * - Since: 1.0.0
 */
@property(nonatomic, readonly) NSString* reportId;

/**
 * Type of the report
 * - Returns: String
 * - Since: 1.0.0
 */
@property(nonatomic, readonly) NSString* type;

/**
 * Date when report is created.
 * - Returns: CFTimeInterval
 * - Since: 1.0.0
 */
@property(nonatomic, readonly) CFTimeInterval timestamp;

/**
 * Contains values of the report
 * - Returns: NSArray of CPValue
 * - Since: 1.0.0
 */
@property(nonatomic, readonly) NSArray* values; //NSArray of CPValue

@end

/**
 * Report objects
 * - Since: 1.0.0
 */
@interface CPValue : NSObject

/**
 * Key of the object
 * - Returns: String
 * - Since: 1.0.0
 */
@property(nonatomic, strong, readonly) NSString *key;

/**
 * Value of the object
 * - Returns: String
 * - Since: 1.0.0
 */
@property(nonatomic, strong, readonly) NSString *value;

@end
