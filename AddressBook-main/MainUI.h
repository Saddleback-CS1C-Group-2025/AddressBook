#ifndef MAIN_UI_H
#define MAIN_UI_H

#include <string>
#include "AddressBookTG.h"

using std::string;

namespace UI
{

    //======================================================================================
    // INPUT / UI HELPERS
    //======================================================================================

    /***************************************************************************************
    * Clears cin error flags and discards remaining characters on the input line.
    ***************************************************************************************/
    void ClearStandardInput();

    /***************************************************************************************
    * Prompts until the user enters an integer within the inclusive range.
    ***************************************************************************************/
    int ReadIntegerInRange(const string& promptMessage,
                                 int     minInclusive,
                                 int     maxInclusive);

    /***************************************************************************************
    * Prompts until the user enters any valid integer.
    ***************************************************************************************/
    int ReadIntegerAny(const string& promptMessage);

    /***************************************************************************************
    * Reads a single line from input (may be empty).
    ***************************************************************************************/
    string ReadLine(const string& promptMessage);

    /***************************************************************************************
    * Reads a line from input, requiring non-empty input. Re-prompts if blank.
    ***************************************************************************************/
    string ReadNonEmptyLine(const string& promptMessage);

    /***************************************************************************************
    * Displays a yes/no prompt and returns true for yes, false for no.
    * Accepts 'y'/'Y' or 'n'/'N' only.
    ***************************************************************************************/
    bool ConfirmYesNo(const string& promptMessage);

    /***************************************************************************************
    * Displays a "Press ENTER to continue..." message and waits for user input.
    ***************************************************************************************/
    void PauseForUser();

    /***************************************************************************************
    * Prompts the user to choose a Contact Type using a numbered list and
    * returns the type string ("Person", "Business", "Vendor", "Emergency").
    ***************************************************************************************/
    string PromptContactType();

    /***************************************************************************************
    * Prompts for a contact ID (integer) with an optional custom label.
    ***************************************************************************************/
    int PromptContactId(const string& label = "Contact ID: ");


    //======================================================================================
    // SUBMENUS
    //======================================================================================

    /***************************************************************************************
    * Displays the "View" submenu (list all contacts or view specific ID).
    ***************************************************************************************/
    void ShowViewMenu(const AddressBookTG& addressBook);
    /***************************************************************************************
    * Displays the "Search / Filter" submenu.
    ***************************************************************************************/

    void ShowSearchFilterMenu(const AddressBookTG& addressBook);

    /***************************************************************************************
    * Displays the "Reports" submenu (missing info, counts by type, group summary).
    ***************************************************************************************/

    void ShowReportsMenu(const AddressBookTG& addressBook);

    /***************************************************************************************
    * Displays the "Tags / Groups" submenu.
    ***************************************************************************************/
    void ShowTagsGroupsMenu(AddressBookTG& addressBook);


    //======================================================================================
    // MAIN MENU LOOP
    //======================================================================================

    /***************************************************************************************
    * Main UI loop - loads from file, displays the main menu, and routes user choices.
    ***************************************************************************************/
    void RunMainMenuLoop(AddressBookTG& addressBook);


} // namespace UI

#endif // MAIN_UI_H
