#include <stdexcept>

#include <bstd_error.hpp>

#include "cli/cli.hpp"

using namespace bstd::json;

int main(int argc, char **argv) {
  auto* c = new cli();

  if(argc > 1) {
    try {
      c->handle_arguments(argc, argv);
    }
    catch(const bstd::error::context_error& _ce) {
      std::cerr << "JSON parse error: " << _ce.what() << std::endl;
    }
    catch(const bstd::error::error& _e) {
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
