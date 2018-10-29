#ifndef JSON_HPP_
#define JSON_HPP_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <bstd_error.hpp>

#include "parser/parser.hpp"

namespace bstd::json {

// A C++ representation of a JSON object. A JSON object consists of objects,
// arrays, key, value pairs, and other values. These can be easily stored as
// C++ structures. This interface allows for accessing and changing the
// object(s). Changes can then be written back to the JSON file.
// This also acts as the highest object in the grammar found here:
// https://www.json.org/
// All other JSON objects inherit from this class.
class json {

  public:

    // Empty json object. Populate with a call to json::parse(string).
    json(const bool _debug = false) : m_debug(_debug) {}

    // Construct from a JSON string.
    // This begins the parsing process.
    json(const std::string& _string, const bool _debug = false);

    json& operator=(json _rhs);

    virtual ~json() {}

    // Getters.

    // Returns the size of m_children.
    virtual const size_t size() const;

    const std::vector<json*>& get_children() const;

    const std::string& get_path() const;

    // Operator overloads.

    // True if this contains exactly the same children as _rhs.
    // TODO: determine if this is what we really want.
    virtual bool operator==(const json& _rhs);

    virtual json& operator+=(const json& _rhs);

    friend json operator+(json _lhs, const json& _rhs);

    friend std::ostream& operator<<(std::ostream& _os, const json& _json);

    // Member functions.

    virtual const std::string to_string() const;

    // Parse a json string.
    // Called by json::json(string, bool) constructor.
    virtual void parse(const std::string& _string) final;

    virtual void add_child(json* _child) final;
    virtual void add_children(const std::vector<json*>&
        _children) final;

    // Writes the json object to m_path or _path if provided.
    void write() const;
    virtual void write(const std::string& _path) const;

  protected:

    bool m_debug{false};

  private:

    const std::size_t MAX_STRING_SIZE{4194304};

    std::string m_path{""};

    // The json objects at the highest level in the .json file.
    std::vector<json*> m_children;

};

}

#endif
