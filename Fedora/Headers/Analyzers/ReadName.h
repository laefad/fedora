//
// Created on 23.07.2021.
//
#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Read function or funCall name
         */
        class ReadName : public AnalyticBasic {
        public:
            /// @see analyzeToken docs
            enum ReadNameMode {
                FUNCTION_DECLARATION,
                RETURNABLE_FUN_CALL,
                FORCE_CALL,
                LIST_VALUE,
                FUNCTION_ARGUMENT,
            };
        private:
            ReadNameMode mode;
        public:
            explicit ReadName(ReadNameMode mode) : mode(mode) {}

            /// Fabric method
            std::shared_ptr<AnalyticBasic> analyzeToken(Token &, ContextBuilder &) override;

            std::string getClassFileName() override;

            /**
             * Read name during function declaration process
             */
            static std::shared_ptr<AnalyticBasic> functionDeclaration(Token &, ContextBuilder &);

            /**
             * Read [Returnable] funcCall name
             */
            std::shared_ptr<AnalyticBasic> returnableFunCall(Token &, ContextBuilder &);

            std::shared_ptr<AnalyticBasic> forceCall(Token &, ContextBuilder &);

            std::shared_ptr<AnalyticBasic> listValue(Token &, ContextBuilder &);

            std::shared_ptr<AnalyticBasic> functionArgument(Token &, ContextBuilder &);
        };
    }
}