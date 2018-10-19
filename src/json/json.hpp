#ifndef JSON_HPP_
#define JSON_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <bstd_error.hpp>

#include "parser/parser.hpp"

namespace bstd {

// A C++ representation of a JSON object. A JSON object essentially consists of
// objects, arrays, key, value pairs, and other values. These can be easily
// stored as C++ structures.
// This interface allows for accessing and changing the object. Changes can then
// be written back to the JSON file.
class json {

  public:

    json() {}

    // Construct from a .json file or a JSON string.
    //
    // _string Path to .json file or JSON string.
    // _debug Debug mode?
    json(const std::string& _string, const bool _debug = false);

    ~json() {}

    const std::string& get_path() const { return m_path; }

    std::string get_string() const { return m_string; }

    // Writes m_string to m_path.
    void write() const;

    void parse();

  protected:

    friend std::ostream& operator<<(std::ostream& _os, const json& _json) {
      return _os << _json.get_string();
    }

    bool m_debug{false};

    std::string m_path{""};

    std::string m_string{""};

};
}

#endif
