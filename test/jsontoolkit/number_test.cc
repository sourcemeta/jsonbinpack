#include <gtest/gtest.h>
#include <jsontoolkit/json.h>

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

// Invalid exponential numbers

TEST(Number, exponential_notation_error_double_upper_e) {
  sourcemeta::jsontoolkit::JSON document{"3EE2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_double_lower_e) {
  sourcemeta::jsontoolkit::JSON document{"3ee2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_double_mixed_e) {
  sourcemeta::jsontoolkit::JSON document{"3eE2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_trailing_upper_e) {
  sourcemeta::jsontoolkit::JSON document{"3E"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_trailing_lower_e) {
  sourcemeta::jsontoolkit::JSON document{"3e"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_trailing_upper_e_minus) {
  sourcemeta::jsontoolkit::JSON document{"3E-"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_trailing_lower_e_minus) {
  sourcemeta::jsontoolkit::JSON document{"3e-"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_leading_upper_e) {
  sourcemeta::jsontoolkit::JSON document{"E2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_leading_lower_e) {
  sourcemeta::jsontoolkit::JSON document{"e2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_minus_leading_upper_e) {
  sourcemeta::jsontoolkit::JSON document{"-E2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_minus_leading_lower_e) {
  sourcemeta::jsontoolkit::JSON document{"-e2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_double_e_with_digits) {
  sourcemeta::jsontoolkit::JSON document{"3E1E2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_left_e_space) {
  sourcemeta::jsontoolkit::JSON document{"3 E2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_right_e_space) {
  sourcemeta::jsontoolkit::JSON document{"3E 2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_double_minus_after_e) {
  sourcemeta::jsontoolkit::JSON document{"3E--2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_double_minus_with_digits_after_e) {
  sourcemeta::jsontoolkit::JSON document{"3E-2-2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_plus_after_e) {
  sourcemeta::jsontoolkit::JSON document{"3E+2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

// From https://en.wikipedia.org/wiki/Scientific_notation

TEST(Number, exponential_notation_integer_1_upper) {
  sourcemeta::jsontoolkit::JSON document{"2E0"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 2.0);
}

TEST(Number, exponential_notation_integer_2_upper) {
  sourcemeta::jsontoolkit::JSON document{"3E2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 300.0);
}

TEST(Number, exponential_notation_integer_3_upper) {
  sourcemeta::jsontoolkit::JSON document{"4.321768E3"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 4321.768);
}

TEST(Number, exponential_notation_integer_4_upper) {
  sourcemeta::jsontoolkit::JSON document{"-5.3E4"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), -53000);
}

TEST(Number, exponential_notation_integer_5_upper) {
  sourcemeta::jsontoolkit::JSON document{"6.72E9"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 6720000000);
}

TEST(Number, exponential_notation_integer_6_upper) {
  sourcemeta::jsontoolkit::JSON document{"2E-1"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 0.2);
}

TEST(Number, exponential_notation_integer_7_upper) {
  sourcemeta::jsontoolkit::JSON document{"9.87E2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 987);
}

TEST(Number, exponential_notation_integer_8_upper) {
  sourcemeta::jsontoolkit::JSON document{"7.51E-9"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 0.00000000751);
}

TEST(Number, exponential_notation_integer_1_lower) {
  sourcemeta::jsontoolkit::JSON document{"2e0"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 2.0);
}

TEST(Number, exponential_notation_integer_2_lower) {
  sourcemeta::jsontoolkit::JSON document{"3e2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 300.0);
}

TEST(Number, exponential_notation_integer_3_lower) {
  sourcemeta::jsontoolkit::JSON document{"4.321768e3"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 4321.768);
}

TEST(Number, exponential_notation_integer_4_lower) {
  sourcemeta::jsontoolkit::JSON document{"-5.3e4"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), -53000);
}

TEST(Number, exponential_notation_integer_5_lower) {
  sourcemeta::jsontoolkit::JSON document{"6.72e9"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 6720000000);
}

TEST(Number, exponential_notation_integer_6_lower) {
  sourcemeta::jsontoolkit::JSON document{"2e-1"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 0.2);
}

TEST(Number, exponential_notation_integer_7_lower) {
  sourcemeta::jsontoolkit::JSON document{"9.87e2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 987);
}

TEST(Number, exponential_notation_integer_8_lower) {
  sourcemeta::jsontoolkit::JSON document{"7.51e-9"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 0.00000000751);
}

TEST(Number, exponential_notation_integer_1_real) {
  sourcemeta::jsontoolkit::JSON document{"2.0e0"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 2.0);
}

TEST(Number, exponential_notation_integer_2_real) {
  sourcemeta::jsontoolkit::JSON document{"3.0e2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 300.0);
}

TEST(Number, exponential_notation_integer_3_real) {
  sourcemeta::jsontoolkit::JSON document{"2.0e-1"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 0.2);
}
