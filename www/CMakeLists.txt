configure_file(oxford-poster.pdf oxford-poster.pdf COPYONLY)
configure_file(benchmark-deck.png benchmark-deck.png COPYONLY)
configure_file(example.png example.png COPYONLY)
configure_file(hybrid.png hybrid.png COPYONLY)
configure_file(jsonschema.png jsonschema.png COPYONLY)
configure_file(timeline.png timeline.png COPYONLY)
configure_file(apple-touch-icon.png apple-touch-icon.png COPYONLY)
configure_file(favicon.ico favicon.ico COPYONLY)
configure_file(icon-192x192.png icon-192x192.png COPYONLY)
configure_file(icon-512x512.png icon-512x512.png COPYONLY)
configure_file(icon.svg icon.svg COPYONLY)
configure_file(index.html index.html COPYONLY)
configure_file(manifest.webmanifest manifest.webmanifest COPYONLY)

find_program(SASSC_BIN NAMES sassc REQUIRED)
add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/main.css"
  COMMAND "${SASSC_BIN}" --style compressed
    "${CMAKE_CURRENT_SOURCE_DIR}/main.scss"
    "${CMAKE_CURRENT_BINARY_DIR}/main.css"
  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/main.scss")
add_custom_target(website DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/main.css")
set_target_properties(website PROPERTIES FOLDER "JSON BinPack/Website")
