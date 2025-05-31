#pragma once
#include "Head_1.h"

enum class MessageType {
    INFO,
    WARNING,
    ERROR,
    MEMORY,
    REGISTER
};

enum class Type2Tpe {
    t8_2_8,
	t8_2_16,
	t16_2_8,
	t16_2_16
};



void message(string msg, uint8_t in_load, uint8_t out_load, MessageType type);

void removeTrailingSpaces(string& str);

void trim(string& str);

void debug(string msg, uint16_t in_addr, uint8_t in_data, MessageType type);

bool carry(uint8_t value);

string toUpper(const string& input);

size_t t2t_message(string message, uint16_t a, uint16_t b, Type2Tpe type);


template<typename T>
T htob(const string& hexStr) {
    unsigned int byte;
    stringstream ss;

    ss << hex << hexStr;
    ss >> byte;

    return static_cast<T>(byte);
}

template<typename T>
constexpr bool parity(T val) {
    static_assert(std::is_unsigned_v<T>, "Only unsigned types are allowed");
#if __cpp_lib_bitops >= 201907L
    return (popcount(val) & 1) == 0;
#else
    return (__builtin_popcountll(static_cast<unsigned long long>(val)) & 1) == 0;
#endif
}

template<typename T>
constexpr bool auxiliaryCarry(T a, T b) {
    static_assert(std::is_unsigned_v<T>, "Only unsigned types are allowed");

    constexpr T nibbleMask = static_cast<T>(0x0F);
    // > 0x0F, -> bit-4
    return ((a & nibbleMask) + (b & nibbleMask)) > nibbleMask;
}

namespace detail {

    inline string clean_hex(const string& s) {
        string str = s;

        // rm 0, 0x pref
        if (str.size() >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
            str = str.substr(2);
        }

        // rem H, h suf
        if (!str.empty() && (str.back() == 'H' || str.back() == 'h')) {
            str.pop_back();
        }

        if (str.empty() || str.find_first_not_of("0123456789abcdefABCDEF") != string::npos) {
            throw invalid_argument("Invalid hex string: " + s);
        }

        return str;
    }

    // hex str -> ui
    inline unsigned parse_hex(const string& s) {
        return stoul(clean_hex(s), nullptr, 16);
    }

    // dec str -> ui
    inline unsigned parse_dec(const string& s) {
		if (s.empty() || s.find_first_not_of("0123456789") != string::npos) {
			throw invalid_argument("Invalid decimal string: " + s);
		}
        return stoul(s, nullptr, 10);
    }

    // split 
    inline pair<string, string> split_bytes(const string& data) {
        if (data.size() <= 2) {
            return { "0", data };
        }
        string high = data.substr(0, data.size() - 2);
        string low = data.substr(data.size() - 2);
        return { high, low };
    }

}


template<typename T>
T ston(const string& input) {
    static_assert(sizeof(T) == 1 || sizeof(T) == 2,
        "ston supports only 8-bit or 16-bit types");

    if (input.empty())
        throw invalid_argument("Empty input");

    bool is_hex = (input.back() == 'H' || input.back() == 'h');
    string data = input;
    if (is_hex) {
        data.pop_back();
    }
    cout << data << endl;

    if constexpr (sizeof(T) == 1) {
        unsigned raw = is_hex
            ? detail::parse_hex(data)
            : detail::parse_dec(data);
        return static_cast<T>(raw & 0xFF);
    }
    else {  
        auto [high_str, low_str] = detail::split_bytes(data);
        unsigned low = is_hex
            ? detail::parse_hex(low_str)
            : detail::parse_dec(low_str);
        unsigned high = is_hex
            ? detail::parse_hex(high_str)
            : detail::parse_dec(high_str);

        return static_cast<T>(((high << 8) & 0xFF00) | (low & 0x00FF));
    }
}
