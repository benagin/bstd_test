#ifndef JSON_PARSER_HPP_
#define JSON_PARSER_HPP_

#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

class json_parser {

  public:

    json_parser() {}

    json_parser(const bool _debug) : m_debug(_debug) {}

    ~json_parser() {}

    // Parse the .json file at _path.
    void parse(const std::string _path) {}

    void test();

  protected:

  private:

    bool m_debug{false};

};

#endif
