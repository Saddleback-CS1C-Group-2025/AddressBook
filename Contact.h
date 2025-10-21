#pragma once

#include <string>
#include <vector>
#include <ostream>
#include <algorithm>

/****************************************************************
 * ENUM: ContactType
 * --------------------------------------------------------------
 * PURPOSE : Categorizes a contact so the address book can filter
 *           and report by type. Extend with new kinds as needed.
 * VALUES  : Person   - Individual / personal contact
 *           Business - Company / organization main contact
 *           Vendor   - Supplier / vendor contact
 *           Emergency- Emergency / critical contact
 * NOTE    : If new values are added OR order changes, update
 *           Contact::contactTypeToString(...) accordingly.
 ***************************************************************/
enum class ContactType { Person, Business, Vendor, Emergency };

/****************************************************************
 * CLASS: Contact
 * --------------------------------------------------------------
 * A lightweight, extensible data holder for different kinds of
 * address book entries. Designed to be subclassed later (e.g.,
 * BusinessContact, EmergencyContact) if specialized fields are
 * needed. For now, it captures common shared attributes.
 *
 * RESPONSIBILITIES:
 *   - Store identity (auto-generated id) and basic info.
 *   - Maintain groups and free-form tags (idempotent add/remove).
 *   - Provide simple string / CSV serialization helpers.
 *
 * LIMITATIONS / FUTURE WORK:
 *   - CSV currently does NOT escape commas or quotes.
 *   - No validation of email / phone formatting yet.
 ***************************************************************/
class Contact {
public:
    /************************************************************
     * Contact (default ctor)
     * ----------------------------------------------------------
     * PURPOSE : Create an empty Person-type contact with a
     *           unique auto-generated id. All strings start empty.
     * RETURNS : (object) New Contact instance.
     ***********************************************************/
    Contact();

    /************************************************************
     * Contact (value ctor)
     * ----------------------------------------------------------
     * PURPOSE : Create a contact initialized with supplied field
     *           values and a unique id.
     * PARAMS  : type         (IN) - Category of contact
     *           firstName    (IN) - Given name
     *           lastName     (IN) - Family name / org remainder
     *           email        (IN) - Email address (optional)
     *           phone        (IN) - Phone number (optional)
     *           addressLine  (IN) - Street / address line
     *           city         (IN) - City component
     *           state        (IN) - State / region
     *           postalCode   (IN) - Postal / ZIP code
     *           notes        (IN) - Free-form notes
     * RETURNS : (object) New Contact instance.
     ***********************************************************/
    Contact(ContactType type,          // IN - category / classification
        std::string firstName,         // IN - given / first name (or primary token)
        std::string lastName,          // IN - family name / remainder (org piece)
        std::string email = {},        // IN - email address (optional)
        std::string phone = {},        // IN - phone number (optional)
        std::string addressLine = {},  // IN - street address line
        std::string city = {},         // IN - city component
        std::string state = {},        // IN - state / region component
        std::string postalCode = {},   // IN - postal / ZIP code
        std::string notes = {});       // IN - free-form notes

    /************************************************************
     * ~Contact (virtual dtor)
     * ----------------------------------------------------------
     * PURPOSE : Ensure correct destruction through a base pointer
     *           when subclasses are introduced later.
     ***********************************************************/
    virtual ~Contact() = default; // Virtual for safe polymorphic deletion later.

    /************************************************************
     * Getters
     * ----------------------------------------------------------
     * PURPOSE : Provide read-only access to underlying fields.
     * NOTE    : All getters are O(1) trivial inline operations.
     ***********************************************************/
    int getId() const { return id_; }
    ContactType getType() const { return type_; }
    const std::string & getFirstName() const { return firstName_; }
    const std::string & getLastName() const { return lastName_; }
    const std::string & getEmail() const { return email_; }
    const std::string & getPhone() const { return phone_; }
    const std::string & getAddressLine() const { return addressLine_; }
    const std::string & getCity() const { return city_; }
    const std::string & getState() const { return state_; }
    const std::string & getPostalCode() const { return postalCode_; }
    const std::string & getNotes() const { return notes_; }
    const std::vector<std::string> & getGroups() const { return groups_; }
    const std::vector<std::string> & getTags() const { return tags_; }

    /************************************************************
     * getFullName
     * ----------------------------------------------------------
     * PURPOSE : Returns a friendly full name. If one part is
     *           empty, returns the other without extra spaces.
     * RETURNS : (string) Combined first + last (or single part).
     ***********************************************************/
    std::string getFullName() const;

