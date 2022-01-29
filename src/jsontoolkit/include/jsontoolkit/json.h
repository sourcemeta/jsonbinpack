#ifndef SOURCEMETA_JSONTOOLKIT_JSON_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_H_

#include <string>
#include <memory>
#include <cinttypes>

// Use a 64-bit size type
#define RAPIDJSON_NO_SIZETYPEDEFINE
namespace rapidjson {
  typedef std::size_t SizeType;
}

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/allocators.h>
#include <rapidjson/error/en.h>

namespace sourcemeta {
  namespace jsontoolkit {
    class JSON {
      public:
        JSON(const std::string &json);
        ~JSON();

        std::size_t length() const;

        bool is_object() const;
        bool is_array() const;
        bool is_boolean() const;
        bool is_number() const;
        bool is_integer() const;
        bool is_string() const;
        bool is_null() const;
        bool is_structural() const;

        bool to_boolean() const;
        std::string to_string() const;
        std::int64_t to_integer() const;
        double to_double() const;

        bool has(const std::size_t index) const;
        bool has(const std::string &key) const;
        JSON at(const std::size_t index);
      private:
        using Backend = rapidjson::GenericValue<
          rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>>;
        JSON(Backend &state);
        Backend backend;
    };
  }
}

#endif
