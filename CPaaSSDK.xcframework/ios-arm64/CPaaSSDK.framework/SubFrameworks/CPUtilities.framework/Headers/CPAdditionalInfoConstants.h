/*
 * Copyright © 2016 GENBAND. All Rights Reserved.
 *
 * GENBAND CONFIDENTIAL. All information, copyrights, trade secrets
 * and other intellectual property rights, contained herein are the property
 * of GENBAND. This document is strictly confidential and must not be
 * copied, accessed, disclosed or used in any manner, in whole or in part,
 * without GENBAND's express written authorization.
 *
 */


// Additional info Action and types for call metrics
#define AI_CALL_METRIC_ACTION @"callMetric"
#define AI_CALL_CREATE @"callCreate"  // Time of the establishCall/acceptCall start
#define AI_CALL_REST_SENT @"callRestSent" // Time of (start/accept) rest request sent
#define AI_CALL_RINGING @"callRinging" // Time of ringing notification receive for outgoing call
#define AI_CALL_ANSWER_RECEIVED @"callAnswerReceived" //Time of getting answer notification for outgoing call
#define AI_INCOMING_CALL @"incomingCall" // Time of An incoming call event came
#define AI_RINGING_FEEDBACK_SENT @"ringingFeedBackSent" // Time of the ringing feedback request sent to spidr

// Additional info Action and types for ip change while in call
#define AI_IP_CHANGE_ACTION @"ipChange"
#define AI_IP_CHANGE_STARTED @"ipChangeStarted" // Time of IP change event start
#define AI_IP_CHANGE_ENDED @"ipChangeEnded" // Time of IP change event finish

// Additional info Action and types for ICE gathering timeout and ICE changes
#define AI_ICE_TIMEOUT_ACTION @"iceTimeout"
#define AI_ICE_NORMAL @"iceNormal" // Time of ICE collection process ended normally
#define AI_ICE_ONE_RELAY @"iceOneRelay" // Time of ICE collection process interrupted by timeout with at least 1(audio and video) relay candidate
#define AI_ICE_NO_RELAY @"iceNoRelay" // Time of  ICE collection process interrupted by timeout with no relay candidate
#define AI_ICE_STATE_ACTION @"iceState"
#define AI_ICE_CONNECTED @"iceConnected" // Time of ICE connection state changed to CONNECTED
#define AI_ICE_DISCONNECTED @"iceDisconnected" // Time of ICE connection state changed to DISCONNECTED
