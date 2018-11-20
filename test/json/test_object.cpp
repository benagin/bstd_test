#include "test_object.hpp"

BSTD_TEST_MAIN(test_object)


test_object::
test_object() {
  ADD_TEST(test_object::object_equal_operator);
  ADD_TEST(test_object::object_plus_equal_operator);
  ADD_TEST(test_object::object_string_addition);
}



const bstd::test::result
test_object::
object_equal_operator() const {
  const bool test1 = m_object1 == m_object1_copy;
  const bool test2 = m_object1 != m_object2;


  return bstd::test::result(test1 && test2,
      "object equal operator failed");
}


const bstd::test::result
test_object::
object_plus_equal_operator() const {
  return bstd::test::result(false,
      "object plus-equal operator failed");
}


const bstd::test::result
test_object::
object_string_addition() const {
  return bstd::test::result(false,
      "object string addition operator failed");
}
