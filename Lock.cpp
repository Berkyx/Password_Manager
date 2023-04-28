//
// Created by berka on 14.05.2022.
//

#include "Lock.hpp"

namespace s25786 {
    auto Lock::encrypt (std::string str) -> std::string {
        auto key = 3;
        for(auto i = 0; str[i] != '\0'; ++i) {
            auto ch = str[i];
            if (ch >= 'a' && ch <= 'z') {
                ch = ch + key;
                if (ch > 'z') {
                    ch = ch - 'z' + 'a' - 1;
                }
                str[i] = ch;
            }
            else if (ch >= 'A' && ch <= 'Z') {
                ch = ch + key;
                if(ch > 'Z') {
                    ch = ch - 'Z' + 'A' -1;
                }
                str[i] = ch;
            }
            else {
                ch = ch + key;
                str[i] = ch;
            }
        }
        return str;
    }
    auto Lock::decrypt (std::string str) -> std::string {
        auto key = 3;
        for (auto i = 0; str[i] != '\0'; ++i) {
            auto ch = str[i];
            if(ch >= 'a' && ch <= 'z') {
                ch = ch - key;
                if(ch < 'a') {
                    ch = ch + 'z' - 'a' + 1;
                }
                str[i] = ch;
            }
            else if(ch >= 'A' && ch <= 'Z') {
                ch = ch - key;
                if(ch > 'a') {
                    ch = ch + 'Z' - 'A' + 1;
                }
                str[i] = ch;
            }
            else {
                ch = ch - key;
                str[i] = ch;
            }
        }
        return str;
    }
} // s25786