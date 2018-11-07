#ifndef UNIT_TEST_HPP
#define UNIT_TEST_HPP

#include <functional>
#include <string>
#include <vector>

#include "result.hpp"

namespace bstd::test {

// Unit testing tool.
// For usage see bstd/doc/test/usage.txt
class unit_test {

  public:

    unit_test() {}

    ~unit_test() {}

    // Returns *this so that this function can be chained.
    // Note: test() can be called as a part of this chain.
    // Example:
    //  auto test = new uni_test();
    //  test.add_test(foo).add_test(bar).add_test(foo_bar).test();
    virtual unit_test& add_test(const std::function<const result()>& _test) final;

    virtual void test() const final;

  private:

    // The set of test functions.
    // These are functions that return a const bool and take no arguments.
    std::vector<std::function<const result()>> m_test;

};

}

#endif
