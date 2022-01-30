#ifndef SOURCEMETA_JSONTOOLKIT_JSON_RAPIDJSON_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_RAPIDJSON_H_

#include <cstddef> // std::size_t

/*
 * This header configures the JSON interface to use rapidjson
 */

// Enable std::string support
#define RAPIDJSON_HAS_STDSTRING 1

// Use a 64-bit size type
#define RAPIDJSON_NO_SIZETYPEDEFINE
namespace rapidjson {
  typedef std::size_t SizeType;
}

#include <rapidjson/rapidjson.h> // rapidjson::SizeType
#include <rapidjson/document.h> // rapidjson::GenericValue
#include <rapidjson/allocators.h> // rapidjson::MemoryPoolAllocator

#define SOURCEMETA_JSONTOOLKIT_JSON_BACKEND \
  rapidjson::GenericValue<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>
#define SOURCEMETA_JSONTOOLKIT_JSON_ITERATOR sourcemeta::jsontoolkit::JSONIterator< \
  sourcemeta::jsontoolkit::JSON, \
  rapidjson::GenericValue<rapidjson::UTF8<>>::ValueIterator>

#endif
