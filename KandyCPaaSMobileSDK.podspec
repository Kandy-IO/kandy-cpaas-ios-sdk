Pod::Spec.new do |s|
    s.name              = 'KandyCPaaSMobileSDK'
    s.version           = '2.0.0'
    s.summary           = 'KandyCPaaSMobileSDK'
    s.homepage          = 'https://github.com/Kandy-IO/kandy-cpaas-ios-sdk'
    s.license 		= { :type => 'MIT', :file => 'mit-license.txt'}
    s.author            = { 'Name' => 'cpaassdk@netas.com.tr' }
    s.platform          = :ios
    s.source            = { :git => 'https://github.com/Kandy-IO/kandy-cpaas-ios-sdk.git', :tag => '2.0.0'}
    s.dependency 	'KandyWebRTC'
    s.ios.deployment_target   = '9.0'
    s.library = ['c++','icucore','z','sqlite3','stdc++']
    s.ios.frameworks = ['AvFoundation','SystemConfiguration','CFNetwork','Security','OpenGLES','QuartzCore','CoreAudio','CoreMedia','CoreVideo','CoreGraphics','GLKit','VideoToolbox','AudioToolbox','PushKit']
    s.vendored_frameworks = ['CPaaSSDK.framework','WebRTC.framework',
      'CPaaSSDK.framework/SubFrameworks/CPUtilities.framework',
      'CPaaSSDK.framework/SubFrameworks/CPAddressBookService.framework',
      'CPaaSSDK.framework/SubFrameworks/CPAuthenticationService.framework',
      'CPaaSSDK.framework/SubFrameworks/CPCallService.framework',
      'CPaaSSDK.framework/SubFrameworks/CPMessagingService.framework',
      'CPaaSSDK.framework/SubFrameworks/CPPresenceService.framework',
      'CPaaSSDK.framework/SubFrameworks/CPPushService.framework',
      'CPaaSSDK.framework/SubFrameworks/NotificationEngine.framework',
      'CPaaSSDK.framework/SubFrameworks/RestManager.framework']
    s.preserve_paths = 'CPaaSSDK.framework/SubFrameworks/*.framework'
    s.pod_target_xcconfig = {
      'ENABLE_BITCODE' => 'NO',
      'FRAMEWORK_SEARCH_PATHS' => '$(inherited) "${PODS_ROOT}/KandyWebRTC/Frameworks"',
      'OTHER_LDFLAGS' => '$(inherited) -framework WebRTC -ObjC',
      'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES'
    }



end
