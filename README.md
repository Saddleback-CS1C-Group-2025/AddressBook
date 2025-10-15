# AddressBook

c++ console address book application.

## Current Modules
- **Contact.cpp / Contact.h** – Contact structure and basic logic  
- **MainUI.cpp / MainUI.h** – User interface and menus  
- **main.cpp** – Entry point

## Build
```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp MainUI.cpp Contact.cpp -o addressbook
./addressbook
