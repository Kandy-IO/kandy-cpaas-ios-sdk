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

@class SMRestHeader;
@class CPRestBody;


/**
 *  Utility class for RestResponse.
 **/
@interface SMRestResponse : NSObject

/**
 * status code of RestResponse
 **/
@property(nonatomic) NSInteger responseCode;

/**
 * Reason phrase of Restresponse
 **/
@property(nonatomic) NSString *reasonPhrase;

/**
 * Header parameters of Restresponse
 **/
@property(nonatomic) SMRestHeader *responseHeader;

/**
 * Body data of Restresponse
 **/
@property(nonatomic) CPRestBody *responseBody;

/**
 * File payload of Restresponse
 **/
@property(nonatomic) NSURL *filePayload;

-(NSString *) restResponseToString;

@end
