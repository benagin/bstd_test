#include "json.hpp"

using namespace bstd::json;

json::
json(const std::string& _string, const bool _debug) : m_debug(_debug) {
  if(m_debug)
    std::cout << "bstd::json" << std::endl;

  constexpr std::string_view dot_json{".json"};
  const auto extension =
    _string.substr(_string.size() - dot_json.length());

  // Check if we have a JSON string.
  if(extension != dot_json)
    m_string = _string;
  else {
    // jsonry to open string as a path.
    m_path = _string;
    // TODO: implement file size check.
    std::ifstream ifs(m_path);
    if(!ifs.is_open())
      throw bstd::error::error("Couldn't open json file at path: " + m_path +
          ". Does it exist?", "bstd::json");

    // Read and store the file if it's valid.
    std::stringstream stream;
    stream << ifs.rdbuf();
    m_string = stream.str();

    if(m_debug)
      std::cout << "Read json file: " << std::endl << m_string << std::endl;
  }

  // Limit the size of JSON objects for performance.
  if(m_string.size() > MAX_STRING_SIZE) {
    std::stringstream ss;
    ss << MAX_STRING_SIZE;
    throw bstd::error::error("btsd::json",
        "The JSON object is too large. The current maximum string size is "
        + ss.str());
  }

  parse();
}


const size_t
bstd::json::json::
size() const {
  return m_children.size();
}


const std::string&
bstd::json::json::
get_path() const {
  return m_path;
}


const std::string&
bstd::json::json::
get_string() const {
  return m_string;
}


const std::string&
bstd::json::json::
to_string() const {
  return m_string;
}


json&
bstd::json::json::
operator[](const size_t index) {
  return m_children[index];
}


const json&
bstd::json::json::
operator[](const size_t _index) const {
  return m_children[_index];
}


json&
bstd::json::json::
operator[](const json& _key) {
  const auto& vit = std::find(m_children.begin(), m_children.end(), _key);

  // TODO: test what happens when *vit is end.
  return *vit;
}


const json&
bstd::json::json::
operator[](const json& _key) const {
  const auto& cvit = std::find(m_children.cbegin(), m_children.cend(), _key);

  // TODO: test what happens when *cvit is end.
  return *cvit;
}


json&
bstd::json::json::
at(const size_t _index) {
  return m_children.at(_index);
}


const json&
bstd::json::json::
at(const size_t _index) const {
  return m_children.at(_index);
}


json&
bstd::json::json::
at(const json& _key) {
  const auto& vit = std::find(m_children.begin(), m_children.end(), _key);

  if(vit == m_children.cend())
    throw std::out_of_range("Cannot get json " + _key);

  return *vit;
}


const json&
bstd::json::json::
at(const json& _key) const {
  const auto cvit = std::find(m_children.cbegin(), m_children.cend(), _key);

  if(cvit == m_children.cend())
    throw std::out_of_range("Cannot get json " + _key);

  return *cvit;
}


const bool
bstd::json::json::
operator==(const json& _rhs) const {
  return this->get_path() == _rhs.get_path()
    or this->get_string() == _rhs.to_string();
}


// TODO: add max size check.
const std::string
bstd::json::json::
operator+(const char* _rhs) const {
  return *this + std::string(_rhs);
}


// TODO: add max size check.
const std::string
bstd::json::json::
operator+(const std::string& _rhs) const {
  return this->to_string() + _rhs;
}


// TODO: add max size check.
const json
bstd::json::json::
operator+(const json& _rhs) {
  json result(*this);
  result.add_child(_rhs);
  result.set_string(result.get_string() + _rhs.get_string());
  return result;
}


void
bstd::json::json::
parse() {
  if(m_debug)
    std::cout << "bstd::json::parse" << std::endl;

  // TODO: Use the results of the parser.
  // TODO: Think about how we want this to work.
  const auto p = new parser(m_debug);
  p->parse(m_string);
}


// TODO: add max size check.
void
bstd::json::json::
add_child(const json& _child) {
  m_children.push_back(_child);
}


void
bstd::json::json::
write() const {
  write(m_path);
}


void
bstd::json::json::
write(const std::string& _path) const {
  if(m_debug)
    std::cout << "bstd::json::write" << std::endl;

  // No need to crash here, we can just do nothing. Log a warning instead.
  if(_path.empty()) {
    std::cerr << "Attempting to write json object to empty path." << std::endl;
    return;
  }

  // TODO: check file size before or after writing.
  std::ofstream ofs(_path, std::ofstream::trunc);

  if(!ofs.is_open())
    throw bstd::error::error("Couldn't open json file for writing: " + _path +
        ". Does it exist?", "json::write");

  ofs << m_string;
}


void
bstd::json::json::
set_string(const std::string& _string) {
  m_string = _string;
}
