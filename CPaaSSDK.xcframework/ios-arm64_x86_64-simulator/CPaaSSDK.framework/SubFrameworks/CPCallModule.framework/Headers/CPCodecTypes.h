//
//  CPCodecTypes.h
//  CPCallModule
//
//  Created by Mehmet on 30.03.2021.
//  Copyright © 2021 Genband. All rights reserved.
//

#ifndef CPCodecTypes_h
#define CPCodecTypes_h

/**
 * Codec types for the supported codecs of WebRTC
 */
typedef NS_ENUM(NSInteger, CPCodecType) {
    
    /// Video type that represents video codecs
    VIDEO NS_SWIFT_NAME(video),
    
    /// Audio type that represents audio codecs
    //AUDIO NS_SWIFT_NAME(audio)
    
    /// All type that represents both codecs video and audio
    //ALL NS_SWIFT_NAME(all)
};

#endif /* CPCodecTypes_h */
