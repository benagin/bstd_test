#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <stdexcept>
#include <string>

// Helps us throw effective errors.
class error : public std::runtime_error {

  public:

    explicit error(const std::string& _where, const std::string& _what)
      : std::runtime_error("\n  Where: " + _where + ".\n  What: " \
          + _what + ".\n") {}

};

#endif
