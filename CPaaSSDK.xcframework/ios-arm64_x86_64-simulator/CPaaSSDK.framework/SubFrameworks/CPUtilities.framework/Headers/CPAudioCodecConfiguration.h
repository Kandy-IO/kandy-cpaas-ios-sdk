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
 * OpusConfiguration class contains all configuration of Opus audio codec.
 * Configurations can be set using this class instance.
 *
 * - Since: 1.0.0
 */
@interface CPAudioCodecConfiguration : NSObject

/**
 * Maxaveragebitrate specifies the maximum average receive
 * bitrate of a session in bits per second (bit/s).  The actual value of the bitrate
 * can vary, as it is dependent on the characteristics of the media in a packet.
 * Note that the maximum average bitrate MAY be modified dynamically during a session.
 * Any positive integer is allowed, but values outside the range 6000 to 510000
 * SHOULD be ignored. If no value is specified, the maximum value will equals to
 * corresponding mode of Opus and corresponding maxplaybackrate is the default.
 * Decreasing MaxAverageBitRate will cause less bandwidth usage
 * (For further information check RFC-7587).
 * - Returns: NSInteger
 *
 * - important:
 * MobileSDK default maxAverageBitRate=20000
 *
 * 6000 <= MaxAverageBitRate <= 510000
 *
 * In case this value set as -1 WebRTC defaults will be use.
 * - Since: 1.0.0
 *
 */
@property (nonatomic) NSInteger opusMaxAverageBitRate;


/**
 * Ptime is the preferred duration of media represented by a
 * packet that a decoder wants to receive, in milliseconds rounded up to the next full
 * integer value.  For Opus, possible values are 3, 5, 10, 20, 40, 60, or an arbitrary
 * multiple of frame size rounded up to the next full integer value, up to a maximum value of 120.
 * If no value is specified, the default is 20. Changing ptime effects all audio codecs.
 * Increasing Ptime will cause less bandwidth usage (For further information check RFC-7587).
 * - Returns: NSInteger
 *
 * - important:
 * MobileSDK default ptime=60
 *
 * 3 <= MaxAverageBitRate <= 120 and it should be multiple of an Opus frame size
 * rounded up to the next full integer value
 *
 * In case this value set as -1 WebRTC defaults will be use.
 * - Since: 1.0.0
 *
 */
@property (nonatomic) NSInteger ptime;

/**
 * Sets DTX value which will enable or disable Discontinuous Transmission feature of Opus codec.
 * When using continuous transmission, Variable Bitrate will reduce
 * the bitrate when the characteristics of the input signal permit, but it will never
 * interrupt the transmission to the receiver.  Therefore, the received signal will
 * maintain the same high level of audio quality over the full duration
 * of a transmission while minimizing the average bitrate over time.
 * In cases where the bitrate of Opus needs to be reduced even further
 * or in cases where only constant bitrate is available, the Opus encoder can use Discontinuous
 * Transmission (DTX), where parts of the encoded signal that correspond to periods of silence
 * in the input speech or audio signal are not transmitted to the receiver.
 * A receiver can distinguish between DTX and packet loss by looking for gaps in the
 * sequence number. On default DTX is disabled and enabling DTX will cause less bandwidth usage
 * (For further information check RFC-7587).
 * If application set dtxEnable parameter as 'YES' DTX will be enable, if application set it as
 * 'NO' DTX will be disable.
 * - Returns: Boolean
 *
 * - important:
 * MobileSDK default DTX is enabled
 * - Since: 1.0.0
 *
 */
@property (nonatomic) BOOL opusDtx;

/**
 * Sets FEC value which will enable or disable ForwardErrorCorrection feature of Opus codec.
 * The voice mode of Opus allows for embedding in-band Forward Error Correction (FEC)
 * data into the Opus bitstream.  This FEC scheme adds redundant information about the
 * previous packet (N-1) to the current output packet N. On the receiving side, the decoder
 * can take advantage of this additional information when it loses a
 * packet and the next packet is available. Disabling FEC cause cause less bandwidth usage
 * (For further information check RFC-7587).
 * If application set fecEnable parameter as 'YES' FEC will be enable, if application set it as
 * 'NO' FEC will be disable.
 * - Returns: Boolean
 *
 * - important:
 * MobileSDK default FEC is enabled
 * - Since: 1.0.0
 *
 */
@property (nonatomic) BOOL opusFec;

/**
 * Sets the MaxPlaybackRate. Maxplaybackrate is a hint about the maximum output sampling rate
 * that the receiver is capable of rendering in Hz. The decoder MUST be capable of decoding
 * any audio bandwidth, but, due to hardware limitations, only signals up to the specified
 * sampling rate can be played back. Sending signals with higher audio bandwidth results
 * in higher than necessary network usage and encoding complexity, so an encoder SHOULD NOT
 * encode frequencies above the audio bandwidth specified by maxplaybackrate.
 * This parameter can take any value between 8000 and 48000, although commonly the value will
 * match one of the Opus bandwidths . By default, the receiver is assumed to have no
 * limitations, i.e., 48000. Decreasing MaxPlaybackRate will cause less bandwidth usage.
 * Decreasing MaxPlaybackRate will cause less bandwidth usage
 * (For further information check RFC-7587).
 * - Returns: NSInteger
 *
 * - important:
 * MobileSDK default MaxPlaybackRate=16000
 *
 * 8000 <= maxPlaybackRate <= 48000
 *
 * In case this value set as -1 WebRTC defaults will be use.
 * - Since: 1.0.0
 *
 */
@property (nonatomic) NSInteger opusMaxPlaybackRate;

/**
 * Init CPAudioCodecConfiguration with MobileSDK preferred sets.
 * If an application use this configuration MobileSDK will modify the
 * Audio Codec parameters automatically with it's preferred set.
 * - Returns: Instance
 * - Since: 1.0.0
 *
 */
+ (nonnull CPAudioCodecConfiguration *) configurationWithMobileSDKPreferredSet;

/**
 * Init CPAudioCodecConfiguration with WebRTC default sets.
 * If an application use this configuration MobileSDK will not modify the
 * Audio Codec parameters automatically.
 * - Returns: Instance
 * - Since: 1.0.0
 *
 */
+ (nonnull CPAudioCodecConfiguration *) configurationWithWebRTCDefaultSet;

/**
 * This method will return the opus fmtp line parameters which will be in the fmtp line of SDP.
 * Only Utils in WebRTC should call this method. Using this method Utils will modify the SDP and
 * bitrate will decrease.
 *
 * - Returns: String fmtpLine
 * - Since: 1.0.0
 */
-(nonnull NSString *) getOpusFMtpLine;

@end