    /************************************************************
     * Setters (fluent)
     * ----------------------------------------------------------
     * PURPOSE : Mutate individual fields; each returns *this to
     *           allow chaining (e.g., c.setFirstName(...).setLastName(...)).
     * RETURNS : (Contact&) Reference to self.
     ***********************************************************/
    Contact & setType(ContactType t) { type_ = t; return *this; }
    Contact & setFirstName(const std::string &v) { firstName_ = v; return *this; }
    Contact & setLastName(const std::string &v) { lastName_ = v; return *this; }
    Contact & setEmail(const std::string &v) { email_ = v; return *this; }
    Contact & setPhone(const std::string &v) { phone_ = v; return *this; }
    Contact & setAddressLine(const std::string &v) { addressLine_ = v; return *this; }
    Contact & setCity(const std::string &v) { city_ = v; return *this; }
    Contact & setState(const std::string &v) { state_ = v; return *this; }
    Contact & setPostalCode(const std::string &v) { postalCode_ = v; return *this; }
    Contact & setNotes(const std::string &v) { notes_ = v; return *this; }

    /************************************************************
     * addGroup / removeGroup / hasGroup
     * ----------------------------------------------------------
     * PURPOSE : Manage membership in a textual group list.
     * RETURNS : add/remove -> true if a modification occurred.
     *            hasGroup  -> true if group present.
     * NOTE    : addGroup ignores empty strings & duplicates.
     ***********************************************************/
    bool addGroup(const std::string &group);
    bool removeGroup(const std::string &group);
    bool hasGroup(const std::string &group) const;

    /************************************************************
     * addTag / removeTag / hasTag
     * ----------------------------------------------------------
     * PURPOSE : Manage free-form tags for flexible filtering.
     * RETURNS : add/remove -> true if a modification occurred.
     *            hasTag    -> true if tag present.
     * NOTE    : addTag ignores empty strings & duplicates.
     ***********************************************************/
    bool addTag(const std::string &tag);
    bool removeTag(const std::string &tag);
    bool hasTag(const std::string &tag) const;

    /************************************************************
     * toString
     * ----------------------------------------------------------
     * PURPOSE : Produces a multi-line human-readable summary.
     * PARAMS  : includeEmptyFields (IN) - When true, prints labels
     *           even for empty fields (useful for alignment).
     * RETURNS : (string) Formatted description.
     ***********************************************************/
    virtual std::string toString(bool includeEmptyFields = false) const;

    /************************************************************
     * toCSV
     * ----------------------------------------------------------
     * PURPOSE : Serialize to a simple comma-separated line.
     * RETURNS : (string) CSV-formatted record.
     * WARNING : Commas / quotes in field values are NOT escaped.
     ***********************************************************/
    virtual std::string toCSV() const;

    /************************************************************
     * contactTypeToString (static)
     * ----------------------------------------------------------
     * PURPOSE : Map enum ContactType to a stable string token.
     * RETURNS : (string) Human-readable type name.
     ***********************************************************/
    static std::string contactTypeToString(ContactType type);

protected:
    /************************************************************
     * DATA MEMBERS (Contact)
     * ----------------------------------------------------------
     * | Name         | Type                     | Purpose / Usage
     * |--------------|--------------------------|-----------------------------------------------|
     * | id_          | int                      | Unique auto-generated identifier (read-only)  |
     * | type_        | ContactType              | Category for filtering/reporting              |
     * | firstName_   | std::string              | Given name / first token                      |
     * | lastName_    | std::string              | Family name / second token / org remainder    |
     * | email_       | std::string              | Contact email (may be blank)                  |
     * | phone_       | std::string              | Contact phone (may be blank)                  |
     * | addressLine_ | std::string              | Street address line                           |
     * | city_        | std::string              | City component                                |
     * | state_       | std::string              | State / region                                |
     * | postalCode_  | std::string              | Postal / ZIP code                             |
     * | notes_       | std::string              | Free-form notes                               |
     * | groups_      | vector<string>           | Named group memberships (unique entries)      |
     * | tags_        | vector<string>           | Free-form tags (unique entries)               |
     * ----------------------------------------------------------
     * DESIGN NOTES:
     *   - groups_ and tags_ intentionally stored as vectors for
     *     predictable iteration order; if performance of lookup
     *     becomes critical, consider unordered_set and export
     *     order separately.
     *   - id_ intentionally simple int; could migrate to UUID if
     *     merging multiple address books later.
     ***********************************************************/
    // Protected so derived classes can access.
    int id_ {0};
    ContactType type_ { ContactType::Person };
    std::string firstName_;
    std::string lastName_;
    std::string email_;
    std::string phone_;
    std::string addressLine_;
    std::string city_;
    std::string state_;
    std::string postalCode_;
    std::string notes_;
    std::vector<std::string> groups_;
    std::vector<std::string> tags_;

private:
    static int nextId_; // auto-increment id source.
    static int generateId();
};

 /***************************************************************
    * operator<< (stream insertion)
    * -------------------------------------------------------------
    * PURPOSE : Allow std::ostream << Contact for easy printing.
    * RETURNS : (ostream&) reference to the passed stream.
    **************************************************************/
std::ostream & operator<<(std::ostream &os, const Contact &c);
