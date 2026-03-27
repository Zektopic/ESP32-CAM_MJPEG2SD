## 2024-05-24 - Avoid temporary String allocations for integers
**Learning:** Using `String(intVal).c_str()` in an ESP32 codebase causes unnecessary heap allocation and memory fragmentation, which is a performance bottleneck.
**Action:** Replace `String(intVal).c_str()` with a local `char` buffer and `snprintf(buffer, sizeof(buffer), "%d", intVal)` to allocate on the stack.