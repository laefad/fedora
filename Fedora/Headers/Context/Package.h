//
// Created on 06.08.2021.
//

#pragma once

#include "Context/Function/Function.h"

namespace fedora {
    namespace context {
        // TODO Пока нигде не используется.
        class Package {
        private:
            std::vector<std::shared_ptr<Function>> children = std::vector<std::shared_ptr<Function>>();
        public:
            Package () = default;
            void addChildFunction(std::shared_ptr<Function> f){
                children.push_back(f);
            }
        };
    }
}
