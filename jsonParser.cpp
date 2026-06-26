/*
Usage: 
  char value[];
  String json = http.getString();
  const char* var = "find";
  getJsonValue(json.c_str(), var, value, 2);
  // 'value' contains returned value associated with variable

  s60sc 2026
*/

#ifndef TEST_ENV
#include "appGlobals.h"
#else
#define FILE_NAME_LEN 64
#include <cstring>
#endif

#include <string_view>
#include <algorithm>

static std::string_view extractNestedValue(std::string_view jsonObject, std::string_view nestedKey);

static void skipWhitespace(std::string_view json, size_t& pos) {
  while (pos < json.length() && std::isspace(json[pos])) pos++;
}

static std::string_view parseString(std::string_view json, size_t& pos) {
  if (json[pos] != '"') return "";
  pos++; // Skip opening quote
  
  size_t start = pos;
  while (pos < json.length()) {
    if (json[pos] == '\\') pos += 2; // Skip escaped character
    else if (json[pos] == '"') {
      std::string_view result = json.substr(start, pos - start);
      pos++; // Skip closing quote
      return result;
    } else pos++;
  }
  return "";
}

static void skipValue(std::string_view json, size_t& pos) {
  if (json[pos] == '"') parseString(json, pos);
  else if (json[pos] == '{') {
    int depth = 1;
    pos++;
    while (pos < json.length() && depth > 0) {
      if (json[pos] == '"') parseString(json, pos);
      else if (json[pos] == '{') {
        depth++;
        pos++;
      } else if (json[pos] == '}') {
        depth--;
        pos++;
      } else pos++;
    }
  } else if (json[pos] == '[') {
    int depth = 1;
    pos++;
    while (pos < json.length() && depth > 0) {
      if (json[pos] == '"') parseString(json, pos);
      else if (json[pos] == '[') {
        depth++;
        pos++;
      } else if (json[pos] == ']') {
        depth--;
        pos++;
      } else pos++;
    }
  } else {
    // Number, boolean, null
    while (pos < json.length() && 
         json[pos] != ',' && 
         json[pos] != '}' && 
         json[pos] != ']') {
      pos++;
    }
  }
}

static std::string_view parseValue(std::string_view json, size_t& pos) {
  size_t start = pos;
  if (json[pos] == '"') return parseString(json, pos);
  else if (json[pos] == '{' || json[pos] == '[') {
    skipValue(json, pos);
    return json.substr(start, pos - start);
  } else {
    // Number, boolean, null - trim whitespace
    while (pos < json.length() && json[pos] != ',' 
      && json[pos] != '}' && json[pos] != ']' && !std::isspace(json[pos])) pos++;
  }
  std::string_view result = json.substr(start, pos - start);
  // Trim trailing whitespace
  size_t end = result.find_last_not_of(" \t\n\r");
  return (end != std::string_view::npos) ? result.substr(0, end + 1) : result;
}

// Recursively search through entire JSON structure for nth occurrence
static std::string_view findNthOccurrence(std::string_view json, size_t& pos, std::string_view key, int& occurrence, int targetOccurrence, bool extractNested = false, std::string_view nestedKey = "") {
  skipWhitespace(json, pos);
  if (pos >= json.length()) return "";
  if (json[pos] == '{') {
    pos++;
    
    while (pos < json.length()) {
      skipWhitespace(json, pos);
      
      if (json[pos] == '}') {
          pos++;
          break;
      }
      
      // Parse key
      std::string_view currentKey = parseString(json, pos);
      skipWhitespace(json, pos);
      
      if (pos >= json.length() || json[pos] != ':') return "";
      pos++;
      skipWhitespace(json, pos);
      
      // Check if this is our key
      if (currentKey == key) {
        occurrence++;
        if (occurrence == targetOccurrence) {
          std::string_view value = parseValue(json, pos);
          // If we need to extract a nested value from the object
          if (extractNested && !nestedKey.empty() && !value.empty() && value[0] == '{') {
            return extractNestedValue(value, nestedKey);
          }
          return value;
        } else skipValue(json, pos);
      } else {
        // Recursively search in nested structures
        if (json[pos] == '{' || json[pos] == '[') {
          std::string_view result = findNthOccurrence(json, pos, key, occurrence, targetOccurrence, extractNested, nestedKey);
          if (!result.empty()) return result;
        } else skipValue(json, pos);
      }
      
      skipWhitespace(json, pos);
      if (pos < json.length() && json[pos] == ',') pos++;
    }
  } else if (json[pos] == '[') {
    pos++;
    
    while (pos < json.length()) {
      skipWhitespace(json, pos);
      
      if (json[pos] == ']') {
        pos++;
        break;
      }
      
      // Recursively search array elements
      if (json[pos] == '{' || json[pos] == '[') {
        std::string_view result = findNthOccurrence(json, pos, key, occurrence, targetOccurrence, extractNested, nestedKey);
        if (!result.empty()) return result;
      } else skipValue(json, pos);

      skipWhitespace(json, pos);
      if (pos < json.length() && json[pos] == ',') pos++;
    }
  }
  return "";
}

// New helper function to extract a nested value
static std::string_view extractNestedValue(std::string_view jsonObject, std::string_view nestedKey) {
  size_t pos = 0;
  int count = 0;
  return findNthOccurrence(jsonObject, pos, nestedKey, count, 1);
}

// Updated function signatures
bool getJsonValue(const char* json, const char* key, char* value, const char* nestedKey, int occurrence) {
  // Returns nth occurrence (1-indexed, default is 1)
  // If nestedKey is provided, extracts that field from the object value
  // ⚡ Bolt optimization: Use string_view instead of string copies for zero-copy string references
  std::string_view jsonStr(json);
  std::string_view keyStr(key);
  if (occurrence < 1) occurrence = 1;
  size_t pos = 0;
  int count = 0;
  
  bool extractNested = (nestedKey != nullptr && strlen(nestedKey) > 0);
  std::string_view nestedKeyStr = extractNested ? std::string_view(nestedKey) : std::string_view("");
  
  std::string_view retvalue = findNthOccurrence(jsonStr, pos, keyStr, count, occurrence, extractNested, nestedKeyStr);
  value[0] = '\0';
  if (!retvalue.empty()) {
      size_t copy_len = std::min(retvalue.length(), (size_t)(FILE_NAME_LEN - 1));
      memcpy(value, retvalue.data(), copy_len);
      value[copy_len] = '\0';
      return true;
  }
  return false;
}