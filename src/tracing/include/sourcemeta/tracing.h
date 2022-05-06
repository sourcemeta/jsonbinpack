#ifndef SOURCEMETA_TRACING_TRACING_H_
#define SOURCEMETA_TRACING_TRACING_H_

#ifdef __APPLE__
#include "tracing_macos.h"
#else
// Otherwise do nothing
#include "tracing_noop.h"
#endif

#endif
