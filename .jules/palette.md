## 2024-11-20 - Ensure Single-Quote Escaping in Inline JS HTML Injection
**Learning:** When using `this.innerHTML` within inline `onclick="..."` HTML attributes to inject elements containing attributes (like `aria-hidden="true"`), the inner attributes must use properly escaped single quotes (`\'true\'`) or standard single quotes (`'true'`) to avoid prematurely terminating the `onclick` attribute and breaking the DOM parser.
**Action:** When adding elements with attributes via inline HTML handlers, always strictly verify the quote boundaries.
## 2024-11-20 - Improve screen reader support for SVG icon buttons
**Learning:** When improving accessibility for SVG-based icon buttons, avoid using `aria-labelledby` referencing elements embedded inside the SVG (like `<text>`). `text` elements embedded inside `<svg>` are often not reliably exposed by browsers or screen readers to form accessible names via `aria-labelledby`.
**Action:** Apply a direct `aria-label` attribute to the parent `<button>` element for reliable screen reader support.
