#include "json_base.hpp"


namespace bstd::json {


json_base::
~json_base() {}


std::ostream&
operator<<(std::ostream& _os, const json_base& _json_base) {
  return _os << _json_base.to_string();
}


void
json_base::
write(const std::string _path, const bool _include_ws) const {
  auto ofs =
    open_json_file(_path, std::fstream::out | std::fstream::trunc);

    ofs << to_string(_include_ws);
}


std::fstream
json_base::
open_json_file(const std::string& _path, std::ios_base::openmode _mode) const {
  if(!is_json_extension(_path))
    throw bstd::error::error("json_base::open_json_file",
        "Couldn't open json file: " + _path + ". The extension is not '.json'");

  std::fstream fstream(_path, _mode);

  if(!fstream.is_open())
    throw bstd::error::error("json_base::open_json_file",
        "Couldn't open json file for writing: " + _path + ". Does it exist?");

  return fstream;
}


const bool
json_base::
is_json_extension(const std::string& _path) const {
  constexpr std::string_view dot_json{".json"};
  const auto extension =
    _path.substr(_path.size() - dot_json.length());

  return extension == dot_json;
}


}
