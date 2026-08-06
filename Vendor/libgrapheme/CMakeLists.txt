# Vendor/libgrapheme/CMakeLists.txt
#
# libgrapheme (https://libs.suckless.org/libgrapheme/), vendored:
# gen/*.h wurden einmalig per "make" erzeugt und liegen hier fest im Repo
# (siehe README/Kommentar oben in der Datei-Historie). Deshalb reicht ein
# stinknormaler add_library-Aufruf, kein Generator-Schritt noetig.
#
# Erwartete Dateien in diesem Ordner:
#   grapheme.h
#   src/*.c, src/util.h
#   gen/bidirectional.h, case.h, character.h, line.h, sentence.h, word.h
#   gen/types.h

add_library(grapheme STATIC
    src/bidirectional.c
    src/case.c
    src/character.c
    src/line.c
    src/sentence.c
    src/utf8.c
    src/util.c
    src/word.c
)

target_include_directories(grapheme
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}"       # fuer grapheme.h und gen/*.h
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"   # fuer src/util.h
)

set_target_properties(grapheme PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)