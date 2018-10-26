#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <map>

#include "member.hpp"

namespace bstd::json {

// The second highest object in the JSON grammar found here:
// https://www.json.org/.
class object final : public member {

  public:

    object(const bool _debug = false) : member(_debug) {}

    object(const std::string& _string, const bool _debug = false)
        : member(_string, _debug) {}

    ~object() {}

    const size_t size() const override final;

    // Accessors.

    member& operator[](const std::string& _string);
    member& operator[](const std::string&& _string);

    member& at(const std::string& _string);
    const member& at(const std::string& _string) const;

    friend std::ostream& operator<<(std::ostream& _os,
        const object& _object) {
      return _os << _object.to_string();
    }

  private:

    std::map<std::string, member> m_values;

};

}

#endif
