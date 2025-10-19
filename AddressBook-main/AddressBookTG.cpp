#include "AddressBookTG.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <map>

//============================= HELPER FUNCTIONS ====================================

// Helpers are in an anonymous namespace to prevent clashes
namespace {
    //  Data Processing: Converts user input IDs to the class's ID getter function.
    Contact* FindContactById(std::vector<Contact>& contacts, int contactId) {
        for (auto & contact : contacts) {
            if (contact.getId() == contactId) {
                return &contact;
            }
        }
        return nullptr;
    }
    //  Overload for const
    const Contact* FindContactById(const std::vector<Contact>& contacts, int contactId) {
        for (const auto & contact : contacts) {
            if (contact.getId() == contactId) {
                return &contact;
            }
        }
        return nullptr;
    }

    //  Input Handling: Enables smarter searching by converting uppercase characters in an input string
    //  to lowercase by reference.
    bool ContainsCaseInsensitive(const std::string& str, const std::string& substr) {
        if (substr.empty()) {
            return true;
        }
        std::string lowerStr, lowerSubstr;
        for (const char c : str) {
            lowerStr += std::tolower(c);
        }
        for (const char c : substr) {
            lowerSubstr += std::tolower(c);
        }
        return lowerStr.find(lowerSubstr) != std::string::npos;
    }
}

//  Data Processing: Converts user input strings to the enum type used by the ContactType class.
ContactType StringToContactType(const std::string& typeStr) {
    if (typeStr == "Person") return ContactType::Person;
    if (typeStr == "Business") return ContactType::Business;
    if (typeStr == "Vendor") return ContactType::Vendor;
    if (typeStr == "Emergency") return ContactType::Emergency;
    return ContactType::Person;
}

//============================= CRUD OPERATIONS ====================================
/*
==================== AddContact() ============
PURPOSE:
This function prompts the user for all contact information and adds it to the address bookTG as a contact.

OUTPUT:
Displays prompts for user input and confirmation message.

NOTES:
- Uses UI helper functions for input
- All fields must be filled
=====================================================
*/
void AddressBookTG::AddContact() {
    std::cout << "\n=== Add New Contact ===\n";
    std::cout << "\nSelect Contact Type:\n";
    std::cout << "1) Person\n";
    std::cout << "2) Business\n";
    std::cout << "3) Vendor\n";
    std::cout << "4) Emergency\n";
    std::cout << "Enter choice (1-4): ";

    int typeChoice;
    std::cin >> typeChoice;
    std::cin.ignore();

    // Get contact type
    ContactType type = ContactType::Person;
    switch (typeChoice) {
        case 1: type = ContactType::Person; break;
        case 2: type = ContactType::Business; break;
        case 3: type = ContactType::Vendor; break;
        case 4: type = ContactType::Emergency; break;
        default:
            std::cout << "Invalid choice, defaulting to Person.\n";
            type = ContactType::Person;
    }

    // Get contact information
    std::string firstName, lastName, email, phone;
    std::string addressLine, city, state, postalCode, notes;

    std::cout << "First Name: ";
    std::getline(std::cin, firstName);
    std::cout << "Last Name: ";
    std::getline(std::cin, lastName);
    std::cout << "Email: ";
    std::getline(std::cin, email);
    std::cout << "Phone: ";
    std::getline(std::cin, phone);
    std::cout << "Address Line: ";
    std::getline(std::cin, addressLine);
    std::cout << "City: ";
    std::getline(std::cin, city);
    std::cout << "State: ";
    std::getline(std::cin, state);
    std::cout << "Postal Code: ";
    std::getline(std::cin, postalCode);
    std::cout << "Notes: ";
    std::getline(std::cin, notes);

    // Push new contact to end of list
    Contact newContact(type, firstName, lastName, email, phone,
                      addressLine, city, state, postalCode, notes);
    contacts_.push_back(newContact);

    std::cout << "\nContact added successfully with ID: " << newContact.getId() << "\n";
}

