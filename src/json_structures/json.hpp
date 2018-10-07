#ifndef JSON_HPP_
#define JSON_HPP_

#include <iostream>
#include <fstream>
#include <string>

#include "../error/error.hpp"

// A C++ representation of a json object. A json object essentially consists of
// objects, arrays, key, value pairs, and other values. These can be easily
// stored as C++ structures.
// This interface allows for accessing and changing the object. Changes can then
// be written back to the json file.
class json {

  public:

    json() {}

    json(const std::string& _path, const std::string& _string,
        const bool _debug = false)
      : m_path(_path), m_string(_string), m_debug(_debug) {}

    ~json() {}

    std::string get_string() const { return m_string; }

    // Writes m_string to m_path.
    void write() const;

  protected:

    friend std::ostream& operator<<(std::ostream&, const json&);

    std::string m_path{""};

    std::string m_string{""};

    bool m_debug{false};

};

#endif
