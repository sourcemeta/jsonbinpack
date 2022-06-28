#ifndef SOURCEMETA_ALTERSCHEMA_BUNDLE_H_
#define SOURCEMETA_ALTERSCHEMA_BUNDLE_H_

#include <alterschema/rule.h>
#include <jsontoolkit/json.h>

#include <memory>  // std::unique_ptr
#include <utility> // std::move
#include <vector>  // std::vector

namespace sourcemeta::alterschema {
class Bundle {
public:
  Bundle() = default;

  auto add(std::unique_ptr<sourcemeta::alterschema::Rule<std::string>> &&rule)
      -> void {
    this->rules.push_back(std::move(rule));
  }

  // TODO: Take proper JSON templates
  auto apply(sourcemeta::jsontoolkit::JSON<std::string> &document) -> void;

private:
  std::vector<std::unique_ptr<sourcemeta::alterschema::Rule<std::string>>>
      rules;
};
} // namespace sourcemeta::alterschema

#endif
