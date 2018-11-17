#include "test_json.hpp"

BSTD_TEST_MAIN(test_json)


test_json::
test_json() {
  ADD_TEST(test_json::json_size);
  ADD_TEST(test_json::json_assignment_operator);
  ADD_TEST(test_json::json_equal_operator);
  ADD_TEST(test_json::json_addition_operator);
  ADD_TEST(test_json::json_string_addition);
}


const bstd::test::result
test_json::
json_size() const {
  const auto zero = m_empty_json.size();
  const auto one = m_one_value.size();

  return bstd::test::result(zero == 0 && one == 1, "json size failed");
}


const bstd::test::result
test_json::
json_assignment_operator() const {
  auto copy = m_json1;

  // Check member variables.
  const bool success = copy.get_path() == m_json1.get_path()
      && copy.get_values() == m_json1.get_values();

  return bstd::test::result(success, "json assignment failed");
}


const bstd::test::result
test_json::
json_equal_operator() const {
  const bool test1 = m_json1 == m_json1_copy;
  const bool test2 = m_json1 != m_json2;


  return bstd::test::result(test1 && test2,
      "json equal operator failed");
}


const bstd::test::result
test_json::
json_addition_operator() const {
  auto result = m_json1 + m_json2;

  return bstd::test::result(result.size() == 2 && result  == m_json1and2,
      "json addition operator failed");
}


const bstd::test::result
test_json::
json_string_addition() const {
  auto result = m_json1 + m_json_string2;

  return bstd::test::result(result.size() == 2 && result  == m_json1and2,
      "json string addition operator failed");
}
