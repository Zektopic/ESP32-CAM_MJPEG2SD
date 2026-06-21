#include <iostream>
#include <cstring>
#include <cassert>
#include "../stringUtils.h"

// Stub for removeChar since it's defined in utils.cpp which has ESP32 dependencies
void removeChar(char* s, char c) {
  // remove specified character from string
  int writer = 0, reader = 0;
  while (s[reader]) {
    if (s[reader] != c) s[writer++] = s[reader];
    reader++;
  }
  s[writer] = 0;
}

// Stub for replaceChar since it's defined in utils.cpp which has ESP32 dependencies
void replaceChar(char* s, char c, char r) {
  // replace specified character in string
  int reader = 0;
  while (s[reader]) {
    if (s[reader] == c) s[reader] = r;
    reader++;
  }
}

void test_replaceChar() {
    // Test 1: Happy path - replacing a character that is present
    char str1[] = "hello world";
    replaceChar(str1, 'o', 'a');
    assert(strcmp(str1, "hella warld") == 0);

    // Test 2: Happy path - replacing multiple instances of a character
    char str2[] = "hello world";
    replaceChar(str2, 'l', 'x');
    assert(strcmp(str2, "hexxo worxd") == 0);

    // Test 3: Edge case - replacing a character at the beginning
    char str3[] = "hello world";
    replaceChar(str3, 'h', 'j');
    assert(strcmp(str3, "jello world") == 0);

    // Test 4: Edge case - replacing a character at the end
    char str4[] = "hello world";
    replaceChar(str4, 'd', 'k');
    assert(strcmp(str4, "hello worlk") == 0);

    // Test 5: Edge case - character not present
    char str5[] = "hello world";
    replaceChar(str5, 'z', 'a');
    assert(strcmp(str5, "hello world") == 0);

    // Test 6: Edge case - string entirely composed of target character
    char str6[] = "ooooo";
    replaceChar(str6, 'o', 'a');
    assert(strcmp(str6, "aaaaa") == 0);

    // Test 7: Edge case - empty string
    char str7[] = "";
    replaceChar(str7, 'o', 'a');
    assert(strcmp(str7, "") == 0);

    // Test 8: Edge case - replacing character with itself
    char str8[] = "hello world";
    replaceChar(str8, 'o', 'o');
    assert(strcmp(str8, "hello world") == 0);

    std::cout << "All tests passed for replaceChar!" << std::endl;
}

void test_removeChar() {
    // Test 1: Happy path - removing a character that is present
    char str1[] = "hello world";
    removeChar(str1, 'o');
    assert(strcmp(str1, "hell wrld") == 0);

    // Test 2: Happy path - removing multiple instances of a character
    char str2[] = "hello world";
    removeChar(str2, 'l');
    assert(strcmp(str2, "heo word") == 0);

    // Test 3: Edge case - removing a character at the beginning
    char str3[] = "hello world";
    removeChar(str3, 'h');
    assert(strcmp(str3, "ello world") == 0);

    // Test 4: Edge case - removing a character at the end
    char str4[] = "hello world";
    removeChar(str4, 'd');
    assert(strcmp(str4, "hello worl") == 0);

    // Test 5: Edge case - character not present
    char str5[] = "hello world";
    removeChar(str5, 'z');
    assert(strcmp(str5, "hello world") == 0);

    // Test 6: Edge case - string entirely composed of target character
    char str6[] = "ooooo";
    removeChar(str6, 'o');
    assert(strcmp(str6, "") == 0);

    // Test 7: Edge case - empty string
    char str7[] = "";
    removeChar(str7, 'o');
    assert(strcmp(str7, "") == 0);

    std::cout << "All tests passed for removeChar!" << std::endl;
}

void test_isPathTraversal() {
    // Tests for isPathTraversal
    assert(isPathTraversal("../") == true);
    assert(isPathTraversal("..\\") == true);
    assert(isPathTraversal("/..") == true);
    assert(isPathTraversal("\\..") == true);
    assert(isPathTraversal("..") == true);

    assert(isPathTraversal("valid_path/test.txt") == false);
    assert(isPathTraversal("/valid/path") == false);
    assert(isPathTraversal("path_without_dots") == false);
    assert(isPathTraversal(".hidden_file") == false);
    assert(isPathTraversal("") == false);
    assert(isPathTraversal(NULL) == false);

    assert(isPathTraversal("path/../with/traversal") == true);
    assert(isPathTraversal("path/..\\with/traversal") == true);
    std::cout << "All tests passed for isPathTraversal!" << std::endl;
}

void test_changeExtension_helper(const char* input, const char* newExt, bool expectedRes, const char* expectedOutput) {
    char buffer[256];
    strcpy(buffer, input);
    bool res = changeExtension(buffer, newExt);
    if (res != expectedRes || strcmp(buffer, expectedOutput) != 0) {
        std::cerr << "Test failed!" << std::endl;
        std::cerr << "Input:    " << input << std::endl;
        std::cerr << "New Ext:  " << newExt << std::endl;
        std::cerr << "Expected Res: " << expectedRes << ", Output: " << expectedOutput << std::endl;
        std::cerr << "Got Res:      " << res << ", Output: " << buffer << std::endl;
        exit(1);
    }
}

void test_changeExtension() {
    // Happy path: Normal file with extension
    test_changeExtension_helper("image.jpg", "png", true, "image.png");

    // File with multiple dots
    test_changeExtension_helper("path.with.dots.jpg", "png", true, "path.with.dots.png");

    // File without extension
    test_changeExtension_helper("no_extension_file", "txt", false, "ntxt");

    // File starting with a dot
    test_changeExtension_helper(".hidden", "txt", false, ".txt");

    std::cout << "All changeExtension tests passed!" << std::endl;
}

int main() {
    test_replaceChar();
    test_removeChar();
    test_isPathTraversal();
    test_changeExtension();
    return 0;
}
