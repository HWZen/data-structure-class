//
// Created by HWZ on 2023/11/13.
//

#ifndef INSTALL_TOOLS_BASE32_H
#define INSTALL_TOOLS_BASE32_H

#include <string>
#include <array>
#include <vector>

inline constexpr std::array base64_chars{
    'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K','L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U','V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e','f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o','p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y','z', '0', '1', '2', '3', '4', '5', '6', '7',
    '8','9', '+', '/'
};

constexpr std::string base64_enc(const auto &array){
    static_assert(sizeof(array[0]) == 1);
    auto len_encoded = ((array.size() + 2) / 3) * 4;

    std::string ret;
    ret.reserve(len_encoded);

    unsigned pos{0};

    while (pos < array.size()){
        ret.push_back(base64_chars[(array[pos + 0] & 0xFC) >> 2]);

        if (pos + 1 < array.size()) {
            ret.push_back(base64_chars[((array[pos + 0] & 0x03) << 4) + ((array[pos + 1] & 0xF0) >> 4)]);
            if (pos + 2 < array.size()) {
                ret.push_back(base64_chars[((array[pos + 1] & 0x0F) << 2) + ((array[pos + 2] & 0xC0) >> 6)]);
                ret.push_back(base64_chars[array[pos + 2] & 0x3F]);
            } else {
                ret.push_back(base64_chars[(array[pos + 1] & 0x0F) << 2]);
                ret.push_back('=');
            }
        }
        else{
            ret.push_back(base64_chars[(array[pos + 0] & 0x03) << 4]);
            ret.push_back('=');
            ret.push_back('=');
        }

        pos += 3;
    }

    return ret;
}

static constexpr unsigned int pos_of_char(const unsigned char chr) {
    //
    // Return the position of chr within base64_encode()
    //

    if      (chr >= 'A' && chr <= 'Z') return chr - 'A';
    else if (chr >= 'a' && chr <= 'z') return chr - 'a' + ('Z' - 'A')               + 1;
    else if (chr >= '0' && chr <= '9') return chr - '0' + ('Z' - 'A') + ('z' - 'a') + 2;
    else if (chr == '+' || chr == '-') return 62; // Be liberal with input and accept both url ('-') and non-url ('+') base 64 characters (
    else if (chr == '/' || chr == '_') return 63; // Ditto for '/' and '_'
    else
        //
        // 2020-10-23: Throw std::exception rather than const char*
        //(Pablo Martin-Gomez, https://github.com/Bouska)
        //
        throw std::exception("Input is not valid base64-encoded data.");
}

template <class Ty>
constexpr std::vector<Ty> base64_dec(const std::string &str){
    static_assert(sizeof(Ty) == 1);

    size_t approx_length_of_decoded_string = str.size() / 4 * 3;
    std::vector<Ty> ret;
    ret.reserve(approx_length_of_decoded_string);
    size_t pos{0};
    while (pos < str.size()) {
        size_t pos_of_char_1 = pos_of_char(str.at(pos+1) );

        ret.push_back(static_cast<std::string::value_type>( ( (pos_of_char(str.at(pos+0)) ) << 2 ) + ( (pos_of_char_1 & 0x30 ) >> 4)));

        if ( ( pos + 2 < str.size()  )       &&  // Check for data that is not padded with equal signs (which is allowed by RFC 2045)
             str[pos+2] != '='     &&
             str[pos+2] != '.'         // accept URL-safe base 64 strings, too, so check for '.' also.
            ){
            unsigned int pos_of_char_2 = pos_of_char(str[pos+2] );
            ret.push_back(static_cast<std::string::value_type>( (( pos_of_char_1 & 0x0f) << 4) + (( pos_of_char_2 & 0x3c) >> 2)));

            if ( ( pos + 3 < str.size() )     &&
                 str[pos+3] != '='  &&
                 str[pos+3] != '.'
                    ){
                ret.push_back(static_cast<std::string::value_type>( ( (pos_of_char_2 & 0x03 ) << 6 ) + pos_of_char(str[pos+3])   ));
            }
        }

        pos += 4;
    }

    return ret;

}




#endif //INSTALL_TOOLS_BASE32_H
