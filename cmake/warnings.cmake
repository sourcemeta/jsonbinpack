if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic
    -Wshadow
    -Wdouble-promotion
    -Wconversion
    -Wunused-parameter
    -Wno-trigraphs
    -Wunreachable-code
    -Wno-missing-braces
    -Wparentheses
    -Wswitch
    -Wunused-function
    -Wno-unused-label
    -Wno-unused-parameter
    -Wunused-variable
    -Wunused-value
    -Wempty-body
    -Wuninitialized
    -Wno-shadow
    -Wno-four-char-constants
    -Wno-conversion
    -Wenum-conversion
    -Wno-float-conversion
    -Wno-newline-eof
    -Wno-implicit-fallthrough
    -Wno-sign-conversion
    -Wno-unknown-pragmas
    -Wno-non-virtual-dtor
    -Wno-overloaded-virtual
    -Wno-exit-time-destructors
    -Wno-c++11-extensions
    -Winvalid-offsetof
    -Wbool-conversion
    -Wint-conversion
    -Wpointer-sign
    -Wconditional-uninitialized
    -Wconstant-conversion
    -Wnon-literal-null-conversion
    -Wshorten-64-to-32
    -Wdeprecated-implementations
    -Winfinite-recursion
    -Wcomma
    -Wdocumentation
    -Wmove
    -Wrange-loop-analysis)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic
    -Wshadow
    -Wdouble-promotion
    -Wconversion
    -Wunused-parameter
    -Wno-trigraphs
    -Wunreachable-code
    -Wno-missing-braces
    -Wparentheses
    -Wswitch
    -Wunused-function
    -Wno-unused-label
    -Wno-unused-parameter
    -Wunused-variable
    -Wunused-value
    -Wempty-body
    -Wuninitialized
    -Wno-shadow
    -Wno-conversion
    -Wenum-conversion
    -Wno-float-conversion
    -Wno-implicit-fallthrough
    -Wno-sign-conversion
    -Wno-unknown-pragmas
    -Wno-non-virtual-dtor
    -Wno-overloaded-virtual
    -Winvalid-offsetof)
endif()
