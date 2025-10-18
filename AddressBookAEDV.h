#pragma once //only included once

#include "Contact.h"
#include <vector>
#include <string>

class AddressBookAEDV
{
private:
    std::vector<Contact> contacts_;

    Contact* FindContactById(int contactId);

public:
    // operations
    void AddContact(const Contact& contact);
    bool EditContact(int contactId, const Contact& updatedContact);
    bool DeleteContact(int contactId);
    void ViewContact(int contactId) const; //see specific ID
    void ListAllContacts() const; //testing and or see ID, view all contacts
};
