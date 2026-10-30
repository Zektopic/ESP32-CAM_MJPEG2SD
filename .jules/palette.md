## 2026-10-30 - Fix minlength and maxlength on number inputs
**Learning:** `minlength` and `maxlength` attributes are not supported on `<input type="number">` and are ignored by browsers, which prevents native HTML validation and affects screen reader context.
**Action:** Always replace `minlength` and `maxlength` with `min` and `max` on `<input type="number">` to ensure proper native form validation and accessible boundary hints.
