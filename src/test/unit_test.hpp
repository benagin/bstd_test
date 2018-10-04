#ifndef UNIT_TEST_HPP
#define UNIT_TEST_HPP

#include <assert.h>
#include <iostream>

class unit_test {

  public:

    unit_test() {}

    unit_test(const bool _debug) : m_debug(_debug) {}

    ~unit_test() {}

    // Run all unit tests.
    void test() const;

  private:

    bool m_debug{false};

};

#endif
