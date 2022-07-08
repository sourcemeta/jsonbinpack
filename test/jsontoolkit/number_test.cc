#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <sstream> // std::ostringstream

TEST(Number, set_negative_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"true"};
  EXPECT_TRUE(document.is_boolean());
  document = -4;
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
}

TEST(Number, set_negative_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"true"};
  EXPECT_TRUE(document.is_boolean());
  document = -4.3;
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
}

TEST(Number, set_negative_integral_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"true"};
  EXPECT_TRUE(document.is_boolean());
  document = -4.0;
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
}

TEST(Number, set_positive_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"true"};
  EXPECT_TRUE(document.is_boolean());
  document = 4;
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
}

TEST(Number, set_positive_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"true"};
  EXPECT_TRUE(document.is_boolean());
  document = 4.3;
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
}

TEST(Number, set_positive_integral_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"true"};
  EXPECT_TRUE(document.is_boolean());
  document = 4.0;
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
}

TEST(Number, string_integer_zero) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"0"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), 0);
  EXPECT_EQ(document, static_cast<std::int64_t>(0));
  EXPECT_EQ(document, static_cast<double>(0));
}

TEST(Number, string_integer_positive_single_digit_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), 3);
  EXPECT_EQ(document, static_cast<std::int64_t>(3));
  EXPECT_EQ(document, static_cast<double>(3));
}

TEST(Number, string_integer_negative_single_digit_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-3"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), -3);
  EXPECT_EQ(document, static_cast<std::int64_t>(-3));
  EXPECT_EQ(document, static_cast<double>(-3));
}

TEST(Number, string_integer_positive_long_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"12345"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), 12345);
  EXPECT_EQ(document, static_cast<std::int64_t>(12345));
  EXPECT_EQ(document, static_cast<double>(12345));
}

TEST(Number, string_integer_negative_long_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-12345"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), -12345);
  EXPECT_EQ(document, static_cast<std::int64_t>(-12345));
  EXPECT_EQ(document, static_cast<double>(-12345));
}

TEST(Number, string_integer_minus_zero) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-0"};
  EXPECT_TRUE(document.is_integer());
  EXPECT_FALSE(document.is_real());
  EXPECT_EQ(document.to_integer(), 0);
  EXPECT_EQ(document, static_cast<std::int64_t>(0));
  EXPECT_EQ(document, static_cast<double>(0));
}

TEST(Number, invalid_string_integer_trailing_minus) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-0-"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, invalid_string_integer_trailing_character) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-0x"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, invalid_minus_in_between_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"123-45"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, invalid_double_minus) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"--123"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, two_zeroes) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"00"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, multiple_zeroes) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"000"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, leading_zero_with_one_digit_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"01"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, leading_zero_with_two_digits_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"012"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, leading_period) {
  sourcemeta::jsontoolkit::JSON<std::string> document{".0"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, trailing_period) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"0."};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, trailing_period_and_minus) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"0.-"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, double_minus_at_start) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"--5"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, leading_minus_and_period) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-.0"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, multiple_leading_plus) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"++5"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, trailing_zero_positive) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"1.50000"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1.5);
  EXPECT_EQ(document, 1.5);
  EXPECT_FALSE(document == static_cast<std::int64_t>(1));
  EXPECT_FALSE(document == static_cast<std::int64_t>(2));
}

TEST(Number, trailing_zero_negative) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-1.50000"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1.5);
  EXPECT_EQ(document, -1.5);
  EXPECT_FALSE(document == static_cast<std::int64_t>(-1));
  EXPECT_FALSE(document == static_cast<std::int64_t>(-2));
}

TEST(Number, single_left_digit_positive_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"1.5"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1.5);
  EXPECT_EQ(document, 1.5);
  EXPECT_FALSE(document == static_cast<std::int64_t>(1));
  EXPECT_FALSE(document == static_cast<std::int64_t>(2));
}

TEST(Number, single_left_digit_negative_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-1.5"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1.5);
  EXPECT_EQ(document, -1.5);
  EXPECT_FALSE(document == static_cast<std::int64_t>(-1));
  EXPECT_FALSE(document == static_cast<std::int64_t>(-2));
}

TEST(Number, leading_decimal_zero) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"1.0005"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1.0005);
  EXPECT_EQ(document, 1.0005);
  EXPECT_FALSE(document == static_cast<std::int64_t>(1));
  EXPECT_FALSE(document == static_cast<std::int64_t>(2));
}

TEST(Number, multi_left_digit_positive_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"1234.5"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1234.5);
  EXPECT_EQ(document, 1234.5);
  EXPECT_FALSE(document == static_cast<std::int64_t>(1234));
  EXPECT_FALSE(document == static_cast<std::int64_t>(1235));
}

TEST(Number, multi_left_digit_negative_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-1234.5"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1234.5);
  EXPECT_EQ(document, -1234.5);
  EXPECT_FALSE(document == static_cast<std::int64_t>(-1235));
  EXPECT_FALSE(document == static_cast<std::int64_t>(-1234));
}

