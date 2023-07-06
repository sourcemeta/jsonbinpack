#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

#include <future>    // std::promise, std::future
#include <optional>  // std::optional
#include <stdexcept> // std::runtime_error
#include <string>    // std::string

#include <gtest/gtest.h>

class TestResolver {
public:
  auto operator()(const std::string &identifier)
      -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>> {
    std::promise<std::optional<sourcemeta::jsontoolkit::JSON>> promise;

    if (identifier == "https://www.jsonbinpack.org/draft/unknown") {
      promise.set_value(sourcemeta::jsontoolkit::parse(R"JSON({
        "$schema": "https://www.jsonbinpack.org/draft/unknown",
        "$id": "https://www.jsonbinpack.org/draft/unknown"
      })JSON"));
    } else {
      promise.set_value(std::nullopt);
    }

    return promise.get_future();
  }
};

TEST(Canonicalizer, unsupported_draft) {
  TestResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/draft/unknown",
    "type": "boolean"
  })JSON")};

  EXPECT_THROW(canonicalizer.apply(
                   schema, "https://json-schema.org/draft/2020-12/schema"),
               std::runtime_error);
}

TEST(Canonicalizer, unknown_draft) {
  TestResolver resolver;
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "boolean"
  })JSON")};

  EXPECT_THROW(canonicalizer.apply(schema, "https://example.com/invalid"),
               std::runtime_error);
}
