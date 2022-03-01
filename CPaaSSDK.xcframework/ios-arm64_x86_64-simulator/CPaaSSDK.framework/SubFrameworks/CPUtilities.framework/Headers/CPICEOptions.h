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

/**
 *  enum class for ICE Options
 * - Since: 1.0.0
 */
typedef NS_ENUM(NSInteger, CPICEOptions){
    /**
     *   Collects ICE candidates before initializing signaling.
     * Vanilla ICE requires candidate collection process, which may take time due to number of interfaces in client’s device and network setup conditions.
     * Vanilla ICE asks clients to sends all candidates in the offer and answer SDPs.This is causing call setup delays.
     * Each side waits for its own candidate collection interval.
     */
    ICE_VANILLA NS_SWIFT_NAME(vanilla),
    
    /**
     *   Completes signaling without waiting for candidate collection.
     * Sends collected candidates to each other (as collection of candidates finished) after the call signaling is done and call is established.
     * This may be causing media delays.
     */
    ICE_TRICKLE NS_SWIFT_NAME(trickle)
};
