#include "cli.hpp"

namespace bstd::json {


void
cli::
handle_arguments(int _argc, char** _argv) {
    // TODO: Use json parser to load supported arguments at runtime.
    std::vector<std::string> arguments;
    std::string path = "";

    // Convert arguments to strings.
    for(auto i = 1; i < _argc; ++i) {
      arguments.push_back(std::string(_argv[i]));

      std::string arg(_argv[i]);

      if(arg == "-d" or arg == "--debug") {
        m_debug = true;
        std::cout << "Debug mode: " << std::boolalpha << m_debug << std::endl;
      }
      else if(arg == "-v" or arg == "--verbose") {
        m_debug = true;
        std::cout << "Debug mode: " << std::boolalpha << m_debug << std::endl;
      }
      else if(arg == "-t" or arg == "--test") {
        m_test = true;
      }
      else if(arg == "help" or arg == "--help") {
        // If we see the help command show usage and stop.
        print_help();
        return;
      }
      else if(arg.front() != '-' and !arg.empty()){
        path = arg;
      }
      else
        throw bstd::error::error("Unknown CLI argument: " + arg,
            "bstd::json::cli::handle_arguments");
    }

    // We have a json file to parse.
    if(!path.empty())
      build_json(path);

    if(m_test) {
      if(m_debug)
        std::cout << "Running tests..." << std::endl;

      // TODO: Start unit tests.
    }
}

void
cli::
build_json(const std::string& _path) const {
  const auto j = new json(_path, m_debug);

  if(m_debug)
    std::cout << "Parsed json: " << std::endl << *j << std::endl;

  delete j;
}

void
cli::
print_help() const {
  const std::ifstream ifs(DEFAULT_HELP_PATH);

  if(!ifs.is_open()) {
    throw bstd::error::error("Couldn't open help file at " + DEFAULT_HELP_PATH +
        ". Does the file exist?", "bstd::json::cli::print_help");

    return;
  }

  std::stringstream stream;
  stream << ifs.rdbuf();
  std::cout << stream.str() << std::endl;

  print_usage();
}

void
cli::
print_usage() const {
  const std::ifstream ifs(DEFAULT_USAGE_PATH);

  if(!ifs.is_open()) {
    throw bstd::error::error("Couldn't open usage file at " + DEFAULT_USAGE_PATH +
        ". Does the file exist?", "bstd::json::cli::print_usage");

    return;
  }

  std::stringstream stream;
  stream << ifs.rdbuf();
  std::cout << stream.str() << std::endl;
}


}
