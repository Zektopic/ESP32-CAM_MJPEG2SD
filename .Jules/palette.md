## 2024-05-19 - Adding aria-hidden to decorative SVGs
**Learning:** Adding `aria-hidden="true"` to `<svg>` tags within UI controls like buttons ensures that screen readers don't redundantly attempt to read out the internal structure of the SVG, such as `<rect>` or `<text>`, which could confuse users. Avoid adding it to favicons (`<link rel="icon"...`) since they aren't part of the accessibility tree.
**Action:** Consistently add `aria-hidden="true"` to inline SVGs serving decorative or structural roles, especially those inside an element acting as a button.
