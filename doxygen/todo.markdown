Status
======

JSON BinPack is under heavy development. This page aims to document what's
missing. If you want to fund JSON BinPack's development, please consider
[becoming a sponsor](https://github.com/sponsors/sourcemeta).

Canonicalizer
-------------

Defined in @ref compiler.

- `TypeUnionAnyOf`: Resolve known bugs
- Perform JSON Schema bundling

Mapper
------

Defined in @ref compiler.

| Category | Status                           |
|----------|----------------------------------|
| Any      | Partial. Does not handle `oneOf` |
| Array    | Missing implementation           |
| Object   | Missing implementation           |
| String   | Missing implementation           |

Encodings
---------

Defined in @ref runtime.

| Encoding                             | Type             | Notes                  |
|--------------------------------------|------------------|------------------------|
| `ONEOF_CHOICE_INDEX_PREFIX`          | @ref plan_any    | Missing implementation |
| `BOUNDED_TYPED_LENGTH_PREFIX`        | @ref plan_array  | Missing implementation |
| `REQUIRED_ONLY_BOUNDED_TYPED_OBJECT` | @ref plan_object | Missing implementation |
| `NON_REQUIRED_BOUNDED_TYPED_OBJECT`  | @ref plan_object | Missing implementation |
| `MIXED_BOUNDED_TYPED_OBJECT`         | @ref plan_object | Missing implementation |
| `REQUIRED_UNBOUNDED_TYPED_OBJECT`    | @ref plan_object | Missing implementation |
| `OPTIONAL_UNBOUNDED_TYPED_OBJECT`    | @ref plan_object | Missing implementation |
| `MIXED_UNBOUNDED_TYPED_OBJECT`       | @ref plan_object | Missing implementation |
| `PACKED_BOUNDED_REQUIRED_OBJECT`     | @ref plan_object | Missing implementation |
| `PACKED_UNBOUNDED_OBJECT`            | @ref plan_object | Missing implementation |
| `URL_PROTOCOL_HOST_REST`             | @ref plan_string | Missing implementation |
| `STRING_BROTLI`                      | @ref plan_string | Missing implementation |
| `STRING_DICTIONARY_COMPRESSOR`       | @ref plan_string | Missing implementation |

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
- Deploy an online web playground
