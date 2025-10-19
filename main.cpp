// main.cpp
#include "AddressBookTG.h"
#include "MainUI.h"

int main()
{
    AddressBook addressBookInstance;
    UI::RunMainMenuLoop(addressBookInstance);
    return 0;
}