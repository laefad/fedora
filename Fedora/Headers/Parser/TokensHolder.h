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

            // TODO или возвращать строку...
            std::vector<Token> getLineOfTokens(uint32_t lineNumber);

            //TODO добавить итератор

            //TODO убрать
            std::vector<Token> &getData();

            size_t size();
        };
    }
}
