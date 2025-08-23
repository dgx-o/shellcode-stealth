#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
typedef unsigned char BYTE;
namespace base32 {
    static const std::string base32_chars = "I5PGRXTYWOLSEM4ZFVD7U3Q2ABJNHK6C"; // randomized >:)
    static inline bool is_base32(BYTE c) {
        return (isalnum(c) && (std::toupper(c) >= 'A' && std::toupper(c) <= 'Z')) ||
            (c >= '2' && c <= '7');
    }
    std::vector<BYTE> base32_decode(std::string const& encoded_string) {
        std::string clean_string;
        for (char c : encoded_string) {
            if (c == '=') break;
            if (is_base32(c)) {
                clean_string += std::toupper(c);
            }
        }
        int in_len = clean_string.size();
        int i = 0;
        int j = 0;
        int in_ = 0;
        BYTE char_array_8[8], char_array_5[5];
        std::vector<BYTE> ret;
        while (in_len > 0) {
            int count = 0;
            while (count < 8 && in_ < clean_string.size()) {
                char_array_8[count++] = base32_chars.find(clean_string[in_++]);
            }
            if (count == 0) break;
            while (count < 8) {
                char_array_8[count++] = 0;
            }
            char_array_5[0] = (char_array_8[0] << 3) | ((char_array_8[1] & 0x1C) >> 2);
            char_array_5[1] = ((char_array_8[1] & 0x03) << 6) | (char_array_8[2] << 1) | ((char_array_8[3] & 0x10) >> 4);
            char_array_5[2] = ((char_array_8[3] & 0x0F) << 4) | ((char_array_8[4] & 0x1E) >> 1);
            char_array_5[3] = ((char_array_8[4] & 0x01) << 7) | (char_array_8[5] << 2) | ((char_array_8[6] & 0x18) >> 3);
            char_array_5[4] = ((char_array_8[6] & 0x07) << 5) | char_array_8[7];
            int bytes_to_add = (count * 5) / 8;
            if (bytes_to_add > 5) bytes_to_add = 5;
            for (j = 0; j < bytes_to_add; j++) {
                ret.push_back(char_array_5[j]);
            }
            in_len -= 8;
        }
        return ret;
    }
}