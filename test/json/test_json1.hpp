#ifndef TEST_JSON1_HPP_
#define TEST_JSON1_HPP_

#include <bstd_json.hpp>

#include <bstd_test.hpp>

class test_json1 final : public bstd::test::test {

  public:

    test_json1();

    ~test_json1() {}

    const bstd::test::result test1() const;

};


#endif
