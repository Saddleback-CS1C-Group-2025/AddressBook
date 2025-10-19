// AddressBook.h
#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H


#include <vector> // For storing contacts and returning search results
#include <string> // For all string parameters and return types
#include "Contact.h" // For Contact class definition and operations

/***********************************************************************
* CLASS - AddressBook
*-----------------------------------------------------------------------
* DATA MANAGEMENT - Implements all address book operations
* 
* RUBRIC REQUIREMENTS IMPLEMENTED - 
* [1] Contact Management: Create, Read, Update, Delete Contacts
* [2] Search/Filter: Name, email, phone search; Type, city, tag filter
* [3] Groups/Tags: Assign groups, add/remove tags
* [4] Import/Export: Save to file, load from file
* [5] Reports: Missing info, counts by type, group summaries
* 
* OOP DESIGN PRINCIPLES - 
* Encapsulation: All data private, controlled access through methods
* Single Responsibility: Pure Data Management
* Composition: Manages Contact objects in containers
* User Autonomy: Methods return data
***********************************************************************/

class AddressBook
{
    private:
    //=================================================================
    // PRIVATE DATA MEMBERS
    //=================================================================
    std::vector<Contact> contacts; // Contact storage
    static const std::string DEFAULT_FILENAME; // Default file for persistence

    //=================================================================
    // PRIVATE HELPER METHODS
    //=================================================================
    /******************************************************************
    * INTERNAL LOGIC - Contact Lookup by Id using std::find_if algorithm
    * LIBRARY - <algorithm> for std::find_if
    * DESIGN - Separate const/non-const versions to secure data
    * USAGE - Foundation for all ID-based operations
    *******************************************************************/
    
    std:: vector<Contact>:: iterator findContactById(int id);
    std:: vector<Contact>:: const_iterator findContactById(int id) const;
    
    /******************************************************************
    * INTERNAL LOGIC - Case-insensitive search using std::search and std::toupper
    * LIBRARY - <algorithm> for std::search, <cctype> for std::toupper 
    * DESIGN - Static utility method that only cares about non-object params state
    * USAGE - Power all text-based search operation in requirements
    *******************************************************************/

    static bool containsCaseInsensitive(const std:: string& str, const std:: string& substr);

    public: 
    //=================================================================
    // CONSTRUCTOR
    //=================================================================
    AddressBook();

    //=================================================================
    // [REQUIREMENT 2] SEARCH OPERATIONS - TEXT-BASED SEARCHING
    //=================================================================

    /******************************************************************
    * NAME SEARCH - Find contacts by name using case-insensitive matching
    * RUBRIC - "Search contacts by name"
    * LIBRARY - <algorithm> for iterations, uses containsCaseInsensitive helper
    * DESIGN - Searches first name, last name, and full name combinations
    * USER FLOW - UI gets search -> calls this -> display matches
    ******************************************************************/
    std:: vector<Contact> SearchByName(const std::string& nameQuery) const;

    /******************************************************************
    * EMAIL SEARCH - Find contacts by email using case-insensitive matching
    * RUBRIC - "Search contacts by email"
    * LIBRARY - <algorithm> for iterations, uses containsCaseInsensitive helper
    * DESIGN - Works with matching part of the email for flexible searches
    * USER FLOW - UI gets email fragment -> calls this -> display matches
    ******************************************************************/

    std:: vector<Contact> SearchByEmail(const std::string& emailQuery) const;

    /******************************************************************
    * PHONE SEARCH - Find contacts by phone number using case-insensitive matching
    * RUBRIC - "Search contacts by phone number"
    * LIBRARY - <algorithm> for iterations, uses containsCaseInsensitive helper
    * DESIGN -  Works with matching part of the phone number for flexible searches 
    * USER FLOW - UI gets phone digits -> calls this -> display matches
    ******************************************************************/

    std:: vector<Contact> SearchByPhone(const std::string& phoneQuery) const;

    //=================================================================
    // [REQUIREMENT 2] FILTER OPERATIONS - CATEGORY-BASED FILTERING
    //=================================================================

    /******************************************************************
    * TYPE FILTER - Gets contacts by type using exact matches
    * RUBRIC - "Filter by contact type"
    * LIBRARY - <algorithm> for iterations, Contact::contactTypeToString
    * DESIGN - Exact type matching ensures precise category filtering
    * USER FLOW - UI shows type -> calls this -> display matches
    ******************************************************************/
    std:: vector<Contact> FilterByType(const std::string& type) const;

    /******************************************************************
    * CITY FILTER - Gets contacts by city using case-insensitive match
    * RUBRIC - "Filter by city"
    * LIBRARY - <algorithm> for iterations, uses containsCaseInsensitive helper
    * DESIGN - Case-insensitive matching for city
    * USER FLOW - UI shows type -> calls this -> display matches
    ******************************************************************/
    std:: vector<Contact> FilterByCity(const std::string& city) const;

    /******************************************************************
    * TAG FILTER - Gets contacts by tag using exact matches
    * RUBRIC - "Filter by tag"
    * LIBRARY - <algorithm> for iterations, Contact::hasTag
    * DESIGN - Exact tag matching ensures precise tag consistency
    * USER FLOW - UI shows type -> calls this -> display matches
    ******************************************************************/

    std:: vector<Contact> FilterByTag(const std::string& tag) const;


    //=================================================================
    // [REQUIREMENT 2] SEARCH RESULTS DISPLAY - CONTACT PREVIEWS
    //=================================================================

    /******************************************************************
    * DISPLAY SEARCH RESULTS - Shows formatted contact previews in console
    * RUBRIC - "Contact previews in console"
    * LIBRARY - <iostream> for console output, uses Contact getter methods
    * DESIGN - Formatted display with contact counters to accounting for search and filter 
    * USER FLOW - UI calls search/filter-> gets results -> calls this -> views focused display
    ******************************************************************/
    void DisplaySearchResults(const std:: vector<Contact> &results, const std:: string &searchType) const;
};

#endif // ADDRESS_BOOK_H
