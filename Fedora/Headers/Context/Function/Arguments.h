#pragma once

#include <string>
#include <vector>

namespace fedora {
    namespace context {
        class NamesOfArguments {
            std::vector<std::u8string> argNames = std::vector<std::u8string>();
        public:
            void addStrToArgNames(const std::u8string& wstring){
                argNames.push_back(wstring);
            }
        };
    }
}