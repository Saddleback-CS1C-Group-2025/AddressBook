// MainUI.cpp
#include "MainUI.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::numeric_limits;
using std::streamsize;
using std::string;
using std::isspace;

namespace
{
    //======================================================================================
    // LOCAL HELPERS
    //======================================================================================

    string Trim(const string& inputString)
    {
        int firstNonSpaceIndex = 0;

        while (firstNonSpaceIndex < (int)inputString.size() &&
               isspace(inputString[firstNonSpaceIndex]))
        {
            firstNonSpaceIndex++;
        }

        int lastNonSpaceIndex = (int)inputString.size();

        while (lastNonSpaceIndex > firstNonSpaceIndex &&
               isspace(inputString[lastNonSpaceIndex - 1]))
        {
            lastNonSpaceIndex--;
        }

        return inputString.substr(firstNonSpaceIndex,
                                  lastNonSpaceIndex - firstNonSpaceIndex);
    }

    bool IsBlank(const string& inputString)
    {
        for (char currentChar : inputString)
        {
            if (!isspace(currentChar))
            {
                return false;
            }
        }
        return true;
    }
}

namespace UI
{
    // =====================================================================================
    // CONSTANTS
    // =====================================================================================
    namespace CONSTANTS
    {
        // General UI Text
        const string PROMPT_INPUT_ARROW                  = "> ";
        const string PROMPT_PRESS_ENTER_TO_CONTINUE      = "\nPress ENTER to continue...";
        const string PROMPT_CONFIRM_YES_NO               = " (y/n): ";
        const string MESSAGE_GOODBYE                     = "Goodbye!\n";
        const string MESSAGE_INVALID_CHOICE              = "Invalid choice.\n";
        const string MESSAGE_CONTACT_NOT_FOUND           = "Contact not found.\n";
        const string MESSAGE_ENTER_VALID_INTEGER         = "Enter a valid integer.\n";
        const string MESSAGE_ENTER_Y_OR_N                = "Please enter y or n.\n";
        const string MESSAGE_INPUT_CANNOT_BE_BLANK       = "Input was blank. Try again.\n";
        const string MESSAGE_ENTER_NUMBER_BETWEEN_BEGIN  = "Please enter a number between ";
        const string MESSAGE_ENTER_NUMBER_BETWEEN_MID    = " and ";
        const string MESSAGE_ENTER_NUMBER_BETWEEN_END    = ".\n";
        const string MESSAGE_FAILED_ADD_TAG              = "Failed to add tag.\n";
        const string MESSAGE_FAILED_REMOVE_TAG           = "Failed to remove tag.\n";
        const string MESSAGE_FAILED_ASSIGN_GROUP         = "Failed to assign group.\n";
        const string MESSAGE_FAILED_REMOVE_GROUP         = "Failed to remove group.\n";

        // Confirmation prompts
        const string PROMPT_SAVE_BEFORE_EXIT = "Save before exiting?";
        const string PROMPT_CONFIRM_DELETE   = "Delete this contact?";

        // Main Menu
        const string TITLE_MAIN_MENU               = "\n=== Address Book ===\n";
        const string MAIN_MENU_OPT_1_ADD           = "1) Add Contact\n";
        const string MAIN_MENU_OPT_2_EDIT          = "2) Edit Contact\n";
        const string MAIN_MENU_OPT_3_DELETE        = "3) Delete Contact\n";
        const string MAIN_MENU_OPT_4_VIEW          = "4) View Contacts\n";
        const string MAIN_MENU_OPT_5_SEARCH_FILTER = "5) Search / Filter\n";
        const string MAIN_MENU_OPT_6_TAGS_GROUPS   = "6) Tags / Groups\n";
        const string MAIN_MENU_OPT_7_REPORTS       = "7) Reports\n";
        const string MAIN_MENU_OPT_8_SAVE          = "8) Save to File\n";
        const string MAIN_MENU_OPT_0_EXIT          = "0) Exit\n";
        const int    MAIN_MENU_MIN_OPTION          = 0;
        const int    MAIN_MENU_MAX_OPTION          = 8;

        // Main Menu Choice Codes
        const int MAIN_CHOICE_EXIT          = 0;
        const int MAIN_CHOICE_ADD           = 1;
        const int MAIN_CHOICE_EDIT          = 2;
        const int MAIN_CHOICE_DELETE        = 3;
        const int MAIN_CHOICE_VIEW          = 4;
        const int MAIN_CHOICE_SEARCH_FILTER = 5;
        const int MAIN_CHOICE_TAGS_GROUPS   = 6;
        const int MAIN_CHOICE_REPORTS       = 7;
        const int MAIN_CHOICE_SAVE          = 8;

