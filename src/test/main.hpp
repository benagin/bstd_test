#ifndef BSTD_TEST_MAIN_HPP_
#define BSTD_TEST_MAIN_HPP_

// This includes a main function which runs the tests in the class provided as
// an argument.
#define BSTD_TEST_MAIN(test_class_name) \
  int \
  main() { \
    const test_class_name test; \
    test.run(); \
  }

#endif
