
#include "Context/Function/FeFunction.h"
#include "Types/UnbindedFunCall.h"
#include "Types/BindedFunCall.h"

#include "Utils/Logger.h"

namespace fedora::context {
    FeFunction::FeFunction(
        std::shared_ptr<Function> parent, 
        std::u8string name
    ): 
        Function(std::move(parent), std::move(name)),
        children(Context()),
        returnable(nullptr),
        args(std::vector<std::u8string>())
    {}

    FeFunction::FeFunction(
        std::shared_ptr<Function> parent, 
        std::u8string name,
        std::shared_ptr<fedora::types::BasicType> returnable,
        Function::Arguments args,
        Context children
    ): 
        Function(std::move(parent), std::move(name)),
        children(children),
        returnable(returnable),
        args(args)
    {}

    std::u8string FeFunction::logRet() const {
        return returnable->eval();
    }

    std::shared_ptr<Function::Arguments> FeFunction::getArguments() const {
        return std::make_shared<Function::Arguments>(args);
    }

    const std::shared_ptr<Function::Context> FeFunction::getContext() const {
        return std::make_shared<Function::Context>(children);
    }

    std::pair<std::shared_ptr<Function>, FunctionRelation> FeFunction::find(
        std::u8string name, FunctionRelation filteredType
    ) {
        //find child
        if (filteredType == FunctionRelation::Child || filteredType == FunctionRelation::Any) {
            for (auto ch : children) {
                if (name == ch.first) {
                    return std::make_pair(
                        ch.second,
                        FunctionRelation::Child
                    );
                }
            }
        } else {
            return std::make_pair(
                nullptr, 
                FunctionRelation::Any
            );
        }

        //find self
        if (filteredType == FunctionRelation::Self || filteredType == FunctionRelation::Any) {
            if (name == this->name) {
                return std::make_pair(
                    shared_from_this(), 
                    FunctionRelation::Self
                );
            }
        } else {
            return std::make_pair(
                nullptr, 
                FunctionRelation::Any
            );
        }

        //find subling
        if (parent && 
            (filteredType == FunctionRelation::Subling || 
             filteredType == FunctionRelation::Any
            )
        ) {
            return parent->find(name, FunctionRelation::Child);
        } else {
            return std::make_pair(
                nullptr, 
                FunctionRelation::Any
            );
        }

        //find parent
        if (filteredType == FunctionRelation::Parent || 
            filteredType == FunctionRelation::Any
        ) {
            if (parent) {
                return parent->find(name, FunctionRelation::Parent);
            } else {
                // Если нет элемента выше, то этот считается коренным 
                // и дает видимость ко всем своим потомкам 1 уровня
                return parent->find(name, FunctionRelation::Child);
            }
        } else {
            return std::make_pair(
                nullptr, 
                FunctionRelation::Any
            );
        }

        return std::make_pair(
            nullptr, 
            FunctionRelation::Any
        );

    }

    std::shared_ptr<types::BasicType> FeFunction::call(
        std::shared_ptr<ContextualComplement::Context> context
    ) {
        using types::Type;
        using types::UnbindedFunCall;
        using types::BindedFunCall;
        
        if (returnable->type() == Type::FUN_CALL) {
            auto ufc = static_cast<UnbindedFunCall *>(returnable.get());

            auto requiredName = ufc->getFunctionName();

            // find in inner functions
            auto target = find(requiredName, FunctionRelation::Child);
            if (target.first) {
                return ufc->bind(target.first);
            }
            
            // find in args
            for (auto [key, value] : *context) {
                if (key == requiredName) {
                    return value;
                }
            }

            // find in upper
            target = find(requiredName);
            if (target.first) {
                return ufc->bind(target.first);
            } 

            fedora::Logger::logE(u8"FeFunction::call not found function [" +
                         requiredName + 
                         u8"] in function [" +
                         getName() +
                         u8"]");
            // TODO throw RUNTIME ERROR
            throw std::exception();
        }

        ContextualComplement::addContextToElement(returnable, context);
        return returnable;
    }

}
