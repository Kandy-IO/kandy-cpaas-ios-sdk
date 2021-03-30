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
#import <AVFoundation/AVFoundation.h>

/**
 *  This class is used to set WebRTC Audio Session Configuration.
 *
 * - Since: 1.0.0
 */
@interface CPAudioSessionConfiguration : NSObject

/**
 * Category of AudioSession.
 * - Returns: String
 *
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSString *category;

/**
 * Category options of AudioSession.
 * - Returns: AVAudioSessionCategoryOptions
 *
 * - Since: 1.0.0
 */
@property(nonatomic, assign) AVAudioSessionCategoryOptions categoryOptions;

/**
 * Mode of AudioSession.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSString *mode;

@end
