#include <iostream>
#include <cstring>
#include <cassert>
#include "../stringUtils.h"

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

int main() {
    test_removeChar();
    return 0;
}
