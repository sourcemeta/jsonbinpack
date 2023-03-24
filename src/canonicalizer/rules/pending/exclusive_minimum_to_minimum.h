namespace sourcemeta::jsonbinpack::canonicalizer {

class ExclusiveMinimumToMinimum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMinimumToMinimum() : Rule("exclusive_minimum_to_minimum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::exclusiveMinimum) &&
           (schema.at(keywords::validation::exclusiveMinimum).is_integer() ||
            schema.at(keywords::validation::exclusiveMinimum).is_real());
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    if (schema.at(keywords::validation::exclusiveMinimum).is_integer()) {
      const std::int64_t minimum =
          schema.at(keywords::validation::exclusiveMinimum).to_integer() + 1;
      if (!schema.defines(keywords::validation::minimum) ||
          (schema.at(keywords::validation::minimum).is_real() &&
           static_cast<long double>(
               schema.at(keywords::validation::minimum).to_real()) < minimum)) {
        schema.assign(keywords::validation::minimum, minimum);
      } else if (schema.at(keywords::validation::minimum).is_integer()) {
        schema.assign(
            keywords::validation::minimum,
            std::max(schema.at(keywords::validation::minimum).to_integer(),
                     minimum));
      }
    } else {
      const double minimum =
          schema.at(keywords::validation::exclusiveMinimum).to_real() + 1.0;
      if (!schema.defines(keywords::validation::minimum) ||
          (schema.at(keywords::validation::minimum).is_integer() &&
           schema.at(keywords::validation::minimum).to_integer() <
               static_cast<long double>(minimum))) {
        schema.assign(keywords::validation::minimum, minimum);
      } else if (schema.at(keywords::validation::minimum).is_real()) {
        schema.assign(
            keywords::validation::minimum,
            std::max(schema.at(keywords::validation::minimum).to_real(),
                     minimum));
      }
    }

    schema.erase(keywords::validation::exclusiveMinimum);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
