#ifndef MEMBER_HPP_
#define MEMBER_HPP_

#include "json.hpp"

namespace bstd::json {

// Interface between the base json class and derived classes.
// Here, we can prevent the derived classes from accessing certain methods.
class member : public json {

  public:

    member() {}

    ~member() {}

    const std::string& get_path() const = delete;

    void write() const = delete;

  protected:

    virtual void write(const std::string& _path) const {}


    // Only accessed from derived classes.
    member(const bool _debug) : json(_debug) {}
    member(const std::string& _string, const bool _debug)
        : json(_string, _debug) {}

};

}

#endif
