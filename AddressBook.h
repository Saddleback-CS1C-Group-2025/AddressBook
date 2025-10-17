#pragma once

#include "Contact.h"
#include <vector>
#include <string>
#include <iostream>

class AddressBook {
private:
    std::vector<Contact> contacts_;

public:
    // Basic CRUD operations
    void AddContact();
    bool EditContact(int contactId);
    bool DeleteContact(int contactId);

    // View operations
    void ListAllPreviews() const;
    bool ViewContact(int contactId) const;

    // Search operations
    void SearchByName(const std::string& query) const;
    void SearchByEmail(const std::string& query) const;
    void SearchByPhone(const std::string& query) const;

    // Filter operations
    void FilterByType(const std::string& type) const;
    void FilterByCity(const std::string& city) const;
    void FilterByTag(const std::string& tag) const;

    // Tag/Group operations
    bool AddTag(int contactId, const std::string& tag);
    bool RemoveTag(int contactId, const std::string& tag);
    bool AssignToGroup(int contactId, const std::string& group);
    bool RemoveFromGroup(int contactId, const std::string& group);

    // File operations
    void LoadFromFile();
    void SaveToFile() const;

    // Reports
    void ReportMissingInfo() const;
    void ReportCountsByType() const;
    void ReportGroupSummary() const;
};