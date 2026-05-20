## 2026-05-13 - CSS Disabled States

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
**Action:** When updating CSS selectors where the HTML structure has changed (like the addition of `.pin-menu`), strictly map the `+` adjacent selectors to the new structure rather than converting them to `~` general sibling selectors for structure-dependent display logic## 2026-04-16 - Accessible Dynamically Generated Radio Buttons
**Learning:** When generating radio buttons dynamically in JavaScript, failing to wrap the option text in a `<label>` tag and associating it with the `<input type="radio">` using a unique `id` and `for` attribute makes the radio buttons difficult to select (small click target) and inaccessible to screen readers.
**Action:** Always generate unique `ids` for dynamically created radio buttons (e.g., by appending a counter like `saveKey + valCntr`) and wrap their text labels in `<label for="...">` tags to ensure proper accessibility and usability.
## 2025-04-21 - [Fix Accordion Menu Toggling]
**Learning:** [In `data/MJPEG2SD.htm` and `data/Auxil.htm`, `.menu-action` checkboxes are separated from their `.nav-toggle` labels by a `.pin-menu` div. While CSS rules linking checkbox focus state to the label should use `~` (e.g., `.menu-action:focus-visible ~ .nav-toggle`), rules targeting the content div for visibility toggling must use the explicit adjacent chain (e.g., `.menu-action + .pin-menu + label + div`) rather than `~ label + div` to avoid inadvertently hiding subsequent unrelated menu sections.]
**Action:** [When modifying UI templates with custom checkbox-based accordions or menus, strictly verify adjacent vs general sibling CSS selectors to ensure intermediate injected DOM elements (like pins or icons) don't silently break expand/collapse functionality.]

## 2024-05-20 - Confirmations for Destructive Actions
**Learning:** Found that a destructive action (clearing all saved IP addresses from the Camera Hub's local storage) was performed immediately upon clicking a "Delete All" button without any confirmation dialog. This can lead to accidental data loss.
**Action:** Always wrap custom destructive actions (e.g., clearing local storage) in `window.confirm()` dialogs to prevent accidental data loss and improve the overall UX.
## 2024-05-14 - Empty States in Dynamic UI
**Learning:** For sections of the UI generated dynamically via JS (like the camera hub list), users are left confused when data is empty because the container renders completely blank.
**Action:** Always verify what the UI looks like when state arrays are empty, and inject an explicit empty state message utilizing existing `itemInactive` and font-style CSS to guide the user.

## 2026-05-02 - Keep dynamic ARIA labels synchronized with visual text updates
**Learning:** When JavaScript dynamically updates the visual text of an interactive element (e.g., changing 'Start Recording' to 'Stop Recording' on a button), the `aria-label` (if present) is NOT automatically updated. If the element relies on `aria-label` to mask unicode icons or provide a clean accessible name, screen readers will announce the old state, causing severe confusion.
**Action:** When updating the `.innerHTML` or `.textContent` of an element to reflect a state change, always check if the element has an `aria-label`. If it does, ensure you also call `.setAttribute('aria-label', ...)` with the new accessible name to keep it synchronized with the visual state.
## 2026-05-08 - Native Disabled Attributes and Not-Allowed Cursor
**Learning:** Relying solely on CSS classes (like `.disabled`) and `pointer-events: none` to disable UI elements prevents mouse interaction visually, but leaves the elements completely accessible and operable to keyboard and screen reader users. Additionally, `cursor: default` fails to convey the disabled state clearly compared to `cursor: not-allowed`.
**Action:** When disabling elements, always ensure the native HTML `disabled` attribute is toggled alongside any visual CSS changes. Furthermore, use `cursor: not-allowed` for clearer user feedback and avoid `pointer-events: none` which completely hides the element's disabled state from the cursor interaction.
## 2025-02-13 - Fixed Accessibility for Disabled States
**Learning:** Applying a `.disabled` CSS class with `pointer-events: none` only visually prevents mouse interactions but leaves elements fully accessible to keyboards/screen readers.
**Action:** Always pair visual CSS classes with the native HTML `disabled` attribute for full accessibility compliance, and use `cursor: not-allowed` instead of `cursor: default` for clearer UX feedback. When removing `pointer-events: none`, ensure all associated JavaScript enable/disable functions explicitly toggle the `el.disabled = true/false` attribute to prevent elements from becoming functionally clickable.

## 2024-05-20 - CSS `pointer-events: none` Accessibility Pitfall
**Learning:** Applying `.disabled` CSS class with `pointer-events: none` only visually prevents mouse interactions but leaves elements fully accessible to keyboards/screen readers.
**Action:** Always pair visual CSS classes with the native HTML `disabled` attribute for full accessibility compliance. Use `cursor: not-allowed` instead of `cursor: default` for clearer UX feedback, and ensure all associated JavaScript enable/disable functions explicitly toggle `el.disabled = true/false`.
## 2024-05-12 - Disabled Cursor Visibility
**Learning:** `pointer-events: none` completely blocks mouse interactions, which inherently prevents the `cursor: not-allowed` style from rendering when a user hovers over a disabled element. Using this CSS approach alone fails to provide clear visual feedback to mouse users.
**Action:** Always combine the native HTML `disabled` attribute (managed via JavaScript) with CSS pseudo-selectors (`:disabled` or `.disabled`) containing `cursor: not-allowed`, and explicitly avoid `pointer-events: none` on interactive elements where hover feedback is desired.
## 2024-05-18 - Dynamically Link Error Messages to Inputs
**Learning:** Screen readers need explicit linking (`aria-describedby`) and live regions (`aria-live`) to properly associate dynamically inserted validation error text with the form inputs causing them. Just appending a red text div next to the input is only visual, leaving screen-reader users uninformed of validation failures.
**Action:** Always add unique IDs to dynamic error elements, set `aria-live="polite"` on them, and tie them to their input fields via `aria-describedby` and `aria-invalid="true"`.

## 2026-04-24 - Protecting Destructive Actions with Confirmation Dialogs
**Learning:** Destructive actions like clearing all local storage IPs lacked a confirmation step, potentially leading to accidental data loss with a single misclick.
**Action:** Always wrap destructive actions in `window.confirm()` dialogs to ensure intentionality before irreversible changes occur.

## 2026-05-03 - Native HTML disabled vs CSS pointer-events
**Learning:** In the UI (e.g., `MJPEG2SD.htm`), applying a `.disabled` CSS class with `pointer-events: none` only visually prevents mouse interactions but leaves the element fully accessible to keyboard navigation and screen readers. Furthermore, JavaScript functions manipulating disabled states (like `disableRangeSlider` in `data/common.js`) often overlook the native DOM state.
**Action:** When creating or manipulating disabled states for interactive elements (like `<button>` or `<input>`), always pair visual CSS classes with the native HTML `disabled` attribute (`disabled` in HTML or `el.disabled = true` in JavaScript) to ensure full accessibility compliance. Additionally, use `cursor: not-allowed` instead of `cursor: default` for clearer UX feedback.

## 2025-02-18 - Dynamically Generated Keyboard Accessible Tiles
**Learning:** When generating interactive tiles or buttons using `div` or `span` elements via JavaScript (like the device hub camera tiles), it is crucial to explicitly add `role="button"`, `tabindex="0"`, and `aria-label` to ensure they are discovered and operable by assistive technologies. Additionally, destructive actions (like removing an item) should be wrapped in confirmation dialogs (e.g., `window.confirm`) to prevent accidental data loss. Furthermore, for non-native interactive elements (e.g. `div`), assigning an `onclick` handler does not automatically provide keyboard support; you must explicitly add an `onkeydown` handler to intercept the `Enter` and `Space` keys to trigger the action.
**Action:** Always verify that dynamically created interactive elements implement proper ARIA roles and keyboard event handlers, and ensure that data removal flows include a confirmation step.

## 2024-05-20 - Disabled State CSS Cursors and Pointer Events
**Learning:** Setting `pointer-events: none;` on a `.disabled` CSS class overrides any custom cursors (like `cursor: not-allowed;`), causing the cursor to visually revert to `default`. Furthermore, removing `pointer-events: none` makes the elements natively interactive to mouse clicks again unless they have the HTML `disabled` attribute.
**Action:** When implementing a `not-allowed` cursor for disabled UI states, remove `pointer-events: none`. However, this MUST be paired with ensuring the element sets the native HTML `disabled="true"` attribute (either statically in HTML or dynamically via JS logic) to properly prevent click/focus interactions and maintain screen reader accessibility.

## 2024-05-24 - Accessibility for dynamically generated checkbox/radio labels
**Learning:** When dynamically generating HTML form controls in JavaScript (such as lists of radio buttons using string concatenation), simple adjacent text strings fail to provide accessible names. Additionally, visually grouping labels with `for` tags that don't correspond to an `id` attribute on the target input breaks programmatic mapping for screen readers.
**Action:** When dynamically building UI components in JavaScript, explicitly generate `<label for="...">` elements matching the unique `id` attribute of the generated `<input>` to ensure proper accessible names and click-to-focus functionality.
