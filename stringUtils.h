#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>
#include <stdint.h>


#include <stdbool.h>

bool isPathTraversal(const char* path);
size_t isSubArray(uint8_t* haystack, uint8_t* needle, size_t hSize, size_t nSize);
void removeChar(char* s, char c);

#endif
