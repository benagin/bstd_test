#include "json_parse_error.hpp"

const std::string
json_parse_error::
mark_bad_char(const SIT& _sit, const std::string& _expression) const {
  if(_expression.empty())
    throw error("Empty expression string",
        "json_parse_error::mark_bad_char");

  return mark_bad_string(_sit, _sit, _expression);
}


const std::string
json_parse_error::
mark_bad_string(const SIT& _start, const SIT& _end,
    const std::string& _expression) const {
  auto error = trim(_expression);

  auto start = error.begin() + std::distance(error.cbegin(), _start),
       end = error.begin() + std::distance(error.cbegin(), _end);

  error.insert(start, {' ', '{'});
  error.insert(end + 3, {'}', ' '});

  return error;
}

std::string
json_parse_error::
trim(const std::string& _context) const {
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
