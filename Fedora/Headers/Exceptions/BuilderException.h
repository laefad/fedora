//
// Created on 06.08.2021.
//

#pragma once

#include <utility>

#include "FException.h"
#include "StaticUtils.h"

namespace fedora {
    namespace exception {
        class BuilderException : public FException {
            static std::string makeText(const std::string &msg, const std::string &functionName) {
                std::string res =
                        "ContextBuilder Exception\n" + std::string() + "\tFunction: " + functionName + "\n" +
                        "\tError: " + msg;
                return res;
            }

        public:
            explicit BuilderException(const std::string &msg, const std::string &functionName) : FException(
                    makeText(msg, functionName)) {}

            explicit BuilderException(const std::wstring &msg, const std::string &functionName) : FException(
                    makeText(StaticUtils::ws2s(msg), functionName)) {}
        };
    }
}
