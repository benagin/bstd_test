#ifndef BSTD_JSON_PARSER_HPP_
#define BSTD_JSON_PARSER_HPP_

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <bstd_error.hpp>

#include "json.hpp"
#include "structures/object.hpp"
#include "utilities/json_file_util.hpp"

// Parse JSON according to its grammar (https://www.json.org/).
namespace bstd::json {

    // Parse a .json file or a JSON string and return the result as a json
    // object. The type of object depends on the contents of the file or string.
    std::shared_ptr<json_base> parse(const std::string& _string);

}

#endif
