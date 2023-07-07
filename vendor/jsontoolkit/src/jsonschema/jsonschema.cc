#include <jsontoolkit/json.h>
#include <jsontoolkit/jsonschema.h>

#include <cassert>     // assert
#include <future>      // std::future
#include <sstream>     // std::ostringstream
#include <stdexcept>   // std::invalid_argument, std::runtime_error
#include <type_traits> // std::remove_reference_t

auto sourcemeta::jsontoolkit::is_schema(
    const sourcemeta::jsontoolkit::Value &schema) -> bool {
  return sourcemeta::jsontoolkit::is_object(schema) ||
         sourcemeta::jsontoolkit::is_boolean(schema);
}

auto sourcemeta::jsontoolkit::id(const sourcemeta::jsontoolkit::Value &schema)
    -> std::optional<std::string> {
  assert(is_schema(schema));
  if (sourcemeta::jsontoolkit::is_object(schema) &&
      sourcemeta::jsontoolkit::defines(schema, "$id")) {
    const sourcemeta::jsontoolkit::Value &id{
        sourcemeta::jsontoolkit::at(schema, "$id")};
    if (!sourcemeta::jsontoolkit::is_string(id) ||
        sourcemeta::jsontoolkit::empty(id)) {
      throw std::invalid_argument("The value of the $id property is not valid");
    }

    return sourcemeta::jsontoolkit::to_string(id);
  }

  return std::nullopt;
}

auto sourcemeta::jsontoolkit::metaschema(
    const sourcemeta::jsontoolkit::Value &schema)
    -> std::optional<std::string> {
  if (!sourcemeta::jsontoolkit::is_schema(schema)) {
    throw std::invalid_argument("The input document is not a valid schema");
  }

  if (sourcemeta::jsontoolkit::is_boolean(schema)) {
    return std::nullopt;
  }

  if (sourcemeta::jsontoolkit::defines(schema, "$schema")) {
    const sourcemeta::jsontoolkit::Value &metaschema{
        sourcemeta::jsontoolkit::at(schema, "$schema")};
    if (!sourcemeta::jsontoolkit::is_string(metaschema) ||
        sourcemeta::jsontoolkit::empty(metaschema)) {
      throw std::invalid_argument(
          "The value of the $schema property is not valid");
    }

    return sourcemeta::jsontoolkit::to_string(metaschema);
  }

  return std::nullopt;
}

auto sourcemeta::jsontoolkit::draft(
    const sourcemeta::jsontoolkit::Value &schema,
    const sourcemeta::jsontoolkit::schema_resolver_t &resolver,
    const std::optional<std::string> &default_metaschema)
    -> std::future<std::optional<std::string>> {
  assert(sourcemeta::jsontoolkit::is_schema(schema));

  const std::optional<std::string> schema_id{
      sourcemeta::jsontoolkit::id(schema)};
  const std::optional<std::string> metaschema_id{
      sourcemeta::jsontoolkit::metaschema(schema)};
  const std::optional<std::string> &effective_metaschema_id{
      metaschema_id.has_value() ? metaschema_id : default_metaschema};

  if (effective_metaschema_id.has_value()) {
    // For compatibility with older JSON Schema drafts that didn't support $id
    if (effective_metaschema_id.value() ==
            "http://json-schema.org/draft-00/hyper-schema#" ||
        effective_metaschema_id.value() ==
            "http://json-schema.org/draft-01/hyper-schema#" ||
        effective_metaschema_id.value() ==
            "http://json-schema.org/draft-02/hyper-schema#" ||
        effective_metaschema_id.value() ==
            "http://json-schema.org/draft-03/schema#" ||
        effective_metaschema_id.value() ==
            "http://json-schema.org/draft-04/schema#") {
      std::promise<std::optional<std::string>> promise;
      promise.set_value(effective_metaschema_id);
      return promise.get_future();
    }

    // If the schema defines itself, then the schema is the draft definition
    if (schema_id.has_value() &&
        schema_id.value() == effective_metaschema_id.value()) {
      std::promise<std::optional<std::string>> promise;
      promise.set_value(schema_id);
      return promise.get_future();
    }
  }

  if (effective_metaschema_id.has_value()) {
    const std::optional<sourcemeta::jsontoolkit::JSON> metaschema{
        resolver(effective_metaschema_id.value()).get()};
    if (!metaschema.has_value()) {
      std::ostringstream error;
      error << "Could not resolve schema: " << effective_metaschema_id.value();
      throw std::runtime_error(error.str());
    }

    return draft(metaschema.value(), resolver, effective_metaschema_id.value());
  }

  std::promise<std::optional<std::string>> promise;
  promise.set_value(std::nullopt);
  return promise.get_future();
}

