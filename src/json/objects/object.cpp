#include "object.hpp"

namespace bstd::json {


const size_t
object::
size() const {
  return m_values.size();
}


json&
object::
operator[](const std::string& _string) {
  return m_values[_string];
}


json&
object::
operator[](const std::string&& _string) {
  return m_values[_string];
}


json&
object::
at(const std::string& _string) {
  return m_values.at(_string);
}


const json&
object::
at(const std::string& _string) const {
  return m_values.at(_string);
}


}
