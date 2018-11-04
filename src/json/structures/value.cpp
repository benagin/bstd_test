#include "value.hpp"

namespace bstd::json {


value::
~value() {}


const std::string&
value::
get_name() const {
  return m_name;
}


}
