#include "json_parser.hpp"

json_parser::
json_parser(const std::string& _path,
    const bool _debug) : m_debug(_debug), m_path(_path) {
  std::ifstream ifs(m_path);
  if(m_debug)
    std::cout << "json_parser::json_parser" << std::endl;

  constexpr std::string_view dot_json{".json"};
  const std::string extension =
    m_path.substr(m_path.size() - dot_json.length());

  if(extension != dot_json)
    throw error("File extension is not '.json'",
        "json_parser::json_parser");

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

json_parser::
~json_parser() {
  delete m_json;
}

json*
json_parser::
parse() {
  if(m_debug)
    std::cout << "json_parser::parse" << std::endl;

  // Create a new json object. Populate it. Return it.
  m_json = new json(m_path, m_string, m_debug);

  return m_json;
}
