## 2024-03-23 - Telemetry Interval Busy-Wait Loop Optimization and Bugfix
**Learning:** Found a busy-wait polling loop `while (millis() - sampleInterval < startTime) delay(10);` in `telemetry.cpp` used to pad the collection interval. However, because both `millis()` and `sampleInterval` are unsigned `uint32_t`, if `millis()` is smaller than `sampleInterval` (e.g. at startup or just immediately), it causes an integer underflow resulting in a massive number. This massive number is never less than `startTime`, causing the loop to exit immediately without delaying at all.
**Action:** Replaced polling loops with single sleep commands (`vTaskDelay`) by calculating elapsed time `elapsedTime = millis() - startTime` first, and then checking `if (elapsedTime < sampleInterval)`. This correctly accounts for unsigned math while avoiding busy-wait overhead and actually enforcing the correct interval rate.

## 2024-05-18 - Dangling Pointer Hazard with String Return Types
**Learning:** In the ESP32 Arduino core, methods like `ETH.macAddress()` and `WiFi.STA.macAddress()` return a `String` object by value. Attempting to optimize memory allocations by changing the function signature to return `const char*` and chaining `.c_str()` (e.g. `ETH.macAddress().c_str()`) directly on the returned value creates a severe use-after-free bug (dangling pointer) because the temporary `String` is destructed immediately, invalidating the buffer.
**Action:** Never extract `.c_str()` directly from a function that returns a `String` by value if the pointer is expected to outlive the statement.

## 2024-05-18 - Replacing Dynamic String Allocation with snprintf
**Learning:** Calling `String(FPS).c_str()` causes a dynamic heap allocation for the temporary `String` object and an unnecessary string copy. This pattern occurred repeatedly within a frame processing block, contributing to heap fragmentation and CPU overhead.
**Action:** Replace `String(number).c_str()` patterns with a statically sized local buffer (e.g. `char fpsStr[10]`) and `snprintf` to stringify numbers efficiently.
