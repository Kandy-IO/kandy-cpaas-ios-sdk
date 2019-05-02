# Presence

Presence publishing and watching are managed by the Presence Service which can be called from the `CPaaS` instance. In order to receive and send events, the `CPaaS` instance should be connected first. To see how to connect and set configurations, check **Login** and **Configurations** sections.

### Initialize the Presence Service

In order to use the Presence service, the service provider object must be properly initialized. When properly initialized, the application will be registered to receive Presence notifications from the server.

*Swift Code:*
```swift
// import the SDK
import CPaaSSDK

func initProvider() {
  // select the services that will be used by the application. Specify .presence for Presence
  // service to be enabled. The application should not register presence service for
  // notifications from the APN push service. Set push parameter to 'false'.
  let servicesToEnable = [CPServiceInfo(type: .sms, push: true),
                          CPServiceInfo(type: .presence, push: false)]

  // initialize a CPaaS service provider object with the
  // services that it should provide
  self.cpaas = CPaaS(services: servicesToEnable)
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

@interface AppModel : NSObject <CPPresenceDelegate>
@end

@implementation AppModel

- (void) initProvider {
	// select the services that will be used by the application. Specify ServiceTypePresence
	// for Presence service to be enabled. The application should not register presence service
	// for notifications from the APN push service. Set push parameter to 'false'.
    NSArray<CPServiceInfo*>* cpaasServices= @[[CPServiceInfo buildWithType:CPServiceTypeSms push:true],
                              				[CPServiceInfo buildWithType:CPServiceTypePresence push:false]];

    // initialize a CPaaS service provider object with the
    // services that it should provide
    self.cpaas = [[CPaaS alloc] initWithServices: cpaasServices];
 }
```

### Implement and Set PresenceDelegate

In order for the Mobile SDK to notify the application of notifications received from the server, a presence delegate must be set.

*Swift Code:*
```swift
import CPaaSSDK

class AppModel: PresenceDelegate {

    init() {
        self.cpaas.presenceService!.delegate = self
    }

    // ... application model code ...

    // MARK: PresenceDelegate methods
    func subscriptionExpired(presentityListHandle:PresentityListHandle) {
        // Re-subscribe if not refreshing on a periodic basis
        if presentityListHandle.isEqual(self.presentityList) {
        	self.service.refreshSubscriptions(expiringInSeconds:60){ error in
        		if let error == error {
        			print("An error occurred while refreshing subscriptions: \(error.localizedDecription)")
        		}
        	}
        }
    }

    func listChanged(presentityList: CPPresentityList) {
        // update model PresentityList
        if presentityList.isEqual(self.presentityList) {
            presentityList.fetchStatus {
                (error, newPresentityList) in
                if let error = error {
                    print("Error updating list from notification: \(error.localizedDescription)")
                } else {
                    self.presentityList = newPresentityList
                }
            }
        }
    }

    func statusChanged(presentity:CPPresentity) {
        // update model PresentityList
        self.presentityList?.statusChanged(presentity:presentity)
    }
}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

- (id)init {
    self = [super init];

    self.service = self.cpaas.presenceService;
    self.cpaas.presenceService.delegate = self;

    return self;
}

// ... application model code ...

#pragma mark PresenceDelegate methods

- (void)subscriptionExpiredWithPresentityListHandle:(PresentityListHandle * _Nonnull)presentityListHandle {
    // Re-subscribe if not refreshing on a periodic basis
    if (presentityListHandle.isEqual(self.presentityList)) {
        [self.service refreshSubscriptionsExpiringInSeconds:60 completion:^(CPError * _Nullable error) {
            if (error != nil) {
              NSLog(@"An error occurred while refreshing subscriptions: %@", error.localizedDecription);
            }
        }];
    }
}

- (void)listChangedWithPresentityList:(CPPresentityList * _Nonnull)presentityList {
    // update model PresentityList
    if ([presentityList isEqual:self.presentityList]) {
        [presentityList fetchStatusWithCompletion:^(CPError * _Nullable error, CPPresentityList * _Nullable newPresentityList) {
            if (error != nil) {
                NSLog(@"Error updating list from notification: %@", error.localizedDescription);
            } else {
                self.presentityList = newPresentityList;
            }
        }];
    }
}

- (void)statusChangedWithPresentity:(CPPresentity * _Nonnull)presentity {
      // update model PresentityList
      [self.presentityList statusChangedWithPresentity:presentity];
}
```

## Publishing Presence
An application publishes the status of a user by creating and updating a PresenceSource.

### Publish Presence Source

Publish the presence activity of the local user by creating new PresenceSource or updating an existing PresenceSource.

