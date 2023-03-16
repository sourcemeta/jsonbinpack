#ifndef JSONTOOLKIT_JSON_RAPIDJSON_WRITE_H_
#define JSONTOOLKIT_JSON_RAPIDJSON_WRITE_H_

#include "common.h"
#include "read.h"

#include <cassert>     // assert
#include <cstdint>     // std::int64_t
#include <string>      // std::string
#include <type_traits> // std::enable_if_t, std::is_same_v
#include <utility>     // std::move

namespace sourcemeta::jsontoolkit {

inline auto set(JSON &root, Value &value, const Value &other) -> void {
  value.CopyFrom(other, root.GetAllocator());
}

inline auto set(JSON &value, const Value &other) -> void {
  return set(value, value, other);
}

inline auto set(JSON &, Value &value, Value &&other) -> void {
  value.Swap(other);
}

inline auto set(JSON &value, Value &&other) -> void {
  return set(value, value, other);
}

inline auto erase(Value &value, const std::string &key) -> void {
  assert(is_object(value));
  value.EraseMember(key);
}

inline auto clear(Value &value) -> void {
  if (is_array(value)) {
    value.Erase(value.Begin(), value.End());
  } else {
    value.EraseMember(value.MemberBegin(), value.MemberEnd());
  }
}

inline auto assign(JSON &root, Value &value, const std::string &key,
                   const Value &member) -> void {
  assert(is_object(value));
  auto &allocator{root.GetAllocator()};
  if (defines(value, key)) {
    value[key] = Value{member, allocator};
  } else {
    value.AddMember(from(key), Value{member, allocator}, allocator);
  }
}

inline auto assign(JSON &root, const std::string &key, const Value &member)
    -> void {
  return assign(root, root, key, member);
}

inline auto assign(JSON &root, Value &value, const std::string &key,
                   Value &&member) -> void {
  assert(is_object(value));
  if (defines(value, key)) {
    value[key] = member;
  } else {
    value.AddMember(from(key), Value{member, root.GetAllocator()},
                    root.GetAllocator());
  }
}

inline auto assign(JSON &root, const std::string &key, Value &&member) -> void {
  return assign(root, root, key, std::move(member));
}

// See https://github.com/Tencent/rapidjson/issues/1016
inline auto push_front(JSON &root, Value &value, const Value &element) -> void {
  assert(is_array(value));
  rapidjson::Value empty;
  value.PushBack(empty, root.GetAllocator());
  for (rapidjson::SizeType index = value.Size() - 1; index > 0; --index) {
    value[index] = value[index - 1];
  }

  value[0].CopyFrom(element, root.GetAllocator());
}

inline auto push_front(JSON &root, const Value &element) -> void {
  return push_front(root, root, element);
}

inline auto push_back(JSON &root, Value &value, const Value &element) -> void {
  assert(is_array(value));
  value.PushBack(rapidjson::Value().CopyFrom(element, root.GetAllocator()),
                 root.GetAllocator());
}

inline auto push_back(JSON &root, const Value &element) -> void {
  return push_back(root, root, element);
}

inline auto push_back(JSON &root, Value &value, Value &&element) -> void {
  assert(is_array(value));
  value.PushBack(element, root.GetAllocator());
}

inline auto push_back(JSON &root, Value &&element) -> void {
  return push_back(root, root, element);
}

inline auto make_object(Value &value) -> void { value.SetObject(); }
inline auto make_array(Value &value) -> void { value.SetArray(); }

} // namespace sourcemeta::jsontoolkit

#endif
