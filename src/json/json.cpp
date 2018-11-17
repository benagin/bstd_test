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
  std::swap(m_value, _rhs.m_value);

  return *this;
}


const std::size_t
json::
size() const {
  return m_value->size();
}


const std::string&
json::
get_path() const {
  return m_path;
}


void
json::
set_path(const std::string& _path) {
  m_path = _path;
}


const std::shared_ptr<value>&
json::
get_value() const {
  return m_value;
}


void
json::
set_value(const std::shared_ptr<value>& _value) {
  m_value = _value;
}


const std::string
json::
to_string() const {
  return m_value->to_string();
}


bool
json::
operator==(const json& _rhs) const {
  if(size() != _rhs.size())
    return false;

  return m_value == _rhs.m_value;
}


bool
json::
operator!=(const json& _rhs) const {
  return !(*this == _rhs);
}


/*
json&
json::
operator+=(const json& _rhs) {
  add_values(_rhs.m_value);
  return *this;
}
*/


/*
json&
operator+(json _lhs, const json& _rhs) {
  _lhs += _rhs;
  return _lhs;
}
*/


void
json::
parse(const std::string& _string) {
  const auto p = new parser(m_debug);
  p->parse(_string, this);
  delete p;
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

  ofs << m_value->to_string();
}


}
