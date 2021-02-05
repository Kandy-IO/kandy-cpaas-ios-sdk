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
#import "CPCallStates.h"


@class CPError;
@class CPCallState;
@class CPMediaAttributes;

@protocol CPCallDelegate;
@protocol CPIncomingCallDelegate;
@protocol CPOutgoingCallDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 * Represents events of Call
 * This protocol must be conformed by classes which uses CPCallService
 * - Since: 1.0.0
 */
@protocol CPCallApplicationDelegate <NSObject>

/**
 * This method is invoked when there is an IncomingCall
 * Used for informing the application about new call.
 * @param call reference of incoming call
 * - Since: 1.0.0
 */
- (void) incomingCall:(id<CPIncomingCallDelegate>) call;

/**
 * This is the call back method for any call state change on the CallDelegate.
 *
 * @param call which of state changed
 * @param callState the new state of the related call
 * - Since: 1.0.0
 */
- (void) callStatusChanged:(id<CPCallDelegate>)call withState:(CPCallState*)callState;

/**
 * This method is invoked when a detailed call information is available that can be used on statistics
 *
 * @param call related call
 * @param detailedInfo additional info dictionary
 * - Since: 1.0.0
 */
- (void) callAdditionalInfoChanged:(id<CPCallDelegate>)call withDictionary:(NSDictionary*)detailedInfo;

/**
 * This is the call back method for any call's media attributes change on the CallDelegate.
 *
 * @param call which of media attributes changed
 * @param mediaAttributes the new media attributes of the related call
 * - Since: 1.0.0
 */
- (void) mediaAttributesChanged:(id<CPCallDelegate>)call withMediaAttributes:(CPMediaAttributes *) mediaAttributes;

/**
 * This method is invoked when establishCall has succeeded.
 * @param call performed establishment successfully
 * @see [CPOutgoingCallDelegate establishCall:]
 * - Since: 1.0.0
 */
- (void) establishCallSucceeded:(id<CPOutgoingCallDelegate>) call;

/**
 * This method is invoked when establishCall has failed.
 * @param call couldn't made outgoing call establisment
 * @param error definition of failure
 * @see [CPOutgoingCallDelegate establishCall:]
 * - Since: 1.0.0
 */
- (void) establishCallFailed:(id<CPOutgoingCallDelegate>) call withError:(CPError *)error;

/**
 * Method invoked when attempt to accept an incoming call has succeeded.
 * @param call performed accepting successfully
 * @see [CPIncomingCallDelegate acceptCall:]
 * - Since: 1.0.0
 */
- (void) acceptCallSucceed:(id<CPIncomingCallDelegate>) call;

/**
 * Method invoked when attempt to accept an incoming call has failed.
 * @param call couldn't be accepted
 * @param error definition of failure
 * @see [CPIncomingCallDelegate acceptCall:]
 * - Since: 1.0.0
 */
- (void) acceptCallFailed:(id<CPIncomingCallDelegate>) call withError:(CPError *)error;

/**
 * Method invoked when attempt to reject an incoming call has succeeded.
 * @param call performed reject successfully
 * @see [CPIncomingCallDelegate rejectCall]
 * - Since: 1.0.0
 */
- (void) rejectCallSuccedded:(id<CPIncomingCallDelegate>) call;

/**
 * Method invoked when attempt to reject an incoming call has failed.
 * @param call that couldn't be rejected
 * @param error definition of failure
 * @see [CPIncomingCallDelegate rejectCall]
 * - Since: 1.0.0
 */
- (void) rejectCallFailed:(id<CPIncomingCallDelegate>) call withError:(CPError *)error;

/**
 * Method invoked when attempt to ignore a call has succeeded.
 * @param call performed ignore successfully
 * @see [CPIncomingCallDelegate ignoreCall]
 * - Since: 1.0.0
 */
- (void) ignoreSucceed:(id<CPCallDelegate>) call;

/**
 * Method invoked when attempt to ignore a call has failed.
 * @param call couldn't be ignored
 * @param error definition of failure
 * @see [CPIncomingCallDelegate ignoreCall]
 * - Since: 1.0.0
 */
- (void) ignoreFailed:(id<CPCallDelegate>) call withError:(CPError *)error;

/**
 * Method invoked when attempt to sendRingingFeedback an incoming call has succeeded.
 * @param call performed sendRingingFeedback successfully
 * @see [IncomingCallDelegate sendRingingFeedback]
 * @since 2.15.0
 *
 */
- (void) sendRingingFeedbackSucceed:(id<CPIncomingCallDelegate>) call;

/**
 * Method invoked when attempt to sendRingingFeedback an incoming call has failed.
 * @param call that coludn't send ringing feedback
 * @param error definition of failure
 * @see [IncomingCallDelegate sendRingingFeedback]
 * @since 2.15.0
 *
 */
- (void) sendRingingFeedbackFailed:(id<CPIncomingCallDelegate>) call withError:(CPError *) error;

/**
 * This method is invoked when endCall has succeeded.
 * This is the call back method for the endCall request
 * @param call performed end successfully
 * @see [CPCallDelegate endCall]
 * - Since: 1.0.0
 */
