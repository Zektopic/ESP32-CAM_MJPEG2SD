## 2024-05-24 - Image processing optimization

**Learning:** `rgbToGray` was recalculating array offsets dynamically using multiplication (`i * 3`). While standard on desktops, this is expensive on resource-constrained microcontrollers like the ESP32.
**Action:** Use pointer-bumping/arithmetic (`*dst++`, `src += 3`) for all performance-critical image processing loops to avoid index calculation overhead.
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
## 2025-02-12 - Fixed-point integer math in image processing
**Learning:** On ESP32 devices, floating-point arithmetic inside tight image processing loops (e.g., bilinear interpolation in `rescaleImage`) causes severe performance bottlenecks because floating point operations are expensive.
**Action:** Use fixed-point integer math with bitshifting (e.g., scaling ratios by `1 << 16` into `uint32_t`) to optimize performance while maintaining required precision.
## 2024-05-30 - O(N^2) String Concatenation in Loops (Schlemiel the Painter's Algorithm)
**Learning:** When concatenating strings inside a loop in C/C++ (e.g., during base64 encoding), avoid using `strcat` or `strncat`. These functions repeatedly scan the destination string from the beginning to find the null terminator on every single iteration, leading to O(N^2) time complexity.
**Action:** Always maintain an offset tracking variable (`int outLen = 0`) and use `memcpy` to append data (`memcpy(encoded + outLen, chunk, size); outLen += size;`). This ensures the write location is explicitly known, dropping the time complexity to O(N).
## 2024-06-25 - Array Offset Recalculation Overhead in Nested Loops
**Learning:** Found an inefficiency in `motionDetect.cpp` during bilinear interpolation where matrix elements were fetched dynamically within a tight inner loop utilizing multi-dimensional matrix mathematics `input[(yL * inputWidth + xL) * colorDepth + channel]`. For every pixel on every channel, these variables are re-calculated repeatedly, causing significant lag on ESP32 devices when handling real-time streams.
**Action:** Extract all base matrix additions before the loops and increment loop matrix arrays with pointer-bumping (`idxA++`) rather than performing full matrix element math on every operation.

## 2024-06-25 - Unroll runtime-constant loops in tight paths
**Learning:** Found an inefficiency in `motionDetect.cpp` where pixel processing functions (`rescaleImage`, `getImageData`, `checkMotion`) used inner `for` loops (e.g., `for (int channel = 0; channel < colorDepth; channel++)`) to process color channels. Since `colorDepth` is constant for any given frame execution, continuously evaluating this condition within loops that run ~9,216 times per frame causes substantial loop setup and branch prediction overhead on ESP32.
**Action:** Unroll loops that depend on runtime-configured variables that are locally constant inside performance-critical paths by using explicit branches (e.g., `if (colorDepth == 3) { ... } else { ... }`). This completely eliminates loop iteration overhead in tight algorithms on microcontrollers.

## 2024-06-25 - Batch Network Writes to Prevent TCP Overhead
**Learning:** When sending base64 encoded data over a network socket (e.g., in SMTP attachments), using `client.write` for tiny chunks (e.g., 4 bytes) causes severe TCP network overhead due to tiny packet sizes.
**Action:** Always allocate a larger buffer to batch encoded data before transmitting it over the network to reduce network calls and packet overhead.
## 2025-02-13 - Correct Fallback Behavior When Loop Unswitching
**Learning:** When manually unswitching/unrolling loops based on runtime constants like `colorDepth` (e.g., in `motionDetect.cpp`), explicitly ensure that the fallback `else` branch retains the dynamic increment (`i += colorDepth`) rather than hardcoding it to `1`, to correctly support configurations where `colorDepth` is neither 1 nor 3 (e.g., RGB565).
**Action:** When creating unrolled loop branches, closely match the increment and array access logic of the original loop in the fallback branch instead of making assumptions about alternative values.

## 2024-06-25 - Avoid O(N^2) strlen overhead in formatting loops
**Learning:** Calling `strlen()` to find the end of a buffer inside a loop (e.g. `sprintf(buf + strlen(buf), ...)`) causes an O(N^2) performance hit because it has to traverse the entire string on each iteration.
**Action:** Maintain an `offset` variable and use `offset += snprintf(buf + offset, size - offset, ...)` to concatenate strings in O(N) time.
## 2026-05-11 - Unswitch loops for constants in performance critical sections
**Learning:** For manually unswitching loops on runtime-configured but locally constant variables like `colorDepth`, copying the inner operations in full branches saves branch predictions and avoids looping overheads on embedded microcontrollers like the ESP32.
**Action:** When working with image processing loops in ESP32 projects, always hoist if checks over constants like `colorDepth` outside to duplicate the loops.

