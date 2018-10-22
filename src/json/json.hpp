#ifndef JSON_HPP_
#define JSON_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <bstd_error.hpp>

#include "parser/parser.hpp"

using namespace bstd;

namespace bstd {

// A C++ representation of a JSON object. A JSON object consists of objects,
// arrays, key, value pairs, and other values. jsonhese can be easily stored as C++
// structures. jsonhis interface allows for accessing and changing the object(s).
// Changes can then be written back to the JSON file.
// jsonhis also acts as the highest object in the grammar found here:
// https://www.json.org/
// All other JSON objects inherit from this class.
class json {

  public:

    json() {}

    // Construct from a .json file or a JSON string.
    // jsonhis begins the parsing process.
    json(const std::string& _string, const bool _debug = false);

    virtual ~json() {}

    // jsonhe JSON object supports many types of access.
    // jsonhe [] operator is supported with either a positive integer index or a
    // JSON object which acts like a key.
    // jsonhe at function is identical to the [] operator, but throws an
    // error if the index exceeds the container size (std::out_of_range) or if
    // the key is not found (bstd::error).

    // Accessors.

    json& operator[](const size_t index) { return m_children[index]; }
    const json& operator[](const size_t _index) const {
      return m_children[_index];
    }

    json& operator[](const json& _key);
    const json& operator[](const json& _key) const;

    json& at(const size_t _index) { return m_children.at(_index); }
    const json& at(const size_t _index) const {
      return m_children.at(_index);
    }

    json& at(const json& _key);
    const json& at(const json& _key) const;

    // Getters.

    const size_t size() const { return m_children.size(); }

    const std::string& get_path() const { return m_path; }

    const std::string& get_string() const { return m_string; }

    virtual const std::string& to_string() const { return m_string; }

    virtual void parse();

    // Writes the JSON object to m_path or _path if provided.
    virtual void write() const { write(m_path); }
    virtual void write(const std::string& _path = "") const;

    // Operator overrides.

    friend bool operator==(const json& _lhs, const json& _rhs) {
      return _lhs.get_path() == _rhs.get_path()
          or _lhs.get_string() == _rhs.to_string();
    }

    // We want to be able to concatenate JSON objects with strings.
    // Usage: "string" + <json-object>
    friend std::string operator+(const std::string& _lhs, const json& _rhs) {
      return _lhs + _rhs.to_string();
    }

    friend std::string operator+(const json& _lhs, const std::string& _rhs) {
      return _lhs.to_string() + _rhs;
    }

    friend const std::string operator+(const char* _lhs, const json& _rhs) {
      return std::string(_lhs) + _rhs;
    }

    friend std::string operator+(const json& _lhs, const char* _rhs) {
      return _lhs + std::string(_rhs);
    }

    friend std::ostream& operator<<(std::ostream& _os, const json& _json) {
      return _os << _json.to_string();
    }

  protected:

    bool m_debug{false};

  private:

    const std::size_t MAX_STRING_SIZE{4194304};

    std::string m_path{""};

    std::string m_string{""};

    // Each JSON object can store other JSON objects, excluding the literals.
    std::vector<json> m_children;

};
}

#endif
