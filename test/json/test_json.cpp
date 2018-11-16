#include "test_json.hpp"

BSTD_TEST_MAIN(test_json)


test_json::
test_json() {
  ADD_TEST(test_json::test1);
}


const bstd::test::result
test_json::
test1() const {
  return bstd::test::result(true, "");
}
