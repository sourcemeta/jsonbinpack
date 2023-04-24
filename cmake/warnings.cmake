if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
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
    -Wrange-loop-analysis
    # Assume that signed arithmetic overflow of addition, subtraction and
    # multiplication wraps around using twos-complement representation
    # See https://users.cs.utah.edu/~regehr/papers/overflow12.pdf
    # See https://www.postgresql.org/message-id/1689.1134422394@sss.pgh.pa.us
    -fwrapv)
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
    -Winvalid-offsetof
    # Assume that signed arithmetic overflow of addition, subtraction and
    # multiplication wraps around using twos-complement representation
    # See https://users.cs.utah.edu/~regehr/papers/overflow12.pdf
    # See https://www.postgresql.org/message-id/1689.1134422394@sss.pgh.pa.us
    -fwrapv)
elseif(MSVC)
  add_compile_options(/options:strict /W4 /WX /WL /sdl)
else()
  message(WARNING "Unrecognized compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()
