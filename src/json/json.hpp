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
// arrays, key, value pairs, and other values. jsonhese can be easily stored as C++
// structures. jsonhis interface allows for accessing and changing the object(s).
// Changes can then be written back to the JSON file.
// jsonhis also acts as the highest object in the grammar found here:
// https://www.json.org/
// All other JSON objects inherit from this class.
class json {

  public:

    json(const bool _debug = false) : m_debug(_debug) {}

    // Construct from a JSON string.
    // This begins the parsing process.
    json(const std::string& _string, const bool _debug = false);

    // Required for std::insert(...).
    json& operator=(json _rhs) {
      std::swap(m_path, _rhs.m_path);
      std::swap(m_name, _rhs.m_name);
      std::swap(m_children, _rhs.m_children);

      return *this;
    }

    virtual ~json() {}

    // Getters.

    // Returns the size of the string representation of the JSON object.
    virtual const size_t size() const;

    virtual const std::string& get_name() const final;

    virtual const std::vector<json>& get_children() const final;

    const std::string& get_path() const;

    // Operator overrides.

    const bool operator==(const json& _rhs) const;

    virtual const std::string operator+(const std::string& _rhs) const;

    virtual const std::string operator+(const char* _rhs) const;

    // The right hand side object is essentially copied into the left hand side
    // object (this). The two JSON strings are concatenated.
    // NOTE: this means you lose the path (and other member variables) of the
    // right hand side object.
    virtual const json operator+(const json& _rhs) const;

    friend const std::string operator+(const char* _lhs, const json& _rhs) {
      return std::string(_lhs) + _rhs;
    }

    friend std::string operator+(const std::string& _lhs, const json& _rhs) {
      return _lhs + _rhs.to_string();
    }

    friend std::ostream& operator<<(std::ostream& _os, const json& _json) {
      return _os << _json.to_string();
    }

    virtual const std::string to_string() const;

    virtual void add_child(const json& _child) final;
    virtual void add_children(const std::vector<json>& _children) final;

    // Writes the JSON object to m_path or _path if provided.
    void write() const;
    virtual void write(const std::string& _path) const;

  protected:

    void parse(const std::string& _string);

    bool m_debug{false};

  private:

    const std::size_t MAX_STRING_SIZE{4194304};

    std::string m_path{""};

    // Either the file name (this is an instance of json) or the string
    // associated with this element (classes that derive from json).
    // From the grammar (https://www.json.org/) this is the string in:
    // member
    //  ws string ws ':' element
    std::string m_name{""};

    // The JSON objects at the highest level in the .json file.
    std::vector<json> m_children;

};

}

#endif
