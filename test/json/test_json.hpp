#ifndef TEST_JSON_HPP_
#define TEST_JSON_HPP_

#include <bstd_test.hpp>
#include <bstd_json.hpp>

class test_json final : public bstd::test::test {

  public:

    test_json();

    ~test_json() {}

    const bstd::test::result json_size() const;
    const bstd::test::result json_assignment_operator() const;
    const bstd::test::result json_equal_operator() const;
    const bstd::test::result json_addition_operator() const;


  private:

    std::string m_json_string1{"{ \"name1\": \"value1\" }"};
    std::string m_json_string2{"{ \"name2\": \"value2\" }"};

    bstd::json::json m_empty_json{""};
    bstd::json::json m_one_child{"{}"};
    bstd::json::json m_json1{m_json_string1};
    bstd::json::json m_json1_copy{m_json_string1};
    bstd::json::json m_json2{m_json_string2};
    bstd::json::json m_json1and2{m_json_string1 + m_json_string2};

};


#endif
