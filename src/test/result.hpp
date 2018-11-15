#ifndef BSTD_TEST_RESULT_HPP_
#define BSTD_TEST_RESULT_HPP_

#include <string>
#include <utility>

namespace bstd::test {

// Represents a test result.
// This contains a boolean representing the test's success
// and a string which contains the reason for failure if applicable.
typedef std::pair<bool, std::string> result;

}

#endif
