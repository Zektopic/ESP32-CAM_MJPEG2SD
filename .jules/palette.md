## 2024-05-20 - Global Keyboard Event Handling for Custom Components
**Learning:** This application makes heavy use of interactive SVG `<rect>` elements and icon-only `<div>` elements as custom buttons. While ARIA labels and `tabindex` make them focusable for screen readers, they do not inherently trigger `click` events upon receiving 'Enter' or 'Space' keystrokes like native `<button>` tags do.
**Action:** Always ensure that a global or component-level `keydown` listener exists to translate 'Enter' (keyCode 13) and 'Space' (keyCode 32) presses into `click()` events for non-native interactive elements (like SVG rects or divs with `role="button"`), while also preventing default scrolling for the Space key.

## 2024-03-25 - Focus Visible Styles for Keyboard Navigation
**Learning:** The project's UI relies heavily on generic `button` elements, but previously lacked a distinct visual focus indicator for keyboard navigation (`:focus-visible`). This made it difficult for users relying on keyboard navigation (Tab key) to identify which element had focus.
**Action:** Added `button:focus-visible` to `data/MJPEG2SD.htm` and `data/Auxil.htm` using existing design tokens (`var(--buttonActive)`). This ensures a clear focus ring is present for keyboard users without affecting mouse/touch users. Always ensure interactive elements have clear focus states.

## 2024-05-20 - Restoring Keyboard Focus on Custom Buttons
**Learning:** Custom interactive elements (like `div[role="button"]` or `nav[role="button"]`) often have their default browser focus outline explicitly removed (`outline: none;`) to prevent it from showing on mouse click. This breaks keyboard navigation visibility.
**Action:** Always add an explicit `:focus-visible` CSS rule using existing design tokens (e.g., `outline: 2px solid var(--buttonActive);`) when `outline: none;` is used, ensuring keyboard users can see what is focused without compromising mouse interaction aesthetics. Also ensure icon-only interactive divs have `role="button"`, `tabindex="0"`, and `aria-label` set.
