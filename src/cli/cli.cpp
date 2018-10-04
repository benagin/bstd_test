#include "cli.hpp"

void cli::handle_arguments(int _argc, char** _argv) {
    std::vector<std::string> arguments;

    // Convert arguments to strings.
    for(auto i = 1; i < _argc; ++i) {
      arguments.push_back(std::string(_argv[i]));

      std::string arg(_argv[i]);

      m_debug = arg == "-d" or arg == "--debug";
      m_test = arg == "-t" or arg == "--test";
    }

    if(m_debug) {
      std::cout << "Debug mode: " << std::boolalpha << m_debug << std::endl;
      std::cout << "Run tests: " << m_test << std::endl;
    }

    if(m_test) {
      const auto& ut = new unit_test(m_debug);
      ut->test();
    }
}

void cli::print_usage() const {
  const std::ifstream ifs(DEFAULT_CONFIG_PATH);

  if(!ifs.is_open())
    std::cerr << "Couldn't open usage config file at " + DEFAULT_CONFIG_PATH
      << std::endl << "Does the file exist?" << std::endl;

  std::stringstream stream;
  stream << ifs.rdbuf();
  std::cout << stream.str() << std::endl;
}
