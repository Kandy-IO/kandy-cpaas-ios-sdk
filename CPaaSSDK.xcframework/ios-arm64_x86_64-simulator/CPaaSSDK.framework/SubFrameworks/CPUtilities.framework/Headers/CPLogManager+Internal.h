//
//  CPLogManager+Private.h
//  CPUtilities
//
//  Created by Erhan Bayraktar on 8.04.2019.
//  Copyright © 2019 GENBAND. All rights reserved.
//

#import "CPLogManager.h"
#import "CPLogType.h"

NS_ASSUME_NONNULL_BEGIN

@interface CPLogManager (Internal)

/**
 * Log method that calls the LoggingInterface implementation defined in Configuration
 * @param logLevel LogLevel which is used for checking logLevel
 * @param logContext NSString which includes package and class name
 * @param methodName SEL
 * @param logMessage NSString which includes log message
 *
 * - Since: 1.0.0
 **/
-(void)log:(CPLogLevel)logLevel withLogContext:(NSString *)logContext withMethodName:(SEL) methodName withMessage:(NSString*)logMessage;

@end

NS_ASSUME_NONNULL_END
