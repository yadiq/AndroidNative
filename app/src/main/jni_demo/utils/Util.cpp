//
// 工具类
//

#include "Util.h"

string Util::byteToHex(char byte) {
    string str;
    str.append(1, hex_char[byte >> 4]);
    str.append(1, hex_char[byte & 0x0f]);
    return str;
}

string Util::bytesToHex(char *bytes, int length) {
    string str;
    for (int i = 0; i < length; i++) {
        str.append(byteToHex(*(bytes + i)));
    }
    return str;
}

string Util::bytesToHex2(char *bytes, int length) {
    char dest[length * 2];
    for (int i = 0; i < length; i++) {
        sprintf(&dest[i * 2], "%02x", (unsigned char) bytes[i]);
    }
    string str(dest, length * 2);
    return str;
}

string Util::hexToBytes(char *hex, int length) {
    char dest[length / 2];
    unsigned int val;
    for (int i = 0; i < length; i += 2) {
        sscanf(hex + i, "%02x", &val);
        dest[i / 2] = val;
    }
    string str(dest, length / 2);
    return str;
}

string Util::removeChar(string str, char c) {
    //使用 erase 和 remove 配合
    //运行remove后, 容器的[first, newEnd)内的元素为所有未被删除的元素, [newEnd, end)之间的元素已经没用了.
    //再运行erase, 清空[newEnd, end)之间的元素
    str.erase(remove(str.begin(), str.end(), c), str.end());
    return str;
}