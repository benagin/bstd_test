#include "object.hpp"

namespace bstd::json {


value&
object::
operator[](const std::string& _string) {
  return m_values[_string];
}


value&
object::
operator[](const std::string&& _string) {
  return m_values[_string];
}


value&
object::
at(const std::string& _string) {
  return m_values.at(_string);
}


const value&
object::
at(const std::string& _string) const {
  return m_values.at(_string);
}


}
