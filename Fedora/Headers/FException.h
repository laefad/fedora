//
// Created on 21.07.2021.
//
#pragma once

#include "StaticUtils.h"

namespace fedora {
    struct FException : public std::exception {
    public:
        std::string s;

        FException(std::wstring ss) {
            s = StaticUtils::ws2s(ss);
        }

        FException(std::string ss):s(ss){}

        ~FException() throw() {} // Updated
        const char *what() const throw() { return s.c_str(); }
    };
}
