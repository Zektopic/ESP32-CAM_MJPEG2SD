## $(date +%Y-%m-%d) - CSS Disabled States

**Learning:** Removing `pointer-events: none` from disabled CSS classes is necessary to allow `cursor: not-allowed` to function correctly, but requires applying the native `disabled` attribute to prevent fall-through clicks and ensure screen reader/keyboard accessibility. Dynamic enabling/disabling via JS must also explicitly toggle the element's `.disabled` property.
**Action:** Always pair visual CSS `.disabled` classes with the native HTML `disabled` attribute, and ensure JS toggle functions synchronize both.
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

## 2023-10-27 - Dynamically Generated Form Input Labels
**Learning:** When building configuration forms dynamically via JavaScript (such as `buildTable` in `data/common.js`), it is crucial to ensure that settings' text labels are properly wrapped in `<label for="...">` tags. Without this, inputs lack accessible names, breaking screen reader compatibility and preventing users from focusing the input by clicking its label text.
**Action:** Always wrap setting names in `<label>` tags with the `for` attribute matching the `id` of the dynamically generated form input element.
## 2024-04-08 - [Hide Password Inputs]
**Learning:** Found that multiple sensitive configuration fields (WiFi, FTP, SMTP, and Web passwords) in `Auxil.htm` and `MJPEG2SD.htm` were using the default `text` type, leaving them visible on screen and potentially vulnerable to shoulder-surfing.
**Action:** Always verify that newly added or existing sensitive input fields explicitly use `type="password"`.

## 2024-05-20 - Explicit Adjacent Sibling Selectors for Toggles
**Learning:** In `data/MJPEG2SD.htm` and `data/Auxil.htm`, `.menu-action` checkboxes are separated from their `.nav-toggle` labels by a `.pin-menu` div. While CSS rules linking checkbox focus state to the label should use `~` (e.g., `.menu-action:focus-visible ~ .nav-toggle`), rules targeting the content div for visibility toggling must use the explicit adjacent chain (e.g., `.menu-action + .pin-menu + label + div`) rather than `~ label + div` to avoid inadvertently hiding subsequent unrelated menu sections.
**Action:** When updating CSS selectors where the HTML structure has changed (like the addition of `.pin-menu`), strictly map the `+` adjacent selectors to the new structure rather than converting them to `~` general sibling selectors for structure-dependent display logic.
## 2026-04-16 - Accessible Dynamically Generated Radio Buttons
**Learning:** When generating radio buttons dynamically in JavaScript, failing to wrap the option text in a `<label>` tag and associating it with the `<input type="radio">` using a unique `id` and `for` attribute makes the radio buttons difficult to select (small click target) and inaccessible to screen readers.
**Action:** Always generate unique `id`s for dynamically created radio buttons (e.g., by appending a counter like `saveKey + valCntr`) and wrap their text labels in `<label for="...">` tags to ensure proper accessibility and usability.
## 2025-04-21 - [Fix Accordion Menu Toggling]
**Learning:** [In `data/MJPEG2SD.htm` and `data/Auxil.htm`, `.menu-action` checkboxes are separated from their `.nav-toggle` labels by a `.pin-menu` div. While CSS rules linking checkbox focus state to the label should use `~` (e.g., `.menu-action:focus-visible ~ .nav-toggle`), rules targeting the content div for visibility toggling must use the explicit adjacent chain (e.g., `.menu-action + .pin-menu + label + div`) rather than `~ label + div` to avoid inadvertently hiding subsequent unrelated menu sections.]
**Action:** [When modifying UI templates with custom checkbox-based accordions or menus, strictly verify adjacent vs general sibling CSS selectors to ensure intermediate injected DOM elements (like pins or icons) don't silently break expand/collapse functionality.]

## 2024-05-20 - Confirmations for Destructive Actions
**Learning:** Found that a destructive action (clearing all saved IP addresses from the Camera Hub's local storage) was performed immediately upon clicking a "Delete All" button without any confirmation dialog. This can lead to accidental data loss.
**Action:** Always wrap custom destructive actions (e.g., clearing local storage) in `window.confirm()` dialogs to prevent accidental data loss and improve the overall UX.

## 2026-05-02 - Keep dynamic ARIA labels synchronized with visual text updates
**Learning:** When JavaScript dynamically updates the visual text of an interactive element (e.g., changing 'Start Recording' to 'Stop Recording' on a button), the `aria-label` (if present) is NOT automatically updated. If the element relies on `aria-label` to mask unicode icons or provide a clean accessible name, screen readers will announce the old state, causing severe confusion.
**Action:** When updating the `.innerHTML` or `.textContent` of an element to reflect a state change, always check if the element has an `aria-label`. If it does, ensure you also call `.setAttribute('aria-label', ...)` with the new accessible name to keep it synchronized with the visual state.
## 2024-05-12 - Disabled Cursor Visibility
**Learning:** `pointer-events: none` completely blocks mouse interactions, which inherently prevents the `cursor: not-allowed` style from rendering when a user hovers over a disabled element. Using this CSS approach alone fails to provide clear visual feedback to mouse users.
**Action:** Always combine the native HTML `disabled` attribute (managed via JavaScript) with CSS pseudo-selectors (`:disabled` or `.disabled`) containing `cursor: not-allowed`, and explicitly avoid `pointer-events: none` on interactive elements where hover feedback is desired.
