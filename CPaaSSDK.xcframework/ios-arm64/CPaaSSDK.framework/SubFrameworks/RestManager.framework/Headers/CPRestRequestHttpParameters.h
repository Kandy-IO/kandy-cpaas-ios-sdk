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

@class CPLogManager;

/**
 *  Utility class for RestRequestHttpParameters.
 **/
@interface CPRestRequestHttpParameters : NSObject {
    CPLogManager *logManager;
    NSString *TAG;
}

/**
 * httpParameters of \link RestRequest.h \endlink 
 **/
@property(nonatomic,copy, readonly) NSMutableDictionary * httpParameters;
/**
 * Adds the given headerItem to \link RestHeader.h \endlink
 * @param headerItem
 **/
-(void) addHttpParameters:(NSString*) name andValue:(NSString*) value;

@end
