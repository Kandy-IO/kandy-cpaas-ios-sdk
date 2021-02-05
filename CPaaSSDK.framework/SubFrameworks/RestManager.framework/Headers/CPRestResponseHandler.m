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

#import "CPRestResponseHandler.h"
#import "SMRestResponse.h"
#import "CPRestBody.h"
@import CPUtilities.Private;

@interface CPRestResponseHandler()
{
    CPLogManager *logManager; // Manages the logging
    NSString *TAG; // TAG for logging
    NSString *responseBodyName; //General name of the response body
    
    void (^completionBlock)(CPError *, NSDictionary*);
}
@end

@implementation CPRestResponseHandler

- (id) initWithResponseBodyName:(NSString *)responseBodyIdentifier
                           tag:(NSString *)tag
                   completionHandler:(void (^)(CPError *, NSDictionary *))completion{
    
    self = [super init];
    if(self)
    {
        TAG = tag;
        logManager = [[CPConfig sharedInstance] logManager];
        completionBlock = completion;
        responseBodyName = responseBodyIdentifier;
    }
    return self;
}

- (void) onFinish:(SMRestResponse *)response {
    if(nil != response) {
        if (completionBlock) {
            NSMutableDictionary * messageBodyDictionary = nil;
            if (response.responseBody.messageBody) {
                messageBodyDictionary = [response.responseBody.messageBody objectForKey:responseBodyName];
            } else if (response.filePayload) {
                messageBodyDictionary = [NSMutableDictionary dictionaryWithDictionary: @{@"file": response.filePayload}];
            }
            completionBlock(nil, messageBodyDictionary);
        }
    }
}

- (void)onFailed:(CPError *) error{
    
    if(!error)
        error = [[CPError alloc] initWithDomain:MOBILE_ERROR_DOMAIN code:ERROR_NULL_PARAMETER description:@"Rest failed."];
    
    [logManager log:ERROR withLogContext:TAG withMethodName:_cmd withMessage:[NSString stringWithFormat: @"Request failed. Error Code %ld -- Error description: %@",(long)error.code , error.description]];
    
    if(completionBlock) completionBlock(error, nil);
}


@end
