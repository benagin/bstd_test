#include "cli.hpp"

void cli::handle_arguments(int _argc, char** _argv) {
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
      else if(arg == "-t" or arg == "--test") {
        m_test = true;
      }
      else if(arg == "help" or arg == "--help") {
        // If we see the help command show usage and stop.
        print_usage();
        return;
      }
      else if(!arg.empty()){
        path = arg;
      }
      else
        std::cerr << "Unknown CLI argument: " << arg << std::endl;
    }

    // We have a json file to parse.
    if(!path.empty())
      run_parser(path);

    if(m_test) {
      if(m_debug)
        std::cout << "Running tests..." << std::endl;

      const auto& ut = new unit_test(m_debug);
      ut->test();
      delete ut;
    }
}

void cli::run_parser(const std::string& _arg) const {
  const auto parser = new json_parser(_arg, m_debug);
  const auto json = parser->parse();

  if(m_debug)
    std::cout << "Parsed json: " << std::endl << *json << std::endl;

  delete parser;
  delete json;
}

void cli::print_usage() const {
  const std::ifstream ifs(DEFAULT_CONFIG_PATH);

  if(!ifs.is_open()) {
    std::cerr << "Couldn't open usage config file at " << DEFAULT_CONFIG_PATH
      << std::endl << "Does the file exist?" << std::endl;

    return;
  }

  std::stringstream stream;
  stream << ifs.rdbuf();
  std::cout << stream.str() << std::endl;
}
