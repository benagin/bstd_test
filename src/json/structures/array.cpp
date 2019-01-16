#include "array.hpp"

namespace bstd::json {


const std::size_t
array::
size() const {
  return m_values.size();
}


bool
array::
operator==(const array& _rhs) const {
  // TODO: implement.
  return true;
}


bool
array::
operator!=(const array& _rhs) const {
  return !(*this == _rhs);
}


array&
array::
operator+=(const array& _rhs) {
  // TODO: implement.
  return *this;
}


const std::string
array::
to_string(const bool _include_ws) const {
  std::string result = value::to_string(_include_ws);

  if(_include_ws)
    result += m_value_ws.first;

  result += "[";

  // The array is either empty and might have whitepsace or it contains some
  // members.
  if(m_values.empty() and _include_ws)
    result += m_ws;
  else
    for(const auto& value : m_values)
      result += value->to_string(_include_ws) + ',';

  result += "]";

  if(_include_ws)
    result += m_value_ws.first;

  return result;
}


const std::shared_ptr<value>&
array::
add_value(const std::shared_ptr<value>& _value) {
  m_values.push_back(_value);
  return _value;
}


}
