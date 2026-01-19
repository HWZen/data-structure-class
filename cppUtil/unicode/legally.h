//
// Created by HWZ on 2024/5/23.
//

#ifndef ZHUAN_HARDWARE_LIB_LEGALLY_H
#define ZHUAN_HARDWARE_LIB_LEGALLY_H

#include <string>
#include <array>

inline constexpr auto legalStringUTF16(std::wstring str) -> std::wstring {
    constexpr auto surrogate_base        = static_cast<uint32_t>(0x10000);
    constexpr auto lead_surrogate_begin  = static_cast<uint32_t>(0xD800);
    constexpr auto lead_surrogate_end    = static_cast<uint32_t>(0xDBFF);
    constexpr auto trail_surrogate_begin = static_cast<uint32_t>(0xDC00);
    constexpr auto trail_surrogate_end   = static_cast<uint32_t>(0xDFFF);
    constexpr auto surrogate_bits        = static_cast<uint32_t>(10);

    auto is_lead_surrogate = [](const uint32_t codepoint) constexpr noexcept {
        return codepoint >= lead_surrogate_begin && codepoint <= lead_surrogate_end;
    };

    auto is_trail_surrogate = [](const uint32_t codepoint) constexpr noexcept {
        return codepoint >= trail_surrogate_begin && codepoint <= trail_surrogate_end;
    };

    auto legalCodepoint = [](const uint32_t codepoint) constexpr noexcept {
        return codepoint <= 0x10FFFF;
    };

    for (auto it = str.begin(); it < str.end(); ) {

        if (is_lead_surrogate(*it)) {
            if (it + 1 == str.end() || !is_trail_surrogate(*(it + 1))) {
                it = str.erase(it);
                continue;
            }
            auto lead = *it;
            auto trail = *(++it);
            auto codepoint = ((lead - lead_surrogate_begin) << surrogate_bits) + (trail - trail_surrogate_begin) + surrogate_base;
            if (!legalCodepoint(codepoint) || codepoint > 0x10000) {
                it = str.erase(it - 1, it + 1);
                continue;
            }
            ++it;  // move past the trail surrogate
        } else if (is_trail_surrogate(*it)) {
            it = str.erase(it);
            continue;
        }
        if (it == str.end())
            break;
        uint32_t codepoint = *it;
        if (!legalCodepoint(codepoint))[[unlikely]] {
            it = str.erase(it);
        }
        ++it;
    }
    return str;
}

inline constexpr auto legalStringUTF8(std::string str)  -> std::string{
    // Unicode              UTF-8
    // U+0000...U+007F      0xxxxxxx
    // U+0080...U+07FF      110xxxxx 10xxxxxx
    // U+0800...U+FFFF      1110xxxx 10xxxxxx 10xxxxxx
    // U+10000...U+10FFFF   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    constexpr std::array<std::uint8_t, 256> utf8_extra_bytes = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5,
    };

    constexpr std::array<std::uint32_t, 6> utf8_offsets = {
            0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080,
    };

    if (str.empty())
        return str;

    auto legalCodepoint = [&](std::string::iterator &it) constexpr noexcept {
        uint32_t codepoint = 0;
        if ((uint8_t(*it) >> 6) == 0x02)[[unlikely]]
            return false;
        codepoint += (uint8_t)(*it);
        const auto extra_bytes_to_read = utf8_extra_bytes[(uint8_t)*it];
        if ((it + extra_bytes_to_read) >= str.end())[[unlikely]]
            return false;
        for (auto i = 1; i <= extra_bytes_to_read; ++i) {
            if ((static_cast<uint8_t>(*(it + i)) & 0xC0) != 0x80)[[unlikely]]
                return false;
            codepoint <<= 6;
            codepoint += (uint8_t)(*(it + i));
        }
        codepoint -= utf8_offsets[extra_bytes_to_read];
        if (codepoint > 0x10ffff)[[unlikely]]
            return false;
        it += extra_bytes_to_read + 1;
        return true;
    };

    for (auto it = str.begin(); it < str.end(); ) {
        if (!legalCodepoint(it))[[unlikely]]{
            it = str.erase(it);
        }
    }

    return str;
}


#endif //ZHUAN_HARDWARE_LIB_LEGALLY_H
