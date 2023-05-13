#include <jsonbinpack/encoding/encoding.h>

#include <utility> // std::move

namespace sourcemeta::jsonbinpack {

BYTE_CHOICE_INDEX::BYTE_CHOICE_INDEX(const BYTE_CHOICE_INDEX &other)
    : choices{sourcemeta::jsontoolkit::copy(other.choices)} {}

BYTE_CHOICE_INDEX::BYTE_CHOICE_INDEX(
    std::vector<sourcemeta::jsontoolkit::JSON> &&other)
    : choices{std::move(other)} {}

LARGE_CHOICE_INDEX::LARGE_CHOICE_INDEX(const LARGE_CHOICE_INDEX &other)
    : choices{sourcemeta::jsontoolkit::copy(other.choices)} {}

LARGE_CHOICE_INDEX::LARGE_CHOICE_INDEX(
    std::vector<sourcemeta::jsontoolkit::JSON> &&other)
    : choices{std::move(other)} {}

TOP_LEVEL_BYTE_CHOICE_INDEX::TOP_LEVEL_BYTE_CHOICE_INDEX(
    const TOP_LEVEL_BYTE_CHOICE_INDEX &other)
    : choices{sourcemeta::jsontoolkit::copy(other.choices)} {}

TOP_LEVEL_BYTE_CHOICE_INDEX::TOP_LEVEL_BYTE_CHOICE_INDEX(
    std::vector<sourcemeta::jsontoolkit::JSON> &&other)
    : choices{std::move(other)} {}

CONST_NONE::CONST_NONE(const sourcemeta::jsontoolkit::JSON &input)
    : value{sourcemeta::jsontoolkit::from(input)} {}
CONST_NONE::CONST_NONE(const sourcemeta::jsontoolkit::Value &input)
    : value{sourcemeta::jsontoolkit::from(input)} {}
CONST_NONE::CONST_NONE(const CONST_NONE &other)
    : value{sourcemeta::jsontoolkit::from(other.value)} {}

} // namespace sourcemeta::jsonbinpack
