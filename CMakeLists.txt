cmake_minimum_required(VERSION 4.0)
project(AddressBook)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AddressBook
        AddressBook.cpp
        Contact.cpp
        Contact.h
        main.cpp
        MainUI.cpp
        MainUI.h
        AddressBook.h)
