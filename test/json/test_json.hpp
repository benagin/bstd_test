#ifndef TEST_JSON_HPP_
#define TEST_JSON_HPP_

#include <bstd_json.hpp>

#include <bstd_test.hpp>

class test_json final : public bstd::test::test {

  public:

    test_json();

    ~test_json() {}

    const bstd::test::result test1() const;

};


#endif
