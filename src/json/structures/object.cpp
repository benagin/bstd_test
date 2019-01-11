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
operator==(const object& _rhs) const {

  // TODO: implement.
  return true;
}


bool
object::
operator!=(const object& _rhs) const {
  return !(*this == _rhs);
}


object&
object::
operator+=(const object& _rhs) {
  // TODO: implement.
  return *this;
}


const std::string
object::
to_string(const bool _include_ws) const {
  // TODO: use _include_ws.
  std::string result = "";

  for(const auto& value : m_values)
    result += value.second->to_string(_include_ws);

  return result;
}


const std::shared_ptr<value>&
object::
add_value(const std::shared_ptr<value>& _value) {
  if(!_value)
    throw bstd::error::error("bstd::json::object",
        "Attempting to add null value to json object with name " +
        this->get_name());

  m_values.insert(std::make_pair(_value->get_name(), _value));
  return _value;
}


}
