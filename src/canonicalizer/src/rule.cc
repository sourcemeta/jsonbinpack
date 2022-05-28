#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/schema.h>
#include <sourcemeta/assert.h>
#include <utility> // std::move

sourcemeta::jsonbinpack::canonicalizer::Rule::Rule(std::string name)
    : _name{std::move(name)} {}

auto sourcemeta::jsonbinpack::canonicalizer::Rule::name() const
    -> const std::string & {
  return this->_name;
}

auto sourcemeta::jsonbinpack::canonicalizer::Rule::apply(
    sourcemeta::jsontoolkit::JSON &value) -> bool {

  // A rule cannot be applied to a non-parsed JSON value given
  // that the condition operates on a constant document
  value.parse();

  const sourcemeta::jsontoolkit::Schema schema{value};
  if (this->condition(schema)) {
    this->transform(value);
    value.parse();
    // The condition must always be false after applying the
    // transformation in order to avoid infinite loops
    const sourcemeta::jsontoolkit::Schema new_schema{value};
    sourcemeta::assert::CHECK(
        !this->condition(new_schema),
        "A rule condition must not hold after applying the rule");
    return true;
  }

  return false;
}
