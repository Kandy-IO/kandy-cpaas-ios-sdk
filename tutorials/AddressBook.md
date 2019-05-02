# Address Book and Directory

$KANDY$ offers set of APIs to store, manage and search contacts through address books, lists and directories.

## Managing Address Book Contacts

### CPContact Object

$KANDY$ Mobile SDK provides and use `CPContact` model for all of the Address Book operations. A `CPContact` object should contain an unique ID and set of attributes.

`CPContact` object can also contain attributes such as:

* primary contact (corresponds to "User Id")
* first name
* last name
* email address
* home phone number
* business phone number
* fax number
* mobile phone number
* pager
* buddy (whether user is part of friends' group or not)
* username

### Adding a new Contact

$KANDY$ Mobile SDK provides `addContact` ability to add `CPContact` objects to user's address book. `addContact` operation requires a new `CPContact` object with unique Contact ID.

In default, addressbookId is `default`.

#### Example Usage

*Swift Code:*

```swift
import CPaaSSDK

/// First, create CPContact Object.
let entity = CPContact(contactId: <#unique identifier#>)
/// Set relevant informations
entity.mobile = <#mobile number#>
entity.email = <#email address#>
...

/// Save contact to personal addressbook
/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.addContact(contact: entity,
                                     completion: { (error) in
    if let error = error {
        NSLog("Couldn't save the contact to addressbook - Error: \(error.localizedDescription)")
        return
    }

    NSLog("Contact is saved to the addressbook")
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

/// First, create CPContact Object.
CPContact *entity = [[CPContact alloc] initWithContactId:<#unique identifier#>];
/// Set relevant informations
entity.mobile = <#mobile number#>;
entity.email = <#email address#>;
...

/// Save contact to personal addressbook
/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService addContactWithAddressbookId:@"default"
                                            contact:entity
                                         completion:^(CPError * _Nullable error) {
    if (error) {
        NSLog("Couldn't save the contact to addressbook - Error: %@", error.localizedDescription);
        return;
    }

    NSLog("Contact is saved to the addressbook");
}];
```

### Updating a contact

$KANDY$ Mobile SDK provides `updateContact` ability to update an existing `CPContact` on the user's specified address book. A contact's attributes can be updated through each change in the properties of the `CPContact` object. Update operation only changes provided modifications and giving empty string value can be used as a remove operation.

#### Example Usage

*Swift Code:*

```swift
import CPaaSSDK

/// Entity is the contact object that should be updated.
/// Edit relevant informations
entity.mobile = <#new mobile number#>
entity.email = <#new email address#>
...

/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.updateContact(contact: entity,
                                        completion: { (error) in
    if let error = error {
        NSLog("Couldn't update the contact to addressbook - Error: \(error.localizedDescription)")
        return
    }

    NSLog("Contact is updated")
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

/// Entity is the contact object that should be updated.
/// Edit relevant informations
entity.mobile = <#new mobile number#>;
entity.email = <#new email address#>;
...

/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService updateContactWithAddressbookId:@"default"
                                                 contact:entity
                                              completion:^(CPError * _Nullable error) {
    if (error) {
        NSLog("Couldn't update the contact to addressbook - Error: %@", error.localizedDescription);
        return;
    }

    NSLog("Contact is updated");
}];
```

### Getting all contacts

In order to fetch all contacts from a specific adddress book, $KANDY$ Mobile SDK provides `retrieveContactList` API.

#### Example Usage

```swift
import CPaaSSDK

/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.retrieveContactList(completion: { (error, contactList) in
if let error = error {
NSLog("Couldn't retrieve contact list from addressbook - Error: \(error.localizedDescription)")
return
}

for contact in contacts! {
NSLog("Contact: \(contact)")
}
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService retrieveContactListWithAddressBookId:@"default"
completion:^(CPError * _Nullable error,
NSArray<CPContact *> * _Nullable contactList) {
if (error) {
NSLog("Couldn't retrieve contact list from addressbook - Error: %@", error.localizedDescription);
return;
}

for (CPContact *contact in contactList) {
NSLog("Contact: %@", contact);
}
}];
```

### Getting a contact

In order to get a single contact from a specific adddress book, $KANDY$ Mobile SDK provides `getContact` API.

#### Example Usage

*Swift Code:*

```swift
import CPaaSSDK

/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.getContact(contactId: <#identifier of the contact#>,
completion: { (error, retrievedContact) in
if let error = error {
NSLog("Couldn't get the contact from addressbook - Error: \(error.localizedDescription)")
return
}

NSLog("Contact is retrieved successfuly - Contact: \(retrievedContact!)")
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService deleteContactWithAddressbookId:@"default"
contact:<#identifier of the contact#>
completion:^(CPError * _Nullable error, CPContact * _Nonnull retrievedContact) {
if (error) {
NSLog("Couldn't get the contact from addressbook - Error: %@", error.localizedDescription);
return;
}

NSLog("Contact is retrieved successfuly - Contact: %@", retrievedContact);
}];
```


### Deleting a contact

In order to delete a single contact from a specific adddress book, $KANDY$ Mobile SDK provides `deleteContact` API.

#### Example Usage

*Swift Code:*

```swift
import CPaaSSDK

/// Entity is the contact object that should be removed.
/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.deleteContact(identifier: entity.contactId,
                                        completion: { (error) in
    if let error = error {
        NSLog("Couldn't delete the contact from addressbook - Error: \(error.localizedDescription)")
        return
    }

    NSLog("Contact is deleted")
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

/// Entity is the contact object that should be removed.
/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService deleteContactWithAddressbookId:@"default"
                                                 contact:entity.contactId
                                              completion:^(CPError * _Nullable error) {
    if (error) {
        NSLog("Couldn't delete the contact from addressbook - Error: %@", error.localizedDescription);
        return;
    }

    NSLog("Contact is deleted");
}];
```

### Directly updating or removing contact attributes

$KANDY$ Mobile SDK provides ability to updating or removing a specific contact attribute.

#### Example Usage

To update an attribute of the contact:

*Swift Code:*

```swift
import CPaaSSDK

/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.updateAttribute(contactIdentifier: <#Contact Identifier#>, attributeId: <#Attribute Name#>, attributeVal: <#New Value#>, completion: { (error) in
    if let error = error {
        NSLog("Couldn't update the attribute from addressbook - Error: \(error.localizedDescription)")
        return
    }

    NSLog("Contact is deleted")
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService updateAttributeWithAddressbookId:@"default"
                                         contactIdentifier: <#Contact Identifier#>
                                               attributeId: <#Attribute Name#>
                                              attributeVal: <#New Value#>
                                                completion:^(CPError * _Nullable error) {
    if (error) {
        NSLog("Couldn't update the attribute from addressbook - Error: %@", error.localizedDescription);
        return;
    }

    NSLog("Contact is deleted");
}];
```
To remove an attribute, you need to provide ID of the attribute (`AttributeName`) to AddressBookService

*Swift Code:*

```swift
import CPaaSSDK

/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.updateAttribute(contactIdentifier: <#Contact Identifier#>, attributeId: <#Attribute Name#>, completion: { (error) in
    if let error = error {
        NSLog("Couldn't delete the attribute from addressbook - Error: \(error.localizedDescription)")
        return
    }

    NSLog("Contact is deleted")
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService updateAttributeWithAddressbookId:@"default"
                                         contactIdentifier: <#Contact Identifier#>
                                               attributeId: <#Attribute Name#>
                                                completion:^(CPError * _Nullable error) {
    if (error) {
        NSLog("Couldn't delete the attribute from addressbook - Error: %@", error.localizedDescription);
        return;
    }

    NSLog("Contact is deleted");
}];
```

## Managing Address Book Lists

$KANDY$ Mobile SDK offers ability to manage address book lists.


### Adding a new address book list

$KANDY$ Mobile SDK provides `addAddressBookList` ability to add `AddressBookList` objects to user's address book lists. `addAddressBookList` operation requires a new `AddressBookList` object with unique list ID.

*Swift Code:*

```swift
import CPaaSSDK

var exampleList = CPAddressBookList(listId: <#List Name#>)
// ... setting Contact's attributes

/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.addAddressBookList(addressbookList: exampleList, completion: { (error, newList) in
    if let error = error {
        NSLog("Couldn't create new list - Error: \(error.localizedDescription)")
        return
    }

    // exampleList successfully added to user's "default" address book and AddAddressBookListCallback returns uploaded exampleList object value.
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

CPAddressBookList *exampleList = [[CPAddressBookList alloc] initWithListId:<#List Name#>];
// ... setting Contact's attributes

/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService addAddressBookListWithAddressBookId:@"default"
                                              addressbookList:exampleList
                                                   completion:^(CPError * _Nullable error, CPAddressBookList * _Nullable newList) {
    if (error) {
        NSLog("Couldn't create new list - Error: %@", error.localizedDescription);
        return;
    }

    // exampleList successfully added to user's "default" address book and AddAddressBookListCallback returns uploaded exampleList object value.

}];
```

### Adding or updating contact's to address book list membership

Address Book list membership of the contact can be managed by `CPContact` object's `lists` property. A contact can contain multiple address book list membership, but this number can vary between address book providers. Current implementation of the $KANDY$ Address Book service only allows one adress book list membership.

Example usage of adding or updating a contact to list on $KANDY$ Mobile SDK:

*Swift Code:*

```swift
import CPaaSSDK;

/// Entity is the contact object that should be updated.
entity.lists.append(<#List Name#>)

/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.updateContact(contact: entity,
                                     completion: { (error) in
    if let error = error {
        NSLog("Couldn't update the contact to addressbook - Error: \(error.localizedDescription)")
        return
    }

    NSLog("Contact is updated")
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

/// Entity is the contact object that should be updated.
NSMutableArray *newListsArray = [[NSMutableArray alloc] initWithArray:entity.lists];
[newListsArray addObject:@"<#List Name#>"];
entity.lists = newListsArray;

/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService updateContactWithAddressbookId:@"default"
                                                 contact:entity
                                              completion:^(CPError * _Nullable error) {
    if (error) {
        NSLog("Couldn't update the contact to addressbook - Error: %@", error.localizedDescription);
        return;
    }

    NSLog("Contact is updated");
}];
```

Note that, this operation requires using `updateContact` operation, $KANDY$ Mobile SDK does not provide separate address book list API. Also, this operation will create a new address book list if that's not created previosly.

### Updating an address book list

$KANDY$ Mobile SDK provides `updateAddressBookList` ability to update an existing `AddressBookList`s while maintaining its membership information.

*Swift Code:*

```swift
import CPaaSSDK

var updatedList = CPAddressBookList(listId: <#List Name#>)

/// cpaas is the main instance which holds logged-in user.
/// existingList is the list which will be updated
cpaas.addressBookService?.updateAddressBookList(oldListId: existingList.listId, addressbookList: updatedList
                                                completion: { (error, newList) in
    if let error = error {
        NSLog("Couldn't update the list - Error: \(error.localizedDescription)")
        return
    }

    NSLog("List is updated")
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

CPAddressBookList *updatedList = [[CPAddressBookList alloc] initWithListId:<#List Name#>];

/// cpaas is the main instance which holds logged-in user.
/// existingList is the list which will be updated
[cpaas.addressBookService updateAddressBookListWithAddressbookId:@"default"
                                                       oldListId: existingList.listId
                                                 addressbookList: updatedList
                                                      completion:^(CPError * _Nullable error, CPAddressBookList * _Nullable newList) {
    if (error) {
        NSLog("Couldn't update the list - Error: %@", error.localizedDescription);
        return;
    }

    NSLog("List is updated");
}];
```

### Getting all address book lists

In order to fetch all address book lists from a specific adddress book, $KANDY$ Mobile SDK provides `retrieveAddressBookLists` API.

*Swift Code:*

```swift
import CPaaSSDK

/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.retrieveAddressBookList(completion: { (error, lists) in
    if let error = error {
        NSLog("Couldn't retrieve the lists - Error: \(error.localizedDescription)")
        return
    }

    NSLog("Lists are retrieved - Lists: \(lists)")
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService retrieveAddressBookListWithAddressBookId:@"default"
                                                        completion:^(CPError * _Nullable error, NSArray<CPAddressBookList *> * _Nullable lists) {
    if (error) {
        NSLog("Couldn't retrieve the lists - Error: %@", error.localizedDescription);
        return;
    }

    NSLog("Lists are retrieved - Lists: %@", lists);
}];
```

### Getting an address book list

In order to get a address book list from a specific adddress book, $KANDY$ Mobile SDK provides `getAddressBookList` API.

Example usage of the `getAddressBookList` API:

*Swift Code:*

```swift
import CPaaSSDK

/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.getAddressBookList(listId: <#List Name#>, completion: { (error, list) in
    if let error = error {
        NSLog("Couldn't retrieve the list - Error: \(error.localizedDescription)")
        return
    }

    NSLog("List is retrieved")
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService getAddressBookListWithAddressBookId:@"default" listId:<#List Name#>
                                                   completion:^(CPError * _Nullable error, CPAddressBookList * _Nullable list) {
    if (error) {
        NSLog("Couldn't retrieve the list - Error: %@", error.localizedDescription);
        return;
    }

    NSLog("List is retrieved");
}];
```

### Deleting an address book list

In order to delete a address book list, $KANDY$ Mobile SDK provides `deleteAddressBookList` API.

Example usage of the `deleteAddressBookList` API:

*Swift Code:*

```swift
import CPaaSSDK

/// cpaas is the main instance which holds logged-in user.
cpaas.addressBookService?.deleteAddressBookList(listId: <#List Name#>, completion: { (error) in
    if let error = error {
        NSLog("Couldn't delete the list - Error: \(error.localizedDescription)")
        return
    }

    NSLog("List is deleted")
})
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

/// cpaas is the main instance which holds logged-in user.
[cpaas.addressBookService deleteAddressBookListWithAddressBookId:@"default" listId:<#List Name#>
                                                      completion:^(CPError * _Nullable error) {
    if (error) {
        NSLog("Couldn't delete the list - Error: %@", error.localizedDescription);
        return;
    }

    NSLog("List is deleted");
}];
```

## Directory Search

By using $KANDY$ Mobile SDK, valid contacts in the cloud can be found by performing search operation in `Directory`. In below, how correct search operation can be done is explained.

$KANDY$ performs search operation by taking `CPSearch` object as a parameter. `CPSearch` contains:

* `CPSearchFilter`: Keyword (value) - Field Type pair
* `directoryId: `Directory Identifier
* `orderBy`: Order Type
* `sortBy`: Sorting Rule
* `limit`: Maximum number of contacts will return from operation

### Filter (CPSearchFilter)

#### Value (Keyword)

$KANDY$ searches keyword parameter in the specified `Field Type`. Keyword supports `String` and `NSString`, and shouldn't be `nil` or empty string.

#### Type (Field Type)

Field type points to search keyword in which fields of the contacts in the directory. Available types are specified by `CPAddressBook.FieldType` enum, and available values are:

* name (Searches keyword in both first name and last name fields of contacts)
* firstname (Searches keyword in first name field of contacts)
* lastname (Searches keyword in last name field of contacts)
* username (Searches keyword in username field of contacts)
* phoneNumber (Searches keyword in phone number fields of contacts)

### Order Type

The list of contacts which returned from the search operation will be ordered by the specified order type. Types are `ascending` and `descending` and specied by `CPAddressBook.OrderType` enum.

### Sorting Rule

Specifies to $KANDY$ how to sort results. Available types are specified by `CPAddressBook.FieldType` enum, and in below available values are given:

* name
* firstname
* lastname
* username
* phoneNumber

If Sorting rule is not specified, operation will be performed by using same type used in the `CPSearchFilter` object when passed as an argument to `CPSearch`.

### Limit

Points how many results should be returned from the operation and takes `Int` or `NSUInteger` as an argument. `0` shouldn't be used, which will cause failure.

If pagination or similar mechanism will be used which will need to divide results, limit should be set to positive integer larger than `0` and `getNext` method can be used which will defined in the `CPSearchResult` object.

### Directory Identifier

Directory Identifier points to $KANDY$ where search operation will be done. Currently $KANDY$ only supports `default` identifier. Identifier parameter type should be `String` or `NSString`.


### CPSearchResult

When directory operation is completed successfuly, completion block will return non-nil `CPSearchResult` object as an argument. `CPSearchResult` contains relevant contacts if there is any, and some handy properties.

#### Contacts

Returns relevant contacts searched with the specified parameters as an array. If operation succeeds even no relevant contacts have been found, this array won't be nil.

#### hasNext

This property is only meaningful if `limit` value is defined in the `CPSearch` object which was used in directory search operation. If query result has more contacts than specified `limit`, `hasNext` will return `true`, in all other cases will return `false`. To get next chunk of contacts of the operation `getNext(completion:)` can be used.

#### getNext(completion:)

Returns next chunk of contacts of the succeded directory search operation. Before use, checking whether `hasNext` is `true` or not is recommended. If `hasNext` returns `false`, `getNext(completion:)` will be failed.


### Example Usage

Let assume `UISearchController` will be used in the application in order to show users according to the what they are searching. In every update on the search controller will be called `updateSearchResults(for:)` method defined in `UISearchControllerDelegate`. For more details please see Apple Documentations.

*Swift Code:*

```swift
import CPaaSSDK

func updateSearchResults(for searchController: UISearchController) {
    guard let searchText = searchController.searchBar.text,
        searchText.count > 0 else {
            self.searchResultArray = []
            /// searchResults is the array of contacts as global variable
            /// TableView Cells are initialized according to them.
            self.tableView.reloadData()
            return
    }

    let searchObj = CPSearch(filter: CPSearchFilter(value: searchText, forType: <#field type#>))
    searchObj.orderBy = <#orderType#>
    searchObj.sortBy = <#sortType#>
    searchObj.limit = <#max value#>
    /// cpaas is the main CPaaS instance which holds logged-in user.
    cpaas.addressBookService?.search(with: searchObj, completion: { (error, result) in
        if let error = error {
            self.searchResultArray = []
            self.cpSearchResult = nil
            /// searchResultArray is the array of contacts as global variable
            /// TableView Cells are initialized according to them.
            self.tableView.reloadData()
            NSLog("Couldn't search in directory - Error: \(error.localizedDescription)")
            return
        }

        self.searchResultArray = result.contacts!
        self.cpSearchResult = result
        self.tableView.reloadData()
    })

}
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

- (void)updateSearchResultsForSearchController:(UISearchController *)searchController {
    NSString *searchText = searchController.searchBar.text;
    if (searchText.length <= 0) {
        /// searchResults is the array of contacts as global variable
        /// TableView Cells are initialized according to them.
        searchResultArray = [[NSMutableArray alloc] init];
        [self.tableView reloadData];
        return;
    }

    CPSearchFilter *filter = [[CPSearchFilter alloc] initWithValue:searchText forType:<#field Type#>];
    CPSearch *search = [[CPSearch alloc] initWithFilter:filter];
    [search setOrderBy:<#orderType#>];
    [search setSortBy:<#sortType#>];
    [search setLimit:<#max value#>];
    /// cpaas is the main CPaaS instance which holds logged-in user.
    cpaas.addressBookService searchWith:search completion:^(CPError * _Nullable error, NSArray<CPContact *> * _Nullable result) {
        if (error) {
            /// searchResultArray is the array of contacts as global variable
            /// TableView Cells are initialized according to them.
            searchResultArray = [[NSMutableArray alloc] init];
            cpSearchResult = nil;
            [self.tableView reloadData];
            NSLog(@"Couldn't search in directory - Error: %@", error.localizedDescription);
            return;
        }

        searchResults = [NSMutableArray arrayWithArray:result.contacts];
        cpSearchResult = result;
        [self.tableView reloadData];
    }];

}
```

### Obtaining more results from `CPSearchResult`:

*Swift Code:*

```swift
import CPaaSSDK

func nextSearchResults(searchResult: CPSearchResult) {
    if searchResult.hasNext {
        searchResult.getNext { (error, result) in
            if let error = error {
                NSLog("Couldn't search in directory - Error: \(error.localizedDescription)")
                return
            }

            if let result = result {
                // Next results are obtained.
                // Store new CPSearchResult if planning to use again
            }
        }
    }
}
```

*Objective-C Code:*

```objective-c
@import CPaaSSDK;

- (void)nextSearchResults:(CPSearchResult *)searchResult {
    if (searchResult && searchResult.hasNext) {
        [searchResult getNextWithCompletion:^(CPError * _Nullable error, CPSearchResult * _Nullable searchResult) {
            if (error) {
                NSLog(@"Couldn't search in directory - Error: %@", error.localizedDescription);
                return;
            }

            if (searchResult) {
            // Next results are obtained.
            // Store new CPSearchResult if planning to use again
            }
        }];
    }
}
```
