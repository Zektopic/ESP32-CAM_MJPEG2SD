## 2024-05-19 - Adding aria-hidden to decorative SVGs
**Learning:** Adding `aria-hidden="true"` to `<svg>` tags within UI controls like buttons ensures that screen readers don't redundantly attempt to read out the internal structure of the SVG, such as `<rect>` or `<text>`, which could confuse users. Avoid adding it to favicons (`<link rel="icon"...`) since they aren't part of the accessibility tree.
**Action:** Consistently add `aria-hidden="true"` to inline SVGs serving decorative or structural roles, especially those inside an element acting as a button.

## 2025-01-29 - Mobile Input and A11y Redundancy
**Learning:** Mobile keyboards can erroneously autocorrect or autocapitalize configuration inputs like hostnames and passwords. Also, range sliders inherently announce their values to screen readers, so visually displaying the bounds and current value as separate DOM elements without `aria-hidden="true"` creates redundant and confusing speech output.
**Action:** Always add `autocorrect="off" autocapitalize="none" spellcheck="false"` to non-prose text inputs (like configurations or URLs). Always add `aria-hidden="true"` to visual labels associated with input elements that already provide their own a11y semantics (like range sliders).

## 2024-05-24 - Improve mobile accessibility for inputs and screen readers
**Learning:** Configuration text inputs (like hostnames and passwords) should disable autocorrect, autocapitalize, and spellcheck to improve mobile usability. Visual bound labels for range sliders should include `aria-hidden="true"` to prevent redundant screen reader announcements, as the input element already possesses semantic value.
**Action:** Always add `autocorrect="off" autocapitalize="none" spellcheck="false"` to configuration inputs, and hide redundant visual labels from screen readers.

## 2024-05-24 - Improve Input Accessibility
**Learning:** Adding aria-hidden to visual bounds reduces screen reader clutter for range sliders. Disabling auto-correct/capitalize for password inputs improves mobile UX.
**Action:** Always verify decorative UI elements have aria-hidden and configuration inputs don't try to autocorrect on mobile.

## 2025-01-29 - Mobile Input Redundancy
**Learning:** Adding `autocorrect="off" autocapitalize="none" spellcheck="false"` to non-prose text inputs improves mobile accessibility.
**Action:** Always add `autocorrect="off" autocapitalize="none" spellcheck="false"` to non-prose text inputs (like configurations or URLs).

## 2025-02-18 - Disable autocorrect on dynamic configuration text inputs
**Learning:** Text inputs dynamically generated in JavaScript (e.g. for configuration settings) must also disable autocorrect and autocapitalize to ensure users can enter precise configuration data without mobile keyboard interference.
**Action:** When auditing or implementing mobile accessibility for configuration interfaces, remember to check not only static HTML but also JavaScript strings that generate input elements.

## 2025-01-29 - Redundant ARIA attributes on buttons
**Learning:** Adding an `aria-label` to a native `<button>` that already has exact matching text content (e.g., `<button aria-label="Save Settings">Save Settings</button>`) is a redundant accessibility anti-pattern. While tooltips (`title`) are good for sighted users, redundant ARIA labels bloat the markup and occasionally cause some screen readers to double-announce.
**Action:** Avoid adding `aria-label` attributes to native buttons when the text content already provides the exact same descriptive label. Focus on using `title` for visual tooltips if the text content is clear enough for screen readers.
## 2024-05-25 - Custom Button Keyboard A11y
**Learning:** When using `<div>` or other non-native button elements with `role="button"`, they do not inherently receive keyboard trigger events (`Enter` or `Space`), rendering them inaccessible to keyboard-only users.
**Action:** Always add an explicit `onkeydown` handler to custom buttons to trigger a click on `Enter` or `Space` (e.g., `onkeydown="if(event.key==='Enter'||event.key===' '){event.preventDefault();this.click();}"`).
## 2025-03-09 - Native Button Replacement
**Learning:** While custom buttons (e.g. `<div role="button">`) require manual `tabindex` and `onkeydown` handlers for Space/Enter keys, converting them to native `<button>` elements inherently provides these accessibility features natively. A CSS reset class is useful to preserve existing visual styles when migrating faux buttons to native buttons.
**Action:** When improving accessibility, replace interactive `<span>` or `<div>` elements with native `<button type="button">` elements to automatically benefit from browser-level accessibility semantics and keyboard event handling, while keeping styling intact.
