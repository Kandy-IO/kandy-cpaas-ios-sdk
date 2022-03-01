


#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>


/**
 * Class for media attributes of a Call.
 *
 * - Since: 1.0.0
 */
@interface CPMediaAttributes : NSObject

/**
 *  Boolean value that if the local video is activated for sending
 * - Returns: Boolean
 * - Since: 1.0.0
 */
@property (nonatomic, readonly) BOOL localVideo;

/**
 *  Boolean value that if the remote video is receiving
 * - Returns: Boolean
 * - Since: 1.0.0
 */
@property (nonatomic, readonly) BOOL remoteVideo;

/**
 *  Boolean value that local audio is activated for sending
 * - Returns: Boolean
 * - Since: 1.0.0
 */
@property (nonatomic, readonly) BOOL localAudio;

/**
 *  Defines width/height of remote video
 * - Returns: float value that remote video aspect ratio
 * - Since: 1.0.0
 */
@property (nonatomic, readonly) float remoteVideoAspectRatio;

/**
 *  Defines width/height of local video
 * - Returns: float value that local video aspect ratio
 * - Since: 1.0.0
 */
@property (nonatomic, readonly) float localVideoAspectRatio;


@end
