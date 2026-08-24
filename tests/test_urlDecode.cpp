#include <iostream>
#include <string.h>
#include <cassert>

// Stub out necessary includes for compilation
#include <ctype.h>
#include <stdlib.h>

void urlDecode(char* inVal) {
  // replace url encoded characters in-place
  char* reader = inVal;
  char* writer = inVal;
  while (*reader) {
    if (*reader == '%' && isxdigit((unsigned char)*(reader + 1)) && isxdigit((unsigned char)*(reader + 2))) {
      char h1 = *(reader + 1);
      char h2 = *(reader + 2);
      int v1 = (h1 <= '9') ? (h1 - '0') : ((h1 & 0xDF) - 'A' + 10);
      int v2 = (h2 <= '9') ? (h2 - '0') : ((h2 & 0xDF) - 'A' + 10);
      *writer++ = (char)((v1 << 4) | v2);
      reader += 3;
    } else {
      *writer++ = *reader++;
    }
  }
  *writer = '\0';
}

void test(const char* input, const char* expected) {
    char buffer[1024];
    strcpy(buffer, input);
    urlDecode(buffer);
    if (strcmp(buffer, expected) != 0) {
        std::cerr << "Test failed!" << std::endl;
        std::cerr << "Input:    " << input << std::endl;
        std::cerr << "Expected: " << expected << std::endl;
        std::cerr << "Got:      " << buffer << std::endl;
        exit(1);
    }
}

int main() {
    test("hello%20world", "hello world");
    test("my%2Fpath%2Fto%2Ffile.txt", "my/path/to/file.txt");
    test("%E2%9C%94", "✔"); // Check multi-byte UTF-8
    test("no_encoding", "no_encoding");
    test("%25", "%");
    test("incomplete%", "incomplete%");
    test("incomplete%2", "incomplete%2");

    std::cout << "All urlDecode tests passed!" << std::endl;
    return 0;
}
