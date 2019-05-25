#ifndef TESTER_EXAMPLE1_HPP_
#define TESTER_EXAMPLE1_HPP_

#include <bstd_test.hpp>

/// \brief an example of a derived unit testing class
///
/// Here, we have unit tests as methods (test1, test2, etc.).
/// We also have data used between the tests stored as member variables.
class tester_example1 final : public bstd::test::unit_tester {

  public:

    /// Add test methods to the tester using the ADD_TEST(name) macro.
    tester_example1();

    ~tester_example1() {}

    const bstd::test::result test1() const;
    const bstd::test::result test2() const;

  private:

    int m_test_data_int{55};
    std::string m_test_data_string{"test"};

};


#endif
