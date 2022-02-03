#ifndef SOURCEMETA_JSONTOOLKIT_JSON_ARRAY_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_ARRAY_H_

#include <jsontoolkit/json_type.h>

#include <string_view>
#include <vector>

namespace sourcemeta {
  namespace jsontoolkit {
    template <typename Wrapper> class GenericArray {
      public:
        GenericArray();
        GenericArray(const std::string_view &document);
        sourcemeta::jsontoolkit::Type type() const;
        using size_type = typename std::vector<Wrapper>::size_type;
        Wrapper& at(const size_type index);
        size_type size();
        friend Wrapper;

        using iterator = typename std::vector<Wrapper>::iterator;
        using const_iterator = typename std::vector<Wrapper>::const_iterator;
        using reverse_iterator = typename std::vector<Wrapper>::reverse_iterator;
        using const_reverse_iterator = typename std::vector<Wrapper>::const_reverse_iterator;

        iterator begin();
        iterator end();
        const_iterator cbegin();
        const_iterator cend();
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator crbegin();
        const_reverse_iterator crend();
      private:
        const std::string_view source;
        GenericArray& parse();
        bool must_parse;
        std::vector<Wrapper> data;
    };
  }
}

#endif
