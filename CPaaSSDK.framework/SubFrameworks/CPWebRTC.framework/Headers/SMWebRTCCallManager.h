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
#import <UIKit/UIKit.h>

#define STREAM_NAME @"SPDRASTRM"
#define AUDIO_TRACK_ID @"SPDRSTRMa0"
#define VIDEO_TRACK_ID @"SPDRSTRMv0"

@class SMWebRTCCall;
@class RTCVideoTrack;
@class SMPCObserver;
@class RTCPeerConnection;
@class CPTurnCredential;
@class RTCCameraVideoCapturer;
@class RTCAudioTrack;

@protocol SMWebRTCCallDelegate;

/**
 * Manages WebRTCCall Objects.
 * Holds the list of active WebRTCCall objects.
 *
 * Service layer should use this class to make any stuff with WebRTCCall objects
 *
 */
@interface SMWebRTCCallManager : NSObject

/**
 * Static singleton instance method
 *
 * @return {@link WebRTCCallManager}
 */
+ (SMWebRTCCallManager *) getInstance;

/**
 * Setting static singleton instance
 *
 */
+ (void) setInstance:(SMWebRTCCallManager *)instance;

/**
 * Creates and returns RTCCameraVideoCapturer or returns if already initialized.
 * Use if any modification shall be done to capturer.
 
 * @return RTCCameraVideoCapturer
 */
- (RTCCameraVideoCapturer *) getCapturer;

/**
 * Starts to capture from device with specified preferences.
 * Dont need to call `getCapturer` before, if no modification will done prior to start capture.
 */
- (RTCCameraVideoCapturer *) startCapturerWithCameraPosition:(AVCaptureDevicePosition)cameraPosition preset:(NSString *)sessionPreset;

/**
 * Creates peer connection with given observer
 *
 * @param pcObserver
 * @return
 */
- (RTCPeerConnection *) createPeerConnection:(SMPCObserver *)pcObserver withTurnCredentials:(CPTurnCredential *)turnCredentials;

/**
 * Creates a WebRTCCall Object
 *
 * @return created WebRTCCall object
 */
- (SMWebRTCCall *) createWebRTCCallWithDelegate:(id<SMWebRTCCallDelegate>)webRTCCallDelegate andTurnCredentials:(CPTurnCredential *)turnCredentials;

/**
 * Creates a audio track.
 *
 * @param audioEnabled indicates if audio should be included in stream
 *
 * @return created local Media Stream.
 */
- (RTCAudioTrack*) createAudioTrack:(BOOL) audioEnabled;

/**
 * Creates and returns local media stream
 *
 * @param cameraPosition front or back camera
 * @param preset initial camera resolution
 *
 * @return created local Media Stream.
 */
- (RTCVideoTrack*) createVideoTrackWithCamera:(AVCaptureDevicePosition) cameraPosition preset:(NSString *)sessionPreset;

/**
 * Get ice servers from configuration and create list for peer connection
 *
 * @return list of ICE Servers
 */
- (NSMutableArray *) getICEServersWithTurnCredentials:(CPTurnCredential *)turnCredentials ;
/**
 * Stops allocated video sources
 */
-(void) stopVideoSources;

/**
 * Rotates camera to specified orientation
 *
 * @param AVCaptureVideoOrientation value that will be used for camera orientation
 */
- (void) rotateCameraOrientationToPosition:(AVCaptureVideoOrientation) orientation;

/**
 * Gets and sets useManualAudio property of RTCAudioSession
 *
 * - Since: 1.0.0
 */
@property(nonatomic) BOOL useManualAudio;

/**
 * Gets and sets audioEnabled property of RTCAudioSession
 *
 * - Since: 1.0.0
 */
@property(nonatomic, getter=isVoipAudioEnabled) BOOL voipAudioEnabled;

@end
