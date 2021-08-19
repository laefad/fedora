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
            std::shared_ptr<AnalyticBasic> analyzeToken(parser::Token const &, ContextBuilder &) override;

            std::string getClassFileName() override;

            /**
             * Read name during function declaration process
             */
            static std::shared_ptr<AnalyticBasic> functionDeclaration(parser::Token const &, ContextBuilder &);

            /**
             * Read [Returnable] funcCall name
             */
            static std::shared_ptr<AnalyticBasic> returnableFunCall(parser::Token const &, ContextBuilder &);

            static std::shared_ptr<AnalyticBasic> forceCall(parser::Token const &, ContextBuilder &);

            std::shared_ptr<AnalyticBasic> listValue(parser::Token const &, ContextBuilder &);

            std::shared_ptr<AnalyticBasic> functionArgument(parser::Token const &, ContextBuilder &);
        };
    }
}
