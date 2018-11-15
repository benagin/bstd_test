#include "test_json1.hpp"

BSTD_TEST_MAIN(test_json1)


test_json1::
test_json1() {
  ADD_TEST(test_json1::test1);
}


const bstd::test::result
test_json1::
test1() const {
  return bstd::test::result(true, "");
}
