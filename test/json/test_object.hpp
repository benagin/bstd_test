#ifndef TEST_OBJECT_HPP_
#define TEST_OBJECT_HPP_

#include <bstd_test.hpp>
#include <bstd_json.hpp>

class test_object final : public bstd::test::test {

  public:

    test_object();

    ~test_object() {}

    const bstd::test::result object_equal_operator() const;
    const bstd::test::result object_plus_equal_operator() const;
    const bstd::test::result object_string_addition() const;

  private:

    std::string m_object_string1{"{ \"name1\": \"value1\" }"};
    std::string m_object_string2{"{ \"name2\": \"value2\" }"};

    bstd::json::object m_empty_object{"{}"};
    bstd::json::object m_object1{m_object_string1};
    bstd::json::object m_object1_copy{m_object_string1};
    bstd::json::object m_object2{m_object_string2};
    bstd::json::object m_object1and2{m_object_string1 + m_object_string2};

};


#endif
