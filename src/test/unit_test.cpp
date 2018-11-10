#include "unit_test.hpp"


namespace bstd::test {


unit_test&
unit_test::
add_test(const std::string& _name, test_function _test) {
  m_tests.insert(std::pair<std::string, test_function>(_name,
        _test));
  return *this;
}


void
unit_test::
test() {
  std::size_t passed = 0;

  for(const auto& [name, test] : m_tests) {
    const auto result = (this->*test)();

    std::cout << name;

    if(result.first) {
      ++passed;
      std::cout << " passed." << std::endl;
    }
    else
      std::cout << " failed: " << result.second << std::endl;
  }

  const auto& total = m_tests.size();
  std::stringstream output;

  if(passed == total)
    output << "All (" << total << ") tests passed!";
  else {
    const double ratio = ((double) passed / (double) total) * 100;
    const int percent = ratio;

    output << percent << "% (" << passed << "/" << total << ") of tests passed.";
  }

  std::cout << output.str() << std::endl;
}


}
