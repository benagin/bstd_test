#ifndef BSTD_JSON_PARSER_HPP_
#define BSTD_JSON_PARSER_HPP_

#include <fstream>
#include <iostream>
#include <memory>
#include <string_view>
#include <sstream>

#include <bstd_error.hpp>

#include "json.hpp"
#include "structures/array.hpp"
#include "structures/object.hpp"
#include "utilities/json_file_util.hpp"

// Parse JSON according to its grammar (https://www.json.org/).
namespace bstd::json {

    // Parse a .json file or a JSON string and return the result as a json
    // object. The type of object depends on the contents of the file or string.
    std::shared_ptr<json_base> parse(const std::string& _string);

    std::shared_ptr<object> parse_object(const std::string_view _leading_ws,
        const std::string_view _string);

    std::shared_ptr<array> parse_array(const std::string_view _leading_ws,
        const std::string_view _string);

    // Return and remove the leading whitespace from _string.
    const std::string_view eat_leading_ws(std::string_view _string);
}

#endif
