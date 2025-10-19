// 4) searching and filtering system 
//- implement various searches and filters and contact previews in console
// AddressBook.cpp
#include "AddressBookSF.h"
#include <iostream>
#include <algorithm> // Search algorithm: find_if, search (Requirements 1, 2, 5)
#include <cctype> // Character handling: toupper (Requirements 2)
//=================================================================
// IMPLEMENTATION FILE: AddressBook.cpp
//-----------------------------------------------------------------
// LIBRARY USAGE BY REQUIREMENT:
// Requirement 1 (Contact Management): <algorithm> for find_if
// Requirement 2 (Search/Filter): <algorithm> for search, <cctype> for toupper
// Requirement 4 (Import/Export): <fsteam> for file I/O <sstream> for CSV
// Requirement 5 (Reports): <algorithm> for iteration and counting
//================================================================

//=================================================================
// CONSTANTS
//=================================================================
const std:: string AddressBook:: DEFAULT_FILENAME = "addressbook.csv";

//=================================================================
// CONSTRUCTOR
//=================================================================
AddressBook::AddressBook()
{
    // Vector automatically initialize empty
    // Data load controlled by UI through explicit LoadFromFile() call
}

//=================================================================
// PRIVATE HELPER METHODS IMPLEMENTATION
//=================================================================

// used for modifying
std:: vector<Contact>:: iterator AddressBook:: findContactById(int id)
{
    /******************************************************************
    * SUMMARY - Locates contact by unique ID for modification operations
    * PARAM - id The unique identifier of contant to find
    * RETURN  - iterator to contact if found, end() iterator if not found 
    * DESIGN - Use manual iteration for contact Lookup
    ******************************************************************/
    for (auto it = contacts.begin(); it != contacts.end(); ++it)
    {
        if (it->getId() == id)
        {
            return it;
        }
    }
    return contacts.end();
}

// used for reading 
std:: vector<Contact>:: const_iterator AddressBook:: findContactById(int id) const
{
    /******************************************************************
    * SUMMARY - Locates contact by unique ID for modification operations
    * PARAM - id The unique identifier of contant to find
    * RETURN  - const iterator to contact if found, end() iterator if not found 
    * DESIGN - Use manual iteration for contact Lookup
    ******************************************************************/
    for (auto it = contacts.begin(); it != contacts.end(); ++it)
    {
        if (it->getId() == id)
        {
            return it;
        }
    }
    return contacts.end();
}

bool AddressBook:: containsCaseInsensitive(const std:: string& str, const std:: string& substr)
{
    /******************************************************************
    * SUMMARY - Performs case-insensitive substring search
    * PARAM - str The string to search within 
    * PARAM - substr The string to search for
    * RETURN - true if (case-insensitive) substring found, false otherwise
    * DESIGN - Static utility method that only cares about non-object params state
    ******************************************************************/
    if (substr.empty()) // return all contacts on empty search
    {
        return true;
    }

    std:: string lowerStr, lowerSubstr;

    for (char c : str)
    {
        lowerStr += std::tolower(c);
    }

    for (char c : substr)
    {
        lowerSubstr += std::tolower(c);
    }

    return lowerStr.find(lowerSubstr) < lowerStr.length();
}

//=================================================================
// [REQUIREMENT 2] SEARCH OPERATIONS IMPLEMENTATION
//=================================================================

std:: vector<Contact> AddressBook::SearchByName(const std:: string &nameQuery) const
{
    /******************************************************************
    * SUMMARY - Searches contacts by name (case-insensitive, partial match)
    * PARAM - nameQuery The text to search for in contact names
    * RETURN - Vector of contacts matching the search criteria 
    * DESIGN - Searches first name, last name, and full name combinations
    ******************************************************************/
    std:: vector<Contact> results;
    for (const auto &contact : contacts)
    {
        if (containsCaseInsensitive(contact.getFirstName(), nameQuery) ||
            containsCaseInsensitive(contact.getLastName(), nameQuery) || 
            containsCaseInsensitive(contact.getFullName(), nameQuery))
        {
            results.push_back(contact);
        }
    }
    return results;
}


std:: vector<Contact> AddressBook::SearchByEmail(const std:: string &emailQuery) const
{
    /******************************************************************
    * SUMMARY - Searches contacts by email address (case-insensitive, partial match)
    * PARAM - emailQuery The text to search for in contact emails
    * RETURN - Vector of contacts matching the search criteria 
    * DESIGN - Works with matching part of the email for flexible searches
    ******************************************************************/
    std:: vector<Contact> results;
    for (const auto &contact : contacts)
    {
        if (containsCaseInsensitive(contact.getEmail(), emailQuery))
        {
            results.push_back(contact);
        }
    }
    return results;
}


