#ifndef JSONTOOLKIT_JSON_ITERATORS_H_
#define JSONTOOLKIT_JSON_ITERATORS_H_

#if defined(JSONTOOLKIT_BACKEND_RAPIDJSON)
#include "rapidjson/iterators.h"
#else
#error Unknown JSON Toolkit backend
#endif

namespace sourcemeta::jsontoolkit {

class ArrayIteratorWrapper {
public:
  ArrayIteratorWrapper(Value &input) : data{input} { assert(is_array(input)); }
  auto begin() -> decltype(auto) { return begin_array(this->data); }
  auto end() -> decltype(auto) { return end_array(this->data); }

private:
  Value &data;
};

class ConstArrayIteratorWrapper {
public:
  ConstArrayIteratorWrapper(const Value &input) : data{input} {
    assert(is_array(input));
  }
  auto begin() const -> decltype(auto) { return cbegin_array(this->data); }
  auto end() const -> decltype(auto) { return cend_array(this->data); }

private:
  const Value &data;
};

inline auto array_iterator(const Value &value) -> ConstArrayIteratorWrapper {
  return ConstArrayIteratorWrapper{value};
}

inline auto array_iterator(Value &value) -> ArrayIteratorWrapper {
  return ArrayIteratorWrapper{value};
}

class ObjectIteratorWrapper {
public:
  ObjectIteratorWrapper(Value &input) : data{input} {
    assert(is_object(input));
  }
  auto begin() -> decltype(auto) { return begin_object(this->data); }
  auto end() -> decltype(auto) { return end_object(this->data); }

private:
  Value &data;
};

class ConstObjectIteratorWrapper {
public:
  ConstObjectIteratorWrapper(const Value &input) : data{input} {
    assert(is_object(input));
  }
  auto begin() const -> decltype(auto) { return cbegin_object(this->data); }
  auto end() const -> decltype(auto) { return cend_object(this->data); }

private:
  const Value &data;
};

inline auto object_iterator(const Value &value) -> ConstObjectIteratorWrapper {
  return ConstObjectIteratorWrapper{value};
}

inline auto object_iterator(Value &value) -> ObjectIteratorWrapper {
  return ObjectIteratorWrapper{value};
}

} // namespace sourcemeta::jsontoolkit

#endif
