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

    unit_test() {}

    ~unit_test() {}

    // Returns *this so that this function can be chained.
    // Note: test() can be called as a part of this chain.
    // Example:
    //  auto test = new uni_test();
    //  test.add_test("foo", foo).add_test("bar", bar
    //      .add_test("foo_bar", foo_bar).test();
    virtual unit_test& add_test(const std::string& _name,
        const std::function<const result()>& _test) final;

    // Run each function in m_tests and write results to standard output.
    virtual void test() const final;

  private:

    std::map<std::string, std::function<const result()>> m_tests;

};

}

#endif
