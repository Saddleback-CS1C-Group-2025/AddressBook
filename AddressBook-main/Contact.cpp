//======================================================================
// Implementation File: Contact.cpp
//----------------------------------------------------------------------
// PURPOSE:
//   Defines member functions for the Contact class. Provides logic for
//   id generation, group & tag management, string / CSV formatting,
//   and type-to-string conversion.
//----------------------------------------------------------------------
// DESIGN NOTES:
//   * All mutating operations are simple O(n) scans (vector) because
//     expected list sizes for groups/tags are small. If performance
//     becomes an issue, switch to unordered_set and keep a stable
//     iteration order structure if needed for display.
//   * toCSV currently does NOT escape delimiters; this is called out
//     explicitly so future developers can improve without surprises.
//======================================================================

#include "Contact.h"
#include <sstream>

// Static starting value for auto-incremented ids.
int Contact::nextId_ = 1;

//**********************************************************************
// generateId (private static)
//----------------------------------------------------------------------
// PURPOSE : Supplies a unique sequential id for each new Contact.
// RETURNS : (int) next available id value.
// NOTE    : Simple increment; thread-unsafe (acceptable for this
//           console app). Could be replaced with atomic if needed.
//**********************************************************************
int Contact::generateId() { return nextId_++; }

//**********************************************************************
// Contact (default constructor)
//----------------------------------------------------------------------
// PURPOSE : Initializes a blank Person-type contact with a unique id.
//**********************************************************************
Contact::Contact() : id_(generateId()) {}

//**********************************************************************
// Contact (value constructor)
//----------------------------------------------------------------------
// PURPOSE : Builds a fully-initialized Contact object with all
//           provided field values and an auto-generated id.
// PARAMS  : See header for parameter details.
//**********************************************************************
Contact::Contact(ContactType type,
                                 std::string firstName,
                                 std::string lastName,
                                 std::string email,
                                 std::string phone,
                                 std::string addressLine,
                                 std::string city,
                                 std::string state,
                                 std::string postalCode,
                                 std::string notes)
        : id_(generateId()),
            type_(type),
            firstName_(std::move(firstName)),
            lastName_(std::move(lastName)),
            email_(std::move(email)),
            phone_(std::move(phone)),
            addressLine_(std::move(addressLine)),
            city_(std::move(city)),
            state_(std::move(state)),
            postalCode_(std::move(postalCode)),
            notes_(std::move(notes)) {}

//**********************************************************************
// getFullName
//----------------------------------------------------------------------
// PURPOSE : Returns a friendly full display name. Avoids extra
//           spaces if one of the components is missing.
// RETURNS : (string) Either first, last, or "first last".
// EDGE    : Both empty -> returns empty string.
//**********************************************************************
std::string Contact::getFullName() const {
    if (firstName_.empty()) return lastName_;   // Only last name present
    if (lastName_.empty()) return firstName_;   // Only first name present
    return firstName_ + " " + lastName_;        // Both present
}

//**********************************************************************
// addGroup
//----------------------------------------------------------------------
// PURPOSE : Adds a group label if non-empty and not already present.
// RETURNS : true if the group was inserted; false otherwise.
//**********************************************************************
bool Contact::addGroup(const std::string &group) {
    if (group.empty()) return false; // Reject empty labels
    if (std::find(groups_.begin(), groups_.end(), group) != groups_.end()) return false; // Already there
    groups_.push_back(group);
    return true;
}

//**********************************************************************
// removeGroup
//----------------------------------------------------------------------
// PURPOSE : Removes a group label if present.
// RETURNS : true if a removal occurred; false if not found.
//**********************************************************************
bool Contact::removeGroup(const std::string &group) {
    auto it = std::remove(groups_.begin(), groups_.end(), group); // move matches to end
    if (it == groups_.end()) return false; // Not found
    groups_.erase(it, groups_.end());
    return true;
}

//**********************************************************************
// hasGroup
//----------------------------------------------------------------------
// PURPOSE : Tests membership in the group list.
// RETURNS : true if found; false otherwise.
//**********************************************************************
bool Contact::hasGroup(const std::string &group) const {
    return std::find(groups_.begin(), groups_.end(), group) != groups_.end();
}

//**********************************************************************
// addTag
//----------------------------------------------------------------------
// PURPOSE : Adds a free-form tag if non-empty & unique.
//**********************************************************************
bool Contact::addTag(const std::string &tag) {
    if (tag.empty()) return false; // Reject empty tags
    if (std::find(tags_.begin(), tags_.end(), tag) != tags_.end()) return false; // Already exists
    tags_.push_back(tag);
    return true;
}

