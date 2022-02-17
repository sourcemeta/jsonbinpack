#include <gtest/gtest.h>
#include <stdexcept> // std::domain_error
#include <jsontoolkit/json.h>

TEST(Null, nullptr) {
  sourcemeta::jsontoolkit::JSON document {nullptr};
  EXPECT_TRUE(document.is_null());
}

TEST(Null, valid) {
  sourcemeta::jsontoolkit::JSON document {"null"};
  EXPECT_TRUE(document.is_null());
}

TEST(Null, valid_with_padding) {
  sourcemeta::jsontoolkit::JSON document {"   null   "};
  EXPECT_TRUE(document.is_null());
}

TEST(Null, incomplete_1) {
  sourcemeta::jsontoolkit::JSON document {"nul"};
  EXPECT_THROW(document.is_null(), std::domain_error);
}

TEST(Null, incomplete_2) {
  sourcemeta::jsontoolkit::JSON document {"nu"};
  EXPECT_THROW(document.is_null(), std::domain_error);
}

TEST(Null, incomplete_3) {
  sourcemeta::jsontoolkit::JSON document {"n"};
  EXPECT_THROW(document.is_null(), std::domain_error);
}
