#ifndef CLI_HPP_
#define CLI_HPP_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../parser/parser.hpp"

// Handles the command line interface (CLI) of the json parser.
class cli {

  public:

    cli() {}

    ~cli() {}

    // Handle the valid arguments.
    void handle_arguments(int _argc, char** _argv);

    // Run the parser with a path to a json file.
    void run_parser(const std::string& _path) const;

    void print_help() const;

    void print_usage() const;

  private:

    // Default path to documentation files.
    const std::string DEFAULT_USAGE_PATH{"../../doc/json/usage.txt"};
    const std::string DEFAULT_HELP_PATH{"../../doc/json/help.txt"};

    // Should we print debug information?
    bool m_debug{false};

    // Should we run tests?
    bool m_test{false};

};

#endif
