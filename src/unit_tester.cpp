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
    m_test_report << name << std::endl;
    // TODO: is this a memory leak?
    m_current_test = &test;
    test.run(*this);

    if(test.get_total_tasks() == 0) {
      m_test_report << m_green<< "\tNo tasks were found in this test"
          << m_clear_color << std::endl;
    }

    if(test.all_tasks_passed())
      ++tests_passed;
  }

  const auto& total_tests = m_tests.size();

  if(tests_passed == total_tests)
    m_test_report << m_green << "All (" << total_tests << ") tests passed!";
  else {
    const double ratio = ((double) tests_passed/ (double) total_tests) * 100;
    const int percent = ratio;

    m_test_report << m_red;
    m_test_report << percent << "% (" << tests_passed << "/" << total_tests
        << ") of tests passed.";
  }

  std::cout << std::endl << m_test_report.str() << m_clear_color << std::endl;
}


}