TEST(Number, long_positive_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"1234.56789"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1234.56789);
  EXPECT_EQ(document, 1234.56789);
  EXPECT_FALSE(document == static_cast<std::int64_t>(1234));
  EXPECT_FALSE(document == static_cast<std::int64_t>(1235));
}

TEST(Number, long_negative_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-1234.56789"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1234.56789);
  EXPECT_EQ(document, -1234.56789);
  EXPECT_FALSE(document == static_cast<std::int64_t>(-1235));
  EXPECT_FALSE(document == static_cast<std::int64_t>(-1234));
}

TEST(Number, multiple_sibling_periods) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"123..56"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, multiple_separate_periods) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"12.34.56"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, single_digit_positive_real_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"1.0"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1.0);
  EXPECT_EQ(document, 1.0);
  EXPECT_EQ(document, static_cast<std::int64_t>(1));
}

TEST(Number, single_digit_positive_real_integer_trailing_zero) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"1.0000000"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1.0);
  EXPECT_EQ(document, 1.0);
  EXPECT_EQ(document, static_cast<std::int64_t>(1));
}

TEST(Number, single_digit_negative_real_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-1.0"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1.0);
  EXPECT_EQ(document, -1.0);
  EXPECT_EQ(document, static_cast<std::int64_t>(-1));
}

TEST(Number, single_digit_negative_real_integer_trailing_zero) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-1.0000000"};
  EXPECT_FALSE(document.is_integer());
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1.0);
  EXPECT_EQ(document, static_cast<std::int64_t>(-1));
}

TEST(Number, string_integer_with_plus) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"+5"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, string_zero_with_plus) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"+0"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, negative_with_leading_zero) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-05"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, negative_with_leading_zero_and_space) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-0 5"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, large_positive_exponential_number) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"1.0e28"};
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1e28);
}

TEST(Number, leading_zero_positive_integer_number) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"02"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, leading_zero_negative_integer_number) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-02"};
  EXPECT_THROW(document.is_integer(), std::domain_error);
}

TEST(Number, two_leading_zeroes_real_number) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-00.2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, multiple_leading_zeroes_real_number) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-00000.2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, leading_zero_real_number) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-0.2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -0.2);
}

TEST(Number, large_negative_exponential_number) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-1.0e28"};
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1e28);
}

TEST(Number, large_positive_exponential_number_with_plus_exponent) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"1.0e+28"};
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), 1e28);
}

TEST(Number, large_negative_exponential_number_with_plus_exponent) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-1.0e+28"};
  EXPECT_TRUE(document.is_real());
  EXPECT_EQ(document.to_real(), -1e28);
}

// Invalid exponential numbers

TEST(Number, exponential_notation_error_double_upper_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3EE2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_double_lower_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3ee2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_double_mixed_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3eE2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_trailing_upper_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3E"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_trailing_lower_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3e"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_trailing_upper_e_minus) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3E-"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_trailing_lower_e_minus) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3e-"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_leading_upper_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"E2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_leading_lower_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"e2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_minus_leading_upper_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-E2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_minus_leading_lower_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-e2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_double_e_with_digits) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3E1E2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_left_e_space) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3 E2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_right_e_space) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3E 2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_double_minus_after_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3E--2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_error_double_minus_with_digits_after_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3E-2-2"};
  EXPECT_THROW(document.is_real(), std::domain_error);
}

TEST(Number, exponential_notation_plus_after_e) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3E+2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 300.0);
  EXPECT_EQ(document, static_cast<std::int64_t>(300));
  EXPECT_EQ(document, static_cast<double>(300));
}

// From https://en.wikipedia.org/wiki/Scientific_notation

TEST(Number, exponential_notation_integer_1_upper) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"2E0"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 2.0);
  EXPECT_EQ(document, static_cast<std::int64_t>(2));
  EXPECT_EQ(document, static_cast<double>(2));
}

TEST(Number, exponential_notation_integer_2_upper) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3E2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 300.0);
  EXPECT_EQ(document, static_cast<std::int64_t>(300));
  EXPECT_EQ(document, static_cast<double>(300));
}

TEST(Number, exponential_notation_integer_3_upper) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"4.321768E3"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 4321.768);
  EXPECT_FALSE(document == static_cast<std::int64_t>(4321));
  EXPECT_FALSE(document == static_cast<std::int64_t>(4322));
}

TEST(Number, exponential_notation_integer_4_upper) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-5.3E4"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), -53000);
  EXPECT_EQ(document, static_cast<std::int64_t>(-53000));
}

TEST(Number, exponential_notation_integer_5_upper) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"6.72E9"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 6720000000);
  EXPECT_EQ(document, static_cast<std::int64_t>(6720000000));
}

TEST(Number, exponential_notation_integer_6_upper) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"2E-1"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 0.2);
  EXPECT_FALSE(document == static_cast<std::int64_t>(0));
  EXPECT_FALSE(document == static_cast<std::int64_t>(1));
}