/*
==================== EditContact() ============
PURPOSE:
Edits an existing contact by searching for the ID in AddressBookTG.

OUTPUT:
Returns true if contact was found and edited, false otherwise.

NOTES:
- Displays current values before prompting for new ones
- Empty inputs will keep existing values
=====================================================
*/
bool AddressBookTG::EditContact(int contactId) {
    Contact* contact = FindContactById(contacts_, contactId);
    if (!contact) {
        return false;
    }

    // Displays current contact info
    std::cout << "\n=== Edit Contact (ID: " << contactId << ") ===\n";
    std::cout << "Leave blank to keep current value.\n\n";
    std::cout << "Current Information:\n";
    std::cout << contact->toString() << "\n";

    std::string input;

    // Editing type is done through an enum
    std::cout << "\nNew Type (1=Person, 2=Business, 3=Vendor, 4=Emergency) [Current: "
              << Contact::contactTypeToString(contact->getType()) << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        int typeChoice = std::stoi(input);
        switch (typeChoice) {
            case 1: contact->setType(ContactType::Person); break;
            case 2: contact->setType(ContactType::Business); break;
            case 3: contact->setType(ContactType::Vendor); break;
            case 4: contact->setType(ContactType::Emergency); break;
            default: contact->setType(ContactType::Person); break;
        }
    }

    // Standard logic for editing the remaining fields
    std::cout << "First Name [" << contact->getFirstName() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) contact->setFirstName(input);

    std::cout << "Last Name [" << contact->getLastName() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) contact->setLastName(input);

    std::cout << "Email [" << contact->getEmail() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) contact->setEmail(input);

    std::cout << "Phone [" << contact->getPhone() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) contact->setPhone(input);

    std::cout << "Address Line [" << contact->getAddressLine() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) contact->setAddressLine(input);

    std::cout << "City [" << contact->getCity() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) contact->setCity(input);

    std::cout << "State [" << contact->getState() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) contact->setState(input);

    std::cout << "Postal Code [" << contact->getPostalCode() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) contact->setPostalCode(input);

    std::cout << "Notes [" << contact->getNotes() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) contact->setNotes(input);

    std::cout << "\nContact updated successfully!\n";
    return true;
}

/*
==================== DeleteContact() ============
PURPOSE:
Removes a contact from the address bookTG by ID.

OUTPUT:
Returns true if contact was found and deleted, false otherwise.

=====================================================
*/
bool AddressBookTG::DeleteContact(int contactId) {
    auto contactSearch = std::find_if(
        contacts_.begin(),
        contacts_.end(),
        [contactId](const Contact& c) {
            return c.getId() == contactId;
        }
    );

    // Contact not found
    if (contactSearch == contacts_.end()) {
        return false;
    }

    // Contact found
    contacts_.erase(contactSearch);
    std::cout << "Contact deleted successfully.\n";
    return true;
}

//============================= VIEW OPERATIONS ====================================
/*
==================== ListAllPreviews() ============
PURPOSE:
Displays a preview list of all contacts showing ID, name, and type.

=====================================================
*/
void AddressBookTG::ListAllPreviews() const {
    std::cout << "\n=== All Contacts ===\n";

    if (contacts_.empty()) {
        std::cout << "No contacts in address book.\n";
        return;
    }
    std::cout << "\nTotal contacts: " << contacts_.size() << "\n\n";

    for (const auto& contact : contacts_) {
        std::cout << "ID: " << contact.getId()
                  << " | Name: " << contact.getFullName()
                  << " | Type: " << Contact::contactTypeToString(contact.getType())
                  << "\n";
    }
}

/*
==================== ViewContact() ============
PURPOSE:
Displays full details of a specific contact by ID in AddressBookTG.

OUTPUT:
Returns true if contact found and displayed, false otherwise.

=====================================================
*/
bool AddressBookTG::ViewContact(int contactId) const {
    const Contact* contact = FindContactById(contacts_, contactId);
    if (!contact) {
        return false;
    }

    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << contact->toString(true);
    std::cout << std::string(60, '=') << "\n";
    return true;
}

//============================= SEARCH OPERATIONS ====================================

/*
==================== SearchByName() ============
PURPOSE:
Searches for contacts by name.
Searches for contacts by email in AddressBookTG.
=====================================================
*/
void AddressBookTG::SearchByName(const std::string& query) const {
    std::vector<Contact> results;

    for (const auto& contact : contacts_) {
        if (ContainsCaseInsensitive(contact.getFirstName(), query) ||
            ContainsCaseInsensitive(contact.getLastName(), query) ||
            ContainsCaseInsensitive(contact.getFullName(), query)) {
            results.push_back(contact);
            }
    }
    DisplaySearchResults(results, "Name contains '" + query + "'");
}

