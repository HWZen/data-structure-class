//
// Created by HWZ on 2024/9/24.
//

#ifndef BASE91_H
#define BASE91_H
#include <array>
#include <vector>
#include <string>
#include <unordered_map>

template <class Ty>
constexpr std::vector<Ty> base91_decode(const std::string &str)
{
    static_assert(sizeof(Ty) == 1);

    auto pos_of_char = [](const unsigned char chr)constexpr -> unsigned int
    {
        constexpr std::array base91_alphabet{
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$',
            '%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '<', '=',
            '>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~', '"'
        };
        static const std::unordered_map<char, unsigned int> base91_map = [&]{
            std::unordered_map<char, unsigned int> m;
            for (unsigned int i = 0; i < base91_alphabet.size(); ++i) {
                m[base91_alphabet[i]] = i;
            }
            return m;
        }();
        const auto it = base91_map.find(static_cast<char>(chr));
        if (it == base91_map.end()) [[unlikely]] {
            throw std::exception("Invalid character in base91 string");
        }
        return it->second;
    };

    std::vector<Ty> output;
    auto approx_length_of_decoded_string = ((str.size() * 13) / 14) + 10;
    output.reserve(approx_length_of_decoded_string);
    int n = 0;
    unsigned int b = 0;
    int v = -1;

    for (auto chr : str) {
        auto c = pos_of_char(chr);
        if (v < 0) {
            v = c;
        } else {
            v += c * 91;
            b |=  static_cast<unsigned int>(v) << n;
            n += ((v & 8191) > 88) ? 13 : 14;
            do {
                output.push_back(b & 255);
                b >>= 8;
                n -= 8;
            } while (n >= 8);
            v = -1;
        }
    }
    if (v + 1) {
        output.push_back((b | v << n) & 255);
    }
    return output;
}

std::string base91_encode(const auto &input)
{
    constexpr std::array base91_alphabet{
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$',
        '%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '<', '=',
        '>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~', '"'
    };
    auto b = 0;
    auto n = 0;
    std::string output;
    auto approx_length_of_encoded_string = ((input.size() * 13) / 8) + 10;
    output.reserve(approx_length_of_encoded_string);
    for (auto i : input) {
        b |= i << n;
        n += 8;
        if (n > 13) {
            auto v = b & 8191;
            if (v > 88) {
                b >>= 13;
                n -= 13;
            } else {
                v = b & 16383;
                b >>= 14;
                n -= 14;
            }
            output.push_back(base91_alphabet[v % 91]);
            output.push_back(base91_alphabet[v / 91]);
        }
    }
    if (n) {
        output.push_back(base91_alphabet[b % 91]);
        if (n > 7 || b > 90) {
            output.push_back(base91_alphabet[b / 91]);
        }
    }
    return output;
}


#endif //BASE91_H