// TODO: Support every JSON Schema draft from Draft 7 and older
// for completeness, returning the draft itself as the only vocabulary.
static auto core_vocabulary(const std::string &draft) -> std::string {
  if (draft == "https://json-schema.org/draft/2020-12/schema" ||
      draft == "https://json-schema.org/draft/2020-12/hyper-schema") {
    return "https://json-schema.org/draft/2020-12/vocab/core";
  } else if (draft == "https://json-schema.org/draft/2019-09/schema" ||
             draft == "https://json-schema.org/draft/2019-09/hyper-schema") {
    return "https://json-schema.org/draft/2019-09/vocab/core";
  } else {
    std::ostringstream error;
    error << "Unrecognized draft: " << draft;
    throw std::runtime_error(error.str());
  }
}

auto sourcemeta::jsontoolkit::vocabularies(
    const sourcemeta::jsontoolkit::Value &schema,
    const sourcemeta::jsontoolkit::schema_resolver_t &resolver,
    const std::optional<std::string> &default_metaschema)
    -> std::future<std::unordered_map<std::string, bool>> {
  std::promise<std::unordered_map<std::string, bool>> promise;

  // If the meta-schema, as referenced by the schema, is not recognized, or is
  // missing, then the behavior is implementation-defined. If the
  // implementation proceeds with processing the schema, it MUST assume the
  // use of the vocabulary from the core specification.
  // See https://json-schema.org/draft/2020-12/json-schema-core.html#section-8
  std::unordered_map<std::string, bool> result;

  /*
   * (1) Identify the schema's metaschema
   */
  const std::optional<std::string> metaschema_id{
      sourcemeta::jsontoolkit::metaschema(schema)};
  if (!metaschema_id.has_value() && !default_metaschema.has_value()) {
    // If the schema has no declared metaschema and the user didn't
    // provide a explicit default, then we cannot do anything.
    // Better to abort instead of trying to guess.
    throw std::runtime_error(
        "Cannot determine the metaschema of the given schema");
  }
  const std::string &effective_metaschema_id{metaschema_id.has_value()
                                                 ? metaschema_id.value()
                                                 : default_metaschema.value()};

  /*
   * (2) Resolve the metaschema
   */
  std::future<std::optional<sourcemeta::jsontoolkit::JSON>> metaschema_future{
      resolver(effective_metaschema_id)};
  const std::optional<sourcemeta::jsontoolkit::JSON> metaschema{
      metaschema_future.get()};
  if (!metaschema.has_value()) {
    std::ostringstream error;
    error << "Could not resolve schema: " << effective_metaschema_id;
    throw std::runtime_error(error.str());
  }
  const std::optional<std::string> resolved_id{
      sourcemeta::jsontoolkit::id(metaschema.value())};
  if (!resolved_id.has_value() ||
      resolved_id.value() != effective_metaschema_id) {
    std::ostringstream error;
    error << "Resolved metaschema id does not match request: "
          << effective_metaschema_id;
    throw std::runtime_error(error.str());
  }

  /*
   * (3) Resolve the metaschema's draft
   */
  const std::optional<std::string> draft{
      sourcemeta::jsontoolkit::draft(metaschema.value(), resolver,
                                     default_metaschema)
          .get()};
  if (!draft.has_value()) {
    std::ostringstream error;
    error << "Could not determine draft for schema: " << resolved_id.value();
    throw std::runtime_error(error.str());
  }
  const std::string core{core_vocabulary(draft.value())};

  /*
   * (4) Parse the "$vocabulary" keyword, if any
   */
  if (!sourcemeta::jsontoolkit::defines(metaschema.value(), "$vocabulary")) {
    // The core vocabulary is always used
    // See https://json-schema.org/draft/2020-12/json-schema-core.html#section-8
    // See
    // https://datatracker.ietf.org/doc/html/draft-handrews-json-schema-02#section-8
    result.insert({core, true});

    if (draft.value() == "https://json-schema.org/draft/2020-12/schema" ||
        draft.value() == "https://json-schema.org/draft/2020-12/hyper-schema") {
      // See
      // https://json-schema.org/draft/2020-12/json-schema-core.html#section-10
      result.insert(
          {"https://json-schema.org/draft/2020-12/vocab/applicator", true});
      // See
      // https://json-schema.org/draft/2020-12/json-schema-core.html#section-11
      result.insert(
          {"https://json-schema.org/draft/2020-12/vocab/unevaluated", true});
      // See
      // https://json-schema.org/draft/2020-12/json-schema-validation.html#section-6
      result.insert(
          {"https://json-schema.org/draft/2020-12/vocab/validation", true});
      // See
      // https://json-schema.org/draft/2020-12/json-schema-validation.html#section-8
      result.insert(
          {"https://json-schema.org/draft/2020-12/vocab/content", true});
      // See
      // https://json-schema.org/draft/2020-12/json-schema-validation.html#section-9
      result.insert(
          {"https://json-schema.org/draft/2020-12/vocab/meta-data", true});
    } else if (draft.value() ==
                   "https://json-schema.org/draft/2019-09/schema" ||
               draft.value() ==
                   "https://json-schema.org/draft/2019-09/hyper-schema") {
      // See
      // https://datatracker.ietf.org/doc/html/draft-handrews-json-schema-02#section-9
      result.insert(
          {"https://json-schema.org/draft/2019-09/vocab/applicator", true});
      // See
      // https://datatracker.ietf.org/doc/html/draft-handrews-json-schema-validation-02#section-6
      result.insert(
          {"https://json-schema.org/draft/2019-09/vocab/validation", true});
      // The Format vocabulary is optional by default
      // See
      // https://datatracker.ietf.org/doc/html/draft-handrews-json-schema-validation-02#section-7
      result.insert(
          {"https://json-schema.org/draft/2019-09/vocab/format", false});
      // See
      // https://datatracker.ietf.org/doc/html/draft-handrews-json-schema-validation-02#section-8
      result.insert(
          {"https://json-schema.org/draft/2019-09/vocab/content", true});
      // See
      // https://datatracker.ietf.org/doc/html/draft-handrews-json-schema-validation-02#section-9
      result.insert(
          {"https://json-schema.org/draft/2019-09/vocab/meta-data", true});
    }

    promise.set_value(result);
    return promise.get_future();
  }

  const sourcemeta::jsontoolkit::Value &vocabulary_value{
      sourcemeta::jsontoolkit::at(metaschema.value(), "$vocabulary")};

  // Handle core vocabulary edge cases
  if (!sourcemeta::jsontoolkit::defines(vocabulary_value, core)) {
    throw std::runtime_error(
        "Every metaschema must declare the core vocabulary");
  } else if (!sourcemeta::jsontoolkit::to_boolean(
                 sourcemeta::jsontoolkit::at(vocabulary_value, core))) {
    throw std::runtime_error("The core vocabulary must be marked as required");
  }

  for (auto iterator = sourcemeta::jsontoolkit::cbegin_object(vocabulary_value);
       iterator != sourcemeta::jsontoolkit::cend_object(vocabulary_value);
       iterator++) {
    result.insert({sourcemeta::jsontoolkit::key(*iterator),
                   sourcemeta::jsontoolkit::to_boolean(
                       sourcemeta::jsontoolkit::value(*iterator))});
  }

  promise.set_value(result);
  return promise.get_future();
}

