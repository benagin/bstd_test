#ifndef BSTD_CONTEXT_ERROR_HPP_
#define BSTD_CONTEXT_ERROR_HPP_

#include <cmath>

#include "error.hpp"

namespace bstd::error {

// Error helper for errors within a string.
// Here, context is a string that contains an error.
// This is useful for things like parsing where you want to indicate the cause
// of the error within a string.
class context_error : public error {

  typedef std::string::const_iterator CSIT;

  public:

    explicit context_error(const std::string& _where, const std::string& _what)
        : error(_where, _what) {}

    // Report error for a character in a context.
    //
    // _context Context that contains the error.
    // _csit    Iterator to the bad character.
    // _what    What went wrong.
    explicit context_error(const std::string& _context, const CSIT& _csit,
        const std::string& _what)
        : error("character '" + std::string(1, *_csit) + "' in context '" +
          mark_char(_csit, _context, this), _what) {}


    // Report error for a string in a context.
    //
    // _context The larger expression that contains the bad character.
    // _start   Iterator to the start of the bad string.
    // _last    Iterator to last character of the bad string.
    // _what    What went wrong.
    explicit context_error(const std::string& _context, const CSIT& _start,
        const CSIT& _last, const std::string& _what)
        : error(std::string(_start, _last) + "' in context '" +
          mark_string(_start, _last, _context, this), _what) {}

  private:

    // Marks a character in a string with angle brackets (<, >).
    // Example: 'This string has a bad<d> character.'
    // Only return ample context for the character.
    //
    // _csit    The character to mark.
    // _context The context containing the character
    // _ce      An object so this friend class works (unused).
    friend const std::string mark_char(const CSIT& _csit,
        const std::string& _context, const context_error* _ce) {
      if(_context.empty())
        throw context_error("context_error::mark_char", "Empty context string");

      return mark_string(_csit, _csit, _context, _ce);
    }


    // Same as above, but marks a string.
    //
    // _start   Iterator to the start of the string.
    // _last    Iterator to the last character of the string.
    // _context The context that contains the string.
    // _ce      An object so this friend class works (unused).
    friend const std::string mark_string(const CSIT& _start, const CSIT& _last,
        const std::string& _context, const context_error* _ce){
      auto error = trim(_context, _ce);

      auto start = error.begin() + std::distance(error.cbegin(), _start),
           end = error.begin() + std::distance(error.cbegin(), _last);

      error.insert(start, {' ', '{'});
      error.insert(end + 3, {'}', ' '});

      return error;
    }

    // Trim context to keep it under MAX_CONTEXT_SIZE.
    //
    // _context The context string.
    // _ce      An object so this friend class works (unused).
    friend std::string trim(const std::string& _context,
        const context_error* _ce) {
      // If the context of an error is larger than this we wil trim it to keep
      // output cleaner.
      constexpr size_t MAX_CONTEXT_SIZE = 30;

      // The max amount of characters we will trim from the end of the context
      // before trimming from the beginning.
      constexpr size_t MAX_TRIM_SIZE = 10;

      // Get a non-const copy.
      std::string error(_context);

      const auto size = error.size();
      if(size < MAX_CONTEXT_SIZE)
        return error;

      const auto& size_to_trim = std::ceil((MAX_CONTEXT_SIZE - size) / 2);

      const std::string ellipsis = "...";

      // Trim from the end of the context string.
      error = error.substr(size - size_to_trim) + ellipsis;

      // Trim from the beginning and end of the context.
      if(size_to_trim > MAX_TRIM_SIZE)
        error = error.substr(0, size_to_trim).insert(0, ellipsis);

      return error;
    }

};

}

#endif
