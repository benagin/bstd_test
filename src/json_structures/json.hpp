#ifndef JSON_HPP_
#define JSON_HPP_

#include <iostream>
#include <string>

class json {

  public:

    json() {}

    json(const std::string& _string, const bool _debug = false);

    ~json() {}

    const std::string get_string() const { return m_string; }

  protected:

    friend std::ostream& operator<<(std::ostream&, const json&);

    std::string m_string{""};

    bool m_debug{false};

};

#endif
