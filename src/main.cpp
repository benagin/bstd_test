#include "cli/cli.hpp"

int main(int argc, char **argv) {
  auto* c = new cli();

  if(argc > 1)
    c->handle_arguments(argc, argv);
  else
    c->print_usage();

  delete c;
}
