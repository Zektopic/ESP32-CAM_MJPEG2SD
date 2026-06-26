1. Add `title` attribute tooltips to the `brightness`, `contrast`, `saturation`, `sharpness`, and `denoise` range inputs in `data/MJPEG2SD.htm` via the `run_in_bash_session` tool using a python replacement script:
```bash
cat << 'PY_EOF' > patch.py
with open('data/MJPEG2SD.htm', 'rb') as f:
    content = f.read()

content = content.replace(b'<input type="range" id="brightness"', b'<input title="Set image brightness" type="range" id="brightness"')
content = content.replace(b'<input type="range" id="contrast"', b'<input title="Set image contrast" type="range" id="contrast"')
content = content.replace(b'<input type="range" id="saturation"', b'<input title="Set image saturation" type="range" id="saturation"')
content = content.replace(b'<input type="range" id="sharpness"', b'<input title="Set image sharpness" type="range" id="sharpness"')
content = content.replace(b'<input type="range" id="denoise"', b'<input title="Set image de-noise level" type="range" id="denoise"')

with open('data/MJPEG2SD.htm', 'wb') as f:
    f.write(content)
PY_EOF
python3 patch.py
rm patch.py
```
2. Verify the changes visually using `git diff data/MJPEG2SD.htm` to ensure the tooltips were cleanly added.
3. Run the repository tests to verify correctness: execute `pip install playwright pytest-playwright && playwright install chromium` and `python test_playwright.py`. Also run the C++ test suite with `g++ -o test_mock_bin test_mock.cpp && ./test_mock_bin`, and then delete the compiled binary with `rm test_mock_bin`. Finally remove cached python files `rm -rf __pycache__ .pytest_cache`.
4. Complete pre-commit steps to ensure proper testing, verification, review, and reflection are done.
5. Create a branch and submit the PR using the `submit` tool.
