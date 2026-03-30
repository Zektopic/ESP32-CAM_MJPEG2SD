#include "stringUtils.h"
#include <string.h>

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
