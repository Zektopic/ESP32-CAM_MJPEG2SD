#include "stringUtils.h"
#include <ctype.h>
#include <string.h>

bool isPathTraversal(const char* path) {
  if (!path) return false;
  return strstr(path, "../") || strstr(path, "..\\") ||
         strstr(path, "/..") || strstr(path, "\\..") ||
         !strcmp(path, "..");
}

// removeChar is defined in utils.cpp and declared in globals.h
bool changeExtension(char* fileName, const char* newExt) {
  // replace original file extension with supplied extension (buffer must be large enough)
  if (!fileName || !newExt) return false;
  int inNamePtr = (int)strlen(fileName) - 1;
  // find '.' before extension text, stopping at path separators
  while (inNamePtr >= 0 && fileName[inNamePtr] != '.' && fileName[inNamePtr] != '/' && fileName[inNamePtr] != '\\') inNamePtr--;
  if (inNamePtr < 0 || fileName[inNamePtr] != '.') return false; // No extension found, do not corrupt buffer
  inNamePtr++;
  size_t extLen = strlen(newExt);
  memcpy(fileName + inNamePtr, newExt, extLen);
  fileName[inNamePtr + extLen] = 0;
  return (inNamePtr > 1) ? true : false;
}

bool urlEncode(const char* inVal, char* encoded, size_t maxSize) {
  size_t encodedLen = 0;
  static const char hexTable[] = "0123456789ABCDEF";
  // Optimized: Use a lookup table to determine unreserved characters in O(1) time
  // to avoid costly function calls (isalnum, strchr) inside a tight loop.
  static const bool unreserved[256] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  while (*inVal) {
    unsigned char c = (unsigned char)*inVal;
    if (unreserved[c]) {
      encodedLen++;
      // Check considering null terminator
      if (encodedLen + 1 > maxSize) return false;
      *encoded++ = c;
    } else {
      encodedLen += 3;
      if (encodedLen + 1 > maxSize) return false;  // Buffer overflow
      *encoded++ = '%';
      *encoded++ = hexTable[c >> 4];
      *encoded++ = hexTable[c & 0xf];
    }
    inVal++;
  }
  *encoded = 0;
  return true;
}