/*
==================== SearchByEmail() ============
PURPOSE:
Searches for contacts by email.
Searches for contacts by phone number in AddressBookTG.
=====================================================
*/
void AddressBookTG::SearchByEmail(const std::string& query) const {
    std::vector<Contact> results;

    for (const auto& contact : contacts_) {
        if (ContainsCaseInsensitive(contact.getEmail(), query)) {
            results.push_back(contact);
        }
    }

    DisplaySearchResults(results, "Email contains '" + query + "'");
}

/*
==================== SearchByPhone() ============
PURPOSE:
Searches for contacts by phone number.
Filters contacts by exact type match in AddressBookTG.
=====================================================
*/
void AddressBookTG::SearchByPhone(const std::string& query) const {
    std::vector<Contact> results;

    for (const auto& contact : contacts_) {
        if (ContainsCaseInsensitive(contact.getPhone(), query)) {
            results.push_back(contact);
        }
    }

    DisplaySearchResults(results, "Phone contains '" + query + "'");
}

//============================= FILTER OPERATIONS ====================================
/*
==================== FilterByType() ============
PURPOSE:
Filters contacts by exact type match.
Filters contacts by city (case-insensitive, partial match) in AddressBookTG.
=====================================================
*/
void AddressBookTG::FilterByType(const std::string& type) const {
    std::vector<Contact> results;

    for (const auto& contact : contacts_) {
        if (Contact::contactTypeToString(contact.getType()) == type) {
            results.push_back(contact);
        }
    }

    DisplaySearchResults(results, "Type = '" + type + "'");
}

/*
==================== FilterByCity() ============
PURPOSE:
Filters contacts by city (case-insensitive, partial match).
Filters contacts by tag (exact match) in AddressBookTG.
=====================================================
*/
void AddressBookTG::FilterByCity(const std::string& city) const {
    std::vector<Contact> results;

    for (const auto& contact : contacts_) {
        if (ContainsCaseInsensitive(contact.getCity(), city)) {
            results.push_back(contact);
        }
    }

    DisplaySearchResults(results, "City contains '" + city + "'");
}

/*
==================== FilterByTag() ============
PURPOSE:
Filters contacts by tag (exact match).
Displays formatted search/filter results in AddressBookTG.
=====================================================
*/
void AddressBookTG::FilterByTag(const std::string& tag) const {
    std::vector<Contact> results;

    for (const auto& contact : contacts_) {
        if (contact.hasTag(tag)) {
            results.push_back(contact);
        }
    }

    DisplaySearchResults(results, "Tag = '" + tag + "'");
}

/*
==================== DisplaySearchResults() ============
PURPOSE:
Displays formatted search/filter results.
Adds a tag to a specific contact by ID in AddressBookTG.
=====================================================
*/
void AddressBookTG::DisplaySearchResults(const std::vector<Contact>& results, const std::string& searchType) const {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "SEARCH RESULTS: " << searchType << "\n";
    std::cout << std::string(70, '=') << "\n";
    std::cout << "Found " << results.size() << " contact(s)\n";
    std::cout << std::string(70, '-') << "\n";

    if (results.empty()) {
        std::cout << "No contacts found matching search criteria.\n";
        return;
    }

    for (size_t i = 0; i < results.size(); ++i) {
        const Contact& contact = results[i];

        std::cout << "\nContact " << (i + 1) << " of " << results.size() << "\n";
        std::cout << std::string(40, '-') << "\n";
        std::cout << "ID: " << contact.getId() << "\n";
        std::cout << "Name: " << contact.getFullName() << "\n";
        std::cout << "Type: " << Contact::contactTypeToString(contact.getType()) << "\n";
        std::cout << "Email: " << contact.getEmail() << "\n";
        std::cout << "Phone: " << contact.getPhone() << "\n";
        std::cout << "City: " << contact.getCity() << "\n";
        std::cout << "State: " << contact.getState() << "\n";

        if (!contact.getTags().empty()) {
            std::cout << "Tags: ";
            for (const auto& tag : contact.getTags()) {
                std::cout << tag << " | ";
            }
            std::cout << "\n";
        }

        if (!contact.getGroups().empty()) {
            std::cout << "Groups: ";
            for (const auto& group : contact.getGroups()) {
                std::cout << group << " | ";
            }
            std::cout << "\n";
        }
    }

    std::cout << "\n" << std::string(70, '=') << "\n";
}

