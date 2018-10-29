#ifndef VALUE_HPP_
#define VALUE_HPP_

#include "json.hpp"

namespace bstd::json {

// Interface between the base json class and derived classes.
// Here, we can prevent the derived classes from accessing certain methods.
// This class represents a value from the grammar (https://www.json.org/).
// Different from the grammar, this class stores the associated string (name).
// This string is seen under member in the grammar.
class value : public json {

  public:

    // Getters.

    // Derived classes do not have multiple objects at the top level.
    const std::vector<json*>& get_children() const  = delete;

    virtual const std::string& get_name() const final;

    // Derived classes do not store a path.
    const std::string& get_path() const = delete;

    virtual const std::string to_string() const = 0;

    // Since derived classes don't store a path we can't write without an
    // argument.
    void write() const = delete;

    virtual void write(const std::string& _path) const = 0;

  protected:

    // Only accessed from derived classes.
    value(const bool _debug) : json(_debug) {}
    value(const std::string& _string, const bool _debug)
        : json(_string, _debug) {}

    ~value() {}

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
