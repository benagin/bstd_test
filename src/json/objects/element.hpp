#ifndef ELEMENT_HPP_
#define ELEMENT_HPP_

namespace bstd {

// The second highest object in the JSON grammar found here:
// https://www.json.org/.
class element : public json {

  public:

    element() {}

    ~element() {}

  private:

    friend std::ostream& operator<<(std::ostream& _os,
        const element& _element) {
      return _os << _element.to_string();
    }

};
}

#endif
