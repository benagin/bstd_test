#ifndef JSON_PARSE_ERROR_HPP_
#define JSON_PARSE_ERROR_HPP_

#include <cmath>

#include "./error.hpp"

// Throw errors related to parsing json.
class json_parse_error : public error {

  typedef std::string::const_iterator SIT;

  public:

    // Report error for specific character in an expression.
    //
    // _expression The larger expression that contains the bad character.
    // _sit        Iterator pointing to the bad character.
    // _what       The error.
    explicit json_parse_error(const std::string& _expression, const SIT& _sit,
        const std::string& _what)
      : error("character '" + std::string(1, *_sit) + "' in expression '" +
          mark_bad_char(_sit, _expression), _what) {}

    // Report error for specific substring in an expression.
    //
    // _expression The larger expression that contains the bad character.
    // _start      Iterator to the start of the bad string.
    // _end        Iterator to the end of the bad string.
    // _what       The error.
    explicit json_parse_error(const std::string& _expression, const SIT& _start,
        const SIT& _end, const std::string& _what)
      : error(std::string(_start, _end) + "' in expression '" +
          mark_bad_string(_start, _end, _expression), _what) {}

  private:

    // Marks a bad character in a string with angle brackets (<, >).
    // Example: 'This string has a bad<d> character.'
    // Only return ample context for the bad character.
    //
    // _sit The bad character.
    // _expression The larger expression containing *_sit.
    const std::string mark_bad_char(const SIT& _sit,
        const std::string& _expression) const;

    // Same as above, but marks a string.
    //
    // _start      Iterator to the start of the bad string.
    // _end        Iterator to the end of the bad string.
    // _expression The larger expression that contains the bad string.
    const std::string mark_bad_string(const SIT& _start, const SIT& _end,
        const std::string& _expression) const;

    // Trim context to keep it under MAX_CONTEXT_SIZE.
    //
    // _context The context string.
    std::string trim(const std::string& _context) const;

};


#endif
