//
// Created on 09.08.2021.
//

#pragma once

#include "Context/Function/Function.h"
#include "Context/Function/Returnable/Returnable.h"
#include <utility>

namespace fedora {
    namespace builder {
        class BuildableFunction : public context::Function {
            bool contextIsReady = false;
        public:
            explicit BuildableFunction(std::shared_ptr<Function> parent) : context::Function(std::move(parent)) {}

            bool isNameDeclared() {
                return !name.empty();
            }

            bool isContextEmpty() {
                return children.empty();
            }

            void addKeyWord(KeyWord &t) {
                keyWords.push_back(t);
            }

            void setName(std::wstring &s) {
                name = s;
            }

            void setContextFinished() {
                contextIsReady = true;
            }

            bool isContextFinished() const {
                return contextIsReady;
            }


            void setReturnable(context::Returnable &r) {
                returnable = std::make_unique<context::Returnable>(r);
            }
        };
    }
}
