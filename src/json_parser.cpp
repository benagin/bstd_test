#include "json_parser.hpp"

json_parser::json_parser(const std::string& _path,
    const bool _debug) : m_debug(_debug), m_path(_path) {
  std::ifstream ifs(m_path);
  if(m_debug)
    std::cout << "json_parser::json_parser" << std::endl;

  if(!ifs.is_open()) {
    std::cerr << "Couldn't open json file at path: " << m_path
      << std::endl << "Does the file exist?" << std::endl;

    return;
  }

  // Read and store the file if it's valid.
  std::stringstream stream;
  stream << ifs.rdbuf();
  m_string = stream.str();

  if(m_debug)
    std::cout << "Read json file: " << std::endl << m_string << std::endl;
}

json_parser::~json_parser() {
  delete m_json;
}

json* json_parser::parse() {
  if(m_debug)
    std::cout << "json_parser::parse" << std::endl;

  m_json = new json(m_string);
  return m_json;
}