TEST(Number, exponential_notation_integer_7_upper) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"9.87E2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 987);
  EXPECT_EQ(document, static_cast<std::int64_t>(987));
}

TEST(Number, exponential_notation_integer_8_upper) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"7.51E-9"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 0.00000000751);
  EXPECT_FALSE(document == static_cast<std::int64_t>(0));
  EXPECT_FALSE(document == static_cast<std::int64_t>(1));
}

TEST(Number, exponential_notation_integer_1_lower) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"2e0"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 2.0);
  EXPECT_EQ(document, static_cast<std::int64_t>(2));
}

TEST(Number, exponential_notation_integer_2_lower) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3e2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 300.0);
  EXPECT_EQ(document, static_cast<std::int64_t>(300));
}

TEST(Number, exponential_notation_integer_3_lower) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"4.321768e3"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 4321.768);
  EXPECT_FALSE(document == static_cast<std::int64_t>(4321));
  EXPECT_FALSE(document == static_cast<std::int64_t>(4322));
}

TEST(Number, exponential_notation_integer_4_lower) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-5.3e4"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), -53000);
  EXPECT_EQ(document, static_cast<std::int64_t>(-53000));
}

TEST(Number, exponential_notation_integer_5_lower) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"6.72e9"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 6720000000);
  EXPECT_EQ(document, static_cast<std::int64_t>(6720000000));
}

TEST(Number, exponential_notation_integer_6_lower) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"2e-1"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 0.2);
  EXPECT_FALSE(document == static_cast<std::int64_t>(0));
  EXPECT_FALSE(document == static_cast<std::int64_t>(1));
}

TEST(Number, exponential_notation_integer_7_lower) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"9.87e2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 987);
  EXPECT_EQ(document, static_cast<std::int64_t>(987));
}

TEST(Number, exponential_notation_integer_8_lower) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"7.51e-9"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 0.00000000751);
  EXPECT_FALSE(document == static_cast<std::int64_t>(0));
  EXPECT_FALSE(document == static_cast<std::int64_t>(1));
}

TEST(Number, exponential_notation_integer_1_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"2.0e0"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 2.0);
  EXPECT_EQ(document, static_cast<std::int64_t>(2));
}

TEST(Number, exponential_notation_integer_2_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3.0e2"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 300.0);
  EXPECT_EQ(document, static_cast<std::int64_t>(300));
}

TEST(Number, exponential_notation_integer_3_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"2.0e-1"};
  EXPECT_TRUE(document.is_real());
  EXPECT_FALSE(document.is_integer());
  EXPECT_EQ(document.to_real(), 0.2);
  EXPECT_FALSE(document == static_cast<std::int64_t>(0));
  EXPECT_FALSE(document == static_cast<std::int64_t>(1));
}

TEST(Number, integer_equality_with_padding) {
  sourcemeta::jsontoolkit::JSON<std::string> left{"5"};
  left.parse();
  sourcemeta::jsontoolkit::JSON<std::string> right{"  5   "};
  right.parse();
  sourcemeta::jsontoolkit::JSON<std::string> extra{"  5.1 "};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Number, real_equality_with_padding) {
  sourcemeta::jsontoolkit::JSON<std::string> left{"5.4"};
  left.parse();
  sourcemeta::jsontoolkit::JSON<std::string> right{"  5.4   "};
  right.parse();
  sourcemeta::jsontoolkit::JSON<std::string> extra{"  5 "};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Number, stringify_positive_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"54"};
  std::ostringstream stream;
  stream << document;
  EXPECT_EQ(stream.str(), "54");
}

TEST(Number, stringify_negative_integer) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-54"};
  std::ostringstream stream;
  stream << document;
  EXPECT_EQ(stream.str(), "-54");
}

TEST(Number, stringify_zero) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"0"};
  std::ostringstream stream;
  stream << document;
  EXPECT_EQ(stream.str(), "0");
}

TEST(Number, stringify_positive_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"5.4"};
  std::ostringstream stream;
  stream << document;
  EXPECT_EQ(stream.str(), "5.4");
}

TEST(Number, stringify_negative_real) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"-5.4"};
  std::ostringstream stream;
  stream << document;
  EXPECT_EQ(stream.str(), "-5.4");
}

// JSON has no distinction between integers and reals
TEST(Number, json_integer_json_real_equal) {
  sourcemeta::jsontoolkit::JSON<std::string> left{"1"};
  sourcemeta::jsontoolkit::JSON<std::string> right{"1.0"};
  left.parse();
  right.parse();
  EXPECT_EQ(left, right);
}

// JSON has no distinction between integers and reals
TEST(Number, json_real_json_integer_equal) {
  sourcemeta::jsontoolkit::JSON<std::string> left{"1.0"};
  sourcemeta::jsontoolkit::JSON<std::string> right{"1"};
  left.parse();
  right.parse();
  EXPECT_EQ(left, right);
}
