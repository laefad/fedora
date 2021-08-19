#pragma once

#include <string>
#include <vector>

namespace fedora {
    namespace context {
        class NamesOfArguments {
            std::vector<std::wstring> argNames = std::vector<std::wstring>();
        public:
            void addStrToArgNames(const std::wstring& wstring){
                argNames.push_back(wstring);
            }
        };
    }
}