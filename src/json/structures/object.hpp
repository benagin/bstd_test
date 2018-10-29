#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <map>

#include "value.hpp"

namespace bstd::json {

// Represents an object from the JSON grammar (https://www.json.org/).
class object final : public value {

  public:

    object(const bool _debug = false) : value(_debug) {}

    object(const std::string& _string, const bool _debug = false)
        : value(_string, _debug) {}

    ~object() {}

    // Accessors.

    value& operator[](const std::string& _string);
    value& operator[](const std::string&& _string);

    value& at(const std::string& _string);
    const value& at(const std::string& _string) const;

    friend std::ostream& operator<<(std::ostream& _os,
        const object& _object) {
      return _os << _object.to_string();
    }

  private:

    std::map<std::string, value*> m_values;

};

}

#endif
