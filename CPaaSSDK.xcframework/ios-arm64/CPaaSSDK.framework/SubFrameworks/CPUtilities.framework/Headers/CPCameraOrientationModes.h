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

#ifndef MobileSDK_CameraModes_h
#define MobileSDK_CameraModes_h

/**
 *  enum class for Camera Modes
 *
 * - CAMERA_ORIENTATION_USES_NONE,
 * - CAMERA_ORIENTATION_USES_DEVICE,
 * - CAMERA_ORIENTATION_USES_STATUS_BAR
 *
 * - Since: 1.0.0
 */
typedef NS_ENUM(NSInteger, CPCameraOrientationMode) {
    
    /// Doesn't react to the orientation changes
    CAMERA_ORIENTATION_USES_NONE NS_SWIFT_NAME(none),
    
    /// Reacts to the device orientation changes
    CAMERA_ORIENTATION_USES_DEVICE NS_SWIFT_NAME(device),
    
    /// Reacts to the status bar orientation changes
    CAMERA_ORIENTATION_USES_STATUS_BAR NS_SWIFT_NAME(statusBar)
};

#endif
