#include <bstd_json.hpp>

int main() {
  const auto j = new bstd::json::json("");

  std::cout << *j << std::endl;

  delete j;

  const auto o = new bstd::json::object("{ \"test\": \"test\" }");

  std::cout << *o << std::endl;

  delete o;
}
