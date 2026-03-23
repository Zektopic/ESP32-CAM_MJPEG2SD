#include <iostream>
#include <cassert>
#include <cstring>
#include "../stringUtils.h"

void test_urlDecode() {
    // Standard decoding
    char buf1[100] = "Hello%20World";
    urlDecode(buf1);
    assert(strcmp(buf1, "Hello World") == 0);

    // Multiple encodings in a single string
    char buf2[100] = "A%26B%3DC";
    urlDecode(buf2);
    assert(strcmp(buf2, "A&B=C") == 0);

    // Strings with no encodings
    char buf3[100] = "NoSpecialChars";
    urlDecode(buf3);
    assert(strcmp(buf3, "NoSpecialChars") == 0);

    // Edge cases like empty string
    char buf4[100] = "";
    urlDecode(buf4);
    assert(strcmp(buf4, "") == 0);

    // Invalid or malformed formats (e.g., %ZZ)
    char buf5[100] = "Test%ZZ";
    urlDecode(buf5);
    // std::regex matches only [0-9A-Fa-f]{2}, so it will be ignored and left as is
    assert(strcmp(buf5, "Test%ZZ") == 0);

    // End with encoded character
    char buf6[100] = "Test%21";
    urlDecode(buf6);
    assert(strcmp(buf6, "Test!") == 0);

    // Encoded character at the start
    char buf7[100] = "%21Test";
    urlDecode(buf7);
    assert(strcmp(buf7, "!Test") == 0);

    // Only encoded characters
    char buf8[100] = "%21%22%23";
    urlDecode(buf8);
    assert(strcmp(buf8, "!\"#") == 0);

    std::cout << "All urlDecode tests passed successfully!" << std::endl;
}

int main() {
    test_urlDecode();
    return 0;
}
