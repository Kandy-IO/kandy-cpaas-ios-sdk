---
  topics:
  - title: Using the $KANDY$ Mobile SDK in the iOS Project
    body: In this section you will learn how to use the $KANDY$ Mobile SDK in the iOS project.
  - title: Creating the iOS project
    body: In this section you will learn how to create the iOS project using XCode.
---
# Get Started

## Installation

This section contains the required steps for beginning your mobile application development by using $KANDY$ Mobile SDK in the Xcode iOS project.

## Compatible XCode and Swift Versions

The applications which uses $KANDY$ MobileSDK can be built with the XCode 11.x+ and Swift 5.1.2+ versions.

## Creating the iOS project

1. Open the Xcode application.
2. Click Create a new Xcode project.
3. Click **iOS** heading, select **Single View App**, and click **Next**.

![alt text](img/get_started_1.png)

4. Type the project details and click **Create**.
5. Select one of the installation methods below

### Cocoapods installation
1. Add below pods to your Podfile (If you dont have any Podfile, visit this link to install cocoapods: https://guides.cocoapods.org/using/using-cocoapods.html)

* pod 'KandyCPaaSMobileSDK', '~> $SDK_VERSION$'

2. Go to project folder via command line and run "pod install" command and wait for cocoapods to finish installation of Kandy CPaaS MobileSDK & WebRTC frameworks and their dependencies

If you have a trouble with getting latest version of *$KANDY$ iOS SDK* plaese run these suggested commands [here](https://gist.github.com/mbinna/4202236) in project directory where Podfile is located.

### Manual Installation
 Before those steps you need to download **$KANDY$ iOS SDK** framework file from [this link](https://raw.githubusercontent.com/Kandy-IO/kandy-cpaas-ios-sdk/$SDK_VERSION$/dist/CPaaSSDK_$SDK_VERSION$.zip)

1. Go to project settings and navigate to **Build Phases**.
2. Add **CPaaSSDK.framework** under **Link Binary With Libraries** section.

![alt text](img/get_started_2.png)

3. Add the following frameworks to the project under the **Link Binary With Libraries**:
	* AvFoundation.framework
	* SystemConfiguration.framework
	* CFNetwork.framework
	* Security.framework
	* OpenGLES.framework
	* QuartzCore.framework
	* AudioToolbox.framework
	* CoreAudio.framework
	* CoreMedia.framework
	* CoreVideo.framework
	* CoreGraphics.framework
	* UIKit.framework
	* Foundation.framework
	* GLKit.framework
	* libc++.tbd
	* libsqlite3.tbd
	* libstdc++.6.0.9.tbd
	* libstdc++.tbd
	* libicucore.tbd

4. Add WebRTC.framework under the **Embedded Binaries** section in **General** tab on Project Settings. Select **Copy items if needed**.
5. Under the **Build Settings** section, search for **Framework Search Paths** and add the following:

  `$(PROJECT_DIR)/CPaaSSDK.framework/SubFrameworks/`

  **Note:** If framework is located in different place rather than main directory of project, above line should be modified accordingly.

**CPaaS SDK** is now ready to implementation.


6. The following part shows how to use **$KANDY$ Mobile SDK** with basic features. While codes are shared for both *Swift* and *Objective-C* languages, some parts may need different implementations, are also indicated.

  **If the project language is selected as *Swift*, do the following:**
  * Navigate to the **Build Settings** in the project settings.
  * Search for **Other Linker Flags** listed under the **Linking** and click.
  * Click **+** button in the list appeared next under to the **Other Linker Flags**.
  * Type *-ObjC* and close the panel.

  ![alt text](img/get_started_3.png)

  * In order to run framework, search for **Enable Bitcode** option listed under the **Build Options**, and change it to the **NO**.

  $KANDY$ Mobile SDK is now ready to use in the application.

### Using the $KANDY$ Mobile SDK in the iOS Project
1. Open *Main.storyboard* and create a basic user interface which contains username, password text fields, and login button.
<hr/>
     <b>Note</b>, when importing $KANDY$ Mobile SDK please import main module instead of submodule for preventing further backward compability issues.
     <br/>
    eg. <code>import CPaaSSDK</code> for Swift and <code>@import CPaaSSDK</code> for Objective-C
<hr/>
2. Set **CPAuthenticationDelegate** to view controller and add protocol stubs.

![alt text](img/get_started_4.png)

3. In order to set configurations for registering to $KANDY$, add followings in to login action.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

let configuration = CPConfig.sharedInstance()
configuration.restServerUrl = "$KANDYFQDN$"
configuration.restServerPort = "443"
configuration.useSecureConnection = true
```

#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

CPConfig *configuration = [CPConfig sharedInstance];
configuration.restServerUrl = @"$KANDYFQDN$";
configuration.restServerPort = @"443";
configuration.useSecureConnection = YES;
```

<!-- tabs:end -->

4. Getting access and id token is explained in [**Getting Access and Id Token from Provider**](GetStarted.md#getting-access-and-id-token-from-provider) section in detail.

5. When all configurations are set correctly, connect method can be called as following.

<!-- tabs:start -->

#### ** Swift Code **

```swift
import CPaaSSDK

let services = [CPServiceInfo(type: .call, push: true), CPServiceInfo(type: .chat, push: true), CPServiceInfo(type: .sms, push: true)]

cpaas = CPaaS(services: services)
cpaas.authenticationService.delegate = self
cpaas.authenticationService.connect(idToken: <ID-Token>, accessToken: <Access-Token>, lifetime: 3600) { (error, channelInfo) in
    if let error = error {
        print("error occured: \(error.localizedDescription)")
        return
    }

    print("Channel Info: \(channelInfo!)")
}
```
#### ** Objective-C Code **

```objectivec
@import CPaaSSDK;

NSArray* services= @[[CPServiceInfo buildWithType:CPServiceTypeSms push:YES],
                    [CPServiceInfo buildWithType:CPServiceTypeCall push:YES],
                    [CPServiceInfo buildWithType:CPServiceTypeChat push:YES]];

cpaas = [[CPaaS alloc] initWithServices: services];
cpaas.authenticationService.delegate = self;
[cpaas.authenticationService connectWithIdToken:<YOUR_ID_TOKEN> accessToken:<YOUR_ACCESS_TOKEN> lifetime:lifetime completion:^(CPError * _Nullable error, NSString * _Nullable channelInfo) {
        if (error) {
        	NSLog(@"error occured: %@", error.localizedDescription);
        	return
        }

        NSLog(@"Channel Info: %@", channelInfo);
}];
```
<!-- tabs:end -->

6. When $KANDY$ is registered, **connectionStatusChanged(state:)** method will be called by *CPAuthenticationDelegate*.

![alt text](img/get_started_5.png)

## Getting Access and Id Token from Provider

<!-- tabs:start -->

#### ** Swift Code **

```swift
func requestAccessToken(completion: @escaping (_ error: String?, _ accessToken: String?)->()) {
    var request = createAuthenticationRequest(with: self.clientID)
    var bodyStr = String(format: "grant_type=password&username=%@&password=%@&client_id=%@&scope=openid", UserConfigurations.sharedInstance.username!, self.password!, self.clientID)
    bodyStr = self.clientSecret != nil && self.clientSecret != "" ? bodyStr+"&clientSecret="+self.clientSecret : bodyStr
    request.httpBody = bodyStr.data(using: String.Encoding.utf8)
    
    self.makeAccessTokenRequest(request: request, completion: completion)
}

private func createAuthenticationRequest(with clientID: String) -> URLRequest {

        let url = URL(string: "https://$KANDYFQDN$/cpaas/auth/v1/token")!
        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        request.setValue("application/x-www-form-urlencoded", forHTTPHeaderField: "Content-Type")
        return request
        
    }

private func makeAccessTokenRequest(request:URLRequest, completion: @escaping (_ error: String?, _ accessToken: String?)->()) {
    let task = URLSession.shared.dataTask(with: request) { (data, response, error) in
        if let error = error {
            print("Can't get access token - Error: \(error.localizedDescription)")
            completion(error.localizedDescription, nil)
            return
        } else if let response = response as? HTTPURLResponse {
            if response.statusCode < 300 {
                if data != nil {
                    guard let json = try? JSONSerialization.jsonObject(with: data!, options: JSONSerialization.ReadingOptions(rawValue: 0)),
                        let jsonDictionary = json as? [String: AnyObject] else {
                            print("Couldn't parse response body")
                            completion("Couldn't parse response body", nil)
                            return
                    }
                    //YOUR_ACCESS_TOKEN
                    let accessToken = jsonDictionary["access_token"] as? String
                    //YOUR_ID_TOKEN
                    if let idToken = jsonDictionary["id_token"] as? String { UserConfigurations.sharedInstance.idToken = idToken }
                    if let refreshT = jsonDictionary["refresh_token"] as? String {
                        self.refreshToken = refreshT
                    }
                    
                    if let accessTokenStr = accessToken {
                        completion(nil, accessTokenStr)
                    } else {
                        completion("Can't get access token: \(jsonDictionary.description)", nil)
                    }
                }
            } else {
                // some http error code
                completion("\(response.statusCode) - \(HTTPURLResponse.localizedString(forStatusCode: response.statusCode))", nil)
            }
        } else {
            completion("Unexpected response.", nil)
        }
    }
    task.resume()
}
```
#### ** Objective-C Code **

```objectivec
(void)requestAccessToken: (void (^)(NSString *_Nullable error, NSString *_Nullable accessToken, NSString *_Nullable accessTokenTimeOut))completion {
    NSMutableURLRequest *request = [self createAuthenticationRequestWithClientID:_clientID];
    NSString *bodyStr = [NSString stringWithFormat:@"grant_type=password&username=%@&password=%@&client_id=%@&scope=openid", UserConfigurations.sharedInstance.username!, self.password!, self.clientID];
    bodyStr = _clientSecret && ![_clientSecret isEqualToString:@""] ? [NSString stringWithFormat:@"%@&client_secret=%@", bodyStr, _clientSecret] : bodyStr;
    
    [request setHTTPBody:[bodyStr dataUsingEncoding:kCFStringEncodingUTF8]];
    [self makeAccessTokenRequest:request completion:completion];
}

- (NSMutableURLRequest *) createAuthenticationRequestWithClientID: (NSString *)_id {
    NSString *urlStr = [NSString stringWithFormat:@"https:%@/cpaas/auth/v1/token", [[CPConfig sharedInstance] restServerUrl]];
    NSURL *url = [NSURL URLWithString:urlStr];
    NSMutableURLRequest * request = [NSMutableURLRequest requestWithURL:url];
    [request setHTTPMethod:@"POST"];
    [request setValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
    return request;
}


 (void)makeAccessTokenRequest:(NSMutableURLRequest *)request completion: (void (^)(NSString * _Nullable error, NSString * _Nullable accessToken, NSString * _Nullable accessTokenTimeOut))completion {
    NSURLSessionDataTask *task = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error != nil) {
            completion([NSString stringWithFormat:@"Can't get access token - Error: %@", error.localizedDescription], nil, nil);
            return;
        }
        if (data != nil) {
            NSError *e = nil;
            NSDictionary *dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&e];
            if (!dict) {
                NSLog(@"Couldn't parse response body - Error: %@", e);
                completion([NSString stringWithFormat:@"Couldn't parse response body - Error: %@", e], nil, nil);
            } else {
                //YOUR_ACCESS_TOKEN
                NSString *accessToken = dict[@"access_token"];
                _refreshToken = dict[@"refresh_token"];
                //YOUR_ID_TOKEN
                NSString *idToken = dict[@"id_token"];
                if (idToken) [[UserConfigurations sharedInstance] setIdToken:idToken];
                if (accessToken) {
                    [self.CPaaS.authenticationService setToken:accessToken];
                    completion(nil, accessToken, dict[@"expires_in"]);
                } else {
                    completion([NSString stringWithFormat:@"Couldn't get access token - Error: %@", dict.description], nil, nil);
                }
            }
        }
    }];
    [task resume];
}
```
<!-- tabs:end -->
