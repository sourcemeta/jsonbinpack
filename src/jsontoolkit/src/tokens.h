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

    // A number is a sequence of decimal digits with no superfluous leading
    // zero. It may have a preceding minus sign (U+002D). It may have a
    // fractional part prefixed by a decimal point (U+002E). It may have an
    // exponent, prefixed by e (U+0065) or E (U+0045) and optionally + (U+002B)
    // or – (U+002D). The digits are the code points U+0030 through U+0039.
    // See https://www.ecma-international.org/wp-content/uploads/ECMA-404_2nd_edition_december_2017.pdf
    const char JSON_MINUS = '\u002D';
    const char JSON_ZERO = '\u0030';
    const char JSON_ONE = '\u0031';
    const char JSON_TWO = '\u0032';
    const char JSON_THREE = '\u0033';
    const char JSON_FOUR = '\u0034';
    const char JSON_FIVE = '\u0035';
    const char JSON_SIX = '\u0036';
    const char JSON_SEVEN = '\u0037';
    const char JSON_EIGHT = '\u0038';
    const char JSON_NINE = '\u0039';
    const char JSON_EXPONENT_UPPER = '\u0045';
    const char JSON_EXPONENT_LOWER = '\u0065';
    const char JSON_DECIMAL_POINT = '\u002E';
  }
}

#endif
