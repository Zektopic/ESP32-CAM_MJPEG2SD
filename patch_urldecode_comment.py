import re

with open('src/utils.cpp', 'r') as f:
    content = f.read()

replacement = """  // ⚡ Bolt optimization: Precomputed static boolean lookup table (LUT) to eliminate generic `isxdigit`
  // standard library function call overhead in the hot URL decoding loop, enabling true O(1) checks.
  static const bool isXDigitLUT[256] = {"""

content = re.sub(
    r"  static const bool isXDigitLUT\[256\] = \{",
    replacement,
    content
)

with open('src/utils.cpp', 'w') as f:
    f.write(content)
