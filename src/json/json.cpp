#include "json.hpp"

namespace bstd::json {

json::
json(const std::string& _string, const bool _debug) : m_debug(_debug) {
  if(m_debug)
    std::cout << "bstd::json" << std::endl;

  constexpr std::string_view dot_json{".json"};
  const auto extension =
    _string.substr(_string.size() - dot_json.length());

  auto json_string = _string;

  // Check if we have a JSON string or path.
  if(extension == dot_json) {
    // Try to open string as a path.

    // TODO: implement file size check.
    std::ifstream ifs(_string);

    if(!ifs.is_open())
      throw bstd::error::error("bstd::json(string, bool)",
          "Couldn't open json file at path: " + _string + ". Does it exist?");

    std::stringstream stream;
    stream << ifs.rdbuf();
    json_string = stream.str();
  }

  if(m_debug)
    std::cout << "Parsing json string: " << std::endl << json_string << std::endl;

  // Limit the size of JSON strings.
  if(json_string.size() > MAX_STRING_SIZE) {
    std::stringstream ss;
    ss << MAX_STRING_SIZE;
    throw error::error("btsd::json",
        "The JSON object is too large. The current maximum string size is "
        + ss.str());
  }

  parse(_string);
}


json&
json::
operator=(json _rhs) {
  std::swap(m_path, _rhs.m_path);
  std::swap(m_children, _rhs.m_children);

  return *this;
}


const size_t
json::
size() const {
  return m_children.size();
}


const std::vector<json*>&
json::
get_children() const {
  return m_children;
}


const std::string&
json::
get_path() const {
  return m_path;
}


const std::string
json::
to_string() const {
  std::string result = "";

  for(auto child : m_children)
    result += child->to_string();

  return result;
}


bool
json::
operator==(const json& _rhs) {
  if(size() != _rhs.size())
    return false;

  // Using sorted children vectors we can ensure that each child will be in the
  // same position as its equivalent in _rhs's children vector. If this fails
  // then the json objects aren't equal.
  auto this_children_copy = m_children,
        rhs_children_copy = _rhs.m_children;

  std::sort(this_children_copy.begin(), this_children_copy.end());
  std::sort(rhs_children_copy.begin(), rhs_children_copy.end());

  return this_children_copy == rhs_children_copy;
}


json&
json::
operator+=(const json& _rhs) {
  add_children(_rhs.get_children());
  return *this;
}


// TODO: add max size check.
json
operator+(json _lhs, const json& _rhs) {
  _lhs += _rhs;
  return _lhs;
}


std::ostream&
operator<<(std::ostream& _os, const json& _json) {
  return _os << _json.to_string();
}


void
json::
parse(const std::string& _string) {
  if(m_debug)
    std::cout << "bstd::json::parse" << std::endl;

  const auto p = new parser(m_debug);
  p->parse(_string, this);
  delete p;
}


// TODO: add max size check.
void
json::
add_children(const std::vector<json*>& _children) {
  m_children.insert(m_children.cend(), _children.cbegin(),
      _children.cend());
}


// TODO: add max size check.
void
json::
add_child(json* _child) {
  m_children.push_back(_child);
}


void
json::
write() const {
  write(m_path);
}


void
json::
write(const std::string& _path) const {
  if(m_debug)
    std::cout << "bstd::json::write" << std::endl;

  // No need to crash here, we can just do nothing. Log a warning instead.
  if(_path.empty()) {
    std::cerr << "Attempting to write json object to empty path." << std::endl;
    return;
  }

  std::ofstream ofs(_path, std::ofstream::trunc);

  if(!ofs.is_open())
    throw bstd::error::error("Couldn't open json file for writing: " + _path +
        ". Does it exist?", "json::write");

  for(auto child : m_children)
    ofs << child;
  // TODO: check file size before or after writing.
}


}
