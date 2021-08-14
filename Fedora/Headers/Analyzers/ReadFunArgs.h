#pragma once

#include <memory>
#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
//        namespace funArgs{
//            enum mode {
//                /**
//                 * @example
//                 * let a = b(1 2 3)
//                 */
//                READ_ARGS_TO_DEFINE,
//
//                /**
//                 * @example
//                 * force main(1 2 3)
//                 */
//                READ_ARGS_TO_FORCE,
//            };
//        }
        /**
         * Read function arg names
         *
         * @example case 1: Has args
         * let fun arg1 arg2 = ...
         *
         * @example case 2: Does not have args
         * let fun = ...
         */
        class ReadFunArgs : public AnalyticBasic {
        public:
            std::shared_ptr<AnalyticBasic> analyzeToken(Token const &, ContextBuilder &) override;

            std::string getClassFileName() override;
        };
    }
}
