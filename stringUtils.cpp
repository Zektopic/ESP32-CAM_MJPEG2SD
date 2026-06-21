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
  size_t inNamePtr = strlen(fileName);
  // find '.' before extension text
  while (inNamePtr > 0 && fileName[inNamePtr] != '.') inNamePtr--;
  inNamePtr++;
  size_t extLen = strlen(newExt);
  memcpy(fileName + inNamePtr, newExt, extLen);
  fileName[inNamePtr + extLen] = 0;
  return (inNamePtr > 1) ? true : false;
}

bool urlEncode(const char* inVal, char* encoded, size_t maxSize) {
  int encodedLen = 0;
  char hexTable[] = "0123456789ABCDEF";
  while (*inVal) {
    if (isalnum((unsigned char)*inVal) || strchr("$-_.+!*'(),:@~#", *inVal)) {
      encodedLen++;
      // Check considering null terminator
      if (encodedLen + 1 > maxSize) return false;
      *encoded++ = *inVal;
    } else {
      encodedLen += 3;
      if (encodedLen + 1 > maxSize) return false;  // Buffer overflow
      *encoded++ = '%';
      *encoded++ = hexTable[((unsigned char)*inVal) >> 4];
      *encoded++ = hexTable[((unsigned char)*inVal) & 0xf];
    }
    inVal++;
  }
  *encoded = 0;
  return true;
}
