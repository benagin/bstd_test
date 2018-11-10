#ifndef UNIT_TEST_HPP
#define UNIT_TEST_HPP

#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <map>

#include "result.hpp"

namespace bstd::test {

// Unit testing tool.
// For usage see bstd/doc/test/usage.txt.
class unit_test {

  public:

    // Function signature for unit test functions.
    // const bstd::test::result test_function() const {
    //   ...
    //   Testing code here.
    //   ...
    //
    //   return result;
    // }
    typedef const result (unit_test::*test_function)() const;

    unit_test() {}

    virtual ~unit_test() {}

    // Calls add_test(std::string, test_function).
    // Usage:
    //  ADD_TEST(test_class::test_function);
#define ADD_TEST(function) add_test(#function, static_cast<test_function>(&function))

    // Returns *this so that this function can be chained.
    // Note: test() can be called as a part of this chain.
    // Example:
    //  auto test = new uni_test();
    //  test.add_test("foo", foo).add_test("bar", bar
    //      .add_test("foo_bar", foo_bar).test();
    virtual unit_test& add_test(const std::string& _name,
        test_function _test) final;

    // Run each function in m_tests and write results to standard output.
    virtual void test() final;

  private:

    std::map<std::string, test_function> m_tests;

};


}

#endif
