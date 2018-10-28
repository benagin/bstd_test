#ifndef VALUE_HPP_
#define VALUE_HPP_

#include "element.hpp"

namespace bstd::json {

class value : public element {

  public:

    value() {}

    ~value() {}

    virtual const std::string to_string() const override;

  protected:

    // Only accessed from derived classes.
    value(const bool _debug) : element(_debug) {}
    value(const std::string& _string, const bool _debug)
        : element(_string, _debug) {}

};


}

#endif
