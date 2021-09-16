#pragma once

#include <vector>
#include "Types/UnbindedFunCall.h"

namespace fedora {
    class StackHolder {
    public:
        using Call = std::shared_ptr<types::UnbindedFunCall>;
    private:
        std::vector<Call> calls;

    public:
        explicit StackHolder():
            calls(std::vector<Call>())
        {}

        void addForceCall(Call newForceCall) {
            calls.push_back(newForceCall);
        }

    };
}
