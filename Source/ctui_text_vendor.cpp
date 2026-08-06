extern "C" {
#include <grapheme.h>
}
#include <utf8proc.h>
#include <cstdio>

void TestVendorLibs()
{
    // libgrapheme: naechste Grapheme-Cluster-Grenze in UTF-8-String finden
    const char* text = "a\u0301"; // "a" + kombinierender Akut
    size_t len = grapheme_next_character_break_utf8(text, strlen(text));
    printf("grapheme break at: %zu\n", len);

    // utf8proc: Codepoint aus UTF-8 dekodieren
    utf8proc_int32_t codepoint;
    utf8proc_ssize_t n = utf8proc_iterate(
        reinterpret_cast<const utf8proc_uint8_t*>(text), -1, &codepoint);
    printf("utf8proc codepoint: %d (bytes: %zd)\n", codepoint, n);
}
