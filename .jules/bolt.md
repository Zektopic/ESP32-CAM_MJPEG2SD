## 2024-05-24 - Image processing optimization

**Learning:** `rgbToGray` was recalculating array offsets dynamically using multiplication (`i * 3`). While standard on desktops, this is expensive on resource-constrained microcontrollers like the ESP32.
**Action:** Use pointer-bumping/arithmetic (`*dst++`, `src += 3`) for all performance-critical image processing loops to avoid index calculation overhead.
