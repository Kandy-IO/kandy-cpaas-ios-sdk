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

//! Project version number for CPCallService.
FOUNDATION_EXPORT double CPCallServiceVersionNumber;

//! Project version string for CPCallService.
FOUNDATION_EXPORT const unsigned char CPCallServiceVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <CPCallService/PublicHeader.h>
#import <CPCallService/CPCallApplicationDelegate.h>
#import <CPCallService/CPCallDelegate.h>
#import <CPCallService/CPIncomingCallDelegate.h>
#import <CPCallService/CPOutgoingCallDelegate.h>
#import <CPCallService/CPCallState.h>
#import <CPCallService/CPCallStates.h>
#import <CPCallService/CPMediaAttributes.h>
#import <CPCallService/CPCallService.h>

@class CPServiceInfo;
@protocol CPServiceProtocol;

@class CPUserInfo;
@class CPUriAddress;
@class CPError;

@protocol CPOutgoingCallDelegate;
@protocol CPCallApplicationDelegate;

/**
 * Service Class for Call.
 * Retrieves notification from Notification Manager and redirects them to related classes.
 * Sends reqiured callbacks to application layer.
 *
 * - Since: 1.0.0
 */
@interface CPCallService : NSObject<CPServiceProtocol>

/**
 * Provides reference for sending callbacks to application
 * - Returns: CPCallApplicationDelegate
 */
@property (nonatomic, strong) id<CPCallApplicationDelegate> callApplicationDelegate;

/**
 * If YES, MobileSDK will not initialize the audio unit automatically when an
 * audio track is ready for playout or recording. Instead, applications should
 * call setVoipAudioEnabled. If NO, MobileSDK will initialize the audio unit
 * as soon as an audio track is ready for playout or recording.
 *
 * - important: Default value is NO.
 * - Returns: Boolean
 * - Since: 1.0.0
 */
@property(nonatomic) BOOL useManualAudio;

/**
 * This property is only effective if useManualAudio is YES.
 * Represents permission for MobileSDK to initialize the VoIP audio unit.
 * When set to NO, if the VoIP audio unit used by MobileSDK is active, it will be
 * stopped and uninitialized. This will stop incoming and outgoing audio.
 * When set to YES, MobileSDK will initialize and start the audio unit when it is
 * needed (e.g. due to establishing an audio connection).
 *
 * - important: Default value is NO.
 * - Returns: Boolean
 * - Since: 1.0.0
 */
@property(nonatomic, getter=isVoipAudioEnabled) BOOL voipAudioEnabled;

/**
 * Initializes Call Service Instance with the given configuration.
 * @param config CPUserInfo
 * @param serviceInfo ServiceInformation
 * - Since: 1.0.0
 */
- (id)initWithUserInfo:(CPUserInfo *)userInfo info:(CPServiceInfo *) serviceInfo;

/**
 *  This method is to create outgoing/mobile originated calls
 *
 * @param app delegete of application to return callbacks for call
 * @param originator address of caller
 * @param terminator address of callee
 * @param callHandler completion block with call to establish call
 * - Since: 1.0.0
 */
- (void)createOutGoingCall:(id <CPCallApplicationDelegate>)app
             andOriginator:(CPUriAddress *)originator
             andTerminator:(CPUriAddress *)terminator
                completion:(void (^)(id<CPOutgoingCallDelegate> call, CPError *error))callHandler;


/**
 *  This method is to create outgoing/mobile originated calls
 *
 * @param app delegete of application to return callbacks for call
 * @param terminator address of callee
 * @param callHandler completion block with call to establish call
 * - Since: 1.0.0
 */
- (void) createOutGoingCall:(id <CPCallApplicationDelegate>)app
              andTerminator:(CPUriAddress *)terminator
                 completion:(void (^)(id<CPOutgoingCallDelegate> call, CPError *error))callHandler;


/**
 * @brief This method creates Three Way Call.
 * For now this api just supports to merge two calls.
 *
 * @param firstCall specifies the first call which will be joined to ThreeWay Call
 * @param secondCall specifies the second call which will be joined to ThreeWay Call
 * @param completion completion block with call to establish call
 *
 * @since 2.1.0
 */
- (void) createThreeWayCallWithFirstCall:(id<CPCallDelegate>) firstCall
                              secondCall:(id<CPCallDelegate>) secondCall
                              completion:(void (^)(id<CPOutgoingCallDelegate> call, CPError *error))callHandler;

/**
 *  Rotates camera to specified orientation
 *
 * @param orientation AVCaptureVideoOrientation value that will be used for camera orientation
 * - Since: 1.0.0
 */
-(void) rotateCameraOrientationToPosition:(AVCaptureVideoOrientation) orientation;

/**
 * Returns the active call objects.
 *
 * @return Immutable call list
 * - Since: 1.0.0
 */
- (NSArray *) getActiveCalls;

/**
 * Delegate method to subscribe for call service.
 *
 * @param channelID The channel on which to subscribe for call service.
 * @param completion Code block to execute upon subscription completion.
 * @param notification Returns service name
 * @param error Returns nil unless any error occurs.
 *
 * - Since: 1.0.0
 */
- (void)subscribeWithChannelID:(NSString *)channelID completion:(void (^)(NSString * _Nonnull, CPError * _Nullable))completion;

/**
 * Delegate method to unsubscribe from call service.
 *
 * @param channelID The channel on which to unsubscribe for call service.
 * @param completion Code block to execute upon unsubscription completion.
 * @param error Returns nil unless any error occurs.
 *
 * - Since: 1.0.0
 */
- (void)unsubscribeWithChannelID:(NSString *)channelID completion:(void (^)(CPError * _Nullable))completion;

@end
