#include "parser.hpp"

namespace bstd::json {


std::shared_ptr<json_base>
parse(const std::string& _string) {
  // Could be a .json file path or a JSON string.
  std::string_view json_string = _string;

  try {
    // Try to open string as a path.
    auto ifs = utilities::open_json_file(_string, std::fstream::in);

    json_string = std::string((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());
  }
  catch(bstd::error::error& _e) {
    std::cout <<
      "Couldn't open _string as file. Attempting to parse as a JSON string."
      << std::endl;
  }

  // Now we have a JSON string for sure.

  const auto leading_ws = eat_leading_ws(json_string);

  if(json_string.empty())
    return std::make_shared<json>();

  // Check first non-whitespace character to determine the type of value we
  // have.
  if(json_string.starts_with('{'))
    return parse_object(leading_ws, json_string);
  else if(json_string.starts_with('['))
    return parse_array(leading_ws, json_string);
  else if(json_string.starts_with('\"'))
    // TODO: implement.
    return std::make_shared<object>();
  else if(isdigit(json_string.front()))
    // TODO: implement.
    return std::make_shared<object>();
  else if(json_string.starts_with('t'))
    // TODO: implement.
    return std::make_shared<object>();
  else if(json_string.starts_with('f'))
    // TODO: implement.
    return std::make_shared<object>();
  else if(json_string.starts_with('n'))
    // TODO: implement.
    return std::make_shared<object>();
  else
    throw bstd::error::context_error(_string,
        _string.cbegin(),
        "Invalid JSON value. Expected '{', '[', '\"', number, true, \
        false, or null");
}


std::shared_ptr<object>
parse_object(const std::string_view _leading_ws, const std::string_view _string) {
  // TODO: implement.
  return std::make_shared<object>();
}


std::shared_ptr<array>
parse_array(const std::string_view _leading_ws, const std::string_view _string) {
  // TODO: implement.
  return std::make_shared<array>();
}


const std::string_view
eat_leading_ws(std::string_view _string) {
  for(auto& c : _string)
    if(isspace(c))
      _string.remove_prefix(1);

  return _string;
}


}