## 2024-11-20 - O(N) Performance hit via redundant strlen Calls
**Learning:** Redundant `strlen(variable)` calls in string extraction paths (e.g., `extractQueryKeyVal` and `appSpecific.cpp`) or in `strncpy` operations are causing redundant string traversal. Instead of using pointer math or recalculating, we can remove the redundant splitting logic completely if the function has already separated them, or use a cached length/direct pointer math like `endPtr + 1`.
**Action:** Avoid re-splitting strings that have already been separated by `extractQueryKeyVal`, and avoid calling `strlen` repeatedly on the same variable to extract the value if a pointer like `endPtr` is already available from `strchr`.
## 2026-05-20 - File Read Return Values
**Learning:** When performing bulk I/O with `file.read()` on ESP32, the reported `file.size()` may not exactly match the bytes read. Relying on `file.size()` to set loop bounds without capturing the return value can result in out-of-bounds reads into uninitialized memory.
**Action:** Always capture the return value of `file.read()` (e.g. `size_t bytesRead = file.read(...)`) and use it to bound operations and set the null terminator.

## 2024-05-24 - Avoid O(N) length recalculations and pointer extraction overhead in String comparisons
**Learning:** Comparing `String` or `std::string` objects using `.c_str()` with `strcmp()`, `strlen()`, or `strstr()` bypasses the string object's cached length, introducing unnecessary O(N) length recalculations and pointer extraction overhead.
**Action:** Use native string methods and operators (e.g. `==`, `.length()`, `.find()`, `.compare()`) instead of converting to C-strings for string operations and comparisons.

## 2024-05-24 - Optimize Bilinear Interpolation Row Calculations
**Learning:** Found that bilinear interpolation was repeatedly multiplying row indices inside the inner width loop, costing extra instructions on each pixel step.
**Action:** Hoist the input row offset calculations (both low and high rows) out of the inner loop and access elements via pointer arithmetic (`rowL + offset`, `rowH + offset`) to significantly reduce loop instruction count.

## 2025-02-13 - O(N^2) strlen overhead in backtrace string formatting
**Learning:** Calling `strlen()` to find the end of a buffer inside a formatting loop (e.g., `snprintf(bt + strlen(bt), ...)`) causes an O(N^2) performance hit because it has to traverse the entire string on each iteration (Schlemiel the Painter's Algorithm).
**Action:** Always maintain an explicit `offset` tracker variable and use `offset += snprintf(bt + offset, size - offset, ...)` to concatenate strings in O(1) time per iteration, along with proper bounds checking `if (written > 0 && written < (int)(size - offset))`.

## 2024-05-31 - Avoid O(N^2) strlen overhead in formatting loops
**Learning:** Calling `strlen()` to find the end of a buffer inside a loop (e.g., `snprintf(buf + strlen(buf), ...)`) causes an O(N^2) performance hit because it has to traverse the entire string on each iteration. Furthermore, calculating differences with `sizeof` and `strlen` (e.g., `sizeof(bt) - strlen(bt) - 11`) can silently underflow to `SIZE_MAX` if bounds are exceeded, leading to a critical buffer overflow.
**Action:** Maintain an `offset` variable and calculate the remaining space (`remaining = sizeof(buf) - offset`). Update the offset safely with `offset += written` inside the loop, and use `snprintf(buf + offset, remaining, ...)` to concatenate strings safely in O(N) time.

## 2024-05-03 - String Pointer Optimization
**Learning:** In C/C++ applications on the ESP32, repeatedly calculating string offsets with `strlen()` during in-place string splitting loops introduces an unnecessary O(N) performance penalty.
**Action:** When a pointer to a split character (e.g., via `strchr()`) is already computed and bounded, use pointer arithmetic (`endPtr + 1`) to advance to the remainder of the string instead of re-calculating the length (`variable + strlen(variable) + 1`).
## 2024-05-19 - Replace Stream::readBytes() with block reads for massive bulk I/O speedup
**Learning:** In the ESP32/Arduino framework, the default `Stream::readBytes()` virtual method is devastatingly slow for bulk I/O. It loops byte-by-byte, checking timeouts via `millis()` on every single byte. When operating on derived classes like `fs::File`, `NetworkClientSecure`, or `I2SClass`, bypassing `readBytes()` in favor of the block read `read(uint8_t* buf, size_t size)` delegates execution to underlying DMA or memory copies, removing massive framework overhead. Also importantly, `file.read()` returns the actual read length, which must be explicitly used to null-terminate buffers, instead of implicitly trusting `file.size()`.
**Action:** Always hunt for `readBytes` in performance-critical ESP32 buffers and replace it with `read()`. Always cap buffers with a null-terminator using the returned read length explicitly.
