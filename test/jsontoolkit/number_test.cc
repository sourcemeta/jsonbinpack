#include <gtest/gtest.h>
#include <jsontoolkit/json.h>

TEST(Number, default_constructor) {
  sourcemeta::jsontoolkit::Number document;
  EXPECT_TRUE(document.is_integer());
  EXPECT_EQ(document.integer_value(), 0);
}

TEST(Number, string_integer_zero) {
  sourcemeta::jsontoolkit::JSON document{"0"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), 0);
}

TEST(Number, string_integer_positive_single_digit_integer) {
  sourcemeta::jsontoolkit::JSON document{"3"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), 3);
}

TEST(Number, string_integer_negative_single_digit_integer) {
  sourcemeta::jsontoolkit::JSON document{"-3"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), -3);
}

TEST(Number, string_integer_positive_long_integer) {
  sourcemeta::jsontoolkit::JSON document{"12345"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), 12345);
}

TEST(Number, string_integer_negative_long_integer) {
  sourcemeta::jsontoolkit::JSON document{"-12345"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), -12345);
}

TEST(Number, string_integer_minus_zero) {
  sourcemeta::jsontoolkit::JSON document{"-0"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), 0);
}

TEST(Number, invalid_string_integer_trailing_minus) {
  sourcemeta::jsontoolkit::JSON document{"-0-"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, invalid_string_integer_trailing_character) {
  sourcemeta::jsontoolkit::JSON document{"-0x"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, invalid_minus_in_between_integer) {
  sourcemeta::jsontoolkit::JSON document{"123-45"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, invalid_double_minus) {
  sourcemeta::jsontoolkit::JSON document{"--123"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, two_zeroes) {
  sourcemeta::jsontoolkit::JSON document{"00"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, multiple_zeroes) {
  sourcemeta::jsontoolkit::JSON document{"000"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, leading_zero_with_one_digit_integer) {
  sourcemeta::jsontoolkit::JSON document{"01"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, leading_zero_with_two_digits_integer) {
  sourcemeta::jsontoolkit::JSON document{"012"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, leading_period) {
  sourcemeta::jsontoolkit::JSON document{".0"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, trailing_period) {
  sourcemeta::jsontoolkit::JSON document{"0."};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, trailing_period_and_minus) {
  sourcemeta::jsontoolkit::JSON document{"0.-"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, double_minus_at_start) {
  sourcemeta::jsontoolkit::JSON document{"--5"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, leading_minus_and_period) {
  sourcemeta::jsontoolkit::JSON document{"-.0"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, trailing_zero_positive) {
  sourcemeta::jsontoolkit::JSON document{"1.50000"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1.5);
}

TEST(Number, trailing_zero_negative) {
  sourcemeta::jsontoolkit::JSON document{"-1.50000"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1.5);
}

TEST(Number, single_left_digit_positive_real) {
  sourcemeta::jsontoolkit::JSON document{"1.5"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1.5);
}

TEST(Number, single_left_digit_negative_real) {
  sourcemeta::jsontoolkit::JSON document{"-1.5"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1.5);
}

TEST(Number, leading_decimal_zero) {
  sourcemeta::jsontoolkit::JSON document{"1.0005"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1.0005);
}

TEST(Number, multi_left_digit_positive_real) {
  sourcemeta::jsontoolkit::JSON document{"1234.5"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1234.5);
}

TEST(Number, multi_left_digit_negative_real) {
  sourcemeta::jsontoolkit::JSON document{"-1234.5"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1234.5);
}

TEST(Number, long_positive_real) {
  sourcemeta::jsontoolkit::JSON document{"1234.56789"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1234.56789);
}

TEST(Number, long_negative_real) {
  sourcemeta::jsontoolkit::JSON document{"-1234.56789"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1234.56789);
}

TEST(Number, multiple_sibling_periods) {
  sourcemeta::jsontoolkit::JSON document{"123..56"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, multiple_separate_periods) {
  sourcemeta::jsontoolkit::JSON document{"12.34.56"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, single_digit_positive_real_integer) {
  sourcemeta::jsontoolkit::JSON document{"1.0"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1.0);
}

TEST(Number, single_digit_positive_real_integer_trailing_zero) {
  sourcemeta::jsontoolkit::JSON document{"1.0000000"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1.0);
}

TEST(Number, single_digit_negative_real_integer) {
  sourcemeta::jsontoolkit::JSON document{"-1.0"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1.0);
}

TEST(Number, single_digit_negative_real_integer_trailing_zero) {
  sourcemeta::jsontoolkit::JSON document{"-1.0000000"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1.0);
}
