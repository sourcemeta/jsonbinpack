#include <sourcemeta/core/yaml.h>

#include <sstream>     // std::ostringstream
#include <string_view> // std::string_view

// See https://pyyaml.org/wiki/LibYAML for basic documentation
#include <yaml.h>

// TODO: Perform parsing token by token using `yaml_parser_parse`,
// as that function also let us get line/column information on `yaml_event_t`
static auto yaml_node_to_json(yaml_node_t *const node,
                              yaml_document_t *const document)
    -> sourcemeta::core::JSON {
  if (!node) {
    return sourcemeta::core::JSON{nullptr};
  }

  switch (node->type) {
    case YAML_SCALAR_NODE: {
      const std::string_view input{
          reinterpret_cast<char *>(node->data.scalar.value),
          node->data.scalar.length};

      try {
        // TODO: Avoid this std::string transformation
        return sourcemeta::core::parse_json(std::string{input});
        // Looks like it is very hard in YAML, given a scalar value, to
        // determine whether it is a string or something else without attempting
        // to parsing it and potentially failing to do so
      } catch (const sourcemeta::core::JSONParseError &) {
        return sourcemeta::core::JSON{input};
      }
    }

    case YAML_SEQUENCE_NODE: {
      auto result{sourcemeta::core::JSON::make_array()};
      for (yaml_node_item_t *item = node->data.sequence.items.start;
           item < node->data.sequence.items.top; ++item) {
        yaml_node_t *const child = yaml_document_get_node(document, *item);
        result.push_back(yaml_node_to_json(child, document));
      }

      return result;
    }

    case YAML_MAPPING_NODE: {
      auto result{sourcemeta::core::JSON::make_object()};
      for (yaml_node_pair_t *pair = node->data.mapping.pairs.start;
           pair < node->data.mapping.pairs.top; ++pair) {
        yaml_node_t *const key_node =
            yaml_document_get_node(document, pair->key);
        yaml_node_t *const value_node =
            yaml_document_get_node(document, pair->value);
        if (key_node && key_node->type == YAML_SCALAR_NODE) {
          result.assign(reinterpret_cast<char *>(key_node->data.scalar.value),
                        yaml_node_to_json(value_node, document));
        }
      }

      return result;
    }

    default:
      return sourcemeta::core::JSON{nullptr};
  }
}

static auto internal_parse_json(yaml_parser_t *parser)
    -> sourcemeta::core::JSON {
  yaml_document_t document;
  if (!yaml_parser_load(parser, &document)) {
    // TODO: Ideally we would get line/column information like for `ParseError`
    throw sourcemeta::core::YAMLParseError("Failed to parse the YAML document");
  }

  yaml_node_t *const root = yaml_document_get_root_node(&document);
  if (!root) {
    yaml_document_delete(&document);
    throw sourcemeta::core::YAMLParseError("The input YAML document is empty");
  }

  try {
    const auto result{yaml_node_to_json(root, &document)};
    yaml_document_delete(&document);
    return result;
  } catch (...) {
    yaml_document_delete(&document);
    throw;
  }
}

namespace sourcemeta::core {

auto parse_yaml(const JSON::String &input) -> JSON {
  yaml_parser_t parser;
  if (!yaml_parser_initialize(&parser)) {
    throw YAMLError("Could not initialize the YAML parser");
  }

  yaml_parser_set_encoding(&parser, YAML_UTF8_ENCODING);
  yaml_parser_set_input_string(
      &parser, reinterpret_cast<const unsigned char *>(input.c_str()),
      input.size());

  try {
    const auto result{internal_parse_json(&parser)};
    yaml_parser_delete(&parser);
    return result;
  } catch (...) {
    yaml_parser_delete(&parser);
    throw;
  }
}

auto read_yaml(const std::filesystem::path &path) -> JSON {
  auto stream = read_file(path);
  std::ostringstream buffer;
  buffer << stream.rdbuf();
  return parse_yaml(buffer.str());
}

} // namespace sourcemeta::core
