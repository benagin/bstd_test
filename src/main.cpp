#include "cli/cli.hpp"
#include "error/json_parse_error.hpp"

int main(int argc, char **argv) {
  auto* c = new cli();

  if(argc > 1) {
    try {
      c->handle_arguments(argc, argv);
    }
    catch(json_parse_error _jpe) {
      std::cerr << "JSON parse error: " << _jpe.what() << std::endl;
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
