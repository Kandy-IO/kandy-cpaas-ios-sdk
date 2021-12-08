# Change Log

CPaaS iOS SDK change log.

- This project adheres to [Semantic Versioning](http://semver.org/).
- This change log follows [keepachangelog.com](http://keepachangelog.com/) recommendations.

## 2.23.1 - 2021-12-07

### Fixed
- Build issues on systems using Apple Silicon M1 chip fixed.

## 2.23.0 - 2021-11-03

### Fixed
- XCode 13 compile issues were fixed.

### Known Issues

- Build issues on systems using Apple Silicon M1 chip.

## 2.22.0 - 2021-09-27

### Known Issues

- Build issues with manuel SDK integration on XCode 13.x version.

- Build issues on systems using Apple Silicon M1 chip.

## 2.21.0 - 2021-08-16

## 2.20.0 - 2021-06-29

## 2.19.0 - 2021-06-01

### Fixed
- Support for compressed push types is fixed. `KAE-984`
- Cannot receive notification about admin assignation in group chat is fixed. `KAE-976`

## 2.18.0 - 2021-04-26

## 2.17.0 - 2021-03-26

### Added
- XCFramework support was added
- `(NSArray<NSDictionary *> *) getAvailableCodecs:(CPCodecType)codecType` added to CPCallDelegate class in order to get available codec attributes.

## 2.15.0 - 2021-02-04

### Added
- Ringing feedback options`KAE-889` 

### Fixed
- First time build issue is fixed. `KAE-812`
- Cannot make multiple calls in short time is fixed. `KAE-891`
- Cannot make anonymous call is fixed. `KAE-924`
- WebRTC video orientation parameter should sync with Call Service video orientation is fixed. `KAE-916`
- WebSocket link created infinitely after WiFi reconnect is fixed. `KAE-911`
- Connection state change issue is fixed. `KAE-902`

## 2.14.0 - 2020-12-30

## 2.13.0 - 2020-12-02

### Fixed
- Printing call states is fixed. `KAE-885`

### Removed
- `useSecureConnection`, `domain`, `earlyMediaEnabled` and `DTLS` parameters removed from Configuration. `KAE-862`
- `CPSMSService.uriFormat` removed `KAE-761`

### Changed
- `replaceCodecSet` parameter renamed as `codecPayloadTypeSet`. `KAE-862`

## 2.12.0 - 2020-11-04

## 2.11.0 - 2020-10-05

### Changed
- Return type of `CPCall.getRTPStatistics` was changed as `String`

### Fixed
- Xcode 12 support was added

## 2.10.0 - 2020-08-28

### Added
- Trickle ICE support `KAE-79`

## 2.9.0 - 2020-07-22

### Deprecated
- The Property `CPSMSService.uriFormat` is depracated. It will be removed next releases. 

## 2.8.0 - 2020-07-03

### Changed
- Type of `CPMessage.status` was changed as `MessageDeliveryStatus`
- Type of `CPMessage.conversationType` was changed as `MessageSessionType`
- Type of `CPIsComposingMessage.direction` was changed as `MessageType`

### Note
- These changes is not backward compatible please check your related code base.

## 2.7.0 - 2020-06-12

### Fixed
- Swift compiler issue with upper version of 5.1.2 is fixed. `KAE-695`

### Note
- When importing Kandy CPaaS Mobile SDK please use main module instead of submodule for preventing further backward compability issues. eg. `import CPaaSSDK` for Swift and `@import CPaaSSDK` for Objective-C

## 2.6.0 - 2020-04-05

### Added
- Groups can now have multiple admins and Group properties such as name, subject and image can be changed. `KAE-532`

### Fixed
- Switch Front/Back camera does not work in call. `KAE-616`
- After Session Complete notification the end call DELETE request must be sent. `KAE-669`  

## 2.5.1 - 2020-04-14

### Fixed
- Not able to support Objective-C based projects `KAE-642`

## 2.5.0 - 2020-03-30

### Added
- New PushService parse api for CallKit was implemented `KAE-605`

### Temporary Limitation

- Kandy CPaaS iOS SDK version <b>2.4.0</b> and <b>2.5.0</b> have a known limitation with supporting Objective-C based projects. Swift projects are supported only

## 2.4.0 - 2020-03-02

### Added
- New PushService subscribe api was implemented `KAE-521`
- Xcode 11 and Swift 5.1.2 support `KAE-499`

### Fixed
- Not able to send multimedia file upper than 1MB on IM `KAE-583`

## 2.3.0 - 2020-01-09

### Added
- Call forward feature `KAE-81`

### Fixed
- Background thread was trying to access UI thread is fixed. `KAE-580`


## 2.2.0 - 2019-11-29

### Added
- WebRTC stack upgraded to version M78 KAE-508
- Custom CPaaS Agent HTTP Header is implemented KAE-524

## 2.1.0 - 2019-11-04

### Added
- ThreeWayCall feature implemented `KAE-86`

### Changed
- setCallApplication method has been updated as setCallApplicationDelegate in CPCallService class


## 2.0.0 - 2019-10-03

### Added
- Unified Plan Support `KAE-428`
- Mobile SDK Distribution on CocoaPods `KAE-426`


## 1.8.0 - 2019-08-05

### Added
- Consultative Transfer feature implemented `KAE-84`

### Fixed
- Delete chat message fixed. `KAE-480`


## 1.7.0 - 2019-07-05

### Added
- Blind (Direct) Transfer feature implemented `KAE-82`

### Fixed
- Error case that `fetchMessages(completion:)` method call causes on ChatService is fixed. `KAE-436`


## 1.6.0 - 2019-06-01

### Added
- Swift 5.0 support.

### Fixed
- Mobile SDK logs fixed to show the right version of SDK. `KAE-417`
- Compliance issue with Xcode 10.2.1 is fixed. `KAE-424`


## 1.5.0 - 2019-05-02

### Added
- Query SMS History feature implemented `KAE-291`
