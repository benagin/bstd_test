#include "parser.hpp"

namespace bstd::json {


std::shared_ptr<json>
parse(const std::string& _string) {
  // Could be a .json file path or a JSON string.
  auto json_string = _string;

  // Try to open string as a path.
  auto ifs = utilities::open_json_file(_string, std::fstream::in);

  if(ifs.is_open()) {
    json_string = std::string((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());
  }

  // Now we have a JSON string for sure.

  const auto& leading_ws = trim_leading_ws(json_string);

  auto result = std::make_shared<json>();

  if(json_string.empty())
    return result;

  std::cout << json_string << std::endl;

  // Check first non-whitespace character to determine the type of value we
  // have.
  if(json_string.starts_with('{')) {
    result->add_value(parse_object(leading_ws, json_string));
  }
  else if(json_string.starts_with('['))
    result->add_value(parse_array(leading_ws, json_string));
  else if(json_string.starts_with('\"'))
    // TODO: implement.
    return result;
  else if(isdigit(json_string.front()))
    // TODO: implement.
    return result;
  else if(json_string.starts_with("true"))
    // TODO: implement.
    return result;
  else if(json_string.starts_with("false"))
    // TODO: implement.
    return result;
  else if(json_string.starts_with("null"))
    // TODO: implement.
    return result;
  else {
    std::cout << "else" << std::endl;
    std::string copy(json_string);
    throw bstd::error::context_error(copy, copy.cbegin(),
        "Invalid JSON value. Expected '{', '[', '\"', a number, true, " \
        "false, or null");
  }

  return result;
}


std::shared_ptr<object>
parse_object(const std::string _leading_ws, const std::string _string) {
  // TODO: implement.
  return std::make_shared<object>();
}


std::shared_ptr<array>
parse_array(const std::string _leading_ws, const std::string _string) {
  // TODO: implement.
  return std::make_shared<array>();
}


const std::string
trim_leading_ws(std::string& _string) {
  // Whitespace characters supported by JSON.
  // See grammar (www.json.org) for ws.
  constexpr std::string_view ws = " \t\n\r";

  const auto index = _string.find_first_not_of(ws);

  // Case where there is no whitespace.
  if(index == 0) {
    return "";
  }

  // Case where the whole string is whitespace.
  if(index == _string.npos) {
    _string = "";
    return _string;
  }

  //_string.remove_prefix(index);

  return _string.substr(0, index);
}


}
