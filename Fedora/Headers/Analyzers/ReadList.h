//
// Created on 26.07.2021.
//

#pragma once

#include "AnalyticBasic.h"


namespace fedora {
    namespace analytic {
        namespace readList {
            enum readMode {
                READ_FUNCTION_ARG,
                READ_FUNCTION_RETURN
            };
        }

        /**
         * Прочитать ключевые слова при объявлении функции
         */
        class ReadList : public AnalyticBasic {
        private:
            readList::readMode mode;
        public:
            explicit ReadList(std::vector<Token> t, readList::readMode m) : AnalyticBasic(std::move(t)), mode(m) {}

            /// Определение родительского метода анализа токена
            std::shared_ptr<AnalyticBasic> analyzeToken(Token &) override;

            std::string getFileName() override;
        };
    }
}
