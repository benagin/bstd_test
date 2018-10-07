#include "json.hpp"

std::ostream& operator<<(std::ostream& _os, const json& _json) {
  return _os << _json.get_string();
}

json::json(const std::string& _string, const bool _debug)
  : m_string(_string), m_debug(_debug) {
}
