# Simple Makefile for AddressBook project

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic
SRCS := main.cpp MainUI.cpp AddressBookTG.cpp AddressBookSF.cpp AddressBookAEDV.cpp Contact.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := addressbook

.PHONY: all run debug clean sf tg

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

# Build debug binary with symbols
debug: CXXFLAGS += -g
debug: clean
debug: $(TARGET)
	@echo "Built debug binary: $(TARGET)"

# Convenience target to build using the SF implementation only
sf: CXXFLAGS += -std=c++17
sf:
	$(CXX) $(CXXFLAGS) main.cpp MainUI.cpp AddressBookSF.cpp Contact.cpp -o $(TARGET)_sf
	@echo "Built SF binary: $(TARGET)_sf"

# Convenience target to build using the TG implementation only
tg:
	$(CXX) $(CXXFLAGS) main.cpp MainUI.cpp AddressBookTG.cpp Contact.cpp -o $(TARGET)_tg
	@echo "Built TG binary: $(TARGET)_tg"

clean:
	rm -f $(TARGET) $(TARGET)_sf $(TARGET)_tg $(OBJS)
	@echo "Cleaned."