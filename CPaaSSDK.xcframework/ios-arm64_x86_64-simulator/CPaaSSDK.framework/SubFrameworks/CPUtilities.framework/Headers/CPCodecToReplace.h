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
 * @brief This is the model class to set the
 * custom payload numbers to given codecs in SDP.
 *
 * @since 1.4.0
 */
@interface CPCodecToReplace : NSObject

- (nonnull id) init __attribute__((unavailable("Use one of the static create methods")));

/**
 * Constructor for CodecToReplace class
 *
 * @param codecDefinition the codec that will be changed
 * @param payloadNumber new payload number that will be assigned to the codec,
 * as described in RFC5761 this should be chosen from the range 96-127.
 *
 * @remark If the payload number not set in the range @b 96-127, a @b nil object will return.
 * @since 1.4.0
 */
+ (nullable CPCodecToReplace *) createWithCodecDefinition:(NSString * _Nonnull)codecDefinition
                                         andPayloadNumber:(NSString * _Nonnull)payloadNumber;

/**
 * Constructor for CodecToReplace class
 *
 * @param codecDefinition the codec that will be changed
 * @param payloadNumber new payload number that will be assigned to the codec,
 * as described in RFC5761 this should be chosen from the range 96-127.
 * @param customProperties properties of the codec that should be
 * matched to original codec in order SDK to make the replace
 *
 * @remark If the payload number not set in the range @b 96-127, a @b nil object will return.
 * @since 1.4.0
 */
+ (nullable CPCodecToReplace *) createWithCodecDefinition:(NSString * _Nonnull)codecDefinition
                                            payloadNumber:(NSString * _Nonnull)payloadNumber
                                      andCustomProperties:(NSDictionary<NSString *, NSString *> * _Nullable)customProperties;

/**
 * Returns Codec Definition
 */
@property (nonatomic, readonly, nonnull) NSString *codecDefinition;

/**
 * Returns Codec Payload Number
 */
@property (nonatomic, readonly, nonnull) NSString *payloadNumber;

/**
 * Returns the Custom Codec Properties
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, NSString *> *customProperties;

@end
