//
// Created on 06.08.2021.
//

#pragma once

#include <utility>

#include "Context/Function/Function.h"

namespace fedora {
    namespace context {
        // TODO Пока нигде не используется.
        class Package {
        private:
            std::map<std::u8string, std::shared_ptr<Function>> children;
        public:
            Package ():
                children(std::map<std::u8string, std::shared_ptr<Function>>())
                {}

            void setChildFunction(std::shared_ptr<Function> f, const std::u8string& name){
                children[name] = std::move(f);
            }

            std::shared_ptr<std::map<std::u8string, std::shared_ptr<Function>>> getContext(){
                return std::make_shared<std::map<std::u8string, std::shared_ptr<Function>>>(children);
            }
        };
    }
}
