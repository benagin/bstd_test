#ifndef VALUE_HPP_
#define VALUE_HPP_

#include <algorithm>
#include <sstream>
#include <vector>

#include "json_base.hpp"

namespace bstd::json {

// This class represents a value from the grammar (https://www.json.org/).
// Different from the grammar, this class stores the associated string (name).
// This string is seen under member in the grammar.
class value : public json_base {

  public:

    value(const bool _debug) : json_base(_debug) {}

    virtual ~value() = 0;

    // Getters.

    // Only values have names, so this is marked final.
    virtual const std::string& get_name() const final;

    virtual const std::size_t size() const = 0;

    // Member functions.

    virtual const std::string to_string() const = 0;

    virtual void parse(const std::string& _string) = 0;

    virtual void write(const std::string& _path) const = 0;

  protected:

    bool m_debug{false};

  private:

    // The string associated with this value.
    // From the grammar (https://www.json.org/) this is the string in:
    // member
    //  ws string ws ':' value
    // 'value' represents this value.
    std::string m_name{""};

};


}

#endif
