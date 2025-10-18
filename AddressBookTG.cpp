#include "AddressBook.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <map>

















//ABOVE IS ALL THE FUNCTIONS THAT ARE MISSING FROM ADDRESSBOOK


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
void AddressBook::ReportMissingInfo() const
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

            //Count is then added for the amount of contacts empty
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

void AddressBook::ReportCountsByType() const
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

        //Outputs pair.first (string containing the type) and then pair.second (int containg the count of contacts for the type)
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    //Displays the total amount of contacts overall regardless of type
    std::cout << "\nTotal contacts: " << contacts_.size() << "\n";
}


/*
==================== ReportGroupSummary() ======================
PURPOSE:
This function shows what groups there are, how many contacts are in each groupm and
identifies any patterns with the groups.

OUTPUT:
This function either displays that there are no groups, if there are no contacts that
display groups. Also it displays the group count with the number of contacts under that
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
