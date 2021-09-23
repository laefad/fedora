//
// Created on 06.08.2021.
//

#pragma once

#include <utility>
#include <map>

#include "Context/Function/Function.h"

namespace fedora {
    namespace context {
        // TODO Пока нигде не используется.
        class Package {
        private:
            Function::Context children;
        public:
            Package ():
                children(std::map<std::u8string, std::shared_ptr<Function>>())
                {}

            void setChildFunction(std::shared_ptr<Function> f, const std::u8string& name){
                children[name] = std::move(f);
            }

            const std::shared_ptr<Function::Context> getContext() const {
                return std::make_shared<Function::Context>(children);
            }
        };
    }
}
