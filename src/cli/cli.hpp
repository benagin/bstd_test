#ifndef CLI_HPP_
#define CLI_HPP_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../json_parser.hpp"
#include "../test/unit_test.hpp"

// Handles the command line interface (CLI) of the json parser.
class cli {

  public:

    cli() {}

    ~cli() {}

    // Handle the valid arguments.
    void handle_arguments(int _argc, char** _argv);

    // Run the parser with a path to a json file.
    void run_parser(const std::string& _argc) const;

    // Print the usage statement to help the user know how to run this program.
    void print_usage() const;

  private:

    // Default path to config file. This file contains the usage string.
    const std::string DEFAULT_CONFIG_PATH{"config/usage.txt"};

    // Should we print debug information?
    bool m_debug{false};

    // Should we run tests?
    bool m_test{false};

};

#endif
