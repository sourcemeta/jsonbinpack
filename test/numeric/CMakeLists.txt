noa_googletest(NAMESPACE sourcemeta PROJECT jsonbinpack NAME numeric
  FOLDER "JSON BinPack/Numeric"
  SOURCES
    zigzag_test.cc
    closest_smallest_exponent_test.cc
    divide_ceil_test.cc
    divide_floor_test.cc
    uint_max_test.cc)

target_link_libraries(sourcemeta_jsonbinpack_numeric_unit
  PRIVATE sourcemeta::jsonbinpack::numeric)
