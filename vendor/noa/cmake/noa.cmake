set(NOA_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/noa")
include("${NOA_DIRECTORY}/shim.cmake")
include("${NOA_DIRECTORY}/variables.cmake")
include("${NOA_DIRECTORY}/defaults.cmake")
include("${NOA_DIRECTORY}/compiler/sanitizer.cmake")
include("${NOA_DIRECTORY}/options/enum.cmake")
include("${NOA_DIRECTORY}/commands/copy-file.cmake")
include("${NOA_DIRECTORY}/targets/clang-format.cmake")
include("${NOA_DIRECTORY}/targets/clang-tidy.cmake")
