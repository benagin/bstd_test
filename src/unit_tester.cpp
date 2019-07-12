#include "unit_tester.hpp"


namespace bstd::test {


unit_tester*
unit_tester::
add_test(const std::string& _name, void(*_function)()) {
  m_tests.insert(std::make_pair(_name, unit_test(std::bind(_function))));
  return this;
}


void
unit_tester::
run() {
  std::size_t tests_passed = 0;

  for(auto& [name, test] : m_tests) {
    std::cout << name << std::endl;
    // TODO: is this a memory leak?
    m_current_test = &test;
    test.run(*this);

    if(test.all_tasks_passed())
      ++tests_passed;
  }

  std::stringstream output;
  const auto& total_tests = m_tests.size();

  if(tests_passed == total_tests)
    output << m_green << "All (" << total_tests << ") tests passed!";
  else {
    const double ratio = ((double) tests_passed/ (double) total_tests) * 100;
    const int percent = ratio;

    output << m_red;
    output << percent << "% (" << tests_passed << "/" << total_tests
        << ") of tests passed.";
  }

  std::cout << std::endl << output.str() << m_clear_color << std::endl;
}


}
