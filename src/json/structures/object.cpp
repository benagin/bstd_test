#include "object.hpp"

namespace bstd::json {


const std::size_t
object::
size() const {
  return m_values.size();
}


value&
object::
operator[](const std::string& _string) {
  return *m_values[_string];
}


value&
object::
operator[](const std::string&& _string) {
  return *m_values[_string];
}


value&
object::
at(const std::string& _string) {
  return *m_values.at(_string);
}


const value&
object::
at(const std::string& _string) const {
  return *m_values.at(_string);
}


bool
object::
operator==(const object& _rhs) {

  // TODO: implement.
  return true;
}


object&
object::
operator+=(const object& _rhs) {
  // TODO: implement.
  return *this;
}


const std::string
object::
to_string() const {
  std::string result = "";

  for(const auto& value : m_values)
    result += value.second->to_string();

  return result;
}


void
object::
write(const std::string& _path) const {
  auto ofs =
    json_base::open_json_file(_path, std::fstream::out | std::fstream::trunc);

  // TODO: handle whitespace and newlines.
  for(const auto& value : m_values)
    ofs << value.second->to_string();
  // TODO: check file size before or after writing.
}


}
