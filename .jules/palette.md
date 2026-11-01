## 2024-11-20 - Ensure Single-Quote Escaping in Inline JS HTML Injection
**Learning:** When using `this.innerHTML` within inline `onclick="..."` HTML attributes to inject elements containing attributes (like `aria-hidden="true"`), the inner attributes must use properly escaped single quotes (`\'true\'`) or standard single quotes (`'true'`) to avoid prematurely terminating the `onclick` attribute and breaking the DOM parser.
**Action:** When adding elements with attributes via inline HTML handlers, always strictly verify the quote boundaries.
## 2024-11-20 - Avoid aria-labelledby pointing to aria-hidden elements
**Learning:** When an SVG icon button uses `aria-hidden="true"` on the `<svg>` tag to hide it from screen readers, using `aria-labelledby` on the parent `<button>` to reference a `<text>` node *inside* that SVG can fail across different screen reader/browser combinations because the target node is removed from the accessibility tree.
**Action:** For SVG icon buttons with `aria-hidden="true"`, always prefer applying a direct `aria-label` attribute on the parent `<button>` instead of using `aria-labelledby` to reference child nodes inside the hidden SVG.
## 2024-11-01 - Input Type Number Accessibility
**Learning:** For `<input type="number">`, `minlength` and `maxlength` attributes are invalid and ignored by browsers. `min` and `max` should be used instead to set boundaries for the value.
**Action:** Use `min` and `max` attributes when creating `<input type="number">` elements to ensure proper validation and accessibility.
