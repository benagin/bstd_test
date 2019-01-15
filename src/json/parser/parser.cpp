#include "parser.hpp"

namespace bstd::json {


std::shared_ptr<json_base>
parse(const std::string& _string) {
  // Could be a .json file path or a JSON string.
  auto json_string = _string;

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

  // TODO: implement.
  return std::make_shared<object>();
}


}
