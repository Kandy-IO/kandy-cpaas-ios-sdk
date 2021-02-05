//
//  CPScalingStyles.h
//  CPUtilities
//
//  Created by SIDAL OTHAN on 28.01.2021.
//  Copyright © 2021 GENBAND. All rights reserved.
//

/**
 * Enum class for local and remote video view scaling style
 * Default value is SCALINGSTYLE_ASPECT_RATIO_FIT
 * - Since: 2.15.0
 */

typedef NS_ENUM(NSInteger, CPScalingStyles) {
    
    /// Scaling style is Aspect Ratio Fit
    SCALINGSTYLE_ASPECT_RATIO_FIT NS_SWIFT_NAME(aspectRatioFit)                     = 1,
    
    /// Scaling style is Aspect Ratio Fit
    SCALINGSTYLE_ASPECT_RATIO_FILL NS_SWIFT_NAME(aspectRatioFill)                   = 2
};

