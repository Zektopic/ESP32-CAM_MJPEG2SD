## 2024-05-24 - Avoid temporary String allocations for integers
**Learning:** Using `String(intVal).c_str()` in an ESP32 codebase causes unnecessary heap allocation and memory fragmentation, which is a performance bottleneck.
**Action:** Replace `String(intVal).c_str()` with a local `char` buffer and `snprintf(buffer, sizeof(buffer), "%d", intVal)` to allocate on the stack.
## 2024-03-23 - Telemetry Interval Busy-Wait Loop Optimization and Bugfix
**Learning:** Found a busy-wait polling loop `while (millis() - sampleInterval < startTime) delay(10);` in `telemetry.cpp` used to pad the collection interval. However, because both `millis()` and `sampleInterval` are unsigned `uint32_t`, if `millis()` is smaller than `sampleInterval` (e.g. at startup or just immediately), it causes an integer underflow resulting in a massive number. This massive number is never less than `startTime`, causing the loop to exit immediately without delaying at all.
**Action:** Replaced polling loops with single sleep commands (`vTaskDelay`) by calculating elapsed time `elapsedTime = millis() - startTime` first, and then checking `if (elapsedTime < sampleInterval)`. This correctly accounts for unsigned math while avoiding busy-wait overhead and actually enforcing the correct interval rate.

## 2024-03-23 - Schlemiel the Painter's Algorithm in String Concatenation
**Learning:** Found an O(N^2) complexity issue inside `utilsFS.cpp` during directory parsing where `strlen(jsonBuff)` and `strcat(jsonBuff, ...)` were used inside a loop across potentially thousands of files. `jsonBuff` can be up to 32 KB long, meaning parsing directories was recalculating the length linearly at every step (Schlemiel the Painter's algorithm).
**Action:** Replaced the loop `strlen` and `strcat` with a tracked `buffLen` variable (`size_t buffLen = strlen(jsonBuff);`) that is incremented on each string copy `strcpy(jsonBuff + buffLen, fileInfo.c_str())`. This drops the time complexity of assembling the directory JSON response from O(N^2) to O(N).
## 2024-05-24 - Cache `strlen()` Result to Avoid Repeated O(N) Calculation in Loop Condition
**Learning:** Found a performance bottleneck in `periphsI2C.cpp` inside a `for` loop, where `strlen(str)` was called in the loop termination condition (`for (int i=0; i<strlen(str); i++)`). This recalculates the length of the string on every iteration, leading to an O(N^2) time complexity.
**Action:** Extract the length calculation outside the loop into a variable (`int len = strlen(str);`) and use the variable in the loop condition (`for (int i=0; i<len; i++)`). This optimization reduces the loop execution time complexity from O(N^2) back to O(N).

## 2024-05-24 - Avoid O(N) length recalculations when comparing String objects
**Learning:** Comparing `String` or `std::string` objects (like `WiFi.SSID()`) to C-strings using `strcmp(str.c_str(), "val")` bypasses the object's native O(1) length tracking, forcing `strcmp` to recalculate the length character-by-character, leading to unnecessary O(N) overhead.
**Action:** Use native comparison operators like `str == "val"` instead to leverage the string class's internal length tracking and optimized comparison logic.
## 2024-05-24 - Avoid std::string and std::regex for Basic String Parsing
**Learning:** Found an extremely inefficient `urlDecode` function in `utils.cpp` that used `std::string`, `std::regex_search`, and `std::regex_replace` to parse and decode strings. On memory-constrained devices like the ESP32, this causes significant performance overhead due to multiple dynamic heap allocations, regex compilation, and O(N*M) time complexity.
**Action:** Replaced the regex and `std::string` implementation with an in-place C-string parsing loop (`char* readPtr`, `char* writePtr`) to process the string in O(N) time with no dynamic allocations or heap fragmentation.
## 2024-05-15 - Optimize String Operations
**Learning:** Found several places where `strlen()` was being called on `String.c_str()` or `std::string.c_str()` which converts an O(1) length operation into an O(N) operation since the string's length is already cached in the class but `strlen()` must iterate to find the null byte. Also `strcmp(String.c_str(), "val")` does the same.
**Action:** Replace `strlen(String.c_str())` with `String.length()` and `strcmp` with native `.compare()` or `==` operators.
## 2024-04-10 - O(N) string traversals in routing chains
**Learning:** Calling `strlen()` on the requested URL inside a series of `else if` conditions (used to determine content type based on extension) leads to redundant O(N) calculations. Furthermore, calculating suffix pointer with `variable+(strlen(variable)-strlen(EXT))` without first verifying `strlen(variable) >= strlen(EXT)` is unsafe and can lead to underflow issues.
**Action:** Always cache the length of the string requested before evaluating file extensions in a routing chain, and explicitly check if the length is long enough before performing pointer arithmetic for suffix comparison.
## 2024-05-30 - O(N) strlen overhead when building large JSON objects
**Learning:** When building a large string incrementally across multiple functions (e.g. `buildJsonString` calling `buildAppJsonString`), having the child function return `void` and then using `p += strlen(buffer)` in the parent function forces an O(N) recalculation of the string length just to find the new end of the buffer.
**Action:** Modify the child function to return a pointer to the new end of the string (`char*`) instead of `void`. The parent function can then directly update its pointer without calling `strlen`, eliminating the overhead.
## 2024-05-24 - O(N^2) complexity in Base64 Encoding
**Learning:** Found an O(N^2) complexity issue inside `utils.cpp` during base64 encoding where `strncat(encoded, ...)` was used inside a loop across the input string. `strncat` repeatedly scans for the null terminator, creating quadratic behavior.
**Action:** Replaced `strncat` with an offset-tracked `memcpy(encoded + offset, ...)` and manual null-termination, dropping the complexity to O(N). Added an inline comment explaining the optimization.
