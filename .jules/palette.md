## 2025-06-26 - Native Tooltips for Range Inputs
**Learning:** Native `title` tooltips on `<input type="range">` elements (like Brightness, Contrast, Saturation) provide an immediate, accessible way to explain the purpose of icon-heavy or context-dependent sliders without requiring additional screen space or custom JS tooltip components.
**Action:** When adding missing tooltips to a cluster of related inputs, use Python byte-string replacement for multi-line HTML files to avoid newline issues and accurately target specific ID attributes, ensuring all inputs in a logical grouping receive consistent labeling.
## 2024-07-17 - Added Tooltips and Screen Reader Labels to Camera Hub Buttons
**Learning:** Native HTML buttons in the `#DeviceHub` component (Add IP, Delete All, Refresh) used brief, ambiguous text labels (like "Delete All") which lack context for screen reader users and don't provide tooltips for sighted users.
**Action:** Always verify that interactive elements, especially those with generic text or icons, include descriptive `aria-label` and native `title` attributes to improve accessibility and discoverability without requiring custom CSS or heavy UI changes.
