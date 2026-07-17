## 2025-06-26 - Native Tooltips for Range Inputs
**Learning:** Native `title` tooltips on `<input type="range">` elements (like Brightness, Contrast, Saturation) provide an immediate, accessible way to explain the purpose of icon-heavy or context-dependent sliders without requiring additional screen space or custom JS tooltip components.
**Action:** When adding missing tooltips to a cluster of related inputs, use Python byte-string replacement for multi-line HTML files to avoid newline issues and accurately target specific ID attributes, ensuring all inputs in a logical grouping receive consistent labeling.
## 2024-05-24 - Improve password visibility toggle accessibility
**Learning:** Adding semantic keyboard accessibility (`onkeydown` to support Enter/Space) and stateful title tooltips to icon-only buttons drastically improves screen reader context and keyboard navigation in custom config forms.
**Action:** When adding or fixing custom icon-only toggle buttons in the HTML, always ensure they are fully operable via keyboard (`onkeydown` handling `Enter` and `Space`) and provide dynamic `title` or `aria-label` attributes reflecting their current toggle state.

## 2025-06-26 - Playwright Hover Events on Dropdowns
**Learning:** When using Playwright to visually verify tooltips on hidden or complex DOM elements (like `<select>` dropdowns inside hidden panels), the standard `page.locator().hover()` method may timeout even after the parent elements are forcefully unhidden.
**Action:** Instead of relying on Playwright's native hover simulation, dispatch the event directly using JavaScript: `page.evaluate("document.getElementById('element_id').dispatchEvent(new MouseEvent('mouseover'))")` to ensure the interaction registers for verification screenshots.
