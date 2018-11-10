#include "test_json1.hpp"

const bstd::test::result
test_json1::
test1() const {
  return bstd::test::result(true, "");
}

test_json1::
test_json1() {
  ADD_TEST(test_json1::test1);
}

BSTD_TEST_MAIN(test_json1);
