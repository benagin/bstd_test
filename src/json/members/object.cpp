#include "object.hpp"

namespace bstd::json {


const size_t
object::
size() const {
  return m_values.size();
}


member&
object::
operator[](const std::string& _string) {
  return m_values[_string];
}


member&
object::
operator[](const std::string&& _string) {
  return m_values[_string];
}


member&
object::
at(const std::string& _string) {
  return m_values.at(_string);
}


const member&
object::
at(const std::string& _string) const {
  return m_values.at(_string);
}


}
