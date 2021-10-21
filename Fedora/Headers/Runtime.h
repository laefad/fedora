#pragma once

#include "iostream"

#include "Types/BindedFunCall.h"
#include "Types/Number.h"
#include "Types/List.h"
#include "Types/String.h"
#include "Types/Null.h"
#include "Context/Function/Function.h"
#include "Context/Function/FeFunction.h"
#include "Context/Function/BuiltinFunction.h"
#include "Stack/StackHolder.h"

#include "Utils/Logger.h"

namespace fedora {
    class Runtime {
    public:
        static context::Function::Context getSTDContext() {
            using fedora::context::BuiltinFunction;
            using fedora::context::ContextualComplement;
            using fedora::context::Function;
            using fedora::context::FeFunction;
            using fedora::types::Type;
            using fedora::types::Null;
            using fedora::types::Number;

            auto context = context::Function::Context();

            auto temp = std::make_shared<BuiltinFunction>(
                u8"+",
                2,
                [=] (std::shared_ptr<ContextualComplement::Context> ctx) {
                    auto one = ctx->operator[](u8"_0");
                    auto two = ctx->operator[](u8"_1");

                    if (one->type() != two->type()) {
                        Logger::logE(u8"\'+\' function accept two arguments with different types : " +
                         one->eval() + 
                         u8", " +
                         two->eval());
                        // TODO throw RUNTIME ERROR
                        throw std::exception();
                    }

                    switch (one->type())
                    {
                    case Type::NUMBER :
                        return std::make_shared<Number>(
                            getValueFromNumber(one) + getValueFromNumber(two)
                        );
                    }

                    // TODO remove
                    Logger::logE(u8"end of \'+\' function");
                    throw std::exception();
                }
            );

            // add +
            context[u8"+"] = std::move(temp);

            temp = std::make_shared<BuiltinFunction>(
                u8"log",
                1,
                [=] (std::shared_ptr<ContextualComplement::Context> ctx) {
                    auto one = ctx->at(u8"_0");
                    out(one->eval() + u8"\n");
                    return std::make_shared<Null>();
                }
            );

            //add log
            context[u8"log"] = std::move(temp);

            temp = std::make_shared<BuiltinFunction>(
                u8"$",
                0,
                [=] (std::shared_ptr<ContextualComplement::Context> ctx) {
                    //out(types::String().getImportantQuestion());
                    return std::make_shared<types::String>(types::String(u8"").getImportantQuestion());
                }
            );
    
            //add IMPORANT QUESTION
            context[u8"$"] = std::move(temp);

            return std::move(context);
        }
    private:

        static double getValueFromNumber(std::shared_ptr<types::BasicType> b) {
            return static_cast<fedora::types::Number *>(b.get())->getValue();
        }

        static void out(std::u8string str) {
            std::cout << StaticUtils::u8s2s(str);
        }

    public:
        /// WE MODIFY CONTEXT!!!!!!!
        static void execute(StackHolder sh, context::Function::Context context) {
            using fedora::context::FeFunction;
            using fedora::types::Null;

            auto std = getSTDContext();

            for (auto [key, val] : std) {
                context[key] = std::move(val);
            }

            auto root = std::make_shared<FeFunction>(
                nullptr,
                u8"__ROOT__",
                std::make_shared<Null>(),
                FeFunction::Arguments(),
                context
            );

            for (auto [key, val] : context) {
                context[key]->setParent(root);
            }

            using Call = StackHolder::Call;
            using BindedCall = std::shared_ptr<types::BindedFunCall>;

            for (const Call &call : sh.getData()) {
                types::BindedFunCall * bcall = call->bind(root).get();
                auto res = bcall->execute();

                while(res->type() == types::Type::FUN_CALL) {
                    bcall = dynamic_cast<types::BindedFunCall *>(res.get());
                    res = bcall->execute();
                }
            }
        }
    };
}
