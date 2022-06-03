#include <jsontoolkit/json.h>
#include <jsontoolkit/json_internal.h>

#include <algorithm>   // std::any_of
#include <cmath>       // std::modf
#include <iomanip>     // std::noshowpoint
#include <sstream>     // std::ostringstream
#include <stdexcept>   // std::domain_error, std::logic_error
#include <string>      // std::to_string
#include <string_view> // std::string_view
#include <utility>     // std::in_place_type, std::move

auto sourcemeta::jsontoolkit::JSON::parse_source() -> void {
  const std::string_view document =
      sourcemeta::jsontoolkit::internal::trim(this->source());
  std::variant<std::int64_t, double> number_result;

  switch (document.front()) {
  case sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                      std::string>::token_begin:
    this->data =
        sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                       std::string>{std::string{document}};
    break;
  case sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                       std::string>::token_begin:
    this->data =
        sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                        std::string>{std::string{document}};
    break;
  case sourcemeta::jsontoolkit::String::token_begin:
    this->data = sourcemeta::jsontoolkit::String{std::string{document}};
    break;
  case sourcemeta::jsontoolkit::Number::token_minus_sign:
  case sourcemeta::jsontoolkit::Number::token_number_zero:
  case sourcemeta::jsontoolkit::Number::token_number_one:
  case sourcemeta::jsontoolkit::Number::token_number_two:
  case sourcemeta::jsontoolkit::Number::token_number_three:
  case sourcemeta::jsontoolkit::Number::token_number_four:
  case sourcemeta::jsontoolkit::Number::token_number_five:
  case sourcemeta::jsontoolkit::Number::token_number_six:
  case sourcemeta::jsontoolkit::Number::token_number_seven:
  case sourcemeta::jsontoolkit::Number::token_number_eight:
  case sourcemeta::jsontoolkit::Number::token_number_nine:
    number_result =
        sourcemeta::jsontoolkit::Number::parse(std::string{document});
    if (std::holds_alternative<std::int64_t>(number_result)) {
      this->data = std::get<std::int64_t>(number_result);
    } else {
      this->data = std::get<double>(number_result);
    }

    break;
  case sourcemeta::jsontoolkit::Null::token_constant.front():
    this->data = sourcemeta::jsontoolkit::Null::parse(std::string{document});
    break;
  case sourcemeta::jsontoolkit::Boolean::token_constant_true.front():
  case sourcemeta::jsontoolkit::Boolean::token_constant_false.front():
    *this = sourcemeta::jsontoolkit::Boolean::parse(std::string{document});
    break;
  default:
    throw std::domain_error("Invalid document");
  }
}
