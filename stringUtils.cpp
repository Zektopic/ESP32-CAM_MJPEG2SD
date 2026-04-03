#include "stringUtils.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool isPathTraversal(const char* path) {
  if (!path) return false;
  return strstr(path, "../") || strstr(path, "..\\") ||
         strstr(path, "/..") || strstr(path, "\\..") ||
         !strcmp(path, "..");
}

void removeChar(char* s, char c) {
  // remove specified character from string
  int writer = 0, reader = 0;
  while (s[reader]) {
    if (s[reader] != c) s[writer++] = s[reader];
    reader++;
  }
  s[writer] = 0;
}

void urlDecode(char* inVal) {
  // replace url encoded characters in-place
  char* src = inVal;
  char* dst = inVal;
  while (*src) {
    if (*src == '%' && isxdigit((unsigned char)src[1]) && isxdigit((unsigned char)src[2])) {
      char hex[3] = {src[1], src[2], 0};
      *dst++ = (char)strtol(hex, nullptr, 16);
      src += 3;
    } else {
      *dst++ = *src++;
    }
  }
  *dst = '\0';
}
