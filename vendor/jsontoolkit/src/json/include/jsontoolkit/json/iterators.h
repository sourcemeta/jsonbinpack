#ifndef JSONTOOLKIT_JSON_ITERATORS_H_
#define JSONTOOLKIT_JSON_ITERATORS_H_

#if defined(JSONTOOLKIT_BACKEND_RAPIDJSON)
#include "rapidjson/iterators.h"
#else
#error Unknown JSON Toolkit backend
#endif

namespace sourcemeta::jsontoolkit {

inline auto array_iterator(const Value &value) -> ConstArrayIteratorWrapper {
  return ConstArrayIteratorWrapper{value};
}

inline auto array_iterator(Value &value) -> ArrayIteratorWrapper {
  return ArrayIteratorWrapper{value};
}

inline auto object_iterator(const Value &value) -> ConstObjectIteratorWrapper {
  return ConstObjectIteratorWrapper{value};
}

inline auto object_iterator(Value &value) -> ObjectIteratorWrapper {
  return ObjectIteratorWrapper{value};
}

} // namespace sourcemeta::jsontoolkit

#endif
