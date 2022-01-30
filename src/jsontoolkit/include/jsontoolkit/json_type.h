#ifndef SOURCEMETA_JSONTOOLKIT_JSON_TYPE_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_TYPE_H_

namespace sourcemeta {
  namespace jsontoolkit {
    enum class Type {
      String, Number,
      True, False, Null,
      Object, Array
    };
  }
}

#endif
