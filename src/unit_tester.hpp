#ifndef BSTD_TEST_UNIT_TESTER_HPP
#define BSTD_TEST_UNIT_TESTER_HPP

#include <iostream>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <sstream>

#include "unit_test.hpp"

namespace bstd::test {

/// \brief Store and run unit tests.
///
/// Unit testing tool.
/// Stores a set of unit test functions.
/// Executes provided unit tests and prints information about the results.
/// TODO: it might be possible to include this header via macro
class unit_tester {

  public:

    /// Function signature for unit test functions.
    /// Note: Non-member functions are also allowed.
    /// ```
    /// void test_class::test_method() {
    ///   ...
    ///   Testing code/verifications here.
    //
    //    VERIFY(x == y, "x and y values do not match");
    //    VERIFY(foo() == bar(), "foobar mismatch");
    ///   ...
    /// }
    /// ```
    typedef std::function<void(unit_tester&)> test_function;

    /// \brief Default constructor.
    unit_tester() {}

    /// \brief Default virtual destructor.
    virtual ~unit_tester() {}

    /// \brief Add a test method from a class that derives \ref unit_tester.
    /// Instead of this method the ADD_TEST(name), where `name` is the
    /// name of the method, macro can be used inside the Derived classes
    /// constructor. See example/test_examples1.cpp for an example.
    /// \param _name the name of the test
    /// \param _method a function pointer to the test method
    /// \return `this` so the function can be chained
    template <class Derived>
    unit_tester* add_test(const std::string& _name,
        void(Derived::*_method)());

    /// \brief Add a test function.
    /// \param _name the name of the test
    /// \param _function a function pointer to the test method
    /// \return `this` so the function can be chained
    unit_tester* add_test(const std::string& _name,
        void(*_function)());

    /// Run each function added to this tester and write results to standard
    /// output.
    virtual void run() final;

  protected:

    unit_test* m_current_test{nullptr};

    std::stringstream m_test_report{""};

    const std::string_view m_clear_color {"\x1b[0m"};
    const std::string_view m_green{"\x1b[32m"};
    const std::string_view m_red{"\x1b[31m"};

  private:

    std::map<std::string, unit_test> m_tests;

};


template <class Derived>
unit_tester*
unit_tester::
add_test(const std::string& _name, void(Derived::*_method)()) {
  static_assert(std::is_base_of<unit_tester, Derived>::value,
      "The test class must derive bstd::test::unit_tester");

  // Convert to base class method.
  const test_function method =
      static_cast<void(unit_tester::*)()>(_method);

  m_tests.insert(std::make_pair(_name, unit_test(method)));
  return this;
}

}

/// \brief Create a test by adding it to the tool.
/// This allows the user to call ADD_TEST(test_class::test_method) instead of
/// add_test("name", &test_class::test_method);
/// \param name the name of the method prefixed with the class name
///             (test_class::test_method)
#define ADD_TEST(name)   \
  add_test(#name, &name) \

/// \brief Verify a boolean expression.
/// This acts as a small scall test case within a test.
/// \param expression a boolean expression
/// \param name the name of the verification (string)
#define VERIFY(expression, name)                                      \
  if(expression) {                                                    \
    m_test_report << m_green << "\tVerify \'" << name << "\' passed"; \
    m_current_test->task_pass();                                      \
  }                                                                   \
  else {                                                              \
    m_test_report << m_red << "\tVerify \'" << name << "\' failed";   \
    m_current_test->task_fail();                                      \
  }                                                                   \
  m_test_report << m_clear_color << std::endl;                        \

// TODO: add different types of verification.

#endif
