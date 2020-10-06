Pod::Spec.new do |s|
    s.name              = 'KandyCPaaSMobileSDK'
    s.version           = '2.11.0'
    s.summary           = 'KandyCPaaSMobileSDK'
    s.homepage          = 'https://github.com/Kandy-IO/kandy-cpaas-ios-sdk'
    s.license 		    = { :type => 'MIT', :file => 'mit-license.txt'}
    s.author            = { 'Name' => 'cpaassdk@netas.com.tr' }
    s.platform          = :ios
    s.source            = { :git => 'https://github.com/Kandy-IO/kandy-cpaas-ios-sdk.git', :tag => '2.11.0'}
    s.dependency 	'KandyWebRTC'
    s.ios.deployment_target   = '10.0'
    s.library = ['c++','icucore','z','sqlite3','stdc++']
    s.ios.frameworks = ['AVFoundation','SystemConfiguration','CFNetwork','Security','OpenGLES','QuartzCore','CoreAudio','CoreMedia','CoreVideo','CoreGraphics','GLKit','VideoToolbox','AudioToolbox','PushKit']
    s.vendored_frameworks = ['CPaaSSDK.framework','WebRTC.framework']
    s.preserve_paths = 'CPaaSSDK.framework/SubFrameworks/*.framework'
    s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
    s.user_target_xcconfig = {
        'ENABLE_BITCODE' => 'NO',
        'FRAMEWORK_SEARCH_PATHS' => '$(inherited) "${PODS_ROOT}/KandyCPaaSMobileSDK/CPaaSSDK.framework/SubFrameworks"',
        'OTHER_LDFLAGS' => '$(inherited) -framework WebRTC -ObjC',
        'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES',
        'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64'
    }
end
