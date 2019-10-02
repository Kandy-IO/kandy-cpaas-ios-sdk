/*
 * Copyright © 2019 GENBAND. All Rights Reserved.
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
 * @brief CPCallReceiveBandwidthLimit class can be used for setting
 * limitation to receive bandwidth.
 *
 * @since 1.7.0
 */
@interface CPCallReceiveBandwidthLimit : NSObject

/**
 * audioReceiveBandwidth
 */
@property (nonatomic, strong) NSNumber * audioReceiveBandwidth;

/**
 * videoReceiveBandwidth
 */
@property (nonatomic, strong) NSNumber * videoReceiveBandwidth;

/**
 * Constructor method for CPCallReceiveBandwidthLimit.
 *
 * @param audioReceiveBandwidthLimit preferred audio bandwidth limit
 * @param videoReceiveBandwidthLimit preferred video bandwidth limit
 *
 * @return CPCallReceiveBandwidthLimit instance
 *
 * @since 1.7.0
 */
- (id) initWithAudioReceiveBandwidthLimit:(NSNumber *) audioReceiveBandwidthLimit withVideoReceiveBandwidthLimit:(NSNumber *) videoReceiveBandwidthLimit;

@end
