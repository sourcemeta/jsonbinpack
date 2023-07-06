#ifndef JSONTOOLKIT_JSON_RAPIDJSON_COMMON_H_
#define JSONTOOLKIT_JSON_RAPIDJSON_COMMON_H_

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wambiguous-reversed-operator"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wdocumentation"
#endif
#include <rapidjson/document.h>       // rapidjson::Value, rapidjson::Document
#include <rapidjson/error/en.h>       // rapidjson::GetParseError_En
#include <rapidjson/istreamwrapper.h> // rapidjson::IStreamWrapper
#include <rapidjson/ostreamwrapper.h> // rapidjson::OStreamWrapper
#include <rapidjson/prettywriter.h>   // rapidjson::PrettyWriter
#include <rapidjson/schema.h>         // rapidjson::internal::Hasher
#include <rapidjson/writer.h>         // rapidjson::Writer
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

namespace sourcemeta::jsontoolkit {
using JSON = rapidjson::Document;
using Value = rapidjson::Value;
} // namespace sourcemeta::jsontoolkit

#endif
