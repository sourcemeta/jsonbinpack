#ifndef SOURCEMETA_JSONBINPACK_CLI_UTILS_H_
#define SOURCEMETA_JSONBINPACK_CLI_UTILS_H_

#include <fstream> // std::ifstream
#include <sstream> // std::ostringstream
#include <string>  // std::string

namespace sourcemeta::jsonbinpack::cli::utils {

// Heavily inspired by https://stackoverflow.com/a/116220
static auto read_file(const std::filesystem::path &path) -> std::string {
  constexpr std::size_t buffer_size{4096};
  std::ifstream stream{path.string()};
  stream.exceptions(std::ios_base::badbit);
  std::string buffer(buffer_size, '\0');
  std::string output;
  while (stream.read(&buffer[0], buffer_size)) {
    output.append(buffer, 0,
                  static_cast<std::string::size_type>(stream.gcount()));
  }
  return output.append(buffer, 0,
                       static_cast<std::string::size_type>(stream.gcount()));
}

} // namespace sourcemeta::jsonbinpack::cli::utils

#endif
