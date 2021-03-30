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

/**
 *  Manages threads  and concurrency for SDK
 */
@interface CPThreadManager : NSObject

/**
 *  Static singleton instance method
 *
 * @return {@link ThreadManager}
 */
+ (CPThreadManager *) sharedInstance;


/**
 *  dispacthes the specified block to the worker thread
 *
 * @param dispatch_block - block to be executed in worker thread
 */
- (void) dispatch:(void(^)(void))dispatch_block;


/**
 *  dispacthes the specified block to the application thread
 * which is usually the main thread
 *
 * @param dispatch_block - block to be executed in application thread
 */
- (void) dispatchToApp:(void(^)(void))dispatch_block;


/**
 *  dispacthes the specified block to the main thread
 *
 * @param dispatch_block - block to be executed in main thread
 */
- (void) dispatchToMain:(void(^)(void))dispatch_block;

/**
 *  dispacthes the specified block to the specified NSOperationQueue
 *
 * @param operationQueue - the queue which dispatch_block will be dispacthed
 * @param dispatch_block - block to be executed in main thread
 */
- (void) dispatchToOperationQueue:(NSOperationQueue *)operationQueue  withBlock:(void(^)(void))dispatch_block;

/**
 *  returns the label of current queue
 *
 * @return NSString
 */
+ (NSString *) currentQueueLabel;

/**
 *  returns true if current queue is equal to main queue
 *
 * @return BOOL
 */
+ (BOOL) isCurrentMainQueue;


/**
 *  returns true if current queue is equal to worker queue
 *
 * @return BOOL
 */
+ (BOOL) isCurrentWorkerQueue;

@end
