//
// Created on 07.08.2021.
//

#pragma once

#include <vector>
#include "Utils/BasicSingleton.h"
#include "Stack/ForceCall/ForceCall.h"

namespace fedora {
    class StackHolder : public BasicSingleton {
    private:
        std::vector<std::shared_ptr<context::ForceCall>> calls = std::vector<std::shared_ptr<context::ForceCall>>();

        StackHolder() = default;

        /// Main instance
        static StackHolder *instance;

    public:
        /// Singleton instance getter
        static StackHolder *GetInstance();

        std::shared_ptr<context::ForceCall> addForceCall() {
            std::shared_ptr<context::ForceCall> newForceCall = std::make_shared<context::ForceCall>();
            calls.push_back(newForceCall);
            return newForceCall;
        }

        void cleanFields() override {
            calls.clear();
        }

    };
}
