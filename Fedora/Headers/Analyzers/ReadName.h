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
            std::shared_ptr<AnalyticBasic> analyzeToken(Token const &, ContextBuilder &) override;

            std::string getClassFileName() override;

            /**
             * Read name during function declaration process
             */
            static std::shared_ptr<AnalyticBasic> functionDeclaration(Token const &, ContextBuilder &);

            /**
             * Read [Returnable] funcCall name
             */
            std::shared_ptr<AnalyticBasic> returnableFunCall(Token const &, ContextBuilder &);

            std::shared_ptr<AnalyticBasic> forceCall(Token const &, ContextBuilder &);

            std::shared_ptr<AnalyticBasic> listValue(Token const &, ContextBuilder &);

            std::shared_ptr<AnalyticBasic> functionArgument(Token const &, ContextBuilder &);
        };
    }
}
