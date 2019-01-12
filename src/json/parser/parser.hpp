#ifndef BSTD_JSON_PARSER_HPP_
#define BSTD_JSON_PARSER_HPP_

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <bstd_error.hpp>

namespace bstd::json {

class value;

// Parse JSON according to its grammar (https://www.json.org/).
class parser {

  public:

    parser(const bool _debug = false) : m_debug(_debug) {}

    ~parser() {}

    // Parse a JSON string and return the result as a value (member or element).
    std::shared_ptr<value> parse(const std::string& _string) const;

  protected:

    bool m_debug{false};

};

}

#endif
