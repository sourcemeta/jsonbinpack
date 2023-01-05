#include <jsonbinpack/mapper/states.h>

#include <cstdint> // std::uint8_t
#include <limits>  // std::numeric_limits

namespace sourcemeta::jsonbinpack::mapper {

class IntegerBoundedMultiplier8Bit final
    : public sourcemeta::alterschema::Rule {
public:
  IntegerBoundedMultiplier8Bit() : Rule("integer_bounded_multiplier_8_bit"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    if (sourcemeta::jsonbinpack::encoding::is_encoding(schema) ||
        dialect != "https://json-schema.org/draft/2020-12/schema" ||
        !vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/validation") ||
        !sourcemeta::jsontoolkit::defines(schema, "type") ||
        sourcemeta::jsontoolkit::to_string(
            sourcemeta::jsontoolkit::at(schema, "type")) != "integer" ||
        !sourcemeta::jsontoolkit::defines(schema, "minimum") ||
        !sourcemeta::jsontoolkit::defines(schema, "maximum") ||
        !sourcemeta::jsontoolkit::defines(schema, "multipleOf") ||
        !sourcemeta::jsontoolkit::is_integer(
            sourcemeta::jsontoolkit::at(schema, "multipleOf"))) {
      return false;
    }

    const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
        sourcemeta::jsonbinpack::mapper::states::integer(schema, vocabularies)};
    return states.has_value() &&
           states->size() <= std::numeric_limits<std::uint8_t>::max();
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const auto minimum{sourcemeta::jsontoolkit::to_integer(
        sourcemeta::jsontoolkit::at(value, "minimum"))};
    const auto maximum{sourcemeta::jsontoolkit::to_integer(
        sourcemeta::jsontoolkit::at(value, "maximum"))};
    const auto multiplier{sourcemeta::jsontoolkit::to_integer(
        sourcemeta::jsontoolkit::at(value, "multipleOf"))};

    auto options{sourcemeta::jsontoolkit::make_object()};
    sourcemeta::jsontoolkit::assign(options, "minimum",
                                    sourcemeta::jsontoolkit::from(minimum));
    sourcemeta::jsontoolkit::assign(options, "maximum",
                                    sourcemeta::jsontoolkit::from(maximum));
    sourcemeta::jsontoolkit::assign(options, "multiplier",
                                    sourcemeta::jsontoolkit::from(multiplier));
    sourcemeta::jsonbinpack::encoding::make_integer_encoding(
        document, value, "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED", options);
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
