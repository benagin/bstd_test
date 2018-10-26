#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <map>

#include "json.hpp"

namespace bstd::json {

// The second highest object in the JSON grammar found here:
// https://www.json.org/.
class object final : public json {

  public:

    object(const bool _debug = false) : json(_debug) {}

    object(const std::string& _string, const bool _debug = false)
        : json(_string, _debug) {}

    ~object() {}

    const size_t size() const override;

    // Accessors.

    json& operator[](const std::string& _string);
    json& operator[](const std::string&& _string);

    json& at(const std::string& _string);
    const json& at(const std::string& _string) const;

    friend std::ostream& operator<<(std::ostream& _os,
        const object& _object) {
      return _os << _object.to_string();
    }

  private:

    std::map<std::string, json> m_values;

};
}

#endif
