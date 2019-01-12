#ifndef BSTD_JSON_BASE_HPP_
#define BSTD_JSON_BASE_HPP_

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <bstd_error.hpp>

namespace bstd::json {

class value;

// Abstract class used as base for each json related structure.
class json_base {

  public:

    json_base(const bool _debug) : m_debug(_debug) {}

    virtual ~json_base() = 0;

    virtual const std::size_t size() const = 0;

    // This calls to_string() which includes whitespace by default.
    // If you do not want whitespace use
    // std::cout << derived.to_string(false);
    friend std::ostream& operator<<(std::ostream& _os,
        const json_base& _json_base);

    virtual const std::string to_string(const bool _include_ws = true) const = 0;

    virtual const std::shared_ptr<value>&
        add_value(const std::shared_ptr<value>& _value) = 0;

    virtual void parse(const std::string& _string) = 0;

    virtual void write(const std::string _path, const bool _include_ws = true)
        const final;

  protected:

    virtual std::fstream open_json_file(const std::string& _path,
        std::ios_base::openmode _mode) const final;

    virtual const bool is_json_extension(const std::string& _path) const final;

    bool m_debug{false};

};

}

#endif
