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

NS_ASSUME_NONNULL_BEGIN

/**
 * An UriAddress is used to indicate the originator of a request, the
 * destination of a request, and to specify any redirections of the
 * request.
 * - Since: 1.0.0
 **/
@interface CPUriAddress : NSObject

/**
 * The username to include in this address.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (strong,nonatomic,nonnull) NSString * username;

/**
 * The network domain to include in this address.
 * - Returns: String
 * - Since: 1.0.0
 */
@property (strong,nonatomic,nonnull) NSString * domain;

/**
 * Constructor method for UriAddress.
 * @param primaryContact address of user
 * - Returns: UriAddress instance
 * - Since: 1.0.0
 */
-(CPUriAddress *) initWithPrimaryContact:(NSString *) primaryContact;

/**
 * Constructor method for UriAddress.
 * @param username name of the user
 * @param domain domain of the user
 * - Returns: UriAddress instance
 * - Since: 1.0.0
 */
- (CPUriAddress *) initWithUsername :(NSString *) username withDomain:(nullable NSString *)domain;

/**
 * Static constructor method for UriAddress.
 * @param username name of the user
 * @param domain domain of the user
 * - Returns: UriAddress instance
 * - Since: 1.0.0
 */
+ (CPUriAddress *) uriAddressWithUsername :(NSString *) username withDomain:(nullable NSString *)domain;

/**
 * Retrieve the URI of an address.
 *
 * - Returns: NSString format of xxx\@yyyy, where xxx is the
 * username or phonenumber and yyy is the domain
 * - Since: 1.0.0
 */
-(NSString *) getUri;
@end

NS_ASSUME_NONNULL_END
