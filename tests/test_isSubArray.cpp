#include "../stringUtils.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>
void test(const std::vector<uint8_t>& haystack, const std::vector<uint8_t>& needle, size_t expected) {
    // We use const_cast because the original function takes non-const pointers,
    // though it doesn't modify the arrays.
    uint8_t* h_ptr = haystack.empty() ? nullptr : const_cast<uint8_t*>(haystack.data());
    uint8_t* n_ptr = needle.empty() ? nullptr : const_cast<uint8_t*>(needle.data());

    size_t result = isSubArray(h_ptr, n_ptr, haystack.size(), needle.size());

    if (result != expected) {
        std::cerr << "Test failed!" << std::endl;
        std::cerr << "Expected: " << expected << std::endl;
        std::cerr << "Got:      " << result << std::endl;
        exit(1);
    }
}

int main() {
    // 1. Exact match in the middle
    test({1, 2, 3, 4, 5}, {3, 4}, 4);

    // 2. Exact match at the start
    test({1, 2, 3, 4, 5}, {1, 2}, 2);

    // 3. Exact match at the end
    test({1, 2, 3, 4, 5}, {4, 5}, 5);

    // 4. No match
    test({1, 2, 3, 4, 5}, {6, 7}, 0);

    // 5. Partial match at the end (needle larger than remaining haystack)
    test({1, 2, 3, 4, 5}, {4, 5, 6}, 0);

    // 6. Partial match needing backtracking
    test({1, 1, 1, 2}, {1, 1, 2}, 4);
    test({10, 20, 10, 20, 30}, {10, 20, 30}, 5);

    // 7. Empty haystack
    test({}, {1, 2}, 0);

    // 8. Empty needle (isSubArray logic returns 0 when nSize is 0 because the while loop condition n < nSize fails)
    test({1, 2, 3}, {}, 0);

    // 9. Both empty
    test({}, {}, 0);

    // 10. Needle larger than haystack
    test({1, 2}, {1, 2, 3}, 0);

    // 11. Single element arrays
    test({5}, {5}, 1);
    test({5}, {6}, 0);

    std::cout << "All isSubArray tests passed!" << std::endl;
    return 0;
}
