# Kandy CPaaS iOS SDK

<p>
    <img alt="Cocoapods platforms" src="https://img.shields.io/cocoapods/p/KandyCPaaSMobileSDK">
    <img alt="GitHub release (latest SemVer)" src="https://img.shields.io/github/v/release/kandy-io/kandy-cpaas-ios-sdk">
    <img alt="Cocoapods" src="https://img.shields.io/cocoapods/v/KandyCPaaSMobileSDK">
</p>

## Install

### CocoaPods

[CocoaPods](https://cocoapods.org/pods/KandyCPaaSMobileSDK) is a dependency manager for Cocoa projects. For usage and installation instructions, visit their website. To integrate *Kandy CPaaS iOS SDK* into your Xcode project using CocoaPods, specify it in your `Podfile`:

```ruby
...

target 'YOUR_TARGET_NAME' do
    pod 'KandyCPaaSMobileSDK', '~> 2.14.0'
end

post_install do |installer|
  installer.pods_project.targets.each do |target|
    target.build_configurations.each do |config|
      config.build_settings['ENABLE_BITCODE'] = 'NO'
    end
  end
end

...
```

### Manual

Alternatively *Kandy CPaaS iOS SDK* can be manually integrated to your project with the [followed steps](https://kandy-io.github.io/kandy-cpaas-ios-sdk/tutorials/#/GetStarted?id=manual-installation).

## Documentation

The information about tutorials and documents can be found in the links below

* Documents: [API Docs](https://kandy-io.github.io/kandy-cpaas-ios-sdk/docs)

* Tutorials: [User Guide](https://kandy-io.github.io/kandy-cpaas-ios-sdk/tutorials)

## Compatibility

Compatible iOS versions :

* iOS 10.x+

Compatible XCode and Swift Versions :

* XCode 12.x+

* Swift 5.2.x+

Tested on :

* iPhone 5S, 5C, 6S, 7, 7+, 8, X, iPad mini, iPad 4, and iPad Air
