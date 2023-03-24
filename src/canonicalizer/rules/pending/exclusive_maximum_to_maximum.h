namespace sourcemeta::jsonbinpack::canonicalizer {

class ExclusiveMaximumToMaximum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMaximumToMaximum() : Rule("exclusive_maximum_to_maximum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::exclusiveMaximum) &&
           (schema.at(keywords::validation::exclusiveMaximum).is_integer() ||
            schema.at(keywords::validation::exclusiveMaximum).is_real());
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    if (schema.at(keywords::validation::exclusiveMaximum).is_integer()) {
      const std::int64_t maximum =
          schema.at(keywords::validation::exclusiveMaximum).to_integer() - 1;
      if (!schema.defines(keywords::validation::maximum) ||
          (schema.at(keywords::validation::maximum).is_real() &&
           static_cast<long double>(
               schema.at(keywords::validation::maximum).to_real()) > maximum)) {
        schema.assign(keywords::validation::maximum, maximum);
      } else if (schema.at(keywords::validation::maximum).is_integer()) {
        schema.assign(
            keywords::validation::maximum,
            std::min(schema.at(keywords::validation::maximum).to_integer(),
                     maximum));
      }
    } else {
      const double maximum =
          schema.at(keywords::validation::exclusiveMaximum).to_real() - 1.0;
      if (!schema.defines(keywords::validation::maximum) ||
          (schema.at(keywords::validation::maximum).is_integer() &&
           schema.at(keywords::validation::maximum).to_integer() >
               static_cast<long double>(maximum))) {
        schema.assign(keywords::validation::maximum, maximum);
      } else if (schema.at(keywords::validation::maximum).is_real()) {
        schema.assign(
            keywords::validation::maximum,
            std::min(schema.at(keywords::validation::maximum).to_real(),
                     maximum));
      }
    }

    schema.erase(keywords::validation::exclusiveMaximum);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
