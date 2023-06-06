#ifndef JSONTOOLKIT_JSON_RAPIDJSON_ITERATORS_H_
#define JSONTOOLKIT_JSON_RAPIDJSON_ITERATORS_H_

#include "common.h"
#include "read.h"

#include <cassert>  // assert
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::reverse_iterator,
                    // std::random_access_iterator,
                    // std::bidirectional_iterator_tag

namespace sourcemeta::jsontoolkit {

inline auto value(const rapidjson::Value::Member &member) -> const Value & {
  return member.value;
}

inline auto key(const rapidjson::Value::Member &member) -> std::string {
  return member.name.GetString();
}

inline auto value(rapidjson::Value::Member &member) -> Value & {
  return member.value;
}

inline auto cbegin_array(const Value &value)
    -> rapidjson::Value::ConstValueIterator {
  assert(is_array(value));
  return value.Begin();
}

inline auto cend_array(const Value &value)
    -> rapidjson::Value::ConstValueIterator {
  assert(is_array(value));
  return value.End();
}

// See https://github.com/Tencent/rapidjson/issues/678
inline auto crbegin_array(const Value &value)
    -> std::reverse_iterator<rapidjson::Value::ConstValueIterator> {
  assert(is_array(value));
  return std::reverse_iterator<rapidjson::Value::ConstValueIterator>{
      value.End()};
}

// See https://github.com/Tencent/rapidjson/issues/678
inline auto crend_array(const Value &value)
    -> std::reverse_iterator<rapidjson::Value::ConstValueIterator> {
  assert(is_array(value));
  return std::reverse_iterator<rapidjson::Value::ConstValueIterator>{
      value.Begin()};
}

// See https://github.com/Tencent/rapidjson/issues/678
inline auto rbegin_array(Value &value)
    -> std::reverse_iterator<rapidjson::Value::ValueIterator> {
  assert(is_array(value));
  return std::reverse_iterator<rapidjson::Value::ValueIterator>{value.End()};
}

// See https://github.com/Tencent/rapidjson/issues/678
inline auto rend_array(Value &value)
    -> std::reverse_iterator<rapidjson::Value::ValueIterator> {
  assert(is_array(value));
  return std::reverse_iterator<rapidjson::Value::ValueIterator>{value.Begin()};
}

inline auto begin_array(Value &value) -> rapidjson::Value::ValueIterator {
  assert(is_array(value));
  return value.Begin();
}

inline auto end_array(Value &value) -> rapidjson::Value::ValueIterator {
  assert(is_array(value));
  return value.End();
}

inline auto cbegin_object(const Value &value)
    -> rapidjson::Value::ConstMemberIterator {
  assert(is_object(value));
  return value.MemberBegin();
}

inline auto cend_object(const Value &value)
    -> rapidjson::Value::ConstMemberIterator {
  assert(is_object(value));
  return value.MemberEnd();
}

inline auto begin_object(Value &value) -> rapidjson::Value::MemberIterator {
  assert(is_object(value));
  return value.MemberBegin();
}

inline auto end_object(Value &value) -> rapidjson::Value::MemberIterator {
  assert(is_object(value));
  return value.MemberEnd();
}

class ArrayIteratorWrapper {
public:
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = rapidjson::Value;
  using pointer = value_type *;
  using reference = value_type &;

  ArrayIteratorWrapper(Value &input) : data{input} { assert(is_array(input)); }
  auto begin() -> rapidjson::Value::ValueIterator {
    return begin_array(this->data);
  }
  auto end() -> rapidjson::Value::ValueIterator {
    return end_array(this->data);
  }

private:
  Value &data;
};

class ConstArrayIteratorWrapper {
public:
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = const rapidjson::Value;
  using pointer = value_type *;
  using reference = value_type &;

  ConstArrayIteratorWrapper(const Value &input) : data{input} {
    assert(is_array(input));
  }
  auto begin() const -> rapidjson::Value::ConstValueIterator {
    return cbegin_array(this->data);
  }
  auto end() const -> rapidjson::Value::ConstValueIterator {
    return cend_array(this->data);
  }

private:
  const Value &data;
};

class ObjectIteratorWrapper {
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = rapidjson::Value::Member;
  using pointer = value_type *;
  using reference = value_type &;

  ObjectIteratorWrapper(Value &input) : data{input} {
    assert(is_object(input));
  }
  auto begin() -> rapidjson::Value::MemberIterator {
    return begin_object(this->data);
  }
  auto end() -> rapidjson::Value::MemberIterator {
    return end_object(this->data);
  }

private:
  Value &data;
};

class ConstObjectIteratorWrapper {
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = const rapidjson::Value::Member;
  using pointer = value_type *;
  using reference = value_type &;

  ConstObjectIteratorWrapper(const Value &input) : data{input} {
    assert(is_object(input));
  }
  auto begin() const -> rapidjson::Value::ConstMemberIterator {
    return cbegin_object(this->data);
  }
  auto end() const -> rapidjson::Value::ConstMemberIterator {
    return cend_object(this->data);
  }

private:
  const Value &data;
};

} // namespace sourcemeta::jsontoolkit

#endif
