## 2024-03-24 - SVG Keyboard Accessibility
**Learning:** Custom SVG buttons (shapes like `<rect>`) lack native keyboard event handling in browsers, even if given `tabindex="0"` and `role="button"`.
**Action:** Always apply `tabindex` and ARIA roles to a parent HTML element (like a `<div>`) instead of the SVG graphic itself, and ensure global keydown handlers properly target this parent.

## 2024-03-24 - SVG Keyboard Accessibility
**Learning:** Custom SVG buttons (shapes like `<rect>`) lack native keyboard event handling in browsers, even if given `tabindex="0"` and `role="button"`.
**Action:** Always apply `tabindex` and ARIA roles to a parent HTML element (like a `<div>`) instead of the SVG graphic itself, and ensure global keydown handlers properly target this parent.
