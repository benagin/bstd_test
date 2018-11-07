#include "unit_test.hpp"


namespace bstd::test {


unit_test&
unit_test::
add_test(const std::string& _name, const std::function<const result()>& _test) {
  m_tests.insert(std::pair<std::string, std::function<const result()>>(_name,
        _test));
  return *this;
}


void
unit_test::
test() const {
  int passed = 0;

  for(const auto& [name, test] : m_tests) {
    const auto& result = test();

    std::cout << name;

    if(result.first) {
      ++passed;
      std::cout << " passed." << std::endl;
    }
    else
      std::cout << " failed: " << result.second << std::endl;
  }

  const auto& total = m_tests.size();
  if(passed == total)
    std::cout << "All tests passed!" << std::endl;
  else {
    const double ratio = ((double) passed / (double) total) * 100;
    const int percent = ratio;

    std::stringstream output;
    output << percent << "% (" << passed << "/" << total << ") of tests passed.";
    std::cout << output.str() << std::endl;
  }
}


}
