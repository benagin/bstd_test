#include <stdexcept>

#include "cli/cli.hpp"
#include "error/error.hpp"
#include "error/context_error.hpp"

int main(int argc, char **argv) {
  auto* c = new bstd::cli();

  if(argc > 1) {
    try {
      c->handle_arguments(argc, argv);
    }
    catch(const bstd::context_error& _ce) {
      std::cerr << "JSON parse error: " << _ce.what() << std::endl;
    }
    catch(const bstd::error& _e) {
      std::cerr << "Error: " << _e.what() << std::endl;
    }
    catch(const std::exception& _e) {
      std::cerr << "Error: " << _e.what() << std::endl;
    }
  }
  else
    c->print_usage();

  delete c;
}
