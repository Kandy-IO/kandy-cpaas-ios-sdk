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
#import "SMNotificationParamsDelegate.h"

/**
 * Contains basic PresenceWatcherNotificationParams parameters needed in the execution flow of SDK layer implementation
 **/
@interface SMPresenceWatcherNotificationParams : NSObject<SMNotificationParamsDelegate>

/*
#define STATUS_OPEN            @"open";
#define STATUS_CLOSED          @"closed";
#define ACTIVITY_UNKNOWN       @"unknown";
#define ACTIVITY_AWAY          @"away";
#define ACTIVITY_LUNCH         @"lunch";
#define ACTIVITY_BUSY          @"busy";
#define ACTIVITY_VACATION      @"vacation";
#define ACTIVITY_ON_THE_PHONE  @"on-the-phone";
#define ACTIVITY_OTHER         @"other";
#define NOTE_BE_RIGHT_BACK     @"Be Right Back";
#define NOTE_OFFLINE           @"Offline";
#define USERINPUT_ACTIVE       @"active";
#define USERINPUT_INACTIVE     @"inactive";


#define CONNECTED        0
#define UNAVAILABLE      1
#define AWAY             2
#define OUT_TO_LUNCH     3
#define BUSY             4
#define ON_VACATION      5
#define BE_RIGHT_BACK    6
#define ON_THE_PHONE     7
#define ACTIVE           8
#define INACTIVE         9
#define PENDING          10
#define OFFLINE          11
#define CONNECTEDNOTE    12
#define UNAVAILABLENOTE  13
*/

@property(nonatomic,strong) NSString * name;
@property(nonatomic,strong) NSString * type;
@property(nonatomic,strong) NSString * status;
@property(nonatomic,strong) NSString * activity;

-(int) getState;

@end
