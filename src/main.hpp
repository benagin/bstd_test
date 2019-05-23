#ifndef BSTD_UNIT_TEST_MAIN_HPP_
#define BSTD_UNIT_TEST_MAIN_HPP_

/// This includes a main function which runs the tests in the class provided as
/// an argument.
#define BSTD_UNIT_TEST_MAIN(unit_tester) \
  int                                    \
  main() {                               \
    const test_class test;               \
    test.run();                          \
  }

#endif
