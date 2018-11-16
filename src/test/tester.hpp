#ifndef BSTD_TEST_TESTER_HPP_
#define BSTD_TEST_TESTER_HPP_

#include "test.hpp"

// Helps run tests from different test classes.
class tester final {

  public:

    tester() {}

    ~tester() {}

    template <class Test>
    void run(Test* _test) const;

};

template <class Test>
void
tester::
run(Test* _test) const {

}

#endif
