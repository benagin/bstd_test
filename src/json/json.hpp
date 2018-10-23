#ifndef JSON_HPP_
#define JSON_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
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

    json() {}

    // Construct from a .json file or a JSON string.
    // jsonhis begins the parsing process.
    json(const std::string& _string, const bool _debug = false);

    virtual ~json() {}

    // Getters.

    const size_t size() const;

    const std::string& get_path() const;

    const std::string& get_string() const;

    virtual const std::string& to_string() const;

    // The JSON object supports many types of access.
    // The [] operator is supported with either a positive integer index or a
    // JSON object which acts like a key.
    // The at(...) function is identical to the [] operator, but throws an
    // error if the index exceeds the container size (std::out_of_range) or if
    // the key is not found (bstd::error).

    // Accessors.

    json& operator[](const size_t index);
    const json& operator[](const size_t _index) const;

    json& operator[](const json& _key);
    const json& operator[](const json& _key) const;

    json& at(const size_t _index);
    const json& at(const size_t _index) const;

    json& at(const json& _key);
    const json& at(const json& _key) const;

    // Operator overrides.

    const bool operator==(const json& _rhs) const;

    virtual const std::string operator+(const std::string& _rhs) const;

    virtual const std::string operator+(const char* _rhs) const;

    // The right hand side object is essentially copied into the left hand side
    // object (this). The two JSON strings are concatenated.
    // NOTE: this means you lose the path (and other member variables) of the
    // right hand side object.
    virtual const json operator+(const json& _rhs);

    friend const std::string operator+(const char* _lhs, const json& _rhs) {
      return std::string(_lhs) + _rhs;
    }

    friend std::string operator+(const std::string& _lhs, const json& _rhs) {
      return _lhs + _rhs.to_string();
    }

    friend std::ostream& operator<<(std::ostream& _os, const json& _json) {
      return _os << _json.to_string();
    }

    virtual void parse();

    void add_child(const json& _child);

    // Writes the JSON object to m_path or _path if provided.
    virtual void write() const;
    virtual void write(const std::string& _path) const;

  protected:

    // Not called externally.
    void set_string(const std::string& _string);

    bool m_debug{false};

  private:

    const std::size_t MAX_STRING_SIZE{4194304};

    std::string m_path{""};

    // TODO: test and possibly move away from this implementation if it
    // effects performance.
    std::string m_string{""};

    // Each JSON object can store other JSON objects, excluding the literals.
    std::vector<json> m_children;

};
}

#endif
