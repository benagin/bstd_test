#include "cli/cli.hpp"
#include "error/error.hpp"
#include "error/context_error.hpp"

int main(int argc, char **argv) {
  auto* c = new cli();

  if(argc > 1) {
    try {
      c->handle_arguments(argc, argv);
    }
    catch(context_error _ce) {
      std::cerr << "JSON parse error: " << _ce.what() << std::endl;
    }
    catch(error _e) {
      std::cerr << "Error: " << _e.what() << std::endl;
    }
    catch(...) {
      std::cerr << "Something went wrong." << std::endl;
    }
  }
  else
    c->print_usage();

  delete c;
}
