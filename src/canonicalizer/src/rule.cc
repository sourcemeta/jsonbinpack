#include <jsonbinpack/canonicalizer/rule.h>
#include <stdexcept>
#include <utility> // std::move

sourcemeta::jsonbinpack::canonicalizer::Rule::Rule(std::string name)
    : _name{std::move(name)} {}

auto sourcemeta::jsonbinpack::canonicalizer::Rule::name() const
    -> const std::string & {
  return this->_name;
}

auto sourcemeta::jsonbinpack::canonicalizer::Rule::apply(
    sourcemeta::jsontoolkit::JSON<std::string> &value) const -> bool {

  // A rule cannot be applied to a non-parsed JSON value given
  // that the condition operates on a constant document
  value.parse();

  if (this->condition(value)) {
    this->transform(value);
    value.parse();

    // The condition must always be false after applying the
    // transformation in order to avoid infinite loops
    if (this->condition(value)) {
      throw std::runtime_error(
          "A rule condition must not hold after applying the rule");
    }

    return true;
  }

  return false;
}
