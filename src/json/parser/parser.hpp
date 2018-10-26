#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <bstd_error.hpp>

namespace bstd::json {

class json;

// Parse JSON.
class parser {

  public:

    parser(const bool _debug = false) : m_debug(_debug) {}

    ~parser() {}

    // Parse a JSON string and store the results in _json.
    void parse(const std::string& _string, const json* _json) const;

  protected:

    bool m_debug{false};

};

}

#endif