        // View Menu
        const string TITLE_VIEW_MENU            = "\n=== View Contacts ===\n";
        const string VIEW_MENU_OPT_1_LIST_ALL   = "1) List All Contacts\n";
        const string VIEW_MENU_OPT_2_VIEW_BY_ID = "2) View Contact by ID\n";
        const string VIEW_MENU_OPT_0_BACK       = "0) Back\n";
        const int    VIEW_MENU_MIN_OPTION       = 0;
        const int    VIEW_MENU_MAX_OPTION       = 2;

        // View Menu Choice Codes
        const int VIEW_CHOICE_BACK      = 0;
        const int VIEW_CHOICE_LIST_ALL  = 1;
        const int VIEW_CHOICE_VIEW_BY_ID= 2;

        // Search / Filter Menu
        const string TITLE_SEARCH_FILTER_MENU     = "\n=== Search / Filter ===\n";
        const string SEARCH_FILTER_OPT_1_BY_NAME  = "1) Search by Name\n";
        const string SEARCH_FILTER_OPT_2_BY_EMAIL = "2) Search by Email\n";
        const string SEARCH_FILTER_OPT_3_BY_PHONE = "3) Search by Phone\n";
        const string SEARCH_FILTER_OPT_4_BY_TYPE  = "4) Filter by Type\n";
        const string SEARCH_FILTER_OPT_5_BY_CITY  = "5) Filter by City\n";
        const string SEARCH_FILTER_OPT_6_BY_TAG   = "6) Filter by Tag\n";
        const string SEARCH_FILTER_OPT_0_BACK     = "0) Back\n";
        const int    SEARCH_FILTER_MIN_OPTION     = 0;
        const int    SEARCH_FILTER_MAX_OPTION     = 6;

        // Search / Filter Choice Codes
        const int SEARCH_CHOICE_BACK     = 0;
        const int SEARCH_CHOICE_BY_NAME  = 1;
        const int SEARCH_CHOICE_BY_EMAIL = 2;
        const int SEARCH_CHOICE_BY_PHONE = 3;
        const int SEARCH_CHOICE_BY_TYPE  = 4;
        const int SEARCH_CHOICE_BY_CITY  = 5;
        const int SEARCH_CHOICE_BY_TAG   = 6;

        // Reports Menu
        const string TITLE_REPORTS_MENU       = "\n=== Reports ===\n";
        const string REPORTS_OPT_1_MISSING    = "1) Missing Info\n";
        const string REPORTS_OPT_2_COUNTS     = "2) Counts by Type\n";
        const string REPORTS_OPT_3_GROUPS     = "3) Group Summary\n";
        const string REPORTS_OPT_0_BACK       = "0) Back\n";
        const int    REPORTS_MIN_OPTION       = 0;
        const int    REPORTS_MAX_OPTION       = 3;

        // Reports Choice Codes
        const int REPORTS_CHOICE_BACK      = 0;
        const int REPORTS_CHOICE_MISSING   = 1;
        const int REPORTS_CHOICE_COUNTS    = 2;
        const int REPORTS_CHOICE_GROUPS    = 3;

        // Tags / Groups Menu
        const string TITLE_TAGS_GROUPS_MENU         = "\n=== Tags / Groups ===\n";
        const string TAGS_GROUPS_OPT_1_ADD_TAG      = "1) Add Tag to Contact\n";
        const string TAGS_GROUPS_OPT_2_REMOVE_TAG   = "2) Remove Tag from Contact\n";
        const string TAGS_GROUPS_OPT_3_ASSIGN_GROUP = "3) Assign to Group\n";
        const string TAGS_GROUPS_OPT_4_REMOVE_GROUP = "4) Remove from Group\n";
        const string TAGS_GROUPS_OPT_0_BACK         = "0) Back\n";
        const int    TAGS_GROUPS_MIN_OPTION         = 0;
        const int    TAGS_GROUPS_MAX_OPTION         = 4;

        // Tags / Groups Choice Codes
        const int TAGS_GROUPS_CHOICE_BACK         = 0;
        const int TAGS_GROUPS_CHOICE_ADD_TAG      = 1;
        const int TAGS_GROUPS_CHOICE_REMOVE_TAG   = 2;
        const int TAGS_GROUPS_CHOICE_ASSIGN_GROUP = 3;
        const int TAGS_GROUPS_CHOICE_REMOVE_GROUP = 4;

