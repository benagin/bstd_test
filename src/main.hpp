#ifndef BSTD_TEST_MAIN_HPP_
#define BSTD_TEST_MAIN_HPP_

/// This includes a main function which runs the tests in the class provided as
/// an argument.
/// Note: do not include this define within a namespace.
#define BSTD_TEST_MAIN(unit_tester) \
  int                               \
  main() {                          \
    unit_tester tester;             \
    tester.run();                   \
    return 0;                       \
  }                                 \

#endif