//============================= TAG/GROUP OPERATIONS ====================================
/*
==================== AddTag() ============
PURPOSE:
Adds a tag to a specific contact by ID.
Removes a tag from a specific contact with matching ID in AddressBookTG.
OUTPUT:
Returns false if contact not found or tag already exists.

=====================================================
*/
bool AddressBookTG::AddTag(int contactId, const std::string& tag) {
    Contact* contact = FindContactById(contacts_, contactId);
    if (!contact) {
        return false;
    }
    bool success = contact->addTag(tag);
    if (success) {
        std::cout << "Tag '" << tag << "' added to contact " << contactId << ".\n";
    } else {
        std::cout << "Tag already exists or is empty.\n";
    }

    return success;
}

/*
==================== RemoveTag() ============
PURPOSE:
Removes a tag from a specific contact with matching ID.
Removes a contact from a group by ID in AddressBookTG.
=====================================================
*/
bool AddressBookTG::RemoveTag(int contactId, const std::string& tag) {
    Contact* contact = FindContactById(contacts_, contactId);
    if (!contact) {
        return false;
    }
    bool success = contact->removeTag(tag);
    if (success) {
        std::cout << "Tag '" << tag << "' removed from contact " << contactId << ".\n";
    } else {
        std::cout << "Tag not found.\n";
    }

    return success;
}

/*
==================== AssignToGroup() ============
PURPOSE:
Assigns a contact to a group by ID.

=====================================================
*/
bool AddressBookTG::AssignToGroup(int contactId, const std::string& group) {
    Contact* contact = FindContactById(contacts_, contactId);
    if (!contact) {
        return false;
    }
    bool success = contact->addGroup(group);
    if (success) {
        std::cout << "Contact " << contactId << " assigned to group '" << group << "'.\n";
    } else {
        std::cout << "Group already assigned or is empty.\n";
    }

    return success;
}

/*
==================== RemoveFromGroup() ============
PURPOSE:
Removes a contact from a group by ID.

=====================================================
*/
bool AddressBookTG::RemoveFromGroup(int contactId, const std::string& group) {
    Contact* contact = FindContactById(contacts_, contactId);
    if (!contact) {
        return false;
    }
    bool result = contact->removeGroup(group);
    if (result) {
        std::cout << "Contact " << contactId << " removed from group '" << group << "'.\n";
    } else {
        std::cout << "Group not found.\n";
    }
    return result;
}

//============================= FILE I/O OPERATIONS ====================================

/*
==================== LoadFromFile() ============
PURPOSE:
Loads contacts from a CSV file named "addressbook.csv".

NOTES:
- File name is hardcoded as "addressbook.csv".
- Parses CSV format with pipe-delimited groups and tags.

=====================================================
*/
void AddressBookTG::LoadFromFile() {
    std::ifstream file("addressbook.csv");

    if (!file.is_open()) {
        std::cout << "No existing file found. Created new file.\n";
        return;
    }

    contacts_.clear();
    std::string line;
    int lineCount = 0;

    while (std::getline(file, line)) {
        lineCount++;

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> fields;

        // Parse CSV line
        while (std::getline(ss, token, ',')) {
            fields.push_back(token);
        }

        // Need at least 13 fields (id through tags)
        if (fields.size() < 13) {
            std::cout << "Warning: Skipping malformed line " << lineCount << "\n";
            continue;
        }

        try {
            // Parse fields: id, type, firstName, lastName, email, phone,
            //               addressLine, city, state, postalCode, notes, groups, tags
            int id = std::stoi(fields[0]);
            ContactType type = StringToContactType(fields[1]);

            Contact contact(type, fields[2], fields[3], fields[4], fields[5],
                          fields[6], fields[7], fields[8], fields[9], fields[10]);
            // Preserve the ID from file and advance Contact::nextId_ accordingly
            contact.setIdForImport(id);

            // Parse groups (pipe-delimited)
            if (!fields[11].empty()) {
                std::stringstream groupStream(fields[11]);
                std::string group;
                while (std::getline(groupStream, group, '|')) {
                    if (!group.empty()) {
                        contact.addGroup(group);
                    }
                }
            }

            // Parse tags (pipe-delimited)
            if (!fields[12].empty()) {
                std::stringstream tagStream(fields[12]);
                std::string tag;
                while (std::getline(tagStream, tag, '|')) {
                    if (!tag.empty()) {
                        contact.addTag(tag);
                    }
                }
            }

            contacts_.push_back(contact);

        } catch (const std::exception& error) {
            std::cout << "Error parsing line " << lineCount << ": " << error.what() << "\n";
        }
    }

    file.close();
    std::cout << "Loaded " << contacts_.size() << " contacts from addressbook.csv\n";
}

