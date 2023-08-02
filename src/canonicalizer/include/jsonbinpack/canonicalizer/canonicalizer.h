#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_CANONICALIZER_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_CANONICALIZER_H_

/// @defgroup canonicalizer Canonicalizer
/// @brief A canonicalization rule is expressed using set theory
/// notation. Each rule is expressed as \f$\frac{Condition}{Transformation}\f$,
/// where the given transformation only applies if the condition holds true. In
/// this notation, \f$S\f$ corresponds to the schema in question. After a
/// transformation takes place, its condition must not hold anymore.
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

#include <alterschema/bundle.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/jsonschema.h>

#include <string> // std::string

namespace sourcemeta::jsonbinpack {

/// @ingroup canonicalizer
class Canonicalizer {
public:
  Canonicalizer(const sourcemeta::jsontoolkit::schema_resolver_t &resolver);
  auto apply(sourcemeta::jsontoolkit::JSON &document,
             sourcemeta::jsontoolkit::Value &value,
             const std::string &default_metaschema) const -> void;

  // For convenience
  inline auto apply(sourcemeta::jsontoolkit::JSON &document,
                    const std::string &default_metaschema) const -> void {
    return apply(document, document, default_metaschema);
  }

private:
  sourcemeta::alterschema::Bundle bundle;
};

} // namespace sourcemeta::jsonbinpack

#endif
