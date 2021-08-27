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
            using container = std::vector<Token>;
            using iterator =  container::iterator;
            using const_iterator = container::const_iterator;

            // TODO переместить в cpp

            iterator begin() { return tokens.begin(); }
            iterator end() { return tokens.end(); }
            const_iterator begin() const { return tokens.begin(); }
            const_iterator end() const { return tokens.end(); }
        public:
            explicit TokensHolder();

            /**
             * Add token to tokens list
             *
             * @param a - token to add
             */
            void add(const Token &a);

            /**
             * @return вектор токенов, с линиями принадлежащими отрезку [line-size_t;line+size_t]
             */
            std::vector<Token> getLines(size_t line, size_t range = 2);

            size_t size();
        };
    }
}
