#include <algorithm>
#include <iostream>
#include <vector>

#include "json_parser.hpp"

int main(int argc, char **argv) {
  if(argc > 1) {
    std::vector<std::string> arguments;
    for(int i = 1; i < argc; ++i)
      arguments.push_back(std::string(argv[i]));

    const bool debug = std::find(arguments.cbegin(), arguments.cend(), "-d")
      != arguments.cend()
      || std::find(arguments.cbegin(), arguments.cend(), "--debug")
      != arguments.cend();

    if(debug)
      std::cout << "Debug: " << std::boolalpha << debug << std::endl;

    const bool test = std::find(arguments.cbegin(), arguments.cend(), "-t")
      != arguments.cend()
      || std::find(arguments.cbegin(), arguments.cend(), "--test")
      != arguments.cend();

    if(debug)
      std::cout << "Test: " << test << std::endl;

    if(test) {
      const auto parser = new json_parser(debug);
      parser->test();
    }
  }
  else
    std::cout << "Thanks for using JsonParser." << std::endl
      << "./jsonparse [-t] [-d]" << std::endl
      << "  -t, --test" << std::endl << "    Run tests." << std::endl
      << "  -d, --debug" << std::endl << "    Debug output." << std::endl;
}
