//
// Created on 31.07.2021.
//

#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Here we need to decide what to do when list ends
         *
         * @example case 1: List inside list
         * let a = [ [1] [2] ]
         *
         * @example case 2: List in returnable, so waiting a key word
         * let a = [1 2 3]
         * let b ...
         *
         * @example case 3: List in context
         * let z where
         *   let a = [1 2]
         * = ...
         *
         * @example case 4: List in force call args
         * let a list = ...
         * force a([1 2 3])
         *
         * @example case 5: Combination of list and int
         * let a = main( [1 2] 3 )
         *
         * @example case 6: Combination of list and str
         * let a = main( [1 2] "lmao" )
         *
         * @example case 7: Combination of list and function
         * let a = main ( [1 2] fun)
         */
        class ReadAfterListEnd : public AnalyticBasic {
        public:
            explicit ReadAfterListEnd(std::vector <Token> t) : AnalyticBasic(std::move(t)) {}

            /// @overload parent method
            std::shared_ptr <AnalyticBasic> analyzeToken(Token &) override;

            /// @overload parent method
            std::string getFileName() override;
        };
    }
}