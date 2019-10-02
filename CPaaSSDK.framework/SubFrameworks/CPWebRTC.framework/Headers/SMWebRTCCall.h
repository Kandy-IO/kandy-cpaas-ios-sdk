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

@class CPTurnCredential;
@class CPCallReceiveBandwidthLimit;

typedef struct wMediaState {
    BOOL localVideo;
    BOOL remoteVideo;
    BOOL localAudio;
    BOOL remoteMute;
    float remoteVideoAspectRatio;
    float localVideoAspectRatio;
    AVCaptureDevicePosition captureDevicePosition;
} SMWMediaState;

/** Represents the ice connection state of the peer connection. */
typedef NS_ENUM(NSInteger, WRTCConnectionState) {
    WRTCConnectionStateNew,
    WRTCConnectionStateChecking,
    WRTCConnectionStateConnected,
    WRTCConnectionStateCompleted,
    WRTCConnectionStateFailed,
    WRTCConnectionStateDisconnected,
    WRTCConnectionStateClosed,
    WRTCConnectionStateCount,
};

@protocol SMWebRTCCallDelegate

- (void) webrtcMediaStateChanged:(SMWMediaState) mediaState;

/**
 * Triggered when statistical metric info is available
 * 
 * @param action additioanal info action(iceTemout, iceState etc.)
 * @param type of action (ice conected, disconnnected etc)
 * @param time occurence time of additional info
 */
- (void) additionalInfo:(NSString *)action withType:(NSString*)type andTime:(long)time;

/**
 * Triggered when new ICE Candidate is found.
 *
 * @param iceCandidate which is found
 */
- (void) didGenerateIceCandidate:(NSDictionary *)iceCandidate;

/**
 * Triggered when ICE Connection state is changed.
 */
- (void) didChangeIceConnectionState:(WRTCConnectionState)newState;

@end

@class RTCMediaStream;
@class RTCPeerConnection;
@class RTCSessionDescription;
@class RTCMediaConstraints;
@class SMPCObserver;
@class CPError;

/**
 * WebRTCCall class manages WebRTC PeerConnection actions.
 */
@interface SMWebRTCCall : NSObject

/**
 * Interface of SMWebRTCCall object
 */
@property (weak, readonly) id<SMWebRTCCallDelegate> delegate;

/**
 * Handles communication of streaming data between peers.
 */
@property (strong, atomic, readonly) RTCPeerConnection *peerConnection;

/**
 * Media contraints
 */
@property (readonly) RTCMediaConstraints *mediaConstraints;

/**
 * //TODO remove onhold work around flag
 */
@property (nonatomic, getter = isOnHold, readonly) BOOL onHoldWA;

/**
 *
 * uses single mline for audio only only calls
 */
@property (nonatomic, readonly) BOOL useSingleMLine;

/**
 * Indicates the position of current capture device
 */
@property (nonatomic) AVCaptureDevicePosition currentCaptureDevicePosition;

/**
 * Indicates video resolution of current call
 */
@property (nonatomic, readonly) NSString *currentVideoResolution;

/**
 * Indicates current local DTLS role.
 *
 * - Since: 1.0.0
 */
@property (nonatomic, strong) NSString *currentDtlsRole;

/**
 * Indicates turnCredentials
 */
@property (strong, nonatomic) CPTurnCredential *turnCredentials;

/**
 * Bandwidth limit of receiving media
 *
 * @since 4.6.1
 */
@property (nonatomic, strong, readonly) CPCallReceiveBandwidthLimit *receiveBandwidthLimit;

/**
 * Constructor for WebRTCCall  class
 *
 * @param peerConnection manages communication of streaming with remote peer
 * @param delegate WebRTCCallDelegate callbacks will be implemented in
 */
- (id) initWithPeerConnection:(RTCPeerConnection *)peerConnection delegate:(id<SMWebRTCCallDelegate>)delegateObject;

/**
 * Makes initial WebRTC actions for WebRTCCall object
 * @param videoEnabled indicates call is video or audio call
 * @param singleMLine indicates sdp will contain video m line for audio calls
 * @param localVideoView GUI View for video of user
 * @param remoteVideoView GUI View for video of remote peer
 *
 */
- (void) initializeWithVideo:(BOOL)videoEnabled singleMLine:(BOOL)singleMLine localVideoView:(UIView *)lVideoView remoteVideoView:(UIView *)rVideoView;

/**
 * Creates and sets an offer
 *
 * @param audio indicates if audio enabled in offer
 * @param video indicates if video enabled in offer
 * @param hold indicates offer is created for hold or not.
 * @param handler will be used return callbacks.
 */
- (void) createAndSetOutgoingOfferToStartCallWithAudio: (BOOL)audio
                                              andVideo: (BOOL)video
                                               forHold: (BOOL) hold
                                            andHandler: (void (^)(CPError *error, NSString *sdp)) handler;

/**
 * Creates and sets an offer
 *
 * @param audio indicates if audio enabled in offer
 * @param video indicates if video enabled in offer
 * @param hold indicates offer is created for hold or not.
 * @param handler will be used return callbacks.
 */
- (void) createAndSetOutgoingOfferWithAudio: (BOOL)audio
                             andVideo: (BOOL)video
                              forHold: (BOOL) hold
                           andHandler: (void (^)(CPError *error, NSString *sdp)) handler;

/**
 * Creates and an offer
 *
 * @param audio indicates if audio enabled in offer
 * @param video indicates if video enabled in offer
 * @param hold indicates offer is created for hold or not.
 * @param handler will be used return callbacks.
 */
