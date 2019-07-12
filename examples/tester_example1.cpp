#include "tester_example1.hpp"

BSTD_TEST_MAIN(tester_example1)


tester_example1::
tester_example1() {
  ADD_TEST(tester_example1::test1);
  ADD_TEST(tester_example1::test2);
  ADD_TEST(tester_example1::test2);
}


void
tester_example1::
test1() {

  // Write test here.

  // Basic verification.
  VERIFY(m_test_data_string == "test", "good verification");
  VERIFY(m_test_data_string == "wrong", "bad verification");
}


void
tester_example1::
test2() {

  VERIFY(m_test_data_int == 55, "good verification");
  VERIFY(m_test_data_int == 25, "bad verification");
}

void
tester_example1::
test3() {

  const int the_result_of_some_function = rand();

  VERIFY(the_result_of_some_function == 42, "good verification");
}
