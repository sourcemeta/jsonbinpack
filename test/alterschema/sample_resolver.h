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

    if (identifier == "https://jsonbinpack.sourcemeta.com/test-metaschema-1") {
      promise.set_value(sourcemeta::jsontoolkit::parse(R"JSON({
        "$id": "https://jsonbinpack.sourcemeta.com/test-metaschema-1",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$vocabulary": {
          "https://json-schema.org/draft/2020-12/vocab/core": true,
          "https://jsonbinpack.sourcemeta.com/vocab/test": true
        }
      })JSON"));
      return promise.get_future();
    }

    const std::optional<sourcemeta::jsontoolkit::JSON> result{
        this->resolver(identifier).get()};
    if (result.has_value()) {
      promise.set_value(sourcemeta::jsontoolkit::from(result.value()));
    } else {
      promise.set_value(std::nullopt);
    }

    return promise.get_future();
  }

private:
  sourcemeta::jsontoolkit::DefaultResolver resolver;
};

#endif
