#ifndef JSON_PARSER_HPP_
#define JSON_PARSER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "./json_structures/json.hpp"

class json_parser {

  public:

    json_parser() {}

    json_parser(const std::string& _path, const bool _debug = false);

    ~json_parser();

    const std::string get_path() const { return m_path; }

    json* get_json() const { return m_json; }

    // Parse the .json file at _path.
    json* parse() ;

  protected:

    bool m_debug{false};

  private:

    // The path to the parsed json file.
    std::string m_path{""};

    // The json file in a string.
    std::string m_string{""};

    // The json object that we will parse. Essentially, this is a representation
    // of a json file using C++ objects and data structures.
    json* m_json{nullptr};

};

#endif
