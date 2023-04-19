#ifndef JSONTOOLKIT_JSON_RAPIDJSON_WRITE_H_
#define JSONTOOLKIT_JSON_RAPIDJSON_WRITE_H_

#include "common.h"
#include "read.h"

#include <cassert>     // assert
#include <cstdint>     // std::int64_t
#include <iterator>    // std::cbegin, std::cend
#include <set>         // std::set
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

inline auto erase_many(Value &value, rapidjson::Value::ValueIterator begin,
                       rapidjson::Value::ValueIterator end) -> void {
  value.Erase(begin, end);
}

inline auto erase_many(Value &value, rapidjson::Value::ConstValueIterator begin,
                       rapidjson::Value::ConstValueIterator end) -> void {
  value.Erase(begin, end);
}

inline auto erase_many(Value &value, rapidjson::Value::MemberIterator begin,
                       rapidjson::Value::MemberIterator end) -> void {
  value.EraseMember(begin, end);
}

inline auto erase_many(Value &value,
                       rapidjson::Value::ConstMemberIterator begin,
                       rapidjson::Value::ConstMemberIterator end) -> void {
  value.EraseMember(begin, end);
}

template <typename Iterator>
inline auto erase_many(Value &value, Iterator begin, Iterator end) -> void {
  for (Iterator iterator{begin}; iterator != end; iterator++) {
    erase(value, *iterator);
  }
}

inline auto clear(Value &value) -> void {
  if (is_array(value)) {
    erase_many(value, value.Begin(), value.End());
  } else {
    erase_many(value, value.MemberBegin(), value.MemberEnd());
  }
}

template <typename T> auto clear_except(Value &value, const T &keys) -> void {
  assert(is_object(value));
  std::set<std::string> blacklist;
  for (rapidjson::Value::ConstMemberIterator iterator = value.MemberBegin();
       iterator != value.MemberEnd(); ++iterator) {
    if (keys.find(iterator->name.GetString()) == keys.end()) {
      blacklist.insert(iterator->name.GetString());
    }
  }

  erase_many(value, std::cbegin(blacklist), std::cend(blacklist));
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
