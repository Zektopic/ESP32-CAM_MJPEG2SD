## 2024-11-20 - Replace aria-labelledby with aria-label on SVG-only Buttons
**Learning:** Using `aria-labelledby` that points to an element embedded inside an SVG (like `<text>`) can be problematic for some screen readers, and adds unnecessary indirection when the visible text is effectively functioning as the button label. A direct `aria-label` on the button itself provides a cleaner, more reliable accessible name for screen readers, especially when the text node is primarily for layout.
**Action:** Replace `aria-labelledby` with direct `aria-label` attributes on `btn-reset` buttons that use SVGs for styling, ensuring the label matches the visual text content.
## 2024-11-20 - Ensure Meters are Accessible
**Learning:** Using `aria-hidden="true"` on elements with `role="meter"` makes them completely inaccessible to screen reader users, defeating the purpose of the role. `role="meter"` should always be accompanied by `aria-valuenow`, `aria-valuemin`, and `aria-valuemax` attributes to convey their status.
**Action:** Remove `aria-hidden="true"` from accessible meters and ensure they have valid `aria-value*` attributes.