- (void) endCallSucceeded:(id<CPCallDelegate>) call;

/**
 * This method is invoked when endCall has failed.
 * This is the call back method for the endCall request
 * @param call coudn't be ended
 * @param error definition of failure
 * @see [CPCallDelegate endCall]
 * - Since: 1.0.0
 */
- (void) endCallFailed:(id<CPCallDelegate>)call withError:(CPError *)error;

/**
 * Method invoked when attempt to mute a call has succeeded.
 * @param call performed mute successfully
 * @see [CPCallDelegate mute]
 * - Since: 1.0.0
 */
- (void) muteCallSucceed:(id<CPCallDelegate>) call;

/**
 * Method invoked when attempt to mute a call has failed.
 * @param call coudn't be muted
 * @param error definition of failure
 * @see [CPCallDelegate mute]
 * - Since: 1.0.0
 */
- (void) muteCallFailed:(id<CPCallDelegate>) call withError:(CPError *)error;

/**
 * Method invoked when attempt to unmute a call has succeeded.
 * @param call performed unmute successfully
 * @see [CPCallDelegate unMute]
 * - Since: 1.0.0
 */
- (void) unMuteCallSucceed:(id<CPCallDelegate>) call;

/**
 * Method invoked when attempt to unmute a call has failed.
 * @param call couldn't be unmuted
 * @param error definition of failure
 * @see [CPCallDelegate unMute]
 * - Since: 1.0.0
 */
- (void) unMuteCallFailed:(id<CPCallDelegate>) call withError:(CPError *)error;

/**
 * Method invoked when attempt to start video on a call has succeeded.
 * @param call performed video start successfully
 * @see [CPCallDelegate videoStart]
 * - Since: 1.0.0
 */
- (void) videoStartSucceed:(id<CPCallDelegate>) call;

/**
 * Method invoked when attempt to start video on a call has failed.
 * @param call coudn't start video
 * @param error definition of failure
 * @see [CPCallDelegate videoStart]
 * - Since: 1.0.0
 */
- (void) videoStartFailed:(id<CPCallDelegate>) call withError:(CPError *)error;

/**
 * Method invoked when attempt to stop video on a call has succeeded.
 * @param call performed stop video successfully
 * @see [CPCallDelegate videoStop]
 * - Since: 1.0.0
 */
- (void) videoStopSucceed:(id<CPCallDelegate>) call;

/**
 * Method invoked when attempt to stop video on a call has failed.
 * @param call coudn't stop video
 * @param error definition of failure
 * @see [CPCallDelegate videoStop]
 * - Since: 1.0.0
 */
- (void) videoStopFailed:(id<CPCallDelegate>) call withError:(CPError *)error;

/**
 * Method invoked when attempt to hold a call has succeeded.
 * @param call performed hold successfully
 * @see [CPCallDelegate holdCall]
 * - Since: 1.0.0
 */
- (void) holdCallSucceed:(id<CPCallDelegate>)call;

/**
 * Method invoked when attempt to hold a call has failed.
 * @param call couldn't be holded
 * @param error definition of failure
 * @see [CPCallDelegate holdCall]
 * - Since: 1.0.0
 */
- (void) holdCallFailed:(id<CPCallDelegate>)call withError:(CPError *)error;

/**
 * Method invoked when attempt to unHold a call has succeded.
 * @param call performed unhold successfully
 * @see [CPCallDelegate unHoldCall]
 * - Since: 1.0.0
 */
- (void) unHoldCallSucceed:(id<CPCallDelegate>) call;

/**
 * Method invoked when attempt to unHold a call has failed.
 * @param call couldn't be unholded
 * @param error definition of failure
 * @see [CPCallDelegate unHoldCall]
 * - Since: 1.0.0
 */
- (void) unHoldCallFailed:(id<CPCallDelegate>) call withError:(CPError *)error;

/**
 * Method invoked when attempt to transfer a call has succeeded.
 * @param call performed transfer call successfully
 * @see [CallDelegate transferCall:]
 * @since 1.7.0
 */
- (void) transferCallSucceed:(id<CPCallDelegate>)call;

/**
 * Method invoked when attempt to transfer a call has failed.
 * @param call couldn't made transferring
 * @param error reason of the failure
 * @see [CallDelegate transferCall:]
 * @since 1.7.0
 */
- (void) transferCallFailed:(id<CPCallDelegate>)call withError:(CPError*)error;


/**
 * Method invoked when attempt to forward a call has succeeded.
 * @param call performed forward call successfully
 * @see [CallDelegate transferCall:]
 * @since 2.2.0
 */
- (void) forwardCallSucceed:(id<CPCallDelegate>)call;

/**
 * Method invoked when attempt to forward a call has failed.
 * @param call couldn't succeed forward operation
 * @param error reason of the failure
 * @see [CallDelegate forwardCall:]
 * @since 2.2.0
 */
- (void) forwardCallFailed:(id<CPCallDelegate>)call withError:(CPError*)error;

@end

NS_ASSUME_NONNULL_END
