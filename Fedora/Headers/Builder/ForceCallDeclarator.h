#pragma once

#include <utility>

#include "Builder/BuildableFunCall.h"
#include "Exceptions/BuilderException.h"

namespace fedora {
    namespace builder {
        enum FunCallDeclarationMode {
            SET_NAME,
            SET_ARGUMENTS,
        };

        class ForceCallDeclarator {
            std::shared_ptr<builder::BuildableFunCall> forceCall;
        public:
            explicit ForceCallDeclarator(std::shared_ptr<builder::BuildableFunCall> forceCall) : forceCall(
                    std::move(forceCall)) {}

            void setName(std::u8string const &s) {
                if (forceCall != nullptr) {
                    // TODO раньше было set raw name, не вижу разницы
                    forceCall->setName(s);
                } else
                    throw BuilderException(
                            u8"You're trying to set name for forceCall, but pointer to forceCall is NULLPTR ",
                            u8"ForceCallDeclarator::setName(std::u8string&)");
            }
        };
    }
}
