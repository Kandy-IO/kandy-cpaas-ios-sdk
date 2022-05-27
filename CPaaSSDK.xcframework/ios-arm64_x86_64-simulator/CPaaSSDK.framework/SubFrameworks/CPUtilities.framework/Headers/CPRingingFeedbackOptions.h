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
 * Enum values for ringing feedback options
 *
 *APP --> Ringing Feedback is reponsibility of application.
 *AUTO --> Auto ringing feedback mechanism by SDK.
 *
 * @since 2.15.0
 * @updated 3.3.0
 **/

typedef NS_ENUM(NSInteger, CPRingingFeedbackOptions) {
    
    /** Ringing Feedback is reponsibility of application. */
    APP NS_SWIFT_NAME(app),
    
    /**  Auto ringing feedback mechanism by SDK. */
    AUTO NS_SWIFT_NAME(auto),
};
