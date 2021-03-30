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
 *  enum class for supported audio codec types
 *
 * @since 1.0.0
 */
typedef NS_ENUM(NSInteger, CPAudioCodecTypes){
    /// PCMA
    AC_PCMA NS_SWIFT_NAME(PCMA),
    
    /// PCMU
    AC_PCMU NS_SWIFT_NAME(PCMU),
    
    /// ISAC
    AC_ISAC NS_SWIFT_NAME(ISAC),
    
    /// OPUS
    AC_OPUS NS_SWIFT_NAME(OPUS),
    
    /// G722
    AC_G722 NS_SWIFT_NAME(G722),
    
    /// ILBC
    AC_ILBC NS_SWIFT_NAME(ILBC)
};

/**
 *  enum class for supported video codec types
 *
 * @since 1.0.0
 */
typedef NS_ENUM(NSInteger, CPVideoCodecTypes){
    
    /// VP8
    VC_VP8 NS_SWIFT_NAME(VP8),
    
    /// VP9
    VC_VP9 NS_SWIFT_NAME(VP9),
    
    /// H264
    VC_H264 NS_SWIFT_NAME(H264)
};

NS_ASSUME_NONNULL_BEGIN

/**
 * Represents Base Codec Object
 */
@interface CPCodec : NSObject

@end

@interface CPAudioCodec: CPCodec

- (instancetype)init __attribute__((unavailable("Use static initializer withType:")));

/**
 * Returns Codec Type
 */
@property (nonatomic, readonly) CPAudioCodecTypes type;

/**
 * Initializes Video Codec Object with the given Video Codec Type.
 */
+ (CPAudioCodec *)withType:(CPAudioCodecTypes)codecType;

@end

/**
 * Represents Video Codec Object
 */
@interface CPVideoCodec: CPCodec

- (instancetype)init __attribute__((unavailable("Use static initializer withType:")));

/**
 * Returns Codec Type
 */
@property (nonatomic, readonly) CPVideoCodecTypes type;

/**
 * Initializes Video Codec Object with the given Video Codec Type.
 */
+ (CPVideoCodec *)withType:(CPVideoCodecTypes)codecType;

@end
NS_ASSUME_NONNULL_END

/**
 *  This class stores available audio and video codecs list
 * and also edits given SDP with preferred codecs for audio and video.
 *
 * @since: 1.0.0
 */
@interface CPCodecSet : NSObject

/**
 * AudioCodecs stores available audio codecs list.
 * @return Array
 * @since 1.0.0
 */
@property (strong, nonatomic) NSArray<CPAudioCodec *> * _Nullable audioCodecs;

/**
 * VideoCodecs stores available video codecs list.
 * @return Array
 * @since 1.0.0
 */
@property (strong, nonatomic) NSArray<CPVideoCodec *> * _Nullable videoCodecs;

/**
 * Constructor method for CPCodecSet.
 *
 * @param audioCodecs preferred audio codecs list
 * @param videoCodecs preferred video codecs list
 *
 * @return CPCodecSet instance
 *
 * @since 1.0.0
 */
+ (nonnull CPCodecSet *)audioCodecs:(nullable NSArray<CPAudioCodec *> *)audioCodecs
                        videoCodecs:(nullable NSArray<CPVideoCodec *> *)videoCodecs;

- (nonnull instancetype)init __attribute__((unavailable("Use static initWithAudioCodecs:videoCodecs initializer")));

@end
