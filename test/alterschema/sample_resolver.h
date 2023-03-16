#ifndef SOURCEMETA_TEST_ALTERSCHEMA_SAMPLE_RESOLVER_H_
#define SOURCEMETA_TEST_ALTERSCHEMA_SAMPLE_RESOLVER_H_

#include <jsontoolkit/json.h>

#include <future>   // std::promise, std::future
#include <optional> // std::optional
#include <string>   // std::string

class SampleResolver {
public:
  auto operator()(const std::string &identifier)
      -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>> {
    std::promise<std::optional<sourcemeta::jsontoolkit::JSON>> promise;

    if (identifier == "https://jsonbinpack.org/test-metaschema-1") {
      promise.set_value(sourcemeta::jsontoolkit::parse(R"JSON({
        "$id": "https://jsonbinpack.org/test-metaschema-1",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://jsonbinpack.org/vocab/test": true
        }
      })JSON"));
    } else if (identifier == "https://json-schema.org/draft/2020-12/schema") {
      promise.set_value(sourcemeta::jsontoolkit::parse(R"JSON({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$id": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://json-schema.org/draft/2020-12/vocab/applicator": true,
          "https://json-schema.org/draft/2020-12/vocab/unevaluated": true,
          "https://json-schema.org/draft/2020-12/vocab/validation": true,
          "https://json-schema.org/draft/2020-12/vocab/meta-data": true,
          "https://json-schema.org/draft/2020-12/vocab/format-annotation": true,
          "https://json-schema.org/draft/2020-12/vocab/content": true
        },
        "$dynamicAnchor": "meta",
        "title": "Core and Validation specifications meta-schema",
        "allOf": [
          {"$ref": "meta/core"},
          {"$ref": "meta/applicator"},
          {"$ref": "meta/unevaluated"},
          {"$ref": "meta/validation"},
          {"$ref": "meta/meta-data"},
          {"$ref": "meta/format-annotation"},
          {"$ref": "meta/content"}
        ],
        "type": ["object", "boolean"],
        "properties": {
          "definitions": {
            "type": "object",
            "additionalProperties": { "$dynamicRef": "#meta" },
            "deprecated": true,
            "default": {}
          },
          "dependencies": {
            "type": "object",
            "additionalProperties": {
                "anyOf": [
                    { "$dynamicRef": "#meta" },
                    { "$ref": "meta/validation#/$defs/stringArray" }
                ]
            },
            "deprecated": true,
            "default": {}
          },
          "$recursiveAnchor": {
            "$ref": "meta/core#/$defs/anchorString",
            "deprecated": true
          },
          "$recursiveRef": {
            "$ref": "meta/core#/$defs/uriReferenceString",
            "deprecated": true
          }
        }
      })JSON"));
    } else {
      promise.set_value(std::nullopt);
    }

    return promise.get_future();
  }
};

#endif
