#include "tester_example1.hpp"

BSTD_UNIT_TEST_MAIN(tester_example1)


tester_example1::
tester_example1() {
  ADD_TEST(tester_example1::test1);
  ADD_TEST(tester_example1::test2);
}


const bstd::unit_test::result
tester_example1::
test1() const {

  // Write test here.

  // This is a very basic example of a test.
  const bool success = m_test_data_string == "test";

  return bstd::unit_test::result(success, "test1 failed");
}


const bstd::unit_test::result
tester_example1::
test2() const {

  const bool success = m_test_data_int == 55;

  return bstd::unit_test::result(success, "test2 failed");
}
