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
