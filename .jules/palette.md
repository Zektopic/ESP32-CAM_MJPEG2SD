## 2024-05-20 - Global Keyboard Event Handling for Custom Components
**Learning:** This application makes heavy use of interactive SVG `<rect>` elements and icon-only `<div>` elements as custom buttons. While ARIA labels and `tabindex` make them focusable for screen readers, they do not inherently trigger `click` events upon receiving 'Enter' or 'Space' keystrokes like native `<button>` tags do.
**Action:** Always ensure that a global or component-level `keydown` listener exists to translate 'Enter' (keyCode 13) and 'Space' (keyCode 32) presses into `click()` events for non-native interactive elements (like SVG rects or divs with `role="button"`), while also preventing default scrolling for the Space key.

## 2024-03-25 - Focus Visible Styles for Keyboard Navigation
**Learning:** The project's UI relies heavily on generic `button` elements, but previously lacked a distinct visual focus indicator for keyboard navigation (`:focus-visible`). This made it difficult for users relying on keyboard navigation (Tab key) to identify which element had focus.
**Action:** Added `button:focus-visible` to `data/MJPEG2SD.htm` and `data/Auxil.htm` using existing design tokens (`var(--buttonActive)`). This ensures a clear focus ring is present for keyboard users without affecting mouse/touch users. Always ensure interactive elements have clear focus states.

## 2024-05-20 - Restoring Keyboard Focus on Custom Buttons
**Learning:** Custom interactive elements (like `div[role="button"]` or `nav[role="button"]`) often have their default browser focus outline explicitly removed (`outline: none;`) to prevent it from showing on mouse click. This breaks keyboard navigation visibility.
**Action:** Always add an explicit `:focus-visible` CSS rule using existing design tokens (e.g., `outline: 2px solid var(--buttonActive);`) when `outline: none;` is used, ensuring keyboard users can see what is focused without compromising mouse interaction aesthetics. Also ensure icon-only interactive divs have `role="button"`, `tabindex="0"`, and `aria-label` set.
## 2024-05-20 - Global Focus Visible Styles for Interactive Elements
**Learning:** Default browser outlines for interactive elements are often removed globally (`outline: 0;`). When explicit `:focus-visible` styles are implemented, they should cover all keyboard-navigable interactive elements, not just standard `<button>` tags. This includes custom elements like `div[role="button"]`, as well as standard form inputs (`input`, `select`, `textarea`).
**Action:** When adding `:focus-visible` styles to improve keyboard accessibility, use a broad selector (e.g., `button:focus-visible, [role="button"]:focus-visible, input:focus-visible, select:focus-visible`) to ensure all interactive elements receive a clear, consistent focus ring.

## 2024-05-20 - Custom Checkbox/Toggle Accessibility
**Learning:** Hiding native checkboxes using `display: none;` removes them from the accessibility tree, breaking keyboard navigation entirely for custom toggle switches.
**Action:** When styling custom toggle switches, always hide the native `<input type="checkbox">` using `opacity: 0; position: absolute;` instead of `display: none;`. Ensure a sibling element (like a `.slider`) has a `:focus-visible` CSS rule applied when the hidden checkbox is focused, providing vital visual feedback to keyboard users.

## 2024-05-20 - Avoid Nesting Interactive Elements
**Learning:** Nesting interactive elements (like placing a `<button>` inside an `<a>` tag) violates WCAG 4.1.2 and can cause screen readers to read the element incorrectly or inconsistently, confusing users who rely on assistive technologies.
**Action:** Always refactor HTML to ensure there are no nested interactive elements. If a button needs to act as a link, use a single `<button>` element with an `onclick="window.location.href='...'"` attribute or a styled `<a>` tag with `role="button"`.
## 2025-04-05 - Correct client-side string limits on text inputs
**Learning:** Using 'length' instead of 'maxlength' on HTML inputs is invalid and will be silently ignored by browsers, which can lead to backend buffer overflows if not handled correctly.
**Action:** Always use the valid 'maxlength' attribute on HTML input elements to enforce client-side character limits.

## 2024-05-20 - Use Valid HTML Attributes for Input Limitations
**Learning:** Native HTML `<input>` fields use `maxlength`, not `length`, to enforce character limits on the client side. Using `length=` is an invalid HTML attribute and is silently ignored by the browser, meaning users can type beyond the intended character limit (e.g., for SSIDs or Hostnames) which might cause unexpected truncation or buffer overflows on the backend.
**Action:** Always use `maxlength="[number]"` and `minlength="[number]"` for text-based `<input>` fields.
## 2024-04-07 - Icon-only buttons with text characters need ARIA labels
**Learning:** Legacy UI components in this application (like `MJPEG2SD.htm`) use unicode characters (e.g., `➤`) for iconography within buttons instead of semantic SVG/img icons. This means screen readers will literally read out "Black right-pointing arrowhead" before the text.
**Action:** When auditing legacy UI buttons that mix symbols and text, always add explicit `aria-label` attributes to override the symbol vocalization and provide a clean accessible name.
## 2024-04-08 - [Hide Password Inputs]
**Learning:** Found that multiple sensitive configuration fields (WiFi, FTP, SMTP, and Web passwords) in `Auxil.htm` and `MJPEG2SD.htm` were using the default `text` type, leaving them visible on screen and potentially vulnerable to shoulder-surfing.
**Action:** Always verify that newly added or existing sensitive input fields explicitly use `type="password"`.
