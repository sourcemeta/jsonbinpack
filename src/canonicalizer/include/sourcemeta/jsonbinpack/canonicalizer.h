#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_H_

/// @defgroup canonicalizer Canonicalizer
/// @brief A pure and deterministic function that simplifies a JSON Schema
/// definition to ease the static analysis process
///
/// JSON Schema is a particularly expressive and complex schema language. To
/// mitigate such complexity in the context of static analysis, the
/// *Canonicalizer* component is a total function that maps JSON Schema
/// definitions to equivalent but simpler JSON Schema definitions according to a
/// set formal transformations. The concept of simplifying JSON Schema
/// definitions based on formal transformations for static analysis purposes was
/// originally introduced by [Type Safety with JSON
/// Subschema](https://arxiv.org/abs/1911.12651). We extend their work by
/// modernizing and extending their set of canonicalization rules.
///
/// @image html c4-jsonbinpack-canonicalizer.png width=80%
///
/// The canonicalizer repeatedly applies the set of defined canonizalization
/// transformations rules to every subschema of a given JSON Schema definition
/// until no more transformations are possible. A JSON Schema definition that
/// cannot be further modified by any canonizalization rule is considered to be
/// a *Canonical JSON Schema*. In order to prevent an infinite loop in the
/// canonizalization algorithm, canonizalization rules do not conflict with each
/// other and the pre-condition of a given canonizalization rule does not hold
/// after such canonizalization rule has been applied to the schema.
///
/// Inspired by the notation introduced by [Type Safety with JSON
/// Subschema](https://arxiv.org/abs/1911.12651), each canonizalization rule is
/// defined using the form \f$\frac{Condition}{Transformation}\f$ where \f$S\f$
/// corresponds to the JSON Schema in question.
///
/// @see mapper
//
/// @defgroup canonicalizer_rules_syntax_sugar Syntax Sugar
/// @brief Syntax sugar canonicalization rules aim to simplify the
/// keywords of JSON Schema that JSON BinPack has to deal with.
/// A canonicalization rule is considered to be part of this category
/// if the semantics of the schema can be expressed using simpler keywords.
/// @ingroup canonicalizer
///
/// @defgroup canonicalizer_rules_superfluous Superfluous Keywords
/// @brief Superfluous keywords canonicalization rules aim to remove
/// keywords that are not providing any value to the given schema.
/// A canonicalization rule is considered to be part of this category
/// if the semantics of the schema remain the same after removing
/// a certain keyword.
/// @ingroup canonicalizer
///
/// @defgroup canonicalizer_rules_heterogeneous Heterogeneous Schemas
/// @brief Heterogeneous schemas canonicalization rules aim to simplify
/// schemas by ensuring that any subschema only applies to one and only
/// one JSON data type. A canonicalization rule is considered to be part
/// of this category if it is about turning heterogeneous schemas into
/// homogeneous schemas.
/// @ingroup canonicalizer
///
/// @defgroup canonicalizer_rules_implicit Implicit Constraints
/// @brief Implicit constraints canonicalization rules aim to surface
/// constraints that might apply without the schema reader realizing
/// that this is the case. A canonicalization rule is considered to be
/// part of this category if it is about making implicit constraints
/// explicit.
/// @ingroup canonicalizer
///
/// @defgroup canonicalizer_rules_simplification Schema Simplification
/// @brief Schema simplification canonicalization rules aim to reduce
/// the complexity of schemas by representing the current constraints
/// in a different, simpler manner. A canonicalization rule is considered
/// to be part of this category if it is about applying complex
/// transformations for simplification purposes.
/// @ingroup canonicalizer

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <optional> // std::optional
#include <string>   // std::string

namespace sourcemeta::jsonbinpack {

/// @ingroup canonicalizer
class Canonicalizer {
public:
  /// Create a Canonicalizer object
  Canonicalizer();

  /// Canonicalize the given JSON Schema
  auto apply(sourcemeta::jsontoolkit::JSON &document,
             const sourcemeta::jsontoolkit::SchemaWalker &walker,
             const sourcemeta::jsontoolkit::SchemaResolver &resolver,
             const std::optional<std::string> &default_dialect) const -> void;

private:
  sourcemeta::jsontoolkit::SchemaTransformBundle bundle;
};

} // namespace sourcemeta::jsonbinpack

#endif
