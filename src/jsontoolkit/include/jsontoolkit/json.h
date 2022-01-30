#ifndef SOURCEMETA_JSONTOOLKIT_JSON_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_H_

#include <string>
#include <cinttypes>
#include <cstddef>
#include <iterator>
#include <type_traits>

#if SOURCEMETA_JSONTOOLKIT_JSON_BACKEND == rapidjson
#include <jsontoolkit/json_rapidjson.h>
#else
#error Invalid backend: SOURCEMETA_JSONTOOLKIT_JSON_BACKEND
#endif

namespace sourcemeta {
  namespace jsontoolkit {
    template<typename Type, typename BackendType>
    class JSONIterator {
      public:
        JSONIterator(BackendType &iterator);

        // std::iterator_traits support
        // See https://en.cppreference.com/w/cpp/iterator/iterator_traits
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Type;
        using pointer = Type *;
        using reference = Type &;

        // Operators
        reference operator*();
        pointer operator->();
        JSONIterator<Type, BackendType>& operator++();
        JSONIterator<Type, BackendType>& operator--();
        bool operator==(const JSONIterator<Type, BackendType>& other) const;
        bool operator!=(const JSONIterator<Type, BackendType>& other) const;
      private:
        BackendType backend;
        typename std::remove_const<Type>::type wrapper;
    };

    class JSON {
      public:
        JSON(const std::string &json);
        ~JSON();

        // TODO: Implement setters

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

        std::size_t length() const;
        bool has(const std::size_t index) const;
        bool has(const std::string &key) const;
        JSON at(const std::size_t index);
        JSON at(const std::string &key);

        // TODO: Implement iterators
        // TODO: Implement const and reverse and reverse const iterators
        using iterator = SOURCEMETA_JSONTOOLKIT_JSON_ITERATOR;
        friend iterator;
        iterator begin();
        iterator end();
      private:
        using Backend = SOURCEMETA_JSONTOOLKIT_JSON_BACKEND;
        JSON(Backend &state);
        Backend backend;
    };
  }
}

#endif
