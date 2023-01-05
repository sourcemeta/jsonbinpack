namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class BooleanSchema final : public sourcemeta::alterschema::Rule {
public:
  BooleanSchema() : Rule("boolean_schema"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::unordered_map<std::string, bool> &) const
      -> bool override {
    return sourcemeta::jsontoolkit::is_boolean(schema);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const bool current_value{sourcemeta::jsontoolkit::to_boolean(value)};
    sourcemeta::jsontoolkit::make_object(value);
    if (!current_value) {
      sourcemeta::jsontoolkit::assign(document, value, "not",
                                      sourcemeta::jsontoolkit::make_object());
    }
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
