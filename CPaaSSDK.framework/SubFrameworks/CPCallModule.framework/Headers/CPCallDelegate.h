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
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "CPCallStates.h"


@class CPCallState;
@class CPUriAddress;
@class CPMediaAttributes;
@class CPError;
/**
 *  Call related resources
 * - Since: 1.0.0
 */
@protocol CPCallDelegate <NSObject>

/**
 *  Address of the user who starts call
 * - Returns: CPUriAddress
 * - Since: 1.0.0
 */
@property (strong, nonatomic, nonnull) CPUriAddress * callerAddress;

/**
 *  Address of the user who is being called
 * - Returns: CPUriAddress
 * - Since: 1.0.0
 */
@property (strong, nonatomic, nonnull) CPUriAddress * calleeAddress;

/**
 *  Name of the user who starts call
 * - Returns: String
 * - Since: 1.0.0
 */
@property (strong, nonatomic, nullable) NSString * callerName;

/**
 *  Holds video view which retrieved from local camera.
 * Should be linked with GUI object which is a UIView
 * - Returns: UIView
 * - Since: 1.0.0
 */
@property (strong, nonatomic, nullable) UIView * localVideoView;

/**
 *  Holds video view which received from remote participant of call.
 * Should be linked with GUI object which is a UIView
 * - Returns: UIView
 * - Since: 1.0.0
 */
@property (strong, nonatomic, nullable) UIView * remoteVideoView;

/**
 *  Perform end operation on the call.
 * - Since: 1.0.0
 */
- (void) endCall;

/**
 *  Puts the speaker (microphone) into (in) mute
 * - Since: 1.0.0
 */
- (void) mute;

/**
 *  Resumes the speaker
 * - Since: 1.0.0
 */
- (void) unMute;

/**
 *  Stops the video for the call
 * - Since: 1.0.0
 */
- (void) videoStop;

/**
 *  Starts the video for the call
 * - Since: 1.0.0
 */
- (void) videoStart;

/**
 *  Perform hold operation on this call
 * - Since: 1.0.0
 */
- (void) holdCall;

/**
 *  Perform un-hold (resume) operation on this call
 * - Since: 1.0.0
 */
- (void) unHoldCall;

/**
 * @brief Method used by the application to transfer this call to another endpoint.
 *
 * @param newAddress address of the endpoint to replace this endpoint in the call
 * @since 1.7.0
 */
- (void) transferCall: (CPUriAddress * _Nonnull) newAddress;


/**
 * @brief Method used by the application to transfer this call to another active call.
 *
 * @param call call information of the endpoint to replace this calee in the call
 * @since 1.8.0
 */
- (void) consultativeTransfer: (id<CPCallDelegate> _Nonnull) call;

/**
 * @brief Method used by the application to forward this call to another participant.
 *
 * @param toAddress address information of the endpoint to forward this call to
 * @since 2.2.0
 */
- (void) forwardCall:(CPUriAddress* _Nonnull)toAddress;

/**
 *  Inserts Dual Tone Multi Frequency Signal to sending queue and returns the success
 * @param tone character value of DTMF tone. Can only be 0,1...,9,*,#,a,b,c,d,A,B,C,D;
 * @return YES if tone can be successfully inserted to queue otherwise NO
 * - Since: 1.0.0
 */
- (BOOL) sendDTMF:(char)tone;

/**
 *  Sets device capture and video resolution to specified position and resolution of the related call. If nil resolution value is provided then resotion value in configuration will be used. If resolution in configuration is set to nil default VGA (640x480) value will be set.
 *
 * If a resolution value is not suitable to camera session then camera will not be changed and handler will be triggered with an error
 *
 * @param position AVCaptureDevicePosition of the camera which will be used
 * @param videoResolution that intended to resolution
 * @param handler that returns error
 * - Since: 1.0.0
 */
- (void) setCaptureDevice:(AVCaptureDevicePosition)position
      withVideoResolution:(nonnull NSString *)videoResolution
        completionHandler: (void (^_Nullable)(CPError * _Nullable error)) handler;

/**
 * Returns Id of the call.
 * @return Id unique identifier of call
 * - Since: 1.0.0
 */
@property (strong, nonatomic, readonly, nonnull) NSString *Id;

/**
 * Returns callId that related with CPaaS session id
 * For the outgoing call, this value is not set until establish call is succeeded
 * @return sessionId unique identifier of call that related CPaaS session
 * - Since: 1.0.0
 */
@property (strong, nonatomic, readonly, nullable) NSString *sessionId;

/**
 *  Retrieve state of the call.
 * @return CallStates state of the call
 * - Since: 1.0.0
*/
- (nonnull CPCallState *) getCallState;

/**
 *  Retrieve media attributes of the call.
 * @return MediaAttributes attributes of the call's media
 * - Since: 1.0.0
 */
- (nonnull CPMediaAttributes *) getMediaAttributes;

/**
 *  Tests if the call is in muted state
 * @return YES if call is muted otherwise NO
 * - Since: 1.0.0
 */
- (BOOL) isMute;

/**
 *  Indicates remote side can send video or not. Local side can receive video if he wishes.
 * It is determined by Remote Session Description direction as follows
 * 
 * <table>
 * <tr>
 *    <td></td>
 *    <td>sendrecv</td>
 *    <td>sendonly</td>
 *    <td>recvonly</td>
 *    <td>inactive</td>
 * </tr>
 * <tr>
 *    <td>Values</td>
 *    <td>true</td>
 *    <td>true</td>
 *    <td>false</td>
 *    <td>false</td>
 * </tr>
 * </table>
 *
 * @return BOOL
 * - Since: 1.0.0
 */
- (BOOL) canReceiveVideo;

/**
 *  Indicates remote side can receive video or not. Local side can send video if he wishes.
 * It is determined by Remote Session Description direction as follows
 *
 * <table>
 * <tr>
 *    <td></td>
 *    <td>sendrecv</td>
 *    <td>sendonly</td>
 *    <td>recvonly</td>
 *    <td>inactive</td>
 * </tr>
 * <tr>
 *    <td>Values</td>
 *    <td>true</td>
 *    <td>false</td>
 *    <td>true</td>
 *    <td>false</td>
 * </tr>
 * </table>
 *
 * @return BOOL
 * - Since: 1.0.0
 */
- (BOOL) canSendVideo;

/**
 *  Gets last camera position set. If camera is not active last active camera position will be returned.
 *
 * @return AVCaptureDevicePosition position of the current active camera
 * - Since: 1.0.0
 */
- (AVCaptureDevicePosition) getActiveCamera;

/**
 *  Gets last camera resolution set. Value can return nil if method is called before camera allocation.
 *
 * @return NSString camera resolution of the current active camera
 * @see AVCaptureSessionPreset
 *
 * - Since: 1.0.0
 */
- (nullable NSString *) getCameraResolution;

/**
 *  Gets RTP/RTCP Statistics for related call
 *
 * @param completion Completion Block with array which contains RTP/RTCP Statistics
 *
 * - Since: 1.0.0
 */
- (void) getRTPStatistics:(void (^_Nonnull)(NSArray * _Nullable statistics))completion;

@end
