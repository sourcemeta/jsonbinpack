class MinPropertiesImplicit final : public Rule {
public:
  MinPropertiesImplicit()
      : Rule{"min_properties_implicit",
             "The `minProperties` keyword has a logical default of 0 or the "
             "size of `required`"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema, const std::string &,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return contains_any(
               vocabularies,
               {"https://json-schema.org/draft/2020-12/vocab/validation",
                "https://json-schema.org/draft/2019-09/vocab/validation",
                "http://json-schema.org/draft-07/schema#",
                "http://json-schema.org/draft-06/schema#",
                "http://json-schema.org/draft-04/schema#"}) &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           schema.at("type").to_string() == "object" &&
           !schema.defines("minProperties");
  }

  auto transform(Transformer &transformer) const -> void override {
    if (transformer.schema().defines("required") &&
        transformer.schema().at("required").is_array()) {
      transformer.assign("minProperties",
                         sourcemeta::jsontoolkit::JSON{
                             transformer.schema().at("required").size()});
    } else {
      transformer.assign("minProperties", sourcemeta::jsontoolkit::JSON{0});
    }
  }
};
