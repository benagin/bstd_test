#ifndef BSTD_UNIT_TEST_HPP
#define BSTD_UNIT_TEST_HPP

#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <vector>

#include "result.hpp"

namespace bstd::unit_test {

/// \brief Store and run unit tests
///
/// Unit testing tool.
/// Stores a set of unit test functions.
/// Provides interface for executing and showing the results of these unit test
/// functions.
class unit_tester {

  public:

    /// Function signature for unit test functions.
    /// Note: Non-member functions are also allowed.
    /// ```
    /// const bstd::unit_test::result test_class::test_method() const {
    ///   ...
    ///   Testing code here.
    ///   ...
    ///
    ///   return result;
    /// }
    /// ```
    typedef std::function<const result(const unit_tester&)> test_function;

    /// Default constructor
    unit_tester() {}

    /// Default virtual destructor
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
        const result (Derived::*_method)() const);

    /// \brief Add a test function.
    /// \param _name the name of the test
    /// \param _function a function pointer to the test method
    /// \return `this` so the function can be chained
    unit_tester* add_test(const std::string& _name,
        const result (*_function)());

    /// Run each function added to this tester and write results to standard
    /// output.
    virtual void run() const final;

  private:

    std::vector<std::pair<std::string, test_function>> m_tests;
};


template <class Derived>
unit_tester*
unit_tester::
add_test(const std::string& _name, const result (Derived::*_method)() const) {
  static_assert(std::is_base_of<unit_tester, Derived>::value,
      "Derived must derive from bstd::unit_tester");

  // Convert to base class method.
  const test_function method =
      static_cast<const result (unit_tester::*)() const>(_method);

  m_tests.push_back(std::make_pair(_name, method));
  return this;
}

}

/// Create a test by adding it to the tool.
/// This allows the user to call ADD_TEST(test_class::test_method) instead of
/// add_test("name", &test_class::test_method);
#define ADD_TEST(name)   \
  add_test(#name, &name) \

#endif