std:: vector<Contact> AddressBook::SearchByPhone(const std:: string &phoneQuery) const
{
    /******************************************************************
    * SUMMARY - Searches contacts by phone number (case-insensitive, partial match)
    * PARAM - phoneQuery The text to search for in contact phone numbers
    * RETURN - Vector of contacts matching the search criteria 
    * DESIGN - Works with matching part of the phone number for flexible searches 
    ******************************************************************/
    std:: vector<Contact> results;
    for (const auto &contact : contacts)
    {
        if (containsCaseInsensitive(contact.getPhone(), phoneQuery))
        {
            results.push_back(contact);
        }
    }
    return results;
}


//=================================================================
// [REQUIREMENT 2] FILTER OPERATIONS IMPLEMENTATION
//=================================================================


std:: vector<Contact> AddressBook:: FilterByType(const std::string& type) const
{
    /******************************************************************
    * SUMMARY - Filters contacts by exact match to type 
    * PARAM - type The contact type to filter by ("Person", "Business", etc.)
    * RETURN - Vector of contacts of specified type
    * DESIGN - Exact type matching ensures precise category filtering
    ******************************************************************/
    std:: vector<Contact> results;
    for (const auto &contact : contacts)
    {
        if (Contact::contactTypeToString(contact.getType()) == type)
        {
            results.push_back(contact);
        }
    }
    return results;
}


std:: vector<Contact> AddressBook:: FilterByCity(const std::string& city) const
{
    /******************************************************************
    * SUMMARY - Filters contacts by city (case-insensitive, partial match)
    * PARAM - city The city name to filter by
    * RETURN - Vector of contacts located in the specified city
    * DESIGN - Case-insensitive matching for city
    ******************************************************************/
    std:: vector<Contact> results;
    for (const auto &contact : contacts)
    {
        if (containsCaseInsensitive(contact.getCity(), city))
        {
            results.push_back(contact);
        }
    }
    return results;
}


std:: vector<Contact> AddressBook:: FilterByTag(const std::string& tag) const
{
    /******************************************************************
    * SUMMARY - Filters contacts by exact match to tag (case-insensitive, partial match)
    * PARAM - tag The tag name to filter by
    * RETURN - Vector of contacts with the specified tag
    * DESIGN - Exact tag matching ensures precise tag consistency
    ******************************************************************/
    std:: vector<Contact> results;
    for (const auto &contact : contacts)
    {
        if (contact.hasTag(tag))
        {
            results.push_back(contact);
        }
    }
    return results;
}

//=================================================================
// [REQUIREMENT 2] SEARCH RESULTS DISPLAY IMPLEMENTATION
//=================================================================

void AddressBook:: DisplaySearchResults(const std::vector<Contact>& results, const std::string& searchType) const
{
    /******************************************************************
    * SUMMARY - Shows result counts for focused searches (name, etc.) and broad filters (type, etc.)
    * PARAM - results - Vector of Contact objects returned from search/filter operations 
    * PARAM - searchType - Descriptor that shows the operation called and parameter entered by user
    * RETURN - N/A outputs to console
    * DESIGN - Allows user autonomy to observe the previous call made and decide what to do if they made typos causing undesired output
    ******************************************************************/
    // Header
    std:: cout << "\n" << std::string(50, '=') << std:: endl;
    std:: cout << "SEARCH RESULTS: " << searchType << std:: endl;
    std:: cout << std::string(50, '=') << std:: endl;
    
    // Result count
    std:: cout << "Found " << results.size() << " contact(s)" << std:: endl;
    std:: cout << std::string(50, '-') << std:: endl;

    // Empty results handling
    if (results.empty())
    {
        std:: cout << "No contacts found matching search criteria" << std:: endl;
        return;
    }

    // Preview Contacts display
    for (int i = 0; i < results.size(); ++i)
    {
        const Contact &contact = results[i];

        // Contact header
        std:: cout << "\n" << std::string(25, '-') << std::endl;
        std:: cout << "Contact " << (i + 1) << " of " << results.size() << std:: endl;
        std:: cout << std::string(25, '-') << std::endl;

        // Contact information

        std:: cout << "ID: " << contact.getId() << std::endl;
        std:: cout << "Name: " << contact.getFullName() << std::endl;
        std:: cout << "Type: " << Contact::contactTypeToString(contact.getType()) << std::endl;

        std:: cout << "Email: " << contact.getEmail() << std::endl;
        std:: cout << "Phone: " << contact.getPhone() << std::endl;

        // Geographical Content for IRL contacting
        std:: cout << "City: " << contact.getCity() << std::endl;
        std:: cout << "State: " << contact.getState() << std::endl;
        std:: cout << "AddressLine and Postal Code: " << contact.getAddressLine() << " " 
        << contact.getPostalCode() << std::endl;

        // Specific Categorization
        std:: cout << "Tags: ";
        for (const auto &tag: contact.getTags())
        {
            std:: cout << tag << "| ";
        }
        std:: cout << std:: endl;

        std:: cout << "Groups: ";
        for (const auto &group: contact.getGroups())
        {
            std:: cout << group << "| ";
        }
        std:: cout << std:: endl;

        // Additional info
        std:: cout << "Notes: " << contact.getNotes() << std::endl;

        std:: cout << "\n" << std::string(50, '=') << std::endl;
        


    }

}