        // Prompts
        const string PROMPT_ENTER_CONTACT_ID = "Enter Contact ID: ";
        const string PROMPT_NAME_CONTAINS    = "Name contains: ";
        const string PROMPT_EMAIL_CONTAINS   = "Email contains: ";
        const string PROMPT_PHONE_CONTAINS   = "Phone contains: ";
        const string PROMPT_CITY_VALUE       = "City: ";
        const string PROMPT_TAG_VALUE        = "Tag: ";
        const string PROMPT_TAG_TO_ADD       = "Tag to add: ";
        const string PROMPT_TAG_TO_REMOVE    = "Tag to remove: ";
        const string PROMPT_GROUP_TO_ASSIGN  = "Group to assign: ";
        const string PROMPT_GROUP_TO_REMOVE  = "Group to remove: ";

        // Type Picker
        const string TITLE_SELECT_CONTACT_TYPE = "\nSelect Contact Type:\n";
        const string TYPE_MENU_OPT_1_PERSON    = "1) Person\n";
        const string TYPE_MENU_OPT_2_BUSINESS  = "2) Business\n";
        const string TYPE_MENU_OPT_3_VENDOR    = "3) Vendor\n";
        const string TYPE_MENU_OPT_4_EMERGENCY = "4) Emergency\n";
        const int    TYPE_PICKER_MIN_OPTION    = 1;
        const int    TYPE_PICKER_MAX_OPTION    = 4;

        // Type Tokens
        const string TYPE_PERSON    = "Person";
        const string TYPE_BUSINESS  = "Business";
        const string TYPE_VENDOR    = "Vendor";
        const string TYPE_EMERGENCY = "Emergency";

        // Misc
        const string TEXT_AND = " and ";
    }

    using namespace CONSTANTS;

    // =====================================================================================
    // INPUT / UI HELPERS
    // =====================================================================================

    void ClearStandardInput()
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int ReadIntegerInRange(const string& promptMessage,
                                 int     minInclusive,
                                 int     maxInclusive)
    {
        int  userInput       = 0;
        bool continueReading = true;

        while (continueReading)
        {
            cout << promptMessage;

            if (         cin >> userInput &&
                userInput >= minInclusive &&
                userInput <= maxInclusive)
            {
                ClearStandardInput();
                continueReading = false;
            }
            else
            {
                ClearStandardInput();
                cout << MESSAGE_ENTER_NUMBER_BETWEEN_BEGIN
                     << minInclusive
                     << TEXT_AND
                     << maxInclusive
                     << MESSAGE_ENTER_NUMBER_BETWEEN_END;
            }
        }

        return userInput;
    }

    int ReadIntegerAny(const string& promptMessage)
    {
        int  userInput       = 0;
        bool continueReading = true;

        while (continueReading)
        {
            cout << promptMessage;

            if (cin >> userInput)
            {
                ClearStandardInput();
                continueReading = false;
            }
            else
            {
                ClearStandardInput();
                cout << MESSAGE_ENTER_VALID_INTEGER;
            }
        }

        return userInput;
    }

    string ReadLine(const string& promptMessage)
    {
        string userInput;
        cout << promptMessage;
        getline(cin, userInput);
        return userInput;
    }

    string ReadNonEmptyLine(const string& promptMessage)
    {
        bool needInput = true;
        string trimmedValue;

        while (needInput)
        {
            string input = ReadLine(promptMessage);
            if (!IsBlank(input))
            {
                trimmedValue = Trim(input);
                needInput    = false;
            }
            else
            {
                cout << MESSAGE_INPUT_CANNOT_BE_BLANK;
            }
        }

        return trimmedValue;
    }

    bool ConfirmYesNo(const string& promptMessage)
    {
        bool decided      = false;
        bool result       = false;
        char userResponse = '\0';

        while (!decided)
        {
            cout << promptMessage << PROMPT_CONFIRM_YES_NO;

            if (cin >> userResponse)
            {
                ClearStandardInput();

                if (userResponse == 'y' ||
                    userResponse == 'Y')
                {
                    result  = true;
                    decided = true;
                }
                else if (userResponse == 'n' ||
                         userResponse == 'N')
                {
                    result  = false;
                    decided = true;
                }
                else
                {
                    cout << MESSAGE_ENTER_Y_OR_N;
                }
            }
            else
            {
                ClearStandardInput();
                cout << MESSAGE_ENTER_Y_OR_N;
            }
        }

        return result;
    }

