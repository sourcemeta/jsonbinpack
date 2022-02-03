#ifndef SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_STRING_H_

#include <string_view>

namespace sourcemeta {
  namespace jsontoolkit {
    template <typename Wrapper, typename Backend> class GenericString {
      public:
        GenericString();
        GenericString(const std::string_view &document);

        using traits_type = typename Backend::traits_type;
        using value_type = typename Backend::value_type;
        using allocator_type = typename Backend::allocator_type;
        using size_type = typename Backend::size_type;
        using difference_type = typename Backend::difference_type;
        using reference = typename Backend::reference;
        using const_reference = typename Backend::const_reference;
        using pointer = typename Backend::pointer;
        using const_pointer = typename Backend::const_pointer;
        using iterator = typename Backend::iterator;
        using const_iterator = typename Backend::const_iterator;
        using reverse_iterator = typename Backend::reverse_iterator;
        using const_reverse_iterator = typename Backend::const_reverse_iterator;

        size_type size();

        iterator begin();
        iterator end();
        const_iterator cbegin();
        const_iterator cend();
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator crbegin();
        const_reverse_iterator crend();

        friend Wrapper;
      private:
        const std::string_view source;
        GenericString& parse();
        bool must_parse;
        Backend data;
    };
  }
}

#endif
