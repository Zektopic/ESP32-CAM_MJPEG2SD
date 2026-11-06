## 2024-11-20 - Ensure Single-Quote Escaping in Inline JS HTML Injection
**Learning:** When using `this.innerHTML` within inline `onclick="..."` HTML attributes to inject elements containing attributes (like `aria-hidden="true"`), the inner attributes must use properly escaped single quotes (`\'true\'`) or standard single quotes (`'true'`) to avoid prematurely terminating the `onclick` attribute and breaking the DOM parser.
**Action:** When adding elements with attributes via inline HTML handlers, always strictly verify the quote boundaries.
## 2024-11-20 - Avoid aria-labelledby pointing to aria-hidden elements
**Learning:** When an SVG icon button uses `aria-hidden="true"` on the `<svg>` tag to hide it from screen readers, using `aria-labelledby` on the parent `<button>` to reference a `<text>` node *inside* that SVG can fail across different screen reader/browser combinations because the target node is removed from the accessibility tree.
**Action:** For SVG icon buttons with `aria-hidden="true"`, always prefer applying a direct `aria-label` attribute on the parent `<button>` instead of using `aria-labelledby` to reference child nodes inside the hidden SVG.
## 2024-11-01 - Input Type Number Accessibility
**Learning:** For `<input type="number">`, `minlength` and `maxlength` attributes are invalid and ignored by browsers. `min` and `max` should be used instead to set boundaries for the value.
**Action:** Use `min` and `max` attributes when creating `<input type="number">` elements to ensure proper validation and accessibility.
## 2026-10-30 - Fix minlength and maxlength on number inputs
**Learning:** `minlength` and `maxlength` attributes are not supported on `<input type="number">` and are ignored by browsers, which prevents native HTML validation and affects screen reader context.
**Action:** Always replace `minlength` and `maxlength` with `min` and `max` on `<input type="number">` to ensure proper native form validation and accessible boundary hints.
## 2024-11-20 - Ensure aria-label matches visible text (Label in Name)
**Learning:** When adding `aria-label` attributes to elements (like CSS-driven accordion menu toggles that use the checkbox hack), the `aria-label` string must contain the exact visible text of the corresponding `<label>` element. This satisfies WCAG 2.1 Success Criterion 2.5.3 (Label in Name) and ensures voice-dictation software works correctly when users say the visible text.
**Action:** Always verify that any new `aria-label` includes the element's visible text verbatim (e.g., if visible text is "Camera Control", aria-label should be "Toggle Camera Control Menu").