    void PauseForUser()
    {
        cout << PROMPT_PRESS_ENTER_TO_CONTINUE;
        cin.get();
    }

    string PromptContactType()
    {
        bool validChoice = false;
        string type;

        while (!validChoice)
        {
            cout << TITLE_SELECT_CONTACT_TYPE
                 << TYPE_MENU_OPT_1_PERSON
                 << TYPE_MENU_OPT_2_BUSINESS
                 << TYPE_MENU_OPT_3_VENDOR
                 << TYPE_MENU_OPT_4_EMERGENCY;

            int choice = ReadIntegerInRange(PROMPT_INPUT_ARROW,
                                            TYPE_PICKER_MIN_OPTION,
                                            TYPE_PICKER_MAX_OPTION);

            switch (choice)
            {
                case 1:
                    type        = TYPE_PERSON;
                    validChoice = true;
                    break;
                case 2:
                    type        = TYPE_BUSINESS;
                    validChoice = true;
                    break;
                case 3:
                    type        = TYPE_VENDOR;
                    validChoice = true;
                    break;
                case 4:
                    type        = TYPE_EMERGENCY;
                    validChoice = true;
                    break;
                default:
                    break;
            }
        }
        return type;
    }

    int PromptContactId(const string& label)
    {
        return ReadIntegerAny(label);
    }

    // =====================================================================================
    // SUBMENU: VIEW
    // =====================================================================================

    void ShowViewMenu(const AddressBook& addressBook)
    {
        bool continueLoop   = true;
        int  selectedOption = 0;

        while (continueLoop)
        {
            cout << TITLE_VIEW_MENU
                 << VIEW_MENU_OPT_1_LIST_ALL
                 << VIEW_MENU_OPT_2_VIEW_BY_ID
                 << VIEW_MENU_OPT_0_BACK;

            selectedOption = ReadIntegerInRange(PROMPT_INPUT_ARROW,
                                                VIEW_MENU_MIN_OPTION,
                                                VIEW_MENU_MAX_OPTION);

            if (selectedOption == VIEW_CHOICE_BACK)
            {
                continueLoop = false;
            }
            else if (selectedOption == VIEW_CHOICE_LIST_ALL)
            {
                addressBook.ListAllPreviews();
                PauseForUser();
            }
            else if (selectedOption == VIEW_CHOICE_VIEW_BY_ID)
            {
                int contactId = ReadIntegerAny(PROMPT_ENTER_CONTACT_ID);

                if (!addressBook.ViewContact(contactId))
                {
                    cout << MESSAGE_CONTACT_NOT_FOUND;
                }

                PauseForUser();
            }
        }
    }

    // =====================================================================================
    // SUBMENU: SEARCH / FILTER
    // =====================================================================================

