//
// Created on 03.08.2021.
//

#pragma once

#include <utility>

#include "Stack/ForceCall/ForceCall.h"
#include "Exceptions/BuilderException.h"

namespace fedora {
    namespace builder {
        enum FunCallDeclarationMode {
            SET_NAME,
            SET_ARGUMENTS,
        };

        class ForceCallDeclarator {
            std::shared_ptr<context::ForceCall> forceCall;
        public:
            explicit ForceCallDeclarator(std::shared_ptr<context::ForceCall> forceCall) : forceCall(
                    std::move(forceCall)) {}

            void setName(std::wstring &s) {
                if (forceCall != nullptr) {
                    forceCall->setRawName(s);
                } else
                    throw exception::BuilderException(
                            "You're trying to set name for forceCall, but pointer to forceCall is NULLPTR ",
                            "ForceCallDeclarator::setName(std::wstring&)");
            }
        };
    }
}
