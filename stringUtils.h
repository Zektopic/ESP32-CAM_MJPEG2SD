#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

void removeChar(char* s, char c);
void urlDecode(char* inVal);
bool isPathTraversal(const char* path);

#ifdef __cplusplus
}
#endif

#endif
