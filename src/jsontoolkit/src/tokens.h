#ifndef SOURCEMETA_JSONTOOLKIT_TOKENS_H_
#define SOURCEMETA_JSONTOOLKIT_TOKENS_H_

namespace sourcemeta {
  namespace jsontoolkit {
    const char JSON_ARRAY_START = '[';
    const char JSON_ARRAY_END = ']';
    const char JSON_ARRAY_SEPARATOR = ',';

    // A string is a sequence of Unicode code points wrapped with quotation marks (U+0022)
    // See https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    const char JSON_STRING_QUOTE = '\u0022';

    const char JSON_STRING_ESCAPE_CHARACTER = '\u005C';
  }
}

#endif
