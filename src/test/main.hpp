#ifndef MAIN_HPP_
#define MAIN_HPP_

// This allows test classes to define a main function that runs the class.
// Usage:
// BSTD_TEST_MAIN(class);

#define BSTD_TEST_MAIN(class) \
int \
main() { \
  const auto test_class = new class(); \
  test_class->test(); \
  delete test_class; \
}

#endif
