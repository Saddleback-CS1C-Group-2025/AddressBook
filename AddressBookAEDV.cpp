#include "AddressBookAEDV.h"
#include <iostream>
#include <algorithm>

//helper point3r
Contact* AddressBookAEDV::FindContactById(int contactId) {
    for (size_t i = 0; i < contacts_.size(); ++i) {
        if (contacts_[i].getId() == contactId) {
            return &contacts_[i]; // return pointer and not a copy (referance)
        }
    }
    return nullptr; // it wasnt  found
}

//add contact
void AddressBookAEDV::AddContact(const Contact& contact)
{
    contacts_.push_back(contact);
}

//edit contact
bool AddressBookAEDV::EditContact(int contactId, const Contact& updatedContact) 
{
    Contact* contact = FindContactById(contactId);
    if (!contact) return false;

    // Replace fields individually (id would stay  unchanged)
    contact->setType(updatedContact.getType())
           .setFirstName(updatedContact.getFirstName())
           .setLastName(updatedContact.getLastName())
           .setEmail(updatedContact.getEmail())
           .setPhone(updatedContact.getPhone())
           .setAddressLine(updatedContact.getAddressLine())
           .setCity(updatedContact.getCity())
           .setState(updatedContact.getState())
           .setPostalCode(updatedContact.getPostalCode())
           .setNotes(updatedContact.getNotes());
    return true;
}

//delete contact
bool AddressBookAEDV::DeleteContact(int contactId) {
    auto it = std::remove_if(contacts_.begin(), contacts_.end(),
                             [contactId](const Contact& c){ return c.getId() == contactId; });
    if (it == contacts_.end()) return false;

    contacts_.erase(it, contacts_.end());
    return true;
}

//view contact
void AddressBookAEDV::ViewContact(int contactId) const
{
    for (const auto& contact : contacts_)
    {
        if (contact.getId() == contactId) 
        {
            std::cout << contact;
            return;
        }
    }
    std::cout << "Contact with ID " << contactId << " not found.\n";
}

//list thm all
void AddressBookAEDV::ListAllContacts() const
{
    for (const auto& contact : contacts_)
    {
        std::cout << "ID: " << contact.getId() << " | Name: " 
                  << contact.getFullName() << " | Type: " 
                  << Contact::contactTypeToString(contact.getType()) << "\n";
    }
}



/*#include "AddressBookAEDV.h"
#include <iostream>

int main() {
    AddressBookAEDV ab;
    int choice;

    do {
        std::cout << "1. Add Contact\n";
        std::cout << "2. Edit Contact\n";
        std::cout << "3. Delete Contact\n";
        std::cout << "4. View Contact\n";
        std::cout << "5. List All Contacts\n";
        std::cout << "0. stop\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore(); // clear newline

        switch (choice) {
        case 1: {
            std::string first, last, email, phone;
            std::cout << "first name: ";
            std::getline(std::cin, first);
            std::cout << "last name: ";
            std::getline(std::cin, last);
            std::cout << "email: ";
            std::getline(std::cin, email);
            std::cout << "phone: ";
            std::getline(std::cin, phone);

            Contact newContact(ContactType::Person, first, last, email, phone);
            ab.AddContact(newContact);
            std::cout << "Contact added!\n";
            break;
        }
        case 2: {
            int id;
            std::cout << "Enter contact ID to edit: ";
            std::cin >> id;
            std::cin.ignore();

            std::string first, last, email, phone;
            std::cout << "Enter new first name: ";
            std::getline(std::cin, first);
            std::cout << "Enter new last name: ";
            std::getline(std::cin, last);
            std::cout << "Enter new email: ";
            std::getline(std::cin, email);
            std::cout << "Enter new phone: ";
            std::getline(std::cin, phone);

            Contact updated(ContactType::Person, first, last, email, phone);
            if (ab.EditContact(id, updated))
                std::cout << "Contact updated!\n";
            else
                std::cout << "Contact ID not found.\n";
            break;
        }
        case 3: {
            int id;
            std::cout << "Enter contact ID to delete: ";
            std::cin >> id;
            std::cin.ignore();
            if (ab.DeleteContact(id))
                std::cout << "Contact deleted!\n";
            else
                std::cout << "Contact ID not found.\n";
            break;
        }
        case 4: {
            int id;
            std::cout << "Enter contact ID to view: ";
            std::cin >> id;
            std::cin.ignore();
            ab.ViewContact(id);
            break;
        }
        case 5:
            ab.ListAllContacts();
            break;
        case 0:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}

this is all a main test to see if i missed anything import to main or ig mainUI
*/ 
