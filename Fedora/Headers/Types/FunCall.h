#pragma once

#include <utility>
#include <vector>

#include "Types/BasicType.h"
#include "Context/ContextualComplement.h"

namespace fedora::types {
    class FunCall: public types::BasicType, public fedora::context::ContextualComplement {
    public:
        using FunCallArguments = std::vector<std::shared_ptr<fedora::types::BasicType>>;
    protected:
        // Массив аргументов функции, которая будет вызвана
        FunCallArguments args;
        bool forced;
    protected:
        explicit FunCall(
            fedora::context::ContextualComplement::Context context,
            FunCallArguments args,
            bool forced
        );

        explicit FunCall(FunCallArguments args, bool forced);

    public:
        virtual Type type() override;

        virtual std::u8string eval() = 0;

        bool isForced();

        virtual std::u8string getFunctionName() = 0;

    private:
        explicit FunCall();
    };
}