//**********************************************************************
// removeTag
//----------------------------------------------------------------------
// PURPOSE : Removes a tag if found.
//**********************************************************************
bool Contact::removeTag(const std::string &tag) {
    auto it = std::remove(tags_.begin(), tags_.end(), tag);
    if (it == tags_.end()) return false; // Nothing to remove
    tags_.erase(it, tags_.end());
    return true;
}

//**********************************************************************
// hasTag
//----------------------------------------------------------------------
// PURPOSE : Checks whether a tag exists.
//**********************************************************************
bool Contact::hasTag(const std::string &tag) const {
    return std::find(tags_.begin(), tags_.end(), tag) != tags_.end();
}

//**********************************************************************
// toString
//----------------------------------------------------------------------
// PURPOSE : Build a multi-line human-readable representation.
// PARAMS  : includeEmptyFields -> when true, emits labels even
//           for empty values (useful for aligned tabular views).
// RETURNS : (string) formatted block.
//**********************************************************************
std::string Contact::toString(bool includeEmptyFields) const {
    std::ostringstream oss;
    oss << "ID: " << id_ << '\n';
    oss << "Type: " << contactTypeToString(type_) << '\n';
    if (!getFullName().empty() || includeEmptyFields)
        oss << "Name: " << getFullName() << '\n';
    if (!email_.empty() || includeEmptyFields)
        oss << "Email: " << email_ << '\n';
    if (!phone_.empty() || includeEmptyFields)
        oss << "Phone: " << phone_ << '\n';
    if (!addressLine_.empty() || includeEmptyFields)
        oss << "Address: " << addressLine_ << '\n';
    if (!city_.empty() || includeEmptyFields)
        oss << "City: " << city_ << '\n';
    if (!state_.empty() || includeEmptyFields)
        oss << "State: " << state_ << '\n';
    if (!postalCode_.empty() || includeEmptyFields)
        oss << "Postal: " << postalCode_ << '\n';
    if (!notes_.empty() || includeEmptyFields)
        oss << "Notes: " << notes_ << '\n';
    if (!groups_.empty() || includeEmptyFields) {
        oss << "Groups: ";
        for (size_t i = 0; i < groups_.size(); ++i) {
            if (i) oss << ", ";
            oss << groups_[i];
        }
        oss << '\n';
    }
    if (!tags_.empty() || includeEmptyFields) {
        oss << "Tags: ";
        for (size_t i = 0; i < tags_.size(); ++i) {
            if (i) oss << ", ";
            oss << tags_[i];
        }
        oss << '\n';
    }
    return oss.str();
}

//**********************************************************************
// toCSV
//----------------------------------------------------------------------
// PURPOSE : Serialize the contact into a single comma-separated
//           record. Groups and tags are pipe-delimited internally
//           to keep them as single columns.
// WARNING : No escaping of commas/quotes inside field values.
//           Future improvement: implement RFC 4180 style quoting.
//**********************************************************************
std::string Contact::toCSV() const {
    std::ostringstream oss;
    oss << id_ << ','
        << contactTypeToString(type_) << ','
        << firstName_ << ','
        << lastName_ << ','
        << email_ << ','
        << phone_ << ','
        << addressLine_ << ','
        << city_ << ','
        << state_ << ','
        << postalCode_ << ','
        << notes_ << ',';
    // groups joined by '|'
    for (size_t i = 0; i < groups_.size(); ++i) {
        if (i) oss << '|';
        oss << groups_[i];
    }
    oss << ',';
    // tags joined by '|'
    for (size_t i = 0; i < tags_.size(); ++i) {
        if (i) oss << '|';
        oss << tags_[i];
    }
    return oss.str();
}

//**********************************************************************
// contactTypeToString (static)
//----------------------------------------------------------------------
// PURPOSE : Convert enum value to a stable human-readable string.
//**********************************************************************
std::string Contact::contactTypeToString(ContactType type) {
    switch (type) {
        case ContactType::Person:    return "Person";
        case ContactType::Business:  return "Business";
        case ContactType::Vendor:    return "Vendor";
        case ContactType::Emergency: return "Emergency";
    }
    return "Unknown"; // Defensive fallback (should not happen)
}

//**********************************************************************
// operator<< (free function)
//----------------------------------------------------------------------
// PURPOSE : Allow streaming a Contact directly into an ostream.
// RETURNS : (ostream&) the modified stream (enables chaining).
//**********************************************************************
std::ostream & operator<<(std::ostream &os, const Contact &c) {
    os << c.toString();
    return os;
}

//**********************************************************************
// setIdForImport
//----------------------------------------------------------------------
// PURPOSE : Allow the loader to set the id parsed from file and ensure
//           the global nextId_ is advanced to avoid id collisions.
// NOTES   : Intended for use only during file import.
//**********************************************************************
void Contact::setIdForImport(int importedId) {
    id_ = importedId;
    if (importedId >= nextId_) {
        nextId_ = importedId + 1;
    }
}
