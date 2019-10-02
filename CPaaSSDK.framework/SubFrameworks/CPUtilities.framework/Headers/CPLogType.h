/*
 * Copyright © 2018 GENBAND. All Rights Reserved.
 *
 * GENBAND CONFIDENTIAL. All information, copyrights, trade secrets
 * and other intellectual property rights, contained herein are the property
 * of GENBAND. This document is strictly confidential and must not be
 * copied, accessed, disclosed or used in any manner, in whole or in part,
 * without GENBAND's express written authorization.
 *
 */

/**
 *  enum class for Log Levels
 *
 * @since 1.0.0
 **/

typedef NS_ENUM(NSInteger, CPLogLevel)
{
    /// events that will presumably lead the application to abort
    ERROR NS_SWIFT_NAME(error),
    
    /// potentially harmful situations
    WARNING NS_SWIFT_NAME(warning),
    
    /// informational messages that highlight the progress of the application at coarse-grained level
    INFO NS_SWIFT_NAME(info),
    
    /// finer-grained informational events
    TRACE NS_SWIFT_NAME(trace),
    
    /// method start and finishes
    VERBOSE NS_SWIFT_NAME(verbose),
    
    /// enables webrtc sensitive logging
    TRACE_WEBRTC NS_SWIFT_NAME(traceWebRTC)
};
