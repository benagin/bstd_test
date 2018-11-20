#ifndef BSTD_JSON_OBJECT_HPP_
#define BSTD_JSON_OBJECT_HPP_

#include <map>
#include <memory>

#include "value.hpp"

namespace bstd::json {

// Represents an object from the JSON grammar (https://www.json.org/).
class object final : public value {

  public:

    object(const bool _debug = false) : value(_debug) {}

    // TODO: implement.
    object(const std::string& _string, const bool _debug = false)
        : object(_debug) {}

    ~object() {}

    // Getters and setters.

    const std::size_t size() const override;

    // Accessors.

    value& operator[](const std::string& _string);
    value& operator[](const std::string&& _string);

    value& at(const std::string& _string);
    const value& at(const std::string& _string) const;

    // Operator overloads.

    bool operator==(const object& _rhs) const;

    bool operator!=(const object& _rhs) const;

    object& operator+=(const object& _rhs);

    // Member functions.

    const std::string to_string() const override;

    // Add _value to m_values.
    const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) override;

    // TODO: implement.
    void parse(const std::string& _string) override {}

    void write(const std::string& _path) const override;

  private:

    std::map<std::string, std::shared_ptr<value>> m_values;

};

}

#endif
