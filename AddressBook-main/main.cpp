// main.cpp
#include "AddressBookTG.h"
#include "MainUI.h"

int main()
{
    AddressBookTG addressBookInstance;
    UI::RunMainMenuLoop(addressBookInstance);
    return 0;
}