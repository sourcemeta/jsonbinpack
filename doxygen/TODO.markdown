Status
======

JSON BinPack is under heavy development. This page aims to document what's
missing. If you want to fund JSON BinPack's development, please consider
[becoming a sponsor](https://github.com/sponsors/sourcemeta).

Canonicalizer
-------------

These are documented and implemented in @ref canonicalizer.

| Rule                                                                        | Category                                | Notes                  |
|-----------------------------------------------------------------------------|-----------------------------------------|------------------------|
| @ref sourcemeta::jsonbinpack::canonicalizer::MinPropertiesRequiredTautology | @ref canonicalizer_rules_simplification | Missing documentation  |
| @ref sourcemeta::jsonbinpack::canonicalizer::MinPropertiesRequiredTautology | @ref canonicalizer_rules_simplification | Resolve known bugs     |
| @ref sourcemeta::jsonbinpack::canonicalizer::TypeUnionAnyOf                 | @ref canonicalizer_rules_heterogeneous  | Missing documentation  |
| @ref sourcemeta::jsonbinpack::canonicalizer::TypeUnionAnyOf                 | @ref canonicalizer_rules_heterogeneous  | Resolve known bugs     |
| SchemaBundling                                                              | @ref canonicalizer_rules_simplification | Missing implementation |

Encodings
---------

These are declared and document in @ref encoding, and implemented in @ref
encoder and and @ref decoder.

| Encoding                                                      | Type                 | Notes                  |
|---------------------------------------------------------------|----------------------|------------------------|
| @ref sourcemeta::jsonbinpack::ANY_PACKED_TYPE_TAG_BYTE_PREFIX | @ref encoding_any    | Missing documentation  |
| `ONEOF_CHOICE_INDEX_PREFIX`                                   | @ref encoding_any    | Missing implementation |
| `BOUNDED_TYPED_LENGTH_PREFIX`                                 | @ref encoding_array  | Missing implementation |
| `REQUIRED_ONLY_BOUNDED_TYPED_OBJECT`                          | @ref encoding_object | Missing implementation |
| `NON_REQUIRED_BOUNDED_TYPED_OBJECT`                           | @ref encoding_object | Missing implementation |
| `MIXED_BOUNDED_TYPED_OBJECT`                                  | @ref encoding_object | Missing implementation |
| `REQUIRED_UNBOUNDED_TYPED_OBJECT`                             | @ref encoding_object | Missing implementation |
| `OPTIONAL_UNBOUNDED_TYPED_OBJECT`                             | @ref encoding_object | Missing implementation |
| `MIXED_UNBOUNDED_TYPED_OBJECT`                                | @ref encoding_object | Missing implementation |
| `PACKED_BOUNDED_REQUIRED_OBJECT`                              | @ref encoding_object | Missing implementation |
| `PACKED_UNBOUNDED_OBJECT`                                     | @ref encoding_object | Missing implementation |
| `URL_PROTOCOL_HOST_REST`                                      | @ref encoding_string | Missing implementation |
| `STRING_BROTLI`                                               | @ref encoding_string | Missing implementation |
| `STRING_DICTIONARY_COMPRESSOR`                                | @ref encoding_string | Missing implementation |

Mapper
------

These are documented and implemented in @ref mapper.

| Category | Status                           |
|----------|----------------------------------|
| Any      | Partial. Does not handle `oneOf` |
| Array    | Missing implementation           |
| Object   | Missing implementation           |
| String   | Missing implementation           |

JSON Schema keywords
--------------------

A set of remaining keywords that JSON BinPack is expected to cover, without
which a schema-less encoding is often unacceptable.

| Keyword                 | Vocabulary  | Dialect |
|-------------------------|-------------|---------|
| `$ref`                  | Core        | 2020-12 |
| `$anchor`               | Core        | 2020-12 |
| `$dynamicRef`           | Core        | 2020-12 |
| `$dynamicAnchor`        | Core        | 2020-12 |
| `allOf`                 | Applicator  | 2020-12 |
| `anyOf`                 | Applicator  | 2020-12 |
| `oneOf`                 | Applicator  | 2020-12 |
| `if`                    | Applicator  | 2020-12 |
| `then`                  | Applicator  | 2020-12 |
| `else`                  | Applicator  | 2020-12 |
| `not`                   | Applicator  | 2020-12 |
| `propertyNames`         | Applicator  | 2020-12 |
| `dependentSchemas`      | Applicator  | 2020-12 |
| `unevaluatedProperties` | Unevaluated | 2020-12 |
| `unevaluatedItems`      | Unevaluated | 2020-12 |
| `contentSchema`         | Content     | 2020-12 |
| `contentMediaType`      | Content     | 2020-12 |
| `contentEncoding`       | Content     | 2020-12 |

Other
-----

- Support for recursive schemas
- Make JSON BinPack installable and findable using CMake
- Deploy an online web playground
