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

#define UNAUTHORIZED_TOKEN @"Unauthorized"
#define BAD_TOKEN @"Bad token; invalid JSON"
#define EXPIRED_TOKEN @"token expired"

@class SMRestHeader;
@class CPRestBody;
@class CPRestResponseHandler;
@class SMRestResponse;
@class CPLogManager;

/**
 *  Utility class for RestRequest.
 **/
@interface CPRestRequest : NSObject{
    CPLogManager *logManager;
    NSString  *TAG;
}

- (CPLogManager*)getLogManager;
- (NSString *)getTag;
- (void)completion:(NSObject*_Nullable)context error:(NSError*_Nullable)error;

- (void) cancel;

@property (weak, nullable) NSURLSessionTask* task;

@property (nonatomic) SMRestResponse *restResponse;

/**
 * messageHeader created from RestHeader.
 **/
@property(nonatomic, readonly) SMRestHeader *messageHeader;

/**
 * Service url.
 **/
@property(nonatomic, readonly) NSString *serviceUrl;

/**
 * urlRequest of RestRequest. 
 **/
@property(nonatomic, readonly) NSURLRequest *urlRequest;

/**
 * urlRequest of RestRequest.
 **/
@property(nonatomic, readonly) NSString *HTTPMethodType;

/**
 * Initilize urlRequest paramaters
 **/
- (void) initUrlRequestParameters;

/**
 * This method sets messageHeader \link RestRequest \endlink
 **/
-(void) addHeaderParameters;


/**
 * Generate a session task for use by a connection
 * @param session - Session for which to create the task.
 * @param restResponseHandler - handler from connection object
 * @return session task
 **/
- (NSURLSessionTask *) getTaskForSession:(NSURLSession *)session withResponseHander:(CPRestResponseHandler *) restResponseHandler;

/**
 * Handle any progress indication
 **/
- (void) handleProgress:(NSInteger)progressBytes ofTotal:(NSInteger)totalBytes;

@end
