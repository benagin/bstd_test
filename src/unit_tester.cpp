#include "unit_tester.hpp"


namespace bstd::unit_test {


unit_tester*
unit_tester::
add_test(const std::string& _name, const result (*_function)()) {
  m_tests.push_back(std::make_pair(_name, std::bind(_function)));
  return this;
}


void
unit_tester::
run() const {
  std::size_t passed = 0;

  constexpr std::string_view clear_color {"\x1b[0m"};
  constexpr std::string_view green{"\x1b[32m"};
  constexpr std::string_view red{"\x1b[31m"};

  for(const auto& [name, test] : m_tests) {
    const auto result = test(*this);

    if(result.first) {
      ++passed;
      std::cout << name << " passed" << std::endl;
    }
    else {
      const auto reason = !result.second.empty() ? result.second :
          "No reason given.";
      std::cout << red << name << " failed" << clear_color << ": "
        << reason << std::endl;
    }
  }

  std::stringstream output;
  const auto& total = m_tests.size();

  if(passed == total)
    output << green << "All (" << total << ") tests passed!";
  else {
    const double ratio = ((double) passed / (double) total) * 100;
    const int percent = ratio;

    output << red;
    output << percent << "% (" << passed << "/" << total << ") of tests passed.";
  }

  std::cout << output.str() << clear_color << std::endl;
}


}
