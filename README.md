# AddressBook

A C++ address book application for CS1C.  
This program manages contact information with features for searching, filtering, and generating summary reports.

---

## Current Modules
- **Contact.cpp / Contact.h** – Defines the `Contact` class and core contact data  
- **AddressBook.cpp / AddressBook.h** – Core contact management (add, edit, delete, search, save/load)  
- **MainUI.cpp / MainUI.h** – User interface, menus, and input handling  
- **main.cpp** – Entry point and main program loop  

---

## Build Instructions

You can compile and run this project using any C++17 compiler.

### Windows (Command Prompt or PowerShell)
```powershell
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp MainUI.cpp AddressBook.cpp Contact.cpp -o addressbook.exe
addressbook.exe
```
### Mac/Linux (Terminal)
```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp MainUI.cpp AddressBook.cpp Contact.cpp -o addressbook
./addressbook
```
