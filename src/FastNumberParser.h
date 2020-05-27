#pragma once

#include <charconv>
#include <string>

inline bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

inline size_t getNumFrom(std::string const & s, size_t &pos){
    auto start_pos = pos;
    while (pos < s.size() && isDigit(s[pos]))
        ++pos;
    size_t ans = 0;
    std::from_chars(s.data() + start_pos, s.data() + pos, ans);
    return ans;
}
