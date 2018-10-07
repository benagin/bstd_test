#include "json.hpp"

std::ostream&
operator<<(std::ostream& _os, const json& _json) {
  return _os << _json.get_string();
}

void
json::
write() const {
  if(m_debug)
    std::cout << "json::write" << std::endl;

  std::ofstream ofs(m_path, std::ofstream::trunc);

  if(!ofs.is_open())
    throw error("Couldn't open json file for writing.", "json::write");
}
