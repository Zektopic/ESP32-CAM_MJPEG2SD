const fs = require('fs');

function fixHtml(file) {
  let content = fs.readFileSync(file, 'utf8');

  // Replace old css
  content = content.replace(`.password-wrapper {
        position: relative;
        display: flex;
        align-items: center;
        flex: 1;
        width: 100%;
      }
      .password-toggle {
        position: absolute;
        right: 10px;
        cursor: pointer;
        z-index: 10;
        user-select: none;
      }`, `.password-wrapper {
        position: relative;
        display: inline-block;
        flex: 1;
        width: 100%;
      }
      .password-toggle {
        position: absolute;
        right: 10px;
        top: 50%;
        transform: translateY(-50%);
        cursor: pointer;
        z-index: 10;
        user-select: none;
      }`);

  fs.writeFileSync(file, content, 'utf8');
}

fixHtml('data/MJPEG2SD.htm');
fixHtml('data/Auxil.htm');