    void ShowSearchFilterMenu(const AddressBook& addressBook)
    {
        bool   continueLoop   = true;
        int    selectedOption = 0;
        string query;

        while (continueLoop)
        {
            cout << TITLE_SEARCH_FILTER_MENU
                 << SEARCH_FILTER_OPT_1_BY_NAME
                 << SEARCH_FILTER_OPT_2_BY_EMAIL
                 << SEARCH_FILTER_OPT_3_BY_PHONE
                 << SEARCH_FILTER_OPT_4_BY_TYPE
                 << SEARCH_FILTER_OPT_5_BY_CITY
                 << SEARCH_FILTER_OPT_6_BY_TAG
                 << SEARCH_FILTER_OPT_0_BACK;

            selectedOption = ReadIntegerInRange(PROMPT_INPUT_ARROW,
                                                SEARCH_FILTER_MIN_OPTION,
                                                SEARCH_FILTER_MAX_OPTION);

            if (selectedOption == SEARCH_CHOICE_BACK)
            {
                continueLoop = false;
            }
            else if (selectedOption == SEARCH_CHOICE_BY_NAME)
            {
                query = ReadNonEmptyLine(PROMPT_NAME_CONTAINS);
                std::vector<Contact> results = addressBook.SearchByName(query);
                addressBook.DisplaySearchResults(results, "Name contains '" + query + "'");
                PauseForUser();
            }
            else if (selectedOption == SEARCH_CHOICE_BY_EMAIL)
            {
                query = ReadNonEmptyLine(PROMPT_EMAIL_CONTAINS);
                std::vector<Contact> results = addressBook.SearchByEmail(query);
                addressBook.DisplaySearchResults(results, "Email contains '" + query + "'");
                PauseForUser();
            }
            else if (selectedOption == SEARCH_CHOICE_BY_PHONE)
            {
                query = ReadNonEmptyLine(PROMPT_PHONE_CONTAINS);
                std::vector<Contact> results = addressBook.SearchByPhone(query);
                addressBook.DisplaySearchResults(results, "Phone contains '" + query + "'");
                PauseForUser();
            }
            else if (selectedOption == SEARCH_CHOICE_BY_TYPE)
            {
                query = PromptContactType();
                std::vector<Contact> results = addressBook.FilterByType(query);
                addressBook.DisplaySearchResults(results, "Type = '" + query + "'");
                PauseForUser();
            }
            else if (selectedOption == SEARCH_CHOICE_BY_CITY)
            {
                query = ReadNonEmptyLine(PROMPT_CITY_VALUE);
                std::vector<Contact> results = addressBook.FilterByCity(query);
                addressBook.DisplaySearchResults(results, "City contains '" + query + "'");
                PauseForUser();
            }
            else if (selectedOption == SEARCH_CHOICE_BY_TAG)
            {
                query = ReadNonEmptyLine(PROMPT_TAG_VALUE);
                std::vector<Contact> results = addressBook.FilterByTag(query);
                addressBook.DisplaySearchResults(results, "Tag = '" + query + "'");
                PauseForUser();
            }
        }
    }

    // =====================================================================================
    // SUBMENU: REPORTS
    // =====================================================================================

    void ShowReportsMenu(const AddressBook& addressBook)
    {
        bool continueLoop   = true;
        int  selectedOption = 0;

        while (continueLoop)
        {
            cout << TITLE_REPORTS_MENU
                 << REPORTS_OPT_1_MISSING
                 << REPORTS_OPT_2_COUNTS
                 << REPORTS_OPT_3_GROUPS
                 << REPORTS_OPT_0_BACK;

            selectedOption = ReadIntegerInRange(PROMPT_INPUT_ARROW,
                                                REPORTS_MIN_OPTION,
                                                REPORTS_MAX_OPTION);

            if (selectedOption == REPORTS_CHOICE_BACK)
            {
                continueLoop = false;
            }
            else if (selectedOption == REPORTS_CHOICE_MISSING)
            {
                addressBook.ReportMissingInfo();
                PauseForUser();
            }
            else if (selectedOption == REPORTS_CHOICE_COUNTS)
            {
                addressBook.ReportCountsByType();
                PauseForUser();
            }
            else if (selectedOption == REPORTS_CHOICE_GROUPS)
            {
                addressBook.ReportGroupSummary();
                PauseForUser();
            }
        }
    }

    // =====================================================================================
    // SUBMENU: TAGS / GROUPS
    // =====================================================================================

    void ShowTagsGroupsMenu(AddressBook& addressBook)
    {
        bool   continueLoop   = true;
        int    selectedOption = 0;
        int    contactId      = 0;
        string tagOrGroup;

        while (continueLoop)
        {
            cout << TITLE_TAGS_GROUPS_MENU
                 << TAGS_GROUPS_OPT_1_ADD_TAG
                 << TAGS_GROUPS_OPT_2_REMOVE_TAG
                 << TAGS_GROUPS_OPT_3_ASSIGN_GROUP
                 << TAGS_GROUPS_OPT_4_REMOVE_GROUP
                 << TAGS_GROUPS_OPT_0_BACK;

            selectedOption = ReadIntegerInRange(PROMPT_INPUT_ARROW,
                                                TAGS_GROUPS_MIN_OPTION,
                                                TAGS_GROUPS_MAX_OPTION);

            if (selectedOption == TAGS_GROUPS_CHOICE_BACK)
            {
                continueLoop = false;
            }
            else
            {
                contactId = PromptContactId(PROMPT_ENTER_CONTACT_ID);

                if (selectedOption == TAGS_GROUPS_CHOICE_ADD_TAG)
                {
                    tagOrGroup = ReadNonEmptyLine(PROMPT_TAG_TO_ADD);
                    if (!addressBook.AddTag(contactId,
                                            tagOrGroup))
                    {
                        cout << MESSAGE_FAILED_ADD_TAG;
                    }
                }
                else if (selectedOption == TAGS_GROUPS_CHOICE_REMOVE_TAG)
                {
                    tagOrGroup = ReadNonEmptyLine(PROMPT_TAG_TO_REMOVE);
                    if (!addressBook.RemoveTag(contactId,
                                               tagOrGroup))
                    {
                        cout << MESSAGE_FAILED_REMOVE_TAG;
                    }
                }
                else if (selectedOption == TAGS_GROUPS_CHOICE_ASSIGN_GROUP)
                {
                    tagOrGroup = ReadNonEmptyLine(PROMPT_GROUP_TO_ASSIGN);
                    if (!addressBook.AssignToGroup(contactId,
                                                   tagOrGroup))
                    {
                        cout << MESSAGE_FAILED_ASSIGN_GROUP;
                    }
                }
                else if (selectedOption == TAGS_GROUPS_CHOICE_REMOVE_GROUP)
                {
                    tagOrGroup = ReadNonEmptyLine(PROMPT_GROUP_TO_REMOVE);
                    if (!addressBook.RemoveFromGroup(contactId,
                                                     tagOrGroup))
                    {
                        cout << MESSAGE_FAILED_REMOVE_GROUP;
                    }
                }

                PauseForUser();
            }
        }
    }

