# Change Log

CPaaS iOS SDK change log.

- This project adheres to [Semantic Versioning](http://semver.org/).
- This change log follows [keepachangelog.com](http://keepachangelog.com/) recommendations.

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
