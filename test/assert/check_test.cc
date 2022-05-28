#include <gtest/gtest.h>
#include <sourcemeta/assert.h>
#include <stdexcept> // std::runtime_error

TEST(Check, fail_runtime_error) {
  EXPECT_THROW(sourcemeta::assert::CHECK(1 == 0, "My error"),
               std::runtime_error);
}

TEST(Check, fail_message) {
  try {
    sourcemeta::assert::CHECK(1 == 0, "My error");
  } catch (const std::runtime_error &error) {
    const std::string message{error.what()};
    EXPECT_EQ(message, "My error");
  }
}

TEST(Check, pass) {
  EXPECT_NO_THROW(sourcemeta::assert::CHECK(1 == 1, "My error"));
}
