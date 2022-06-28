#ifndef SOURCEMETA_ALTERSCHEMA_BUNDLE_H_
#define SOURCEMETA_ALTERSCHEMA_BUNDLE_H_

#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <memory> // std::unique_ptr
#include <vector> // std::vector

namespace sourcemeta::alterschema {
class Bundle {
public:
  Bundle() = default;
  auto add(std::unique_ptr<sourcemeta::alterschema::Rule> &&rule) -> void;
  // TODO: Take proper JSON templates
  auto apply(sourcemeta::jsontoolkit::JSON<std::string> &document) -> void;

private:
  std::vector<std::unique_ptr<sourcemeta::alterschema::Rule>> rules;
};
} // namespace sourcemeta::alterschema

#endif
