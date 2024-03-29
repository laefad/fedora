#pragma once

#include <utility>

#include "Types/BasicType.h"

namespace fedora::types {
    class String : public BasicType {
    private:
        std::u8string value;
    public:
        explicit String(std::u8string s) : value(std::move(s)) {}

        std::u8string eval() override;

        Type type() override {
            return types::STRING;
        }

        std::u8string getImportantQuestion();
    };
}