    // =====================================================================================
    // MAIN UI LOOP
    // =====================================================================================

    void RunMainMenuLoop(AddressBook& addressBook)
    {
        bool continueLoop   = true;
        int  selectedOption = 0;
        int  contactId      = 0;

        // Auto-load at startup
        addressBook.LoadFromFile();

        while (continueLoop)
        {
            cout << TITLE_MAIN_MENU
                 << MAIN_MENU_OPT_1_ADD
                 << MAIN_MENU_OPT_2_EDIT
                 << MAIN_MENU_OPT_3_DELETE
                 << MAIN_MENU_OPT_4_VIEW
                 << MAIN_MENU_OPT_5_SEARCH_FILTER
                 << MAIN_MENU_OPT_6_TAGS_GROUPS
                 << MAIN_MENU_OPT_7_REPORTS
                 << MAIN_MENU_OPT_8_SAVE
                 << MAIN_MENU_OPT_0_EXIT;

            selectedOption = ReadIntegerInRange(PROMPT_INPUT_ARROW,
                                                MAIN_MENU_MIN_OPTION,
                                                MAIN_MENU_MAX_OPTION);

            if (selectedOption == MAIN_CHOICE_EXIT)
            {
                if (ConfirmYesNo(PROMPT_SAVE_BEFORE_EXIT))
                {
                    addressBook.SaveToFile();
                }

                cout << MESSAGE_GOODBYE;
                continueLoop = false;
            }
            else if (selectedOption == MAIN_CHOICE_ADD)
            {
                addressBook.AddContact();
                PauseForUser();
            }
            else if (selectedOption == MAIN_CHOICE_EDIT)
            {
                contactId = PromptContactId(PROMPT_ENTER_CONTACT_ID);
                if (!addressBook.EditContact(contactId))
                {
                    cout << MESSAGE_CONTACT_NOT_FOUND;
                }
                PauseForUser();
            }
            else if (selectedOption == MAIN_CHOICE_DELETE)
            {
                contactId = PromptContactId(PROMPT_ENTER_CONTACT_ID);
                if (ConfirmYesNo(PROMPT_CONFIRM_DELETE))
                {
                    if (!addressBook.DeleteContact(contactId))
                    {
                        cout << MESSAGE_CONTACT_NOT_FOUND;
                    }
                }
                PauseForUser();
            }
            else if (selectedOption == MAIN_CHOICE_VIEW)
            {
                ShowViewMenu(addressBook);
            }
            else if (selectedOption == MAIN_CHOICE_SEARCH_FILTER)
            {
                ShowSearchFilterMenu(addressBook);
            }
            else if (selectedOption == MAIN_CHOICE_TAGS_GROUPS)
            {
                ShowTagsGroupsMenu(addressBook);
            }
            else if (selectedOption == MAIN_CHOICE_REPORTS)
            {
                ShowReportsMenu(addressBook);
            }
            else if (selectedOption == MAIN_CHOICE_SAVE)
            {
                addressBook.SaveToFile();
                PauseForUser();
            }
            else
            {
                cout << MESSAGE_INVALID_CHOICE;
                PauseForUser();
            }
        }
    }
}