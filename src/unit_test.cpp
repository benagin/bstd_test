#include "unit_test.hpp"


namespace bstd::test {


const std::size_t
unit_test::
get_total_tasks() const {
  return m_total;
}


void
unit_test::
task_pass() {
  ++m_passed;
  ++m_total;
}


void
unit_test::
task_fail() {
  ++m_total;
}


const bool
unit_test::
all_tasks_passed() const {
  return m_total == m_passed;
}


void
unit_test::
run(unit_tester& _unit_tester) {
  m_function(_unit_tester);
}


}
