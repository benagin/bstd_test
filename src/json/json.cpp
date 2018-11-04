#include "json.hpp"

namespace bstd::json {

json::
json(const std::string& _string, const bool _debug) : json(_debug) {
  auto json_string = _string;

  // Check if we have a JSON string or path.
  if(check_extension(_string)) {
    // Try to open string as a path.

    // TODO: implement file size check.
    auto ifs = open_json_file(_string, std::fstream::in);

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


const std::size_t
json::
size() const {
  return m_children.size();
}


const std::vector<value*>&
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


void
json::
parse(const std::string& _string) {
  const auto p = new parser(m_debug);
  p->parse(_string, this);
  delete p;
}


// TODO: add max size check.
void
json::
add_children(const std::vector<value*>& _children) {
  m_children.insert(m_children.cend(), _children.cbegin(),
      _children.cend());
}


// TODO: add max size check.
void
json::
add_child(value* _child) {
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
  auto ofs = open_json_file(_path, std::fstream::out | std::fstream::trunc);

  // TODO: handle whitespace and newlines.
  for(const auto& child : m_children)
    ofs << child->to_string();
  // TODO: check file size before or after writing.
}


}
