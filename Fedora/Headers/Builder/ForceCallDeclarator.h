//
// Created on 03.08.2021.
//

#pragma once

#include <utility>

#include "Builder/BuildableForceCall.h"
#include "Exceptions/BuilderException.h"

namespace fedora {
    namespace builder {
        enum FunCallDeclarationMode {
            SET_NAME,
            SET_ARGUMENTS,
        };

        class ForceCallDeclarator {
            std::shared_ptr<builder::BuildableForceCall> forceCall;
        public:
            explicit ForceCallDeclarator(std::shared_ptr<builder::BuildableForceCall> forceCall) : forceCall(
                    std::move(forceCall)) {}

            void setName(std::wstring const &s) {
                if (forceCall != nullptr) {
                    forceCall->setRawName(s);
                } else
                    throw exception::BuilderException(
                            L"You're trying to set name for forceCall, but pointer to forceCall is NULLPTR ",
                            L"ForceCallDeclarator::setName(std::wstring&)");
            }
        };
    }
}
