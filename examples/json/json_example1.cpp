#include <bstd_json.hpp>

int main() {
  const auto j = new json("");

  std::cout << *j << std::endl;

  delete j;
}
