#include <bstd_json.hpp>

int main() {
  const auto j = bstd::json::parse("");

  std::cout << *j << std::endl;

  const auto o = bstd::json::parse("{ \"test\": \"test\" }");

  std::cout << *o << std::endl;

  const auto o2 = bstd::json::parse("    a");

}
