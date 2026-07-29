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

## 2024-05-29 - Block reads bypass timedRead overhead
**Learning:** In the ESP32/Arduino framework, `Stream::readBytes()` (used by `File` and `WiFiClientSecure`) incurs significant performance overhead due to per-byte timeout checks (`millis()` via `timedRead()`). This is essentially an O(N) overhead layer around what could be a block read.
**Action:** When loading data into memory buffers where the size is known or we want to read everything available, prefer block reading via `read(uint8_t* buf, size_t size)` over `readBytes()` to bypass this timer overhead and drastically improve bulk I/O performance.
## 2024-11-25 - Frontend DOM Layout Thrashing in Log Rendering
**Learning:** Using `log.innerHTML += ...` inside a recursive `setTimeout` loop recalculates and appends to the DOM sequentially. For large log texts containing thousands of lines, this causes severe layout thrashing and an $O(N^2)$ string concatenation overhead that blocks the frontend.
**Action:** When rendering large arrays of structured text sequentially into the DOM on the frontend, accumulate the transformed strings into an array (`htmlLines`), `join('')` them into a single blob, and update the DOM in one synchronous assignment (`log.innerHTML = ...`).
## 2026-05-21 - O(N^2) strlen overhead in tight inner formatting loops
**Learning:** Found a performance bottleneck inside `checkMotion` in `motionDetect.cpp` where `strlen()` was being called repeatedly inside an inner loop iterating over the `EI_CLASSIFIER_LABEL_COUNT`. `sprintf(outcome + strlen(outcome), ...)` forces the string to be traversed completely on every single append, yielding an O(N^2) complexity that unnecessarily wastes CPU cycles in a tight ML processing path.
**Action:** Replaced the `strlen(outcome)` with a managed `offset` variable, transforming the loop concatenation to `snprintf(outcome + offset, remaining, ...)`, making the operation O(1) per iteration while simultaneously preventing potential buffer overflows.
## 2024-06-19 - Non-blocking servo sweeps
**Learning:** The servo control task blocked the RTOS task thread while sweeping due to `delay()` inside a loop. This prevented the task from processing new pan/tilt notifications instantly and forced sequential panning.
**Action:** Replaced the loop with stateful non-blocking time checks using `millis()` and computed an appropriate `waitTicks` dynamically to use with `ulTaskNotifyTake`. This completely decoupled the sweeps from task execution, halving benchmark sweep time by allowing concurrent sweeps.
## 2024-06-24 - [Optimize strlen on string literals and identical strings]
**Learning:** Calling `strlen` on string literal macros (like `WEBDAV`) forces potential O(N) runtime evaluation instead of compile-time constants. Additionally, repeatedly calling `strlen` on the same dynamic string without modifying it causes redundant O(N) traversals.
**Action:** When evaluating the length of string literals or macros, use `sizeof(MACRO) - 1` instead of `strlen`. When evaluating the length of the same dynamic string multiple times in a function block, cache the length into a variable (e.g., `size_t pathLen = strlen(pathName);`).
## 2024-05-24 - Compile-time strlen for Literals
**Learning:** In the ESP32 codebase, many HTTP and FTP handlers use `strlen()` on hardcoded macros (like `END_BOUNDARY` or `WEBDAV`) and string literals inside loops or hot paths. This causes unnecessary O(N) runtime overhead.
**Action:** Replace `strlen(MACRO)` with `(sizeof(MACRO) - 1)` to enforce compile-time length calculation, saving CPU cycles during network operations.
## 2024-05-25 - Avoid O(N) strlen overhead after snprintf
**Learning:** Determining the length of a string immediately after formatting it with `snprintf` by calling `strlen()` causes an unnecessary O(N) traversal of the string that was just constructed.
**Action:** Use the return value of `snprintf` (clamped to the buffer size if it exceeds the bounds, e.g., `if (len >= size) len = size - 1;`) to determine the length of the formatted string in O(1) time.

## 2024-07-18 - Avoid O(N) strlen checks for string emptiness
**Learning:** Using `strlen(str) > 0` or `!strlen(str)` to check if a string is empty or not introduces an unnecessary O(N) traversal of the entire string up to the null terminator. In functions called sequentially (like `sendHasEntities`), this overhead accumulates.
**Action:** Replace `strlen(str) > 0` with `str[0] != '\0'` (or simply `str[0]`) and `!strlen(str)` with `str[0] == '\0'` (or `!str[0]`). This reduces the time complexity of emptiness checks to O(1).

## 2024-05-30 - O(1) String Emptiness Checks
**Learning:** In C/C++, checking if a string is empty using `strlen(str) == 0` or `!strlen(str)` requires an O(N) traversal of the string to find the null terminator. This introduces unnecessary overhead, especially in loops or frequently called functions like MQTT serialization.
**Action:** Replace `strlen` emptiness checks with O(1) character checks: `str[0] == '\0'` or `str[0] != '\0'`.

## 2024-05-24 - O(N) strlen overhead for boolean empty checks
**Learning:** Checking if a string is empty or has a minimal length using `strlen(str) > 0` or `strlen(str) > 1` forces an O(N) traversal of the string, which is inefficient, especially when checking many dynamically parsed strings like HTTP parameters or parsed JSON keys.
**Action:** Replace length boundary checks with O(1) direct character evaluations utilizing boolean short-circuiting. Use `str[0] != '\0'` instead of `strlen(str) > 0` and `str[0] != '\0' && str[1] != '\0'` instead of `strlen(str) > 1`.

## 2024-05-18 - Avoid blocking loops in File IO
**Learning:** In ESP32/FreeRTOS systems, tight loops reading/writing large chunks to/from slow hardware (like SD cards) will block the current task, potentially triggering Watchdog timeouts and starving other system processes.
**Action:** Always insert `vTaskDelay(1)` or `yield()` inside heavy processing loops (like chunked file IO) to allow other tasks to execute.

## 2024-05-24 - Replace delay with vTaskDelay in FreeRTOS tasks
**Learning:** Arduino's `delay()` function introduces overhead such as watchdog resets, `yieldIfNecessary()`, and busy-waiting via `micros()` to ensure exact delays.
**Action:** When working in FreeRTOS tasks on ESP32, replace `delay(ms)` with native `vTaskDelay(pdMS_TO_TICKS(ms))` to properly place the task in the Blocked state and free CPU cycles for other tasks.
## 2024-11-20 - Replace redundant strncpy+strlen with a single snprintf
**Learning:** Using `strncpy` followed by `snprintf` with `strlen()` to append strings (e.g., `strncpy(subject, _subject, sizeof(subject)-1); snprintf(subject+strlen(subject), ...);`) causes redundant O(N) string traversals and creates potential buffer overruns.
**Action:** Combine multi-step string building operations into a single bounded `snprintf(dest, sizeof(dest), "%s from %s", _subject, hostName)` to eliminate redundant string length calculations.
