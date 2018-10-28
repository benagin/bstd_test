#ifndef ELEMENT_HPP_
#define ELEMENT_HPP_

#include "json.hpp"

namespace bstd::json {

// Interface between the base json class and derived classes.
// Here, we can prevent the derived classes from accessing certain methods.
// This class represents an element from the grammar (https://www.json.org/).
class element : public json {

  public:

    // Getters.

    // Derived classes do not have multiple objects at the top level.
    const std::vector<json>& get_children() const  = delete;

    virtual const std::string& get_name() const final { return m_name; }

    // Derived classes do not store a path.
    const std::string& get_path() const = delete;

    // Member functions.

    virtual const std::string to_string() const = 0;

    // Since derived classes don't store a path we can't write without an
    // argument.
    void write() const = delete;

  protected:

    // Only accessed from derived classes.
    element() {}
    element(const bool _debug) : json(_debug) {}
    element(const std::string& _string, const bool _debug)
        : json(_string, _debug) {}

    ~element() {}

  private:

    virtual void write(const std::string& _path) const final {}

    // The string associated with this element.
    // From the grammar (https://www.json.org/) this is the string in:
    // member
    //  ws string ws ':' element
    std::string m_name{""};

};

}

#endif
