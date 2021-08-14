#pragma once

#include "BasicType.h"

namespace fedora {
    namespace types {

        class String : public BasicType {
        private:
            std::wstring value;
        public:
            std::wstring eval() override;

            Type type() override {
                return types::STRING;
            }

            std::wstring getImportantQuestion();
        };

    }
}
