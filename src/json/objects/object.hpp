#ifndef OBJECT_HPP_
#define OBJECT_HPP_

namespace bstd::json {

// The second highest object in the JSON grammar found here:
// https://www.json.org/.
class object : public json {

  public:

    object() {}

    ~object() {}

  private:

    friend std::ostream& operator<<(std::ostream& _os,
        const object& _object) {
      return _os << _object.to_string();
    }

};
}

#endif
