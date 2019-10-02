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

#import <Foundation/Foundation.h>

//! Project version number for CPaaSSDK.
FOUNDATION_EXPORT double CPaaSSDKVersionNumber;

//! Project version string for CPaaSSDK.
FOUNDATION_EXPORT const unsigned char CPaaSSDKVersionString[];

#ifdef __OBJC__
@import CPUtilities;
@import CPAuthenticationService;
@import CPMessagingService;
@import CPAddressBookService;
@import CPPresenceService;
@import CPPushService;
@import CPCallService;
#endif
