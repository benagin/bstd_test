#ifndef BSTD_JSON_HPP_
#define BSTD_JSON_HPP_

#include "structures/json_base.hpp"
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

    // Getters.

    // Returns m_children.size().
    const std::size_t size() const override;

    const std::vector<value*>& get_children() const;

    const std::string& get_path() const;

    // Operator overloads.

    // True if this contains exactly the same children as _rhs.
    // TODO: determine if this is what we really want.
    bool operator==(const json& _rhs);

    json& operator+=(const json& _rhs);

    // TODO: check if we need different forms of this function.
    //       Also, it might be good to be able to add json to a string.
    friend json operator+(json _lhs, const json& _rhs);

    // Member functions.

    const std::string to_string() const override;

    // Parse a json string.
    // Called by json::json(string, bool) constructor.
    void parse(const std::string& _string) override;

    void add_child(value* _child);
    void add_children(const std::vector<value*>&
        _children);

    // Writes the json object to m_path or _path if provided.
    // Note: this erases the contents of _path if the file exists.
    void write() const;
    void write(const std::string& _path) const override;

  private:

    std::string m_path{""};

    // The json objects at the highest level in the .json file.
    std::vector<value*> m_children;

};

}

#endif
