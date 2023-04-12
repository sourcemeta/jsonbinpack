#include <alterschema/rule.h>

#include <sstream>   // std::ostringstream
#include <stdexcept> // std::runtime_error

auto sourcemeta::alterschema::Rule::operator==(
    const sourcemeta::alterschema::Rule &other) const -> bool {
  return this->name() == other.name();
}

auto sourcemeta::alterschema::Rule::operator!=(
    const sourcemeta::alterschema::Rule &other) const -> bool {
  return !this->operator==(other);
}

auto sourcemeta::alterschema::Rule::name() const -> const std::string & {
  return this->name_;
}

auto sourcemeta::alterschema::Rule::apply(
    sourcemeta::jsontoolkit::JSON &document,
    sourcemeta::jsontoolkit::Value &value, const std::string &dialect,
    const std::unordered_map<std::string, bool> &vocabularies,
    const std::size_t level) const -> bool {
  if (!this->condition(value, dialect, vocabularies, level)) {
    return false;
  }

  this->transform(document, value);

  // The condition must always be false after applying the
  // transformation in order to avoid infinite loops
  if (this->condition(value, dialect, vocabularies, level)) {
    std::ostringstream error;
    error << "Rule condition holds after application: " << this->name();
    throw std::runtime_error(error.str());
  }

  return true;
}
