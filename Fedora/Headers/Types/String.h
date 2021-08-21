#pragma once

#include <utility>

#include "BasicType.h"

namespace fedora {
    namespace types {

        class String : public BasicType {
        private:
            std::wstring value;
        public:
            explicit String(std::wstring s):value(std::move(s)){}

            std::wstring eval() override;

            Type type() override {
                return types::STRING;
            }

            std::wstring getImportantQuestion();
        };

    }
}
