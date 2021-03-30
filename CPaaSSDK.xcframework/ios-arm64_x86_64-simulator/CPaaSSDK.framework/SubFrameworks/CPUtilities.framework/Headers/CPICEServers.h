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

@class CPICEServer;

/**
 *  This class stores ice servers list, adds a new iceServer and  updates iceServer objects.
 *
 * @since 1.0.0
 */
@interface CPICEServers : NSObject

/**
 * Constructor method for ICEServers.
 *
 * @param url URL address of the ICEServer
 * @return String
 * @since 1.0.0
 */
- (void) addICEServer:(nonnull NSString *)url;

/**
 * Constructor method for ICEServers.
 *
 * @param url Url address of the ICEServer
 * @param username Username of the ICEServer
 * @param password Password of the ICEServer
 *
 * @since 1.0.0
 */
- (void) addICEServer:(nonnull NSString *)url
             username:(nonnull NSString *)username
             password:(nonnull NSString *)password;

/**
 * Returns iceServersArray.
 *
 * @return iceServersArray of ICEServers
 *
 * @since 1.0.0
 */
- (nullable NSArray<CPICEServer *> *) servers;

@end


/**
 *  This class stores url, username and password of stun or turn servers.
 *
 * @since 1.0.0
 */
@interface CPICEServer : NSObject

/**
 * The url of iceServer.
 * @return String
 * @since 1.0.0
 */
@property (strong, readonly, nonnull) NSString * url;

/**
 * The username of iceServer.
 * @return String
 * @since 1.0.0
 */
@property (strong, readonly, nullable) NSString * username;

/**
 * The password of iceServer.
 * @return String
 * @since 1.0.0
 */
@property (strong, readonly, nullable) NSString * password;

/**
 * @return Returns **true** if ice servers can be updated
 */
- (BOOL) canUpdateTurnCredentials;

@end
