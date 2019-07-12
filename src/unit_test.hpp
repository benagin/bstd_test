#ifndef BSTD_TEST_UNIT_TEST_HPP
#define BSTD_TEST_UNIT_TEST_HPP

#include <functional>


namespace bstd::test {

class unit_tester;

/// \brief This represents one unit test within a test class.
/// This allows us to keep track of the total verification (or other) tasks
/// within the test and how many have passed.
class unit_test final {

  public:

    typedef std::function<void(unit_tester&)> test_function;

    /// \brief Construct a unit test.
    /// \param the unit test function/method
    unit_test(const test_function& _function) : m_function(_function) {}

    /// \brief Default destructor.
    ~unit_test() {}

    /// \brief Increment the count for passed and total tasks.
    void task_pass();

    /// \brief Increment the count for total tasks.
    void task_fail();

    /// \brief Did all verification tasks within this test pass?
    /// \return true if all tasks have passed; false otherwise
    const bool all_tasks_passed() const;

    /// \brief Run the test.
    /// \param _unit_tester an instance of \ref unit_tester
    void run(unit_tester& _unit_tester);

  private:

    /// Total count of verification (or other) tasks within this test.
    std::size_t m_total{0};

    std::size_t m_passed{0};

    test_function m_function{nullptr};

};

}

#endif
