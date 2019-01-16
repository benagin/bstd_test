#include "json_file_util.hpp"


namespace bstd::json::utilities {


std::fstream
open_json_file(const std::string& _path, std::ios_base::openmode _mode) {
  if(!is_json_extension(_path))
    throw bstd::error::error("bstd::json::utilities::open_json_file",
        "Couldn't open json file: " + _path + ". The extension is not '.json'");

  std::fstream fstream(_path, _mode);

  if(!fstream.is_open())
    throw bstd::error::error("bstd::json::utilities::open_json_file",
        "Couldn't open json file for writing: " + _path + ". Does it exist?");

  return fstream;
}

const bool
is_json_extension(const std::string_view& _path) {
  return _path.ends_with(".json");
}


}
