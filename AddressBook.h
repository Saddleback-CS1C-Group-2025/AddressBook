#pragma once

#include "Contact.h"
#include <vector>
#include <string>
#include <iostream>

class AddressBook {
private:
    std::vector<Contact> contacts_;
    static const std::string DEFAULT_FILENAME;

    // Private helper methods
    Contact* FindContactById(int contactId);
    const Contact* FindContactById(int contactId) const;
    static bool ContainsCaseInsensitive(const std::string& str, const std::string& substr);

public:
    // Basic CRUD operations
    void AddContact();
    void AddContact(const Contact& contact);
    bool EditContact(int contactId);
    bool EditContact(int contactId, const Contact& updatedContact);
    bool DeleteContact(int contactId);

    // View operations
    void ListAllPreviews() const;
    bool ViewContact(int contactId) const;

    // Search operations
    std::vector<Contact> SearchByName(const std::string& nameQuery) const;
    std::vector<Contact> SearchByEmail(const std::string& emailQuery) const;
    std::vector<Contact> SearchByPhone(const std::string& phoneQuery) const;

    // Filter operations
    std::vector<Contact> FilterByType(const std::string& type) const;
    std::vector<Contact> FilterByCity(const std::string& city) const;
    std::vector<Contact> FilterByTag(const std::string& tag) const;

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

    // Helper method used by search methods
    void DisplaySearchResults(const std::vector<Contact>& results, const std::string& searchType) const;
};