*Swift Code:*
```swift
import CPaaSSDK

    // Publish the local client status
    func publishPresence(activity:CPPresenceActivity, completion: @escaping ErrorCompletionBlock) {
        // local source hasn't been created, create one now
        if self.presenceSource == nil {
            self.service.createPresenceSource(activity: activity) {
                (error, newPresenceSource) in
                if error ==  nil {
                    self.presenceSource = newPresenceSource
                }
                completion(error)
            }
        } else {
            // update the existing presence source
            self.presenceSource?.updateActivity(activity:activity) {
                (error, updatedPresenceSource) in
                if error ==  nil {
                    self.presenceSource = updatedPresenceSource
                }
                completion(error)
            }
        }
    }

	func updateMyStatus(activityType:CPPresenceActivities) {
		let presenceActivity = CPPresenceActivity(activityType)
		self.publishPresence(activity: presenceActivity) {
            (error) in
            if error == nil, let presenceSource = self.presenceSource {
                self.updateStatus(withText:presenceSource.activity.string)
            } else {
                // an error occurred
                print("Couldn't update status: \(error.localizedDescription)")
            }
		}
	}
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

 /// Publish the local client status
- (void) publishPresenceWithActivity:(CPPresenceActivity*)activity completion:(void (^ _Nonnull)(CPError * _Nullable))completion {
    // local source hasn't been created, create one now
    if (self.presenceSource == nil) {
        [self.service createPresenceSourceWithActivity:activity completion:^(CPError * _Nullable error, CPPresenceSource * _Nullable newPresenceSource) {
            if (error == nil) {
                self.presenceSource = newPresenceSource;
            }
            completion(error);
        }];
    } else {
        // update the existing presence source
        [self.presenceSource updateActivityWithActivity:activity completion:^(CPError * _Nullable error, CPPresenceSource * _Nullable updatedPresenceSource) {
            if (error == nil) {
                self.presenceSource = updatedPresenceSource;
            }
            completion(error);
        }];
    }
}

- (void) updateMyStatusWithActivityType:(CPPresenceActivities)activityType {
	CPPresenceActivity* presenceActivity = [[CPPresenceActivity alloc] init:activityType];
    [self publishPresenceWithActivity:presenceActivity completion:^(CPError * _Nullable error) {
        PresenceSource* presenceSource = self.presenceSource;
        if (error == nil && presenceSource != nil) {
            [self updateStatusWithText:presenceSource.activity.string];
        } else {
            // an error occurred
            NSLog(@"Couldn't update status: %@", error.localizedDescription);
        }
    }];
}
```

## Watching User Presence
An application watches the presence status of other users by creating a presentity list and subscribing for notifications concerning changes to that users in that list. An application may modify the membership of the presentity watch list after creation.

### Watch Presentity List

Watch the status of users by creating a PresentityList with the contacts to watch. Then subscribe for notifications about changes to the PresentityList.

*Swift Code:*
```swift
import CPaaSSDK

	let contacts = ["user_a@domain.com", "user_b@domain.com", "user_c@domain.com"]
    self.service.createPresentityList(name: "default", presentities: contacts) {
       (error, newPresentityList) in
       if error == nil {
           self.presentityList = newPresentityList

           // subscribe for updates to this list
           self.presentityList?.subscribe { (error) in
               // don't indicate error to application, just print a log
               if let error = error {
                   print("Failed to subscribe to presentityList \(self.presentityList?.name ?? "nil"): \(error.localizedDescription)")
               }
           }
	   } else {
	       print("Failed to create presentityList \(self.presentityList?.name ?? "nil"): \(error.localizedDescription)")
       }
   }
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

	Array* contacts = @[@"user_a@domain.com", @"user_b@domain.com", @"user_c@domain.com"];
	[self.service createPresentityListWithName:@"default" presentities:contacts completion:^(CPError * _Nullable error, PresentityList * _Nullable newPresentityList) {
        if (error == nil) {
            self.presentityList = newPresentityList;

            // subscribe for updates to this list
            [self.presentityList subscribeWithCompletion:^(CPError * _Nullable error) {
                // don't indicate error to application, just print a log
                if (error != nil) {
                    NSLog(@"Failed to subscribe to presentityList %@: %@", self.presentityList.name, error.localizedDescription);
                }
            }];
        } else {
        	NSLog(@"Failed to create presentityList: %@", error.localizedDescription);
        }
    }];
```

### Add User to Presentity List

An application may choose add contacts to an existing PresentityList. No re-subscription to the list is necessary.

*Swift Code:*
```swift
import CPaaSSDK

    let presentity = CPPresentity(userID: "user_d@domain.com")
    self.presentityList?.add(presentity: presentity) {
        (error) in
        if let error = error {
            // an error occurred
            print("Couldn't add user: \(error.localizedDescription)")
        }
    }
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

    CPPresentity* CPpresentity = [[CPPresentity alloc] initWithUserID:@"user_d@domain.com"];
    [self.presentityList addWithPresentity:presentity completion:^(CPError * _Nullable error) {
        if (error != nil) {
            // an error occurred
            NSLog(@"Couldn't add user: %@", error.localizedDescription);
        }
    }];
```

### Remove User from Presentity List

An application may choose remove contacts from a PresentityList.

*Swift Code:*
```swift
import CPaaSSDK

    let presentity = CPPresentity(userID: "user_c@domain.com")
    self.presentityList?.remove(presentity: presentity) {
        (error) in
        if let error = error {
            // an error occurred
            print("Couldn't remove user: \(error.localizedDescription)")
        }
    }
```

*Objective-C Code:*
```objective-c
@import CPaaSSDK;

    CPPresentity* presentity = [[CPPresentity alloc] initWithUserID:@"user_c@domain.com"];
    [self.presentityList removeWithPresentity:presentity completion:^(CPError * _Nullable error) {
        if (error != nil) {
            // an error occurred
            NSLog(@"Couldn't remove user: %@", error.localizedDescription);
        }
    }];
```
