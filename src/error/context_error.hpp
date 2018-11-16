#ifndef BSTD_CONTEXT_ERROR_HPP_
#define BSTD_CONTEXT_ERROR_HPP_

#include <cmath>

#include "./error.hpp"

namespace bstd::error {

// Error helper for errors within a string.
// Here, context is a string that contains an error.
// This is useful for things like parsing where you want to indicate the cause
// of the error within a string.
class context_error : public error {

  typedef std::string::const_iterator SIT;

  public:

    explicit context_error(const std::string& _where, const std::string& _what)
        : error(_where, _what) {}

    // Report error for a character in a context.
    //
    // _context Context that contains the error.
    // _sit     Iterator to the bad character.
    // _what    What went wrong.
    explicit context_error(const std::string& _context, const SIT& _sit,
        const std::string& _what)
        : error("character '" + std::string(1, *_sit) + "' in context '" +
          mark_char(_sit, _context), _what) {}

    // Report error for a string in a context.
    //
    // _context The larger expression that contains the bad character.
    // _start   Iterator to the start of the bad string.
    // _last    Iterator to last character of the bad string.
    // _what    What went wrong.
    explicit context_error(const std::string& _context, const SIT& _start,
        const SIT& _last, const std::string& _what)
        : error(std::string(_start, _last) + "' in context '" +
          mark_string(_start, _last, _context), _what) {}

  private:

    // Marks a character in a string with angle brackets (<, >).
    // Example: 'This string has a bad<d> character.'
    // Only return ample context for the character.
    //
    // _sit     The character to mark.
    // _context The context containing the character
    const std::string mark_char(const SIT& _sit,
        const std::string& _context) const;

    // Same as above, but marks a string.
    //
    // _start   Iterator to the start of the string.
    // _last    Iterator to the last character of the string.
    // _context The context that contains the string.
    const std::string mark_string(const SIT& _start, const SIT& _last,
        const std::string& _context) const;

    // Trim context to keep it under MAX_CONTEXT_SIZE.
    //
    // _context The context string.
    std::string trim(const std::string& _context) const;

};
}

#endif
