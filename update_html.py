import sys
import re

for filename in ['data/MJPEG2SD.htm']:
    with open(filename, 'r') as f:
        content = f.read()

    # Match `disabled>` and replace with `disabled aria-disabled="true">`
    content = re.sub(r'(\sdisabled)>', r'\1 aria-disabled="true">', content)

    with open(filename, 'w') as f:
        f.write(content)
