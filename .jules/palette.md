## 2025-06-26 - Native Tooltips for Range Inputs
**Learning:** Native `title` tooltips on `<input type="range">` elements (like Brightness, Contrast, Saturation) provide an immediate, accessible way to explain the purpose of icon-heavy or context-dependent sliders without requiring additional screen space or custom JS tooltip components.
**Action:** When adding missing tooltips to a cluster of related inputs, use Python byte-string replacement for multi-line HTML files to avoid newline issues and accurately target specific ID attributes, ensuring all inputs in a logical grouping receive consistent labeling.
## 2024-05-24 - Improve password visibility toggle accessibility
**Learning:** Adding semantic keyboard accessibility (`onkeydown` to support Enter/Space) and stateful title tooltips to icon-only buttons drastically improves screen reader context and keyboard navigation in custom config forms.
**Action:** When adding or fixing custom icon-only toggle buttons in the HTML, always ensure they are fully operable via keyboard (`onkeydown` handling `Enter` and `Space`) and provide dynamic `title` or `aria-label` attributes reflecting their current toggle state.

## 2025-06-26 - Playwright Hover Events on Dropdowns
**Learning:** When using Playwright to visually verify tooltips on hidden or complex DOM elements (like `<select>` dropdowns inside hidden panels), the standard `page.locator().hover()` method may timeout even after the parent elements are forcefully unhidden.
**Action:** Instead of relying on Playwright's native hover simulation, dispatch the event directly using JavaScript: `page.evaluate("document.getElementById('element_id').dispatchEvent(new MouseEvent('mouseover'))")` to ensure the interaction registers for verification screenshots.

## 2024-07-17 - Added Tooltips and Screen Reader Labels to Camera Hub Buttons
**Learning:** Native HTML buttons in the `#DeviceHub` component (Add IP, Delete All, Refresh) used brief, ambiguous text labels (like "Delete All") which lack context for screen reader users and don't provide tooltips for sighted users.
**Action:** Always verify that interactive elements, especially those with generic text or icons, include descriptive `aria-label` and native `title` attributes to improve accessibility and discoverability without requiring custom CSS or heavy UI changes.
## 2025-07-22 - Keyboard accessibility for custom buttons
**Learning:** Many interactive components in this application (like custom tabs, overlay controls, and settings menus) use `div` or `nav` elements with `role="button"` and `tabindex="0"`. These elements require explicit keyboard event handling to be accessible to keyboard-only and screen reader users.
**Action:** Always ensure that custom button elements include `onkeydown="if(event.key==='Enter'||event.key===' '){event.preventDefault();this.click();}"` to replicate native HTML button behavior, allowing activation via Enter or Space.
## 2024-07-24 - Dynamic element accessibility
**Learning:** Automatically generated form fields (like toggle switches generated via `common.js`) often lack descriptive context (like a `title` or `aria-label`) that screen readers and power users rely on, since the HTML isn't hand-coded.
**Action:** When working with JS-rendered components, always ensure that dynamic attributes (e.g., using the setting's key name) are injected into the template string to maintain accessibility.

## 2025-01-20 - Dynamic Tooltips for Disabled States
**Learning:** When interactive elements (like buttons) are disabled, removing their tooltip or leaving a default action tooltip is confusing. Users need to know *why* an element is disabled.
**Action:** Update the `disable()` JavaScript helper to accept and set an optional `title` parameter explaining the disabled state, and update `enable()` to restore the original action tooltip.
## 2024-07-29 - Missing Enter Key Support in Standalone Inputs
**Learning:** In HTML interfaces that don't wrap inputs in standard `<form>` tags, users lose the default 'Enter to submit' behavior, causing frustrating interaction dead-ends.
**Action:** Always explicitly bind `onkeydown` event handlers checking for `event.key === 'Enter'` to critical standalone input fields to restore expected keyboard behavior.
