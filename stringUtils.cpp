#include "stringUtils.h"
#include <string.h>

bool changeExtension(char* fileName, const char* newExt) {
  // replace original file extension with supplied extension (buffer must be large enough)
  size_t inNamePtr = strlen(fileName);

  if (inNamePtr == 0) {
      return false;
  }

  // find '.' before extension text
  while (inNamePtr > 0 && fileName[inNamePtr] != '.') {
      inNamePtr--;
  }

  // If no dot was found, or the dot is the very first character (like a hidden file), don't change
  if (inNamePtr == 0) {
      return false;
  }

  inNamePtr++; // point to just after the dot
  size_t extLen = strlen(newExt);
  memcpy(fileName + inNamePtr, newExt, extLen);
  fileName[inNamePtr + extLen] = 0; // null terminate
  return true;
}
