#pragma once
#include <string>
#include <regex>
#include <cstring>
#include <cstdlib>
#include <cctype>

bool urlEncode(const char* inVal, char* encoded, size_t maxSize);
void urlDecode(char* inVal);
