#ifndef SOURCEMETA_JSONTOOLKIT_ALGORITHM_H_
#define SOURCEMETA_JSONTOOLKIT_ALGORITHM_H_

#include <jsontoolkit/json.h>

#include <algorithm> // std::copy_if
#include <iterator>  // std::next, std::make_move_iterator
#include <vector>    // std::vector

namespace sourcemeta::jsontoolkit {
// We can't use std::unique given JSON documents
// cannot be "sorted" in any deterministic manner.
template <typename Source>
// TODO: Can we implement this function obeyind
// std::unique iterator-based interface?
auto unique(sourcemeta::jsontoolkit::JSON<Source> &document) -> void {
  std::vector<sourcemeta::jsontoolkit::JSON<Source>> new_items{};
  // TODO: Make this work on objects too
  auto &items = document.to_array();
  std::copy_if(std::make_move_iterator(std::begin(items)),
               std::make_move_iterator(std::end(items)),
               std::back_inserter(new_items), [&](const auto &item) {
                 return std::find(std::begin(new_items), std::end(new_items),
                                  item) == std::end(new_items);
               });

  document = new_items;
}
} // namespace sourcemeta::jsontoolkit

#endif
