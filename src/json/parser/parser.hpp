#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../../error/error.hpp"
#include "../json.hpp"

class parser {

  public:

    parser() {}

    parser(const bool _debug) : m_debug(_debug) {}

    ~parser();

    // Parse a JSON string.
    void parse(const std::string& _string) ;

  protected:

    bool m_debug{false};

};

#endif
