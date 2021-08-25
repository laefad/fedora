#pragma once

#include <vector>

#include "Parser/Token.h"

namespace fedora {
    namespace parser {
        /**
         * @brief Это класс, который будет хранить в себе все спаршеные токены
         */
        class TokensHolder {
        private:
            std::vector<Token> tokens;
        public:
            explicit TokensHolder();

            /**
             * Add token to tokens list
             *
             * @param a - token to add
             */
            void add(const Token &a);

            //TODO добавить итератор

            //TODO убрать
            std::vector<Token> &getData();

            // ОТСЧЕТ ЛИНИЙ НАЧИНАЕТСЯ С 0!
            std::vector<Token> getLines(size_t line, size_t lines_range);

            size_t size();
        };
    }
}
