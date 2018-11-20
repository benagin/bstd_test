#ifndef BSTD_JSON_HPP_
#define BSTD_JSON_HPP_

#include "json_base.hpp"
#include "structures/value.hpp"
#include "parser/parser.hpp"

namespace bstd::json {

// A C++ representation of a JSON object. A JSON object consists of objects,
// arrays, key, value pairs, and other values. These can be easily stored as
// C++ structures. This interface allows for accessing and changing the
// object(s). Changes can then be written back to the JSON file.
// This also acts as the highest object in the grammar found here:
// https://www.json.org/
class json final : public json_base {

  public:

    // Empty json object. Populate with a call to json::parse(string).
    json(const bool _debug = false) : json_base(_debug) {}

    // Construct from a JSON string.
    // This begins the parsing process.
    json(const std::string& _string, const bool _debug = false);

    json& operator=(json _rhs);

    ~json() {}

    // Getters and setters.

    // Returns m_value.size().
    const std::size_t size() const override;

    const std::string& get_path() const;
    void set_path(const std::string& _path);

    const std::shared_ptr<value>& get_value() const;
    void set_value(const std::shared_ptr<value>& _value);

    // Operator overloads.

    // True if this contains exactly the same values as _rhs.
    bool operator==(const json& _rhs) const;

    bool operator!=(const json& _rhs) const;

    json& operator+=(const json& _rhs);

    friend json operator+(json _lhs, const json& _rhs);

    // Member functions.

    const std::string to_string() const override;

    // Adds _value to m_value. The behavior depends on the type of _value.
    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

    // Parse a json string.
    // Called by json::json(string, bool) constructor.
    void parse(const std::string& _string) override;

    // Writes the json object to m_path or _path if provided.
    // Note: this erases the contents of _path if the file exists.
    void write() const;
    void write(const std::string& _path) const override;

  private:

    std::string m_path{""};

    // The json element at the highest level.
    std::shared_ptr<value> m_value;

};

}

#endif
