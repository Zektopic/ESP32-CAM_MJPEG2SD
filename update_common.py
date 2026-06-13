import sys

with open('data/common.js', 'r') as f:
    content = f.read()

content = content.replace('''        function disable(el) {
          el.classList.add('disabled');
          el.disabled = true;
        }

        function enable(el) {
          el.classList.remove('disabled');
          el.disabled = false;
        }

        function disableRangeSlider(el) {
          const rangeVal = el.parentElement.children.rangeVal;
          const itemInactiveColor =  getComputedStyle(rangeVal).getPropertyValue('--itemInactive');
          rangeVal.style.background = itemInactiveColor;
          el.classList.add('disabled');
          el.disabled = true;
        }

        function enableRangeSlider(el) {
          const rangeVal = el.parentElement.children.rangeVal;
          const itemInactiveColor =  getComputedStyle(rangeVal).getPropertyValue('--buttonReady');
          rangeVal.style.background = itemInactiveColor;
          el.classList.remove('disabled');
          el.disabled = false;
        }''', '''        function disable(el) {
          el.classList.add('disabled');
          el.disabled = true;
          el.setAttribute('aria-disabled', 'true');
        }

        function enable(el) {
          el.classList.remove('disabled');
          el.disabled = false;
          el.removeAttribute('aria-disabled');
        }

        function disableRangeSlider(el) {
          const rangeVal = el.parentElement.children.rangeVal;
          const itemInactiveColor =  getComputedStyle(rangeVal).getPropertyValue('--itemInactive');
          rangeVal.style.background = itemInactiveColor;
          el.classList.add('disabled');
          el.disabled = true;
          el.setAttribute('aria-disabled', 'true');
        }

        function enableRangeSlider(el) {
          const rangeVal = el.parentElement.children.rangeVal;
          const itemInactiveColor =  getComputedStyle(rangeVal).getPropertyValue('--buttonReady');
          rangeVal.style.background = itemInactiveColor;
          el.classList.remove('disabled');
          el.disabled = false;
          el.removeAttribute('aria-disabled');
        }''')

with open('data/common.js', 'w') as f:
    f.write(content)