- (void) createOutgoingOfferWithAudio: (BOOL)audio
                             andVideo: (BOOL)video
                              forHold: (BOOL) hold
                           andHandler: (void (^)(CPError *error, NSString *sdp)) handler;

/**
 * Creates an offer for ice restart
 * It creates same offer as before except for changing ufrag and pwd
 * according to implementation of releted RFC in WEBRTC
 *
 * @param handler
 */
- (void) createOfferForIceRestartWithHandler: (void (^)(CPError *error, NSString *sdp)) handler;

/**
 * Closes current peer connection and creates a new one.
 * This can be used only for startCallUpdate, if you use it for respondcall update new ice candidates
 * will not be send to otherside.
 *
 * @param enableLocalVideo if the local video should be enabled after peer connection reset
 * @param updateTracks update media tracks if required
 */
- (void) resetPeerConnection:(BOOL)enableLocalVideo andUpdateMediaTracks:(BOOL)updateTracks;

/**
 * Updates media tracks if exists or creates them if required.
 *
 * @param enableAudio enable sending audio
 * @param enableVideo enable sending video
 * @param forHold update transceivers' directions for hold
 */
- (int) updateMediaTracksToEnableAudio:(BOOL)enableAudio andEnableVideo:(BOOL)enableVideo forHold:(BOOL)forHold;

/**
 * Invoked when answer of new offer comes.
 *
 * @param remoteSDPStr Remote description for PeerConnection session.
 * @param handler will be used return callbacks.
 */
- (void) incomingOfferWithSDP: (NSString*) remoteSDPStr
                  answerAudio: (BOOL)audio
                  answerVideo: (BOOL) video
                   andHandler: (void (^)(CPError *error, NSString *sdp)) handler;

/**
 * Sets local offer and then remote answer. Generally it is executed at the end of local offer operations
 *
 * @param remoteSDPStr Remote description for PeerConnection session.
 * @param localSDPStr Local description for PeerConnection session.
 * @param type of sdp (answer or pranswer)
 * @param handler will be used return callbacks.
 */
- (void) setLocalOfferRemoteAnswer: (NSString*) remoteSDPStr
                          localSDP: (NSString*) localSDPStr
                           andType: (NSString*) type
                   andHandler: (void (^)(CPError *error, NSString *sdp)) handler;

/**
 * Invoked when an offer comes from remote peer
 *
 * @param remoteSDPStr Remote description for PeerConnection session.
 * @param type of sdp (answer or pranswer)
 * @param handler will be used return callbacks.
 */
- (void) incomingAnswerWithSDP: (NSString*) remoteSDPStr
                       andType: (NSString*) type
                    andHandler: (void (^)(CPError *error, NSString *sdp)) handler;

/**
 * Sets device capture and video resolution to specified position and resolution of the related call
 * @param position AVCaptureDevicePosition of the camera which will be used
 * @param videoResolution that intended to resolution
 * @param handler
 * - Since: 1.0.0
 */
- (void) setCaptureDevice:(AVCaptureDevicePosition)position withVideoResolution:(NSString *)videoResolution withVideoState:(BOOL)videoEnabled completionHandler: (void (^)(CPError *error)) handler;

/**
 * Releases allocated resources for PeerConnection
 */
- (void) dispose;

/**
 * Disables/Enables local audio track
 *
 * @param enabled
 * @return true if set can be done otherwise no
 */
- (BOOL) setAudioEnabled:(BOOL) enabled;

/**
 * Disables/Enables local video track
 *
 * @param enabled
 * @return true if set can be done otherwise no
 */
- (BOOL) setVideoEnabled:(BOOL) enabled;

/**
 * Inits or changes localVideoView with localUIView
 */
- (void) setLocalView:(UIView *)newLocalView;

/**
 * Inits or chagnes remoteVideoView with remoteUIView
 */
- (void) setRemoteView:(UIView *)newRemoteView;

/**
 * Inserts DTMF tone to DTMF send queue
 * @param tone character value of DTMF tone
 * @return YES if tone can be successfully inserted otherwise NO
 */
- (BOOL) sendDTMF:(char)tone;

/**
 * Stabilizes signalling state of peer connection
 *
 * @param handler will be used return callbacks.
 */
- (void) rollbackWithHandler: (void (^)(CPError *error, NSString *sdp)) handler;

/**
 * Stabilizes signalling state of peer connection
 * and changes media state to desired state
 *
 * @param mediaState desired state
 * @param handler will be used return callbacks.
 */
- (void) rollbackWithAudio:(BOOL)audio video:(BOOL)video handler: (void (^)(CPError *error, NSString *sdp)) handler;

/**
 * Sets the Identifier of the call will be used in logging
 * @param callId identifier of call
 */
- (void) setCallID:(NSString *) callid;

/**
 * Retrieves the media state of the delegate(call) object
 * @return MediaState media state of the call
 */
- (SMWMediaState) mediaState;

/**
 * Returns local description of PeerConnection
 *
 * @return localSDP
 */
- (NSString *) getLocalSDP;

/**
 * Returns remote description of PeerConnection
 *
 * @return remoteSDP
 */
- (NSString *) getRemoteSDP;

/**
 * Gets RTP statistics for related call
 */
- (void)getRTPStatistics:(void (^)(NSArray *statistics))completion;

/**
 * Adds ICE Candidates to peer connection object
 */
- (void) addICECandidates:(NSArray *)iceCandidates;

@end
