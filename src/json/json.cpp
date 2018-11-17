#include "json.hpp"

namespace bstd::json {

json::
json(const std::string& _string, const bool _debug) : json(_debug) {
  auto json_string = _string;

  try {
    // Try to open string as a path.
    auto ifs = json_base::open_json_file(_string, std::fstream::in);

    json_string = std::string((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());
  }
  catch(bstd::error::error& _e) {
    if(m_debug)
      std::cout <<
        "Couldn't open _string as file. Attempting to parse as a JSON string."
        << std::endl;
  }

  parse(json_string);
}


json&
json::
operator=(json _rhs) {
  std::swap(m_path, _rhs.m_path);
  std::swap(m_values, _rhs.m_values);

  return *this;
}


const std::size_t
json::
size() const {
  return m_values.size();
}


const std::vector<std::shared_ptr<value>>&
json::
get_values() const {
  return m_values;
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

  // TODO: handle whitespace and newlines.
  for(const auto& value : m_values)
    result += value->to_string();

  return result;
}


bool
json::
operator==(const json& _rhs) const {
  if(size() != _rhs.size())
    return false;

  // Using sorted value vectors we can ensure that each child will be in the
  // same position as its equivalent in _rhs' value vector. If this fails
  // then the json objects aren't equal.
  auto this_values_copy = m_values,
        rhs_values_copy = _rhs.m_values;

  std::sort(this_values_copy.begin(), this_values_copy.end());
  std::sort(rhs_values_copy.begin(), rhs_values_copy.end());

  return this_values_copy == rhs_values_copy;
}


bool
json::
operator!=(const json& _rhs) const {
  return !(*this == _rhs);
}


json&
json::
operator+=(const json& _rhs) {
  add_values(_rhs.m_values);
  return *this;
}


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


void
json::
add_value(const std::shared_ptr<value>& _value) {
  m_values.push_back(_value);
}


void
json::
add_values(const std::vector<std::shared_ptr<value>>& _values) {
  m_values.insert(m_values.end(), _values.begin(),
      _values.end());
}


void
json::
write() const {
  write(m_path);
}


void
json::
write(const std::string& _path) const {
  auto ofs =
    json_base::open_json_file(_path, std::fstream::out | std::fstream::trunc);

  // TODO: handle whitespace and newlines.
  for(const auto& value : m_values)
    ofs << value->to_string();
}


}
