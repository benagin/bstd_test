#ifndef BSTD_TEST_HPP
#define BSTD_TEST_HPP

#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <vector>

#include "result.hpp"

namespace bstd::test {

// Testing tool.
// Stores a set of test functions. Provides interface for executing and showing
// the results of thes test functions.
// For usage see bstd/doc/test/usage.txt.
class test {

  public:

    // Function signature for unit test functions.
    // Note: Non-member functions are also allowed.
    // const bstd::test::result test_class::test_method() const {
    //   ...
    //   Testing code here.
    //   ...
    //
    //   return result;
    // }
    typedef std::function<const result(const test&)> test_function;

    test() {}

    virtual ~test() {}

    // Returns this so that this function can be chained.
    template <class Derived>
    test* add_test(const std::string& _name,
        const result (Derived::*_method)() const);
    test* add_test(const std::string& _name,
        const result (*_function)());

    // Run each function in m_tests and write results to standard output.
    virtual void run() const final;

  private:

    std::vector<std::pair<std::string, test_function>> m_tests;

};


template <class Derived>
test*
test::
add_test(const std::string& _name, const result (Derived::*_method)() const) {
  static_assert(std::is_base_of<test, Derived>::value,
      "Derived must derive from bstd::test");

  // Convert to base class method.
  const test_function method =
      static_cast<const result (test::*)() const>(_method);

  m_tests.push_back(std::make_pair(_name, method));
  return this;
}

}

// Create a test by adding it to the tool.
// This allows the user to call ADD_TEST(test_class::test_method) instead of
// add_test("name", &test_class::test_method);
#define ADD_TEST(name) \
  add_test(#name, &name) \

#endif