auto sourcemeta::jsontoolkit::subschema_iterator(
    const sourcemeta::jsontoolkit::Value &schema,
    const sourcemeta::jsontoolkit::schema_walker_t &walker,
    const sourcemeta::jsontoolkit::schema_resolver_t &resolver,
    const std::optional<std::string> &default_metaschema)
    -> SchemaWalker<std::remove_reference_t<decltype(schema)>> {
  return {schema, walker, resolver, default_metaschema,
          sourcemeta::jsontoolkit::schema_walker_type_t::Deep};
}

auto sourcemeta::jsontoolkit::flat_subschema_iterator(
    const sourcemeta::jsontoolkit::Value &schema,
    const sourcemeta::jsontoolkit::schema_walker_t &walker,
    const sourcemeta::jsontoolkit::schema_resolver_t &resolver,
    const std::optional<std::string> &default_metaschema)
    -> SchemaWalker<std::remove_reference_t<decltype(schema)>> {
  return {schema, walker, resolver, default_metaschema,
          sourcemeta::jsontoolkit::schema_walker_type_t::Flat};
}

auto sourcemeta::jsontoolkit::flat_subschema_iterator(
    sourcemeta::jsontoolkit::Value &schema,
    const sourcemeta::jsontoolkit::schema_walker_t &walker,
    const sourcemeta::jsontoolkit::schema_resolver_t &resolver,
    const std::optional<std::string> &default_metaschema)
    -> SchemaWalker<std::remove_reference_t<decltype(schema)>> {
  return {schema, walker, resolver, default_metaschema,
          sourcemeta::jsontoolkit::schema_walker_type_t::Flat};
}
