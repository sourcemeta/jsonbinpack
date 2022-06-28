#ifndef SOURCEMETA_ALTERSCHEMA_APPLICATOR_H_
#define SOURCEMETA_ALTERSCHEMA_APPLICATOR_H_

#include <string> // std::string

namespace sourcemeta::alterschema {
enum class ApplicatorType { Value, Array, Object };
struct Applicator {
  const std::string vocabulary;
  const std::string keyword;
  const ApplicatorType type;
};
} // namespace sourcemeta::alterschema

#endif
