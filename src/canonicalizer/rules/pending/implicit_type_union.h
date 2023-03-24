#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <utility> // std::move
#include <vector>  // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer {

class ImplicitTypeUnion final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  ImplicitTypeUnion() : Rule("implicit_type_union"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    const bool has_core_vocabulary =
        sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, vocabularies::core);

    const bool has_validation_vocabulary =
        sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, vocabularies::validation);
    const bool has_applicator_vocabulary =
        sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, vocabularies::applicator);
    const bool is_object = schema.is_object();

    if (has_core_vocabulary && is_object &&
        schema.defines(keywords::core::ref)) {
      return false;
    }

    if (has_core_vocabulary && is_object &&
        schema.defines(keywords::core::dynamicRef)) {
      return false;
    }

    if (has_validation_vocabulary && is_object &&
        schema.defines(keywords::validation::type)) {
      return false;
    }

    if (has_validation_vocabulary && is_object &&
        schema.defines(keywords::validation::_const)) {
      return false;
    }

    if (has_validation_vocabulary && is_object &&
        schema.defines(keywords::validation::_enum)) {
      return false;
    }

    if (has_applicator_vocabulary && is_object &&
        schema.defines(keywords::applicator::anyOf)) {
      return false;
    }

    if (has_applicator_vocabulary && is_object &&
        schema.defines(keywords::applicator::allOf)) {
      return false;
    }

    if (has_applicator_vocabulary && is_object &&
        schema.defines(keywords::applicator::oneOf)) {
      return false;
    }

    if (has_applicator_vocabulary && is_object &&
        schema.defines(keywords::applicator::_not)) {
      return false;
    }

    if (has_applicator_vocabulary && is_object &&
        schema.defines(keywords::applicator::_if)) {
      return false;
    }

    if (has_applicator_vocabulary && is_object &&
        schema.defines(keywords::applicator::then)) {
      return false;
    }

    if (has_applicator_vocabulary && is_object &&
        schema.defines(keywords::applicator::_else)) {
      return false;
    }

    return true;
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    // All possible JSON Schema types
    // See
    // https://json-schema.org/draft/2020-12/json-schema-validation.html#rfc.section.6.1.1
    std::vector<sourcemeta::jsontoolkit::JSON<std::string>> types{
        sourcemeta::jsontoolkit::JSON<std::string>{"\"null\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"boolean\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"object\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"array\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"string\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"number\""},
        sourcemeta::jsontoolkit::JSON<std::string>{"\"integer\""}};

    schema.assign(keywords::validation::type, std::move(types));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
