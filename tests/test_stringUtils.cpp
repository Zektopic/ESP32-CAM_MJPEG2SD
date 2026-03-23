#include <stdio.h>
#include <string.h>
#include "stringUtils.h"

int passed = 0;
int failed = 0;

void run_test(const char* test_name, const char* initial_name, const char* new_ext, const char* expected_name, bool expected_result) {
    char buffer[256];
    if (initial_name != NULL) {
        strcpy(buffer, initial_name);
    } else {
        buffer[0] = '\0';
    }

    bool result = changeExtension(buffer, new_ext);

    bool name_match = false;
    if (expected_name != NULL) {
        name_match = (strcmp(buffer, expected_name) == 0);
    } else {
        name_match = (buffer[0] == '\0');
    }

    if (result == expected_result && name_match) {
        printf("PASS: %s\n", test_name);
        passed++;
    } else {
        printf("FAIL: %s\n", test_name);
        printf("  Expected result: %s, Got: %s\n", expected_result ? "true" : "false", result ? "true" : "false");
        printf("  Expected name: '%s', Got: '%s'\n", expected_name ? expected_name : "", buffer);
        failed++;
    }
}

int main() {
    printf("Running changeExtension tests...\n");

    // Happy path (normal filename with extension)
    run_test("Happy path", "test.txt", "csv", "test.csv", true);

    // Filename with multiple dots (should replace the last one)
    run_test("Multiple dots", "archive.tar.gz", "bz2", "archive.tar.bz2", true);

    // Filename with no extension (should not modify and return false)
    run_test("No extension", "README", "md", "README", false);

    // Hidden files starting with a dot like .gitignore (should not modify and return false)
    run_test("Hidden file", ".gitignore", "txt", ".gitignore", false);

    // Just a dot
    run_test("Just a dot", ".", "txt", ".", false);

    // Empty strings
    run_test("Empty string", "", "csv", "", false);

    printf("\nTests complete: %d passed, %d failed.\n", passed, failed);

    return failed == 0 ? 0 : 1;
}
