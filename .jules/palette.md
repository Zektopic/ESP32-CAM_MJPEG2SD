## $(date +%Y-%m-%d) - CSS Disabled States

**Learning:** Removing `pointer-events: none` from disabled CSS classes is necessary to allow `cursor: not-allowed` to function correctly, but requires applying the native `disabled` attribute to prevent fall-through clicks and ensure screen reader/keyboard accessibility. Dynamic enabling/disabling via JS must also explicitly toggle the element's `.disabled` property.
**Action:** Always pair visual CSS `.disabled` classes with the native HTML `disabled` attribute, and ensure JS toggle functions synchronize both.
