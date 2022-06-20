#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class NullAsConst final : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  NullAsConst() : Rule("null_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type") == "null";
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    schema.assign("const", sourcemeta::jsontoolkit::JSON<std::string>{nullptr});
    schema.erase("type");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
