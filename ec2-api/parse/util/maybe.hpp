// mirko.rahn@itwm.fraunhofer.de

#ifndef _XML_PARSE_MAYBE_HPP
#define _XML_PARSE_MAYBE_HPP

#include <boost/functional/hash.hpp>
#include <boost/function.hpp>

template<typename T>
struct maybe
{
private:
  T t;
  bool given;

public:
  maybe () : t(), given(false) {}
  maybe (const T & _t) : t (_t), given (true) {}

  bool isJust (void) const { return given; }
  bool isNothing (void) const { return !given; }

  const T & get_with_default (const T & dflt) const
  {
    return isNothing() ? dflt : t;
  }

  void operator = (const T & x)
  {
    given = true;
    t = x;
  }

  void func(boost::function<void(T&)> f) {
    f(t);
  }
  
  const T & operator * (void) const
  {
    if (isNothing())
      {
        throw std::runtime_error (std::string("maybe: Nothing: ")
                                  + typeid(t).name());
      }

    return t;
  }

  template<typename U>
  friend std::ostream & operator << (std::ostream &, const maybe<U> &);
};

template<typename T>
inline std::size_t hash_value (const maybe<T> & x)
{
  boost::hash<T> hasher;

  return x.isNothing() ? 0 : (1 + hasher (*x));
}

template<typename T>
inline bool operator == (const maybe<T> & x, const maybe<T> & y)
{
  return x.isNothing()
    ? (y.isNothing() ? true : false)
    : (y.isNothing() ? false : (*x == *y))
    ;
}

template<typename T>
std::ostream & operator << (std::ostream & s, const maybe<T> & m)
{
  //return s << (m.isNothing() ? "Nothing" : ("Just " + ::util::show(m.t)));
  return s;
}

template<typename T>
maybe<T> Nothing (void)
{
  return maybe<T>();
}

template<typename T>
maybe<T> Just (const T & t)
{
  return maybe<T>(t);
}

template<typename T, typename U>
maybe<U> fmap (U (*f)(const T &), const maybe<T> & m)
{
  return m.isNothing() ? Nothing<U>() : Just<U>(f (*m));
}

#endif
