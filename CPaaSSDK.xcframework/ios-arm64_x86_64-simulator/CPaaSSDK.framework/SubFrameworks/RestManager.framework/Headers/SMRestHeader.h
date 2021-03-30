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
 *  Utility class for RestHeader.
 **/
@interface SMRestHeader : NSObject 

/**
 * messageHeader.
 **/
@property(nonatomic, readonly) NSDictionary *messageHeader;
/**
 * Constructor with messageHeader
 * @param messageHeader
 **/
-(id)init:(NSDictionary *)messageHeader;

/**
 * Adds the given headerItem to \link messageHeader \endlink
 * @param headerItem
 **/
-(void) addHeaderItem:(NSString *)name andValue:(NSString *)value;

@end
