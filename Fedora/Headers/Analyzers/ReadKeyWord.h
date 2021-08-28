#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Прочитать ключевые слова при объявлении функции
         */
        class ReadKeyWord : public AnalyticBasic {
        public:
            ReadKeyWord() = default;

            /**
            *
            * @param t - token we get
            * @param b - reference to context builder
            * @return next analyzer
            *
            * @example case 1: pure keyword
            * pure let a = 1
            * # we need to init new function and send "pure" keyword to context#
            *
            * @example case 2: force keyword
            * let a = null
            * force a
            * # we use this function to build package-level forceCall #
            *
            * @example case 3: After function finish inside context
            * let a where
            *   let b = null
            *   # after function b finished, this function will read "=" token #
            *   # because after function there have to be declaration of another or the result of higher-level function #
            * = null
            *
            * @example where we DO NOT use this function
            * let a = null
            * let b = force a
            * # in this case, result resolver [ReadResult] will get the "force" token #
            */
            std::shared_ptr<AnalyticBasic> analyzeToken(parser::Token const &, ContextBuilder &) override;

            std::wstring getClassFileName() override;
        };
    }
}