/*
==================== SaveToFile() ============
PURPOSE:
Saves all contacts to a CSV file named "addressbook.csv".

NOTES:
File name is hardcoded as "addressbook.csv".
=====================================================
*/
void AddressBookTG::SaveToFile() const {
    std::ofstream file("addressbook.csv");

    if (!file.is_open()) {
        std::cout << "Error: Could not open file.\n";
        return;
    }

    for (const auto& contact : contacts_) {
        file << contact.toCSV() << "\n";
    }

    file.close();
    std::cout << "Saved " << contacts_.size() << " contacts to addressbook.csv\n";
}


//============================= REPORTS ====================================
/*
==================== ReportMissingInfo() ============
PURPOSE:
This function scans through the contacts in the address book and sees whether
they have an email or phone number.

OUTPUT:
Displays the ID/NAME/TYPE of each contacts missing an email or phone number
as well as the total number of contacts.

NOTES:
- Uses a for loop that scans the contacts for the length of the contact list
  and uses a conditional statement on which if getEmail() or getPhone() is empty
  it outputs the contacts basic information (ID/NAME/TYPE)

=====================================================
*/
void AddressBookTG::ReportMissingInfo() const
{

    std::cout << "\n=== Contacts Missing Information ===\n\n";

    //Keeps track of how many contacts have missing info
    int count = 0;

    //For loop running contact list length
    for (const auto& contact : contacts_) {

        //Conditional statement using empty() to see if retrieved email and phone
        //for contact is empty and if so it runs.
        if (contact.getEmail().empty() || contact.getPhone().empty())
        {

            //Displays the basic info
            std::cout << "ID: " << contact.getId()
                << " | " << contact.getFullName()
                << " | " << Contact::contactTypeToString(contact.getType())
                << "\n";

            //Count is then added for the amount of empty contacts
            count++;
        }
    }

    //Displays the amount of contacts with missing info
    std::cout << "\nTotal: " << count << " contacts missing email or phone\n";
}

/*
==================== ReportCountsByType() ============
PURPOSE:
This function counts how many contacts are categorized for each type.


OUTPUT:
Displays number of contacts per category/type.

NOTES:
- Uses map for better sorting
- uses two for loops: one for loop runs through the contact list assigning
  converted enum to string for the string type
  - Type is then used inside the brackets of count to increment to the next index

=====================================================
*/

void AddressBookTG::ReportCountsByType() const
{
    std::cout << "\n=== Contact Counts by Type ===\n\n";

    //Map also organizes the output alphabetically
    std::map<std::string, int> counts;

    //First for loop counts each contact type
    for (const auto& contact : contacts_)
    {

        //Converts the enum to string
        std::string type = Contact::contactTypeToString(contact.getType());

        //Increments to next index with type being assigned
        counts[type]++;
    }

    //Display for loop
    for (const auto& pair : counts)
    {

        //Outputs pair.first (string containing the type) and then pair.second (int containing the count of contacts for the type)
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    //Displays the total amount of contacts overall regardless of type
    std::cout << "\nTotal contacts: " << contacts_.size() << "\n";
}


/*
==================== ReportGroupSummary() ======================
PURPOSE:
This function shows what groups there are, how many contacts are in each group and
identifies any patterns with the groups.

OUTPUT:
This function either displays that there are no groups, if there are no contacts that
display groups. Also displays the group count with the number of contacts under that
group ("members")

NOTES:
- Made sure to consider contacts that were part of multiple groups
- Used one for loop that runs through the contact list and a nested for loop that runs through the groups
  of the contact and then adds to the count of that specific group.

================================================================
*/
void AddressBookTG::ReportGroupSummary() const
{
    std::cout << "\n=== Group Summary ===\n\n";

    //Uses map to sort the groupCounts dealing with duplicates
    std::map<std::string, int> groupCounts;

    //For loop runs through the contact list
    for (const auto& contact : contacts_)
    {
        //Get reference to contacts groups vector
        const auto& groups = contact.getGroups();

        //Nested for loop runs through the groups of the contact list
        for (const auto& group : groups)
        {
            //groupCounts get iterated for that group
            groupCounts[group]++;
        }
    }


    //If the groupCounts is fully empty then there are no groups defined
    if (groupCounts.empty())
    {
        //Displays that no groups are defined
        std::cout << "No groups defined.\n";
        return;
    }

    //For loop displays the groups and the member counts
    for (const auto& pair : groupCounts)
    {
        //Displays pair.first (group name) and then pair.second (group member count)
        std::cout << pair.first << ": " << pair.second << " members\n";
    }
}
