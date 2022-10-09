#include <jsontoolkit/schema.h>

#include <gtest/gtest.h>
#include <stdexcept> // std::invalid_argument

TEST(Schema, is_schema_true_object) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  document.parse();
  EXPECT_TRUE(sourcemeta::jsontoolkit::schema::is_schema(document));
}

TEST(Schema, is_schema_false_object) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "type": "object"
  })JSON");

  document.parse();
  EXPECT_FALSE(sourcemeta::jsontoolkit::schema::is_schema(document));
}

TEST(Schema, is_schema_true_boolean_true) {
  sourcemeta::jsontoolkit::JSON<std::string> document("true");
  document.parse();
  EXPECT_TRUE(sourcemeta::jsontoolkit::schema::is_schema(document));
}

TEST(Schema, is_schema_true_boolean_false) {
  sourcemeta::jsontoolkit::JSON<std::string> document("false");
  document.parse();
  EXPECT_TRUE(sourcemeta::jsontoolkit::schema::is_schema(document));
}

TEST(Schema, is_schema_false_array) {
  sourcemeta::jsontoolkit::JSON<std::string> document("[]");
  document.parse();
  EXPECT_FALSE(sourcemeta::jsontoolkit::schema::is_schema(document));
}

TEST(Schema, default_2020_12_has_vocabulary_core) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON");

  document.parse();
  EXPECT_TRUE(sourcemeta::jsontoolkit::schema::has_vocabulary(
      document, "https://json-schema.org/draft/2020-12/vocab/core"));
}

TEST(Schema, is_schema_not_parsed) {
  sourcemeta::jsontoolkit::JSON<std::string> document(R"JSON({
    "type": "object"
  })JSON");

  EXPECT_THROW(sourcemeta::jsontoolkit::schema::is_schema(document),
               std::runtime_error);
}
