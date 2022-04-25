#include <gtest/gtest.h>
#include <jsontoolkit/schema.h>
#include <stdexcept> // std::invalid_argument

TEST(Schema, is_schema_true_object) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  document.parse();
  EXPECT_TRUE(sourcemeta::jsontoolkit::Schema::is_schema(document));
  sourcemeta::jsontoolkit::Schema schema{document};
}

TEST(Schema, is_schema_false_object) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "type": "object"
  })JSON");

  document.parse();
  EXPECT_FALSE(sourcemeta::jsontoolkit::Schema::is_schema(document));
  EXPECT_THROW(sourcemeta::jsontoolkit::Schema{document},
               std::invalid_argument);
}

TEST(Schema, is_schema_true_boolean_true) {
  sourcemeta::jsontoolkit::JSON document("true");
  document.parse();
  EXPECT_TRUE(sourcemeta::jsontoolkit::Schema::is_schema(document));
  sourcemeta::jsontoolkit::Schema schema{document};
}

TEST(Schema, is_schema_true_boolean_false) {
  sourcemeta::jsontoolkit::JSON document("false");
  document.parse();
  EXPECT_TRUE(sourcemeta::jsontoolkit::Schema::is_schema(document));
  sourcemeta::jsontoolkit::Schema schema{document};
}

TEST(Schema, is_schema_false_array) {
  sourcemeta::jsontoolkit::JSON document("[]");
  document.parse();
  EXPECT_FALSE(sourcemeta::jsontoolkit::Schema::is_schema(document));
  EXPECT_THROW(sourcemeta::jsontoolkit::Schema{document},
               std::invalid_argument);
}

TEST(Schema, default_2020_12_has_vocabulary_core) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  document.parse();
  sourcemeta::jsontoolkit::Schema schema{document};
  EXPECT_TRUE(schema.has_vocabulary(
      "https://json-schema.org/draft/2020-12/vocab/core"));
}

TEST(Schema, is_schema_not_parsed) {
  sourcemeta::jsontoolkit::JSON document(R"JSON({
    "type": "object"
  })JSON");

  EXPECT_THROW(sourcemeta::jsontoolkit::Schema::is_schema(document),
               std::logic_error);
  EXPECT_THROW(sourcemeta::jsontoolkit::Schema{document}, std::logic_error);
}
