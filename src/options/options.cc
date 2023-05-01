#include <jsonbinpack/options/options.h>

#include <algorithm> // std::transform
#include <iterator>  // std::back_inserter
#include <utility>   // std::move

namespace sourcemeta::jsonbinpack::options {

BYTE_CHOICE_INDEX::BYTE_CHOICE_INDEX(const BYTE_CHOICE_INDEX &other) {
  std::transform(other.choices.cbegin(), other.choices.cend(),
                 std::back_inserter(this->choices), [](const auto &json) {
                   return sourcemeta::jsontoolkit::from(json);
                 });
}

BYTE_CHOICE_INDEX::BYTE_CHOICE_INDEX(
    std::vector<sourcemeta::jsontoolkit::JSON> &&other)
    : choices{std::move(other)} {}

LARGE_CHOICE_INDEX::LARGE_CHOICE_INDEX(const LARGE_CHOICE_INDEX &other) {
  std::transform(other.choices.cbegin(), other.choices.cend(),
                 std::back_inserter(this->choices), [](const auto &json) {
                   return sourcemeta::jsontoolkit::from(json);
                 });
}

LARGE_CHOICE_INDEX::LARGE_CHOICE_INDEX(
    std::vector<sourcemeta::jsontoolkit::JSON> &&other)
    : choices{std::move(other)} {}

TOP_LEVEL_BYTE_CHOICE_INDEX::TOP_LEVEL_BYTE_CHOICE_INDEX(
    const TOP_LEVEL_BYTE_CHOICE_INDEX &other) {
  std::transform(other.choices.cbegin(), other.choices.cend(),
                 std::back_inserter(this->choices), [](const auto &json) {
                   return sourcemeta::jsontoolkit::from(json);
                 });
}

TOP_LEVEL_BYTE_CHOICE_INDEX::TOP_LEVEL_BYTE_CHOICE_INDEX(
    std::vector<sourcemeta::jsontoolkit::JSON> &&other)
    : choices{std::move(other)} {}

CONST_NONE::CONST_NONE(const sourcemeta::jsontoolkit::JSON &input)
    : value{sourcemeta::jsontoolkit::from(input)} {}
CONST_NONE::CONST_NONE(CONST_NONE &&other) noexcept
    : value{sourcemeta::jsontoolkit::from(other.value)} {}
CONST_NONE::CONST_NONE(const CONST_NONE &other)
    : value{sourcemeta::jsontoolkit::from(other.value)} {}

} // namespace sourcemeta::jsonbinpack::options
