const font = require(process.argv[2]);

let result = '';

result += `#ifndef FONT_H_\n#define FONT_H_\n\n#include <vector>\n#include <cstdint>\n\n`;

result += `std::vector<uint8_t> kCharWidths { ${font.widths.map(item => item).join(', ')} };\n\n`;

function convertToByte(bools) {
    let result = 0;
    for (let i = 0; i < 8; i++) {
        if (bools[i]) {
            result += 1 << i;
        }
    }
    return result;
}

const fontData = font.charData.map((item, index) => `  { ${item.map(item2 => convertToByte(item2)).join(', ')
    } }, // char 0x${index.toString(16).padStart(2, '0')}`).join('\n');

result += `std::vector<std::vector<uint8_t>> kCharData {\n${fontData}\n};\n\n`

result += `#endif //FONT_H_\n`;

require('fs').writeFileSync(process.argv[3], result);