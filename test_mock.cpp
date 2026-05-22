#include <iostream>
#include <cstring>

bool isPathTraversal(const char* path) {
  if (!path) return false;
  return strstr(path, "../") || strstr(path, "..\\") ||
         strstr(path, "/..") || strstr(path, "\\..") ||
         !strcmp(path, "..");
}

int main() {
    const char* test_cases[] = {
        "valid_path.txt",
        "folder/file.svg",
        "../file.txt",
        "..\\file.txt",
        "/..",
        "folder/../file",
        ".."
    };

    bool expected[] = {
        false,
        false,
        true,
        true,
        true,
        true,
        true
    };

    bool all_passed = true;
    for (int i = 0; i < 7; ++i) {
        bool result = isPathTraversal(test_cases[i]);
        if (result != expected[i]) {
            std::cout << "Test failed for: " << test_cases[i] << " Expected: " << expected[i] << " Got: " << result << std::endl;
            all_passed = false;
        }
    }

    if (all_passed) {
        std::cout << "All path traversal tests passed!" << std::endl;
        return 0;
    }
    return 1;
}
