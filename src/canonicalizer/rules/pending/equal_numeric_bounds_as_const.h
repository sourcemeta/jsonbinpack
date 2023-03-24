namespace sourcemeta::jsonbinpack::canonicalizer {

class EqualNumericBoundsAsConst final : public sourcemeta::alterschema::Rule {
public:
  EqualNumericBoundsAsConst() : Rule("equal_numeric_bounds_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::minimum) &&
           (schema.at(keywords::validation::minimum).is_integer() ||
            schema.at(keywords::validation::minimum).is_real()) &&
           schema.defines(keywords::validation::maximum) &&
           (schema.at(keywords::validation::maximum).is_integer() ||
            schema.at(keywords::validation::maximum).is_real());
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.assign(keywords::validation::_const,
                  schema.at(keywords::validation::minimum));
    schema.erase(keywords::validation::minimum);
    schema.erase(keywords::validation::maximum);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
