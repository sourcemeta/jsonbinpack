#ifndef SOURCEMETA_JSONTOOLKIT_JSONPOINTER_WALKER_H_
#define SOURCEMETA_JSONTOOLKIT_JSONPOINTER_WALKER_H_

#include <vector> // std::vector

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonpointer_pointer.h>

namespace sourcemeta::jsontoolkit {

/// @ingroup jsonpointer
/// A walker to get every JSON Pointer in a JSON document
template <typename CharT, typename Traits,
          template <typename T> typename Allocator>
class GenericPointerWalker {
private:
  using internal =
      typename std::vector<GenericPointer<CharT, Traits, Allocator>>;

public:
  GenericPointerWalker(const JSON &document) { this->walk(document, {}); }

  using const_iterator = typename internal::const_iterator;
  auto begin() const -> const_iterator { return this->pointers.begin(); };
  auto end() const -> const_iterator { return this->pointers.end(); };
  auto cbegin() const -> const_iterator { return this->pointers.cbegin(); };
  auto cend() const -> const_iterator { return this->pointers.cend(); };

private:
  auto walk(const JSON &document,
            const GenericPointer<CharT, Traits, Allocator> &pointer) -> void {
    this->pointers.push_back(pointer);
    if (document.is_array()) {
      for (std::size_t index = 0; index < document.size(); index++) {
        GenericPointer<CharT, Traits, Allocator> subpointer{pointer};
        subpointer.emplace_back(index);
        this->walk(document.at(index), subpointer);
      }
    } else if (document.is_object()) {
      for (const auto &pair : document.as_object()) {
        GenericPointer<CharT, Traits, Allocator> subpointer{pointer};
        subpointer.emplace_back(pair.first);
        this->walk(pair.second, subpointer);
      }
    }
  }

// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  internal pointers;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::jsontoolkit

#endif
