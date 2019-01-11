#ifndef BSTD_JSON_VALUE_HPP_
#define BSTD_JSON_VALUE_HPP_

#include <algorithm>
#include <vector>

#include "json_base.hpp"

namespace bstd::json {

// This class represents a value from the grammar (https://www.json.org/).
// Different from the grammar, this class also acts as a member and an element.
// It acts as a member by storing the associated string (name) to the value. An
// element is simply a value surrounded by optional whitespace. This keeps track
// of that whitespace so it essentially acts as an element as well.
class value : public json_base {

  public:

    value(const bool _debug) : json_base(_debug) {}

    virtual ~value() = 0;

    // Getters.

    // Only values have names, so this is marked final.
    virtual const std::string& get_name() const final;

    virtual const std::size_t size() const = 0;

    // Member functions.

    virtual const std::string to_string(const bool _include_ws = true) const = 0;

    virtual const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) = 0;

    virtual void parse(const std::string& _string) = 0;

  protected:

    bool m_debug{false};

  private:

    // The string associated with this value.
    // From the grammar (https://www.json.org/) this is the string in:
    // member
    //  ws string ws ':' value
    // 'value' represents this value.
    std::string m_name{""};

    // TODO: keep track of said ws.

};


}

#endif
