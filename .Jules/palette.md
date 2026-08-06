## 2025-01-29 - Mobile Input and A11y Redundancy
**Learning:** Mobile keyboards can erroneously autocorrect or autocapitalize configuration inputs like hostnames and passwords. Also, range sliders inherently announce their values to screen readers, so visually displaying the bounds and current value as separate DOM elements without `aria-hidden="true"` creates redundant and confusing speech output.
**Action:** Always add `autocorrect="off" autocapitalize="none" spellcheck="false"` to non-prose text inputs (like configurations or URLs). Always add `aria-hidden="true"` to visual labels associated with input elements that already provide their own a11y semantics (like range sliders).
## 2025-01-29 - Mobile Input Redundancy
**Learning:** Adding `autocorrect="off" autocapitalize="none" spellcheck="false"` to non-prose text inputs improves mobile accessibility.
**Action:** Always add `autocorrect="off" autocapitalize="none" spellcheck="false"` to non-prose text inputs (like configurations or URLs).
