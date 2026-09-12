#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>

// removeChar is already declared in globals.h
bool isPathTraversal(const char* path);

bool changeExtension(char* fileName, const char* newExt);

bool urlEncode(const char* inVal, char* encoded, size_t maxSize);

#endif
