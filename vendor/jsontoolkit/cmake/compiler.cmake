# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  # See https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
  add_compile_options(
    /options:strict
    /W4
    /WX
    /WL
    /sdl)
else()
  add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic
    -Wshadow
    -Wdouble-promotion
    -Wconversion
    -Wunused-parameter
    -Wtrigraphs
    -Wunreachable-code
    -Wmissing-braces
    -Wparentheses
    -Wswitch
    -Wunused-function
    -Wunused-label
    -Wunused-parameter
    -Wunused-variable
    -Wunused-value
    -Wempty-body
    -Wuninitialized
    -Wshadow
    -Wconversion
    -Wenum-conversion
    -Wfloat-conversion
    -Wimplicit-fallthrough
    -Wsign-compare
    -Wsign-conversion
    -Wunknown-pragmas
    -Wnon-virtual-dtor
    -Woverloaded-virtual
    -Wno-exit-time-destructors
    -Winvalid-offsetof)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  add_compile_options(
    -Wbool-conversion
    -Wint-conversion
    -Wpointer-sign
    -Wconditional-uninitialized
    -Wconstant-conversion
    -Wnon-literal-null-conversion
    -Wshorten-64-to-32
    -Wdeprecated-implementations
    -Winfinite-recursion
    -Wnewline-eof
    -Wfour-char-constants
    -Wselector
    -Wundeclared-selector
    -Wdocumentation
    -Wmove
    -Wc++11-extensions
    -Wrange-loop-analysis)
endif()
