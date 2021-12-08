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
 *  Utility class for RestBody.
 **/
@interface CPRestBody : NSObject

/**
 * messageBody.
 **/
@property(nonatomic, readonly) NSDictionary *messageBody;

/**
 * Constructor with messageBody
 * @param messageBody
 **/
-(id)init:(NSDictionary *)messageBody;

/**
 * This method converts \link RestBody \endlink to NSData
 * @return NSData
 **/
-(NSData *) getRestBodyData;

@end
