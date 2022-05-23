#pragma once

#include "AnalyticBasic.h"

namespace fedora::analytic {
    /**
     * Here we need to decide what to do when list ends
     *
     * @example case 1: List inside list
     * let a = [ [1] [2] ]
     *
     * @example case 2: List in returnable, so waiting a "let" keyword
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
     *
     * @example case 8: Next function implementation
     * let a = [1 2 3]
     * pure let b = ...
     */
    class ReadAfterListEnd : public AnalyticBasic {
    public:
        /// override parent method
        std::shared_ptr<AnalyticBasic> analyzeToken(parser::Token const&, ContextBuilder&) override;

        /// override parent method
        std::u8string getClassFileName() override;
    };
}
