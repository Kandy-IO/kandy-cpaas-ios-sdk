/*
 * Copyright © 2018 Ribbon. All Rights Reserved.
 *
 * Ribbon CONFIDENTIAL. All information, copyrights, trade secrets
 * and other intellectual property rights, contained herein are the property
 * of Ribbon. This document is strictly confidential and must not be
 * copied, accessed, disclosed or used in any manner, in whole or in part,
 * without Ribbon's express written authorization.
 *
 */

#import <AVFoundation/AVFoundation.h>

#import "CPCameraOrientationModes.h"
#import "CPICEOptions.h"
#import "CPLogType.h"

@class CPICEServers;
@class CPCodecSet;
@class CPAudioSessionConfiguration;
@class CPAudioCodecConfiguration;
@class CPLogManager;
@class CPCodecToReplace;
@class CPCallReceiveBandwidthLimit;

@protocol CPLoggingDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 *  Utility class for common configuration management.
 * - Since: 1.0.0
 **/
@interface CPConfig : NSObject

/**
 * Domain of SIP URI used in call or SMS requests.
 *
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSString *domain;

/**
 * Device token which is used when receiving remote notifications.
 * - Since: 2.3.0
 */
@property (nonatomic, strong) NSString *standardDeviceToken;

/**
 * Device token which is used when receiving remote notifications.
 * - Since: 2.3.0
 */
@property (nonatomic, strong) NSString *voipDeviceToken;

/**
 * Server IP information of the baseUrl used for REST request.
 *
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSString *restServerUrl;

/**
 * Server Port information of the baseUrl used for REST request.
 *
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSString *restServerPort;

/**
 * IP information used in web socket connection creation.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSString *webSocketServerUrl;

/**
 * Port information used in web socket connection creation.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSString *webSocketServerPort;

/**
 * Web socket Self signed certificate file data. Can be fetched from a file or string.
 * @code
 * NSString *cerPath = &#91;&#91;NSBundle mainBundle&#92; pathForResource:@"myOwnCertificate" ofType:@"der"&#92;;
 * &#91;&#91;Configuration getInstance] setWebSocketCertificate:&#91;&#91;NSData alloc&#92; initWithContentsOfFile:cerPath&#92;&#92;;
 * @endcode
 *
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSData* webSocketCertificate;

/**
 * Indicates to use secure connection such as https, wss etc.
 * Default value is TRUE (meaning use HTTPS and WSS)
 *
 * - Since: 1.0.0
 */
@property (nonatomic) BOOL useSecureConnection;

/**
 * Sets the preferred set of codecs to use in audio and video calls.
 *
 * - Since: 1.0.0
 */
@property (nonatomic, strong) CPCodecSet *preferredCodecSet;

/**
 * Sets ReplaceCodecSet to modify payload numbers of audio and video codecs
 *
 * - Since: 1.4.0
 */
@property (nonatomic, strong) NSArray<CPCodecToReplace *> * _Nullable replaceCodecSet;

/**
 * Sets the ICE option as ICE_VANILLA or ICE_TRICKLE.
 * Default ICE option is ICE_VANILLA.
 *
 * - Since: 1.0.0
 */
@property(nonatomic) CPICEOptions iceOption;

/**
 * Specifies timeout value of ICE Collection.
 * Default value is 10 and it means that waits 10 seconds for ice gathering.
 * if it is set as 0, it means that waits until ice gathering completion.
 *
 * - Since: 1.0.0
 * - Modified: 2.6.0
 */
@property (nonatomic) NSTimeInterval ICECollectionTimeout;

/**
 * Sets the ICE servers.
 *
 * - Since: 1.0.0
 */
@property (nonatomic, strong) CPICEServers *ICEServers;

/**
 * Sets initial video resolution for video.
 * Value should be one of the AVCaptureSessionPreset strings.
 *
 * If camera does not support the specified value or videoResolution value is to nil medium resolution will be used.
 * @see AVCaptureSessionPreset
 *
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSString *videoResolution;

/**
 * Server certificate to be used in HTTPS connection.Certificate must be .DER format.
 * @code
 * NSString *cerPath = &#91;&#91;NSBundle mainBundle&#92; pathForResource:@"myOwnCertificate" ofType:@"der"&#92;;
 * &#91;&#91;Configuration getInstance] setWebSocketCertificate:&#91;&#91;NSData alloc&#92; initWithContentsOfFile:cerPath&#92;&#92;;
 * @endcode
 *
 * - Since: 1.0.0
 */
@property(nonatomic, strong) NSData *serverCertificate;

/**
 * Sets the audio codec configurations. If parameter is null WebRTC defaults will be use.
 * Warning: This is advance usage if you don't have expertise on audio codecs, especially opus, don't use it.
 *
 * - Since: 1.0.0
 */
@property (nonatomic, strong) CPAudioCodecConfiguration *audioCodecConfigurations;

/**
 * Sets the camera orientation type of video capturer.
 * Video orientation can be changed according to application status bar orientation
 * or device orientation. Camera can be bind to this notifications or not to be bind
 * anything.
 *
 * - Since: 1.0.0
 */
@property(nonatomic) CPCameraOrientationMode orientationMode;

/**
 * Sets the default camera position mode.
 * @see AVCaptureDevicePosition
 *
 * - Since: 1.0.0
 */
@property (nonatomic) AVCaptureDevicePosition cameraPosition;

/**
 * Sets duration value of DTMF tones im ms.
 * Default value is 600 and can be between 40 and 6000.
 *
 * - Updated: 2.0.0
 */
@property (nonatomic) NSUInteger dtmfToneDuration;

/**
 * Sets audio session configuration.
 * @see AVAudioSession
 *
 * - Since: 1.0.0
 */
@property (nonatomic, strong) CPAudioSessionConfiguration *audioSessionConfiguration;

/**
 * Indicates log manager.
 *
 * - Since: 1.0.0
 */
@property(strong, nonatomic, readonly) CPLogManager *logManager;

/**
 * Sets the DTLS enabled or disabled.
 * Default value is NO.
 *
 * - Since: 1.0.0
 */
@property (nonatomic)BOOL dtlsEnabled;

/**
 * Sets the early media feature enabled or disabled.
 * Default value is YES.
 *
 * - Since: 1.0.0
 */
@property (nonatomic)BOOL earlyMediaEnabled;

/**
 * Sending audit message frequency (seconds).
 *
 * - Since: 1.0.0
 */
@property(nonatomic) NSInteger auditFrequency;

/**
 * Forces to disable media transfer when media on hold is active. It helps to fix some
 * MOH issues on PSTN calls
 *
 * @since 1.0.2
 */
@property(nonatomic) BOOL  forceDisableMediaOnHold;

/**
 * Bandwidth limit of receiving media
 *
 * @since 1.7.0
 */
@property (nonatomic, strong) CPCallReceiveBandwidthLimit * _Nullable receiveBandwidthLimit;

/**
 * This method returns (creates if necessary) singleton instance of Configuration class
 *
 * @return shared Configuration instance
 *
 * - Since: 1.0.0
 */
+ (instancetype)sharedInstance;

NS_ASSUME_NONNULL_END

@end
