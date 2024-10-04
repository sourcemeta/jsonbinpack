class SingleTypeArray final : public Rule {
public:
  SingleTypeArray()
      : Rule{"single_type_array",
             "Setting `type` to an array of a single type is "
             "the same as directly declaring such type"} {};

  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return contains_any(
               vocabularies,
               {"https://json-schema.org/draft/2020-12/vocab/validation",
                "https://json-schema.org/draft/2019-09/vocab/validation",
                "http://json-schema.org/draft-07/schema#",
                "http://json-schema.org/draft-06/schema#",
                "http://json-schema.org/draft-04/schema#",
                "http://json-schema.org/draft-03/schema#",
                "http://json-schema.org/draft-02/hyper-schema#",
                "http://json-schema.org/draft-01/hyper-schema#",
                "http://json-schema.org/draft-00/hyper-schema#"}) &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_array() && schema.at("type").size() == 1 &&
           schema.at("type").front().is_string();
  }

  auto transform(Transformer &transformer) const -> void override {
    transformer.replace({"type"}, transformer.schema().at("type").front());
  }
};
