#pragma once

#include <sstream>

#include "FException.h"
#include "StaticUtils.h"

namespace fedora {
    namespace exception {
        class BuilderException : public FException {
        protected:
            std::wstring functionName;

        protected:
            std::wstring construct() const override {
                std::wstringstream buf;

                buf << L"ContextBuilder Exception\n"
                    << L"\tFunction: "
                    << functionName 
                    << L"\n"
                    << L"\tError: "
                    << text;

                return buf.str();
            }

        public:
            explicit BuilderException(std::wstring text, std::wstring functionName):
                FException(text),
                functionName(functionName)
            {}
        };
    }
}
