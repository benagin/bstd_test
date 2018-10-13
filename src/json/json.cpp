#include "json.hpp"


std::ostream&
operator<<(std::ostream& _os, const json& _json) {
  return _os << _json.get_string();
}


json::
json(const std::string& _string, const bool _debug) : m_debug(_debug) {
  if(m_debug)
    std::cout << "json::json" << std::endl;

  constexpr std::string_view dot_json{".json"};
  const std::string extension =
    _string.substr(_string.size() - dot_json.length());

  // Check if we have a JSON string.
  if(extension != dot_json)
    m_string = _string;
  else {
    // Try to open string as a path.
    m_path = _string;
    std::ifstream ifs(m_path);
    if(!ifs.is_open())
      throw error("Couldn't open json file at path: " + m_path +
          ". Does it exist?", "json_parser::json_parser");

    // Read and store the file if it's valid.
    std::stringstream stream;
    stream << ifs.rdbuf();
    m_string = stream.str();

    if(m_debug)
      std::cout << "Read json file: " << std::endl << m_string << std::endl;
  }

  parse();
}


void
json::
parse() {
  if(m_debug)
    std::cout << "json::parse" << std::endl;

  // TODO: Use the results of the parser.
  const auto p = new parser(m_debug);
  p->parse(m_string);
}


void
json::
write() const {
  if(m_debug)
    std::cout << "json::write" << std::endl;

  // No need to crash here, we can just do nothing. Log a warning instead.
  if(m_path.empty()) {
    std::cerr << "Attempting to write json object to empty path." << std::endl;
    return;
  }

  std::ofstream ofs(m_path, std::ofstream::trunc);

  if(!ofs.is_open())
    throw error("Couldn't open json file for writing: " + m_path +
        ". Does it exist?", "json::write");

  ofs << m_string;
}
