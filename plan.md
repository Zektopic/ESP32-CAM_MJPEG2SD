1. **Update `disable` and `enable` functions in `data/common.js`**
   - Use `run_in_bash_session` to execute a python script that reads `data/common.js` and performs a string replacement.
   - It will update `disable(el)` and `disableRangeSlider(el)` to include `el.setAttribute('aria-disabled', 'true');` and update `enable(el)` and `enableRangeSlider(el)` to include `el.removeAttribute('aria-disabled');`.
2. **Update initial disabled buttons in `data/MJPEG2SD.htm`**
   - Use `run_in_bash_session` to run a python script that reads `data/MJPEG2SD.htm`.
   - The script will use regex `re.sub(r'(\sdisabled)>', r'\1 aria-disabled="true">', content)` to add `aria-disabled="true"` to initially disabled `<button>` tags.
3. **Verify the change**
   - Use `run_in_bash_session` to start a local python server `python3 -m http.server 8080 &`.
   - Write and run a Playwright python script to navigate to `http://localhost:8080/data/MJPEG2SD.htm`.
   - It will assert that initially disabled buttons contain `aria-disabled="true"`.
   - It will trigger `disable()` on a button via `page.evaluate` and verify that the `aria-disabled` attribute was successfully set.
   - Kill the python server and clean up the temporary verification script.
4. **Complete pre-commit steps**
   - Complete pre-commit steps to ensure proper testing, verification, review, and reflection are done.
5. **Submit the change.**
   - Use the `submit` tool to create a pull request with the required Palette format.
