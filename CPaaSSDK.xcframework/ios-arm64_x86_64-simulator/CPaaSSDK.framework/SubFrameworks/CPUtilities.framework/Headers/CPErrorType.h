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

/**
 *  enum class for Error Types
 *
 * - Since: 1.0.0
 */
typedef NS_ENUM(NSInteger, CPErrorType) {
    /// Request is succeeded in partial manner
    PARTIAL_SUCCESS,
    
    /// System failure
    ERROR_SYSTEM,
    
    /// Internal server error occurred
    ERROR_INTERNAL_SERVER,
    
    /// Network failures
    ERROR_NETWORK,
    
    /// Server failures
    ERROR_SERVER,
    
    /// Https security failure
    ERROR_SECURITY,
    
    /// Authentication failure
    ERROR_AUTHENTICATION,
    
    /// Authorization failure
    ERROR_AUTHORIZATION,
    
    /// Error on defined Notification Proxy
    ERROR_PROXY,
    
    /// Localization not found or malformed
    ERROR_LOCALIZATION,
    
    /// Input structure is not validated
    ERROR_VALIDATION,
    
    /// Input parameter is null
    ERROR_NULL_PARAMETER,
    
    /// Received notification message can not be parsed
    ERROR_MESSAGE_PARSE,
    
    /// Failure on WebRTC library
    ERROR_WEBRTC,
    
    /// Method can not be performed
    ERROR_METHOD_NOT_ALLOWED,
    
    /// Microphone access is not available
    ERROR_MICROPHONE_ACCESS,
    
    /// Camera access is not available
    ERROR_CAMERA_ACCESS,
    
    /// Remote server busy error
    ERROR_REMOTE_SERVER_BUSY,
    
    /// Session failed
    ERROR_SESSION_FAILED,
    
    /// Another local offer is in progress
    ERROR_LOCAL_OFFER_IN_PROGRESS,
    
    /// Audio Router setActiveAudioRoute error
    ERROR_AUDIO_ROUTE,
    
    /// Method called in invalid state
    ERROR_INVALID_STATE,
    
    /// Websocket could not be connected
    ERROR_WEBSOCKET_TIMEOUT,
    
    /// Request pending
    ERROR_REQUEST_PENDING = 491,
    
    /// An authentication error occurred because of an invalid access token
    ERROR_INVALID_ACCESS_TOKEN = 4011,
    
    /// A generic authorization error occurred
    ERROR_UNAUTHORIZED = 4012,
    
    /// An authentication error occurred because of an expired access token
    ERROR_EXPIRED_ACCESS_TOKEN = 4013
};
