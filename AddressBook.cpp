#include "AddressBook.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <map>

//============================= CONSTANTS ====================================
const std::string AddressBook::DEFAULT_FILENAME = "addressbook.csv";

//============================= HELPER FUNCTIONS ====================================

//helper pointer
Contact* AddressBook::FindContactById(int contactId) {
    for (auto& contact : contacts_) {
        if (contact.getId() == contactId) {
            return &contact;
        }
    }
    return nullptr;
}

const Contact* AddressBook::FindContactById(int contactId) const {
    for (const auto& contact : contacts_) {
        if (contact.getId() == contactId) {
            return &contact;
        }
    }
    return nullptr;
}

//  Input Handling: Enables smarter searching by converting uppercase characters in an input string
//  to lowercase by reference.
bool AddressBook::ContainsCaseInsensitive(const std::string& str, const std::string& substr) {
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

//  Data Processing: Converts user input strings to the enum type used by the ContactType class.
ContactType StringToContactType(const std::string& typeStr) {
    if (typeStr == "Person") return ContactType::Person;
    if (typeStr == "Business") return ContactType::Business;
    if (typeStr == "Vendor") return ContactType::Vendor;
    if (typeStr == "Emergency") return ContactType::Emergency;
    return ContactType::Person;
}

//============================= CRUD OPERATIONS ====================================

//add contact
void AddressBook::AddContact(const Contact& contact)
{
    contacts_.push_back(contact);
}

//edit contact
bool AddressBook::EditContact(int contactId, const Contact& updatedContact)
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

/*
==================== AddContact() ============
PURPOSE:
This function prompts the user for all contact information and adds it to the address book as a contact.

OUTPUT:
Displays prompts for user input and confirmation message.

NOTES:
- Uses UI helper functions for input
- All fields must be filled
=====================================================
*/
void AddressBook::AddContact() {
    std::cout << "\n=== Add New Contact ===\n";
    std::cout << "\nSelect Contact Type:\n";
    std::cout << "1) Person\n";
    std::cout << "2) Business\n";
    std::cout << "3) Vendor\n";
    std::cout << "4) Emergency\n";
    std::cout << "Enter choice (1-4): ";

    const int MAX_CHARS = 50;
    int typeChoice;
    std::cin >> typeChoice;
    std::cin.ignore();

    // User input is converted to enum.
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

    // Contact fields are standardized, entries >50 chars are trimmed, notes can be <=100.
    std::cout << "First Name: ";
    std::getline(std::cin, firstName);
    if (firstName.length() > MAX_CHARS) firstName = firstName.substr(0, MAX_CHARS);
    std::cout << "Last Name: ";
    std::getline(std::cin, lastName);
    if (lastName.length() > MAX_CHARS) lastName = lastName.substr(0, MAX_CHARS);
    std::cout << "Email: ";
    std::getline(std::cin, email);
    if (email.length() > MAX_CHARS) email = email.substr(0, MAX_CHARS);
    std::cout << "Phone: ";
    std::getline(std::cin, phone);
    if (phone.length() > MAX_CHARS) phone = phone.substr(0, MAX_CHARS);
    std::cout << "Address Line: ";
    std::getline(std::cin, addressLine);
    if (addressLine.length() > MAX_CHARS) addressLine = addressLine.substr(0, MAX_CHARS);
    std::cout << "City: ";
    std::getline(std::cin, city);
    if (city.length() > MAX_CHARS) city = city.substr(0, MAX_CHARS);
    std::cout << "State: ";
    std::getline(std::cin, state);
    if (state.length() > MAX_CHARS) state = state.substr(0, MAX_CHARS);
    std::cout << "Postal Code: ";
    std::getline(std::cin, postalCode);
    if (postalCode.length() > MAX_CHARS) postalCode = postalCode.substr(0, MAX_CHARS);
    std::cout << "Notes: ";
    std::getline(std::cin, notes);
    if (notes.length() > MAX_CHARS+50) notes = notes.substr(0, MAX_CHARS+50);

    // New contacts are pushed to end of list.
    Contact newContact(type, firstName, lastName, email, phone,
                      addressLine, city, state, postalCode, notes);
    contacts_.push_back(newContact);

    // Finally, the contact is given a unique ID.
    std::cout << "\nContact added successfully with ID: " << newContact.getId() << "\n";
}

/*
==================== EditContact() ============
PURPOSE:
Edits an existing contact by searching for the ID.

OUTPUT:
Returns true if contact was found and edited, false otherwise.

NOTES:
- Displays current values before prompting for new ones
- Empty inputs will keep existing values
=====================================================
*/
bool AddressBook::EditContact(int contactId) {
    Contact* contact = FindContactById(contactId);
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

    // Standardized logic for editing the remaining fields
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
Removes a contact from the address book by ID.

OUTPUT:
Returns true if contact was found and deleted, false otherwise.

=====================================================
*/
bool AddressBook::DeleteContact(int contactId) {
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
void AddressBook::ListAllPreviews() const {
    std::cout << "\n=== All Contacts ===\n";

    // List is empty
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
Displays full details of a specific contact by ID.

OUTPUT:
Returns true if contact found and displayed, false otherwise.

=====================================================
*/
bool AddressBook::ViewContact(int contactId) const {
    const Contact* contact = FindContactById(contactId);

    if (!contact) {
        return false;
    }

    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << contact->toString(true);
    std::cout << std::string(60, '=') << "\n";
    return true;
}

//============================= SEARCH OPERATIONS ====================================

std::vector<Contact> AddressBook::SearchByName(const std::string& nameQuery) const
{
    /******************************************************************
    * SUMMARY - Searches contacts by name (case-insensitive, partial match)
    * PARAM   - nameQuery The text to search for in contact names
    * RETURN  - Vector of contacts matching the search criteria
    * DESIGN  - Searches first name, last name, and full name combinations
    ******************************************************************/
    std::vector<Contact> results;
    for (const auto &contact : contacts_)
    {
        if (ContainsCaseInsensitive(contact.getFirstName(), nameQuery) ||
            ContainsCaseInsensitive(contact.getLastName(), nameQuery) ||
            ContainsCaseInsensitive(contact.getFullName(), nameQuery))
        {
            results.push_back(contact);
        }
    }
    return results;
}

std::vector<Contact> AddressBook::SearchByEmail(const std::string &emailQuery) const
{
    /******************************************************************
    * SUMMARY - Searches contacts by email address (case-insensitive, partial match)
    * PARAM   - emailQuery The text to search for in contact emails
    * RETURN  - Vector of contacts matching the search criteria
    * DESIGN  - Works with matching part of the email for flexible searches
    ******************************************************************/
    std::vector<Contact> results;
    for (const auto &contact : contacts_)
    {
        if (ContainsCaseInsensitive(contact.getEmail(), emailQuery))
        {
            results.push_back(contact);
        }
    }
    return results;
}

std::vector<Contact> AddressBook::SearchByPhone(const std::string &phoneQuery) const
{
    /******************************************************************
    * SUMMARY - Searches contacts by phone number (case-insensitive, partial match)
    * PARAM   - phoneQuery The text to search for in contact phone numbers
    * RETURN  - Vector of contacts matching the search criteria
    * DESIGN  - Works with matching part of the phone number for flexible searches
    ******************************************************************/
    std::vector<Contact> results;
    for (const auto &contact : contacts_)
    {
        if (ContainsCaseInsensitive(contact.getPhone(), phoneQuery))
        {
            results.push_back(contact);
        }
    }
    return results;
}

//============================= FILTER OPERATIONS ====================================

std::vector<Contact> AddressBook::FilterByType(const std::string& type) const
{
    /******************************************************************
    * SUMMARY - Filters contacts by exact match to type
    * PARAM   - type The contact type to filter by ("Person", "Business", etc.)
    * RETURN  - Vector of contacts of specified type
    * DESIGN  - Exact type matching ensures precise category filtering
    ******************************************************************/
    std::vector<Contact> results;
    for (const auto &contact : contacts_)
    {
        if (Contact::contactTypeToString(contact.getType()) == type)
        {
            results.push_back(contact);
        }
    }
    return results;
}

std::vector<Contact> AddressBook::FilterByCity(const std::string& city) const
{
    /******************************************************************
    * SUMMARY - Filters contacts by city (case-insensitive, partial match)
    * PARAM   - city The city name to filter by
    * RETURN  - Vector of contacts located in the specified city
    * DESIGN  - Case-insensitive matching for city
    ******************************************************************/
    std::vector<Contact> results;
    for (const auto &contact : contacts_)
    {
        if (ContainsCaseInsensitive(contact.getCity(), city))
        {
            results.push_back(contact);
        }
    }
    return results;
}

std::vector<Contact> AddressBook::FilterByTag(const std::string& tag) const
{
    /******************************************************************
    * SUMMARY - Filters contacts by exact match to tag (case-insensitive, partial match)
    * PARAM   - tag The tag name to filter by
    * RETURN  - Vector of contacts with the specified tag
    * DESIGN  - Exact tag matching ensures precise tag consistency
    ******************************************************************/
    std::vector<Contact> results;
    for (const auto &contact : contacts_)
    {
        if (contact.hasTag(tag))
        {
            results.push_back(contact);
        }
    }
    return results;
}

void AddressBook::DisplaySearchResults(const std::vector<Contact>& results, const std::string& searchType) const
{
    /******************************************************************
    * SUMMARY - Shows result counts for focused searches (name, etc.) and broad filters (type, etc.)
    * PARAM   - results - Vector of Contact objects returned from search/filter operations
    * PARAM   - searchType - Descriptor that shows the operation called and parameter entered by user
    * RETURN  - N/A outputs to console
    * DESIGN  - Allows user autonomy to observe the previous call made and decide what to do if they made typos
    ******************************************************************/
    // Header
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "SEARCH RESULTS: " << searchType << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    // Result count
    std::cout << "Found " << results.size() << " contact(s)" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    // Empty results handling
    if (results.empty())
    {
        std::cout << "No contacts found matching search criteria" << std::endl;
        return;
    }

    // Preview Contacts display
    for (int i = 0; i < results.size(); ++i)
    {
        const Contact &contact = results[i];

        // Contact header
        std::cout << "\n" << std::string(25, '-') << std::endl;
        std::cout << "Contact " << (i + 1) << " of " << results.size() << std::endl;
        std::cout << std::string(25, '-') << std::endl;

        // Contact information
        std::cout << "ID: " << contact.getId() << std::endl;
        std::cout << "Name: " << contact.getFullName() << std::endl;
        std::cout << "Type: " << Contact::contactTypeToString(contact.getType()) << std::endl;

        std::cout << "Email: " << contact.getEmail() << std::endl;
        std::cout << "Phone: " << contact.getPhone() << std::endl;

        // Geographical Content for IRL contacting
        std::cout << "City: " << contact.getCity() << std::endl;
        std::cout << "State: " << contact.getState() << std::endl;
        std::cout << "AddressLine and Postal Code: " << contact.getAddressLine() << " "
        << contact.getPostalCode() << std::endl;

        // Specific Categorization
        std::cout << "Tags: ";
        for (const auto &tag: contact.getTags())
        {
            std::cout << tag << "| ";
        }
        std::cout << std::endl;

        std::cout << "Groups: ";
        for (const auto &group: contact.getGroups())
        {
            std::cout << group << "| ";
        }
        std::cout << std::endl;

        // Additional info
        std::cout << "Notes: " << contact.getNotes() << std::endl;

        std::cout << "\n" << std::string(50, '=') << std::endl;
    }
}

//============================= TAG/GROUP OPERATIONS ====================================
/*
==================== AddTag() ============
PURPOSE:
Adds a tag to a specific contact by ID.

OUTPUT:
Returns false if contact not found or tag already exists.

=====================================================
*/
bool AddressBook::AddTag(int contactId, const std::string& tag) {
    Contact* contact = FindContactById(contactId);
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

=====================================================
*/
bool AddressBook::RemoveTag(int contactId, const std::string& tag) {
    Contact* contact = FindContactById(contactId);

    // Contact list is empty
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
bool AddressBook::AssignToGroup(int contactId, const std::string& group) {
    Contact* contact = FindContactById(contactId);
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
bool AddressBook::RemoveFromGroup(int contactId, const std::string& group) {
    Contact* contact = FindContactById(contactId);
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
void AddressBook::LoadFromFile() {
    std::ifstream file(DEFAULT_FILENAME);

    // Will always run for a new user
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

        // Fills fields: id, type, firstName, lastName, email, phone,
        //               addressLine, city, state, postalCode, notes, groups, tags
        try {
            int id = std::stoi(fields[0]);
            ContactType type = StringToContactType(fields[1]);

            Contact contact(type, fields[2], fields[3], fields[4], fields[5],
                          fields[6], fields[7], fields[8], fields[9], fields[10]);

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
    std::cout << "Loaded " << contacts_.size() << " contacts from " << DEFAULT_FILENAME << "\n";
}

/*
==================== SaveToFile() ============
PURPOSE:
Saves all contacts to a CSV file named "addressbook.csv".

NOTES:
File name is hardcoded as "addressbook.csv".
=====================================================
*/
void AddressBook::SaveToFile() const {
    std::ofstream file(DEFAULT_FILENAME);

    if (!file.is_open()) {
        std::cout << "Error: Could not open file.\n";
        return;
    }

    for (const auto& contact : contacts_) {
        file << contact.toCSV() << "\n";
    }

    file.close();
    std::cout << "Saved " << contacts_.size() << " contacts to " << DEFAULT_FILENAME << "\n";
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
- Uses a for loop that scans the contacts for the length of the contact list.
  If getEmail() or getPhone() is empty it outputs the contact's ID/NAME/TYPE

=====================================================
*/
void AddressBook::ReportMissingInfo() const
{

    std::cout << "\n=== Contacts Missing Information ===\n\n";

    // Keeps track of how many contacts have missing info
    int count = 0;

    // For loop running contact list length
    for (const auto& contact : contacts_) {

        // Conditional statement using empty() to see if retrieved email and phone
        // for contact is empty and if so it runs.
        if (contact.getEmail().empty() || contact.getPhone().empty())
        {

            //Displays the basic info
            std::cout << "ID: " << contact.getId()
                << " | " << contact.getFullName()
                << " | " << Contact::contactTypeToString(contact.getType())
                << "\n";

            // Count is then added for the amount of empty contacts
            count++;
        }
    }

    // Displays the amount of contacts with missing info
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

void AddressBook::ReportCountsByType() const
{
    std::cout << "\n=== Contact Counts by Type ===\n\n";

    // Map also organizes the output alphabetically
    std::map<std::string, int> counts;

    // First for loop counts each contact type
    for (const auto& contact : contacts_)
    {

        // Converts the enum to string
        std::string type = Contact::contactTypeToString(contact.getType());

        // Increments to next index with type being assigned
        counts[type]++;
    }

    // Display for loop
    for (const auto& pair : counts)
    {

        // Outputs pair.first (string containing the type)
        // then pair.second (int containing the count of contacts for the type)
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    // Displays the total amount of contacts overall regardless of type
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
void AddressBook::ReportGroupSummary() const
{
    std::cout << "\n=== Group Summary ===\n\n";

    // Uses map to sort the groupCounts dealing with duplicates
    std::map<std::string, int> groupCounts;

    // For loop runs through the contact list
    for (const auto& contact : contacts_)
    {
        // Get reference to contacts groups vector
        const auto& groups = contact.getGroups();

        // Nested for loop runs through the groups of the contact list
        for (const auto& group : groups)
        {
            // groupCounts get iterated for that group
            groupCounts[group]++;
        }
    }


    // If the groupCounts is fully empty then there are no groups defined
    if (groupCounts.empty())
    {
        // Displays that no groups are defined
        std::cout << "No groups defined.\n";
        return;
    }

    // For loop displays the groups and the member counts
    for (const auto& pair : groupCounts)
    {
        // Displays pair.first (group name) and then pair.second (group member count)
        std::cout << pair.first << ": " << pair.second << " members\n";
    }
}