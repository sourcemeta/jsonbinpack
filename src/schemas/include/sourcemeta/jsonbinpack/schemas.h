#ifndef SOURCEMETA_JSONBINPACK_SCHEMAS_H_
#define SOURCEMETA_JSONBINPACK_SCHEMAS_H_

#include <string> // std::string

namespace sourcemeta::jsonbinpack::schemas {
namespace encoding::v1 {
const std::string id{
    "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json"};
const char *const json = R"JSON({
  "$id": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$vocabulary": {
    "https://json-schema.org/draft/2020-12/vocab/core": true
  },
  "$comment": "TODO: Make this a proper encoding schema"
})JSON";
} // namespace encoding::v1
} // namespace sourcemeta::jsonbinpack::schemas

#endif
