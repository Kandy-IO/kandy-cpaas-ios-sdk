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
 *  Utility class for LoggingDelegate. The application using the SDK must implement this delegate and assign an instance of this implementation to Logger property in the Configuration through the application's startup flow.
 */
@protocol CPLoggingDelegate <NSObject>


@required
/**
 * Main logging method defining the actual logging process
 * @param logLevel LogLevel which is used for checking logLevel
 * @param logContext NSString which includes package and class name
 * @param methodName SEL
 * @param logMessage NSString which includes log message
 *
 * - Since: 1.0.0
 */
-(void)log:(CPLogLevel)logLevel withLogContext:(nonnull NSString *)logContext
                                withMethodName:(nullable SEL) methodName
                                   withMessage:(nonnull NSString*)logMessage;

@end
