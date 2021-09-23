#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

#include "Parser/Token.h"
#include "Parser/TokensHolder.h"

#include "Parser/Utf8istream.h"

namespace fedora {
    namespace parser {
        /// Класс для парсинга файла на токены
        class Parser {
        public:

            explicit Parser(Utf8istream in);

            /**
             * @brief Обработать данные и получить токены из источника
             *
             * @return TokensHolder с полученными токенами
             */
            TokensHolder parse();

            // TODO Нужен ли метод для изменения текущей line ? 
            // Допустим установить начальную строку на 10

        private:
            /// Входящий поток
            Utf8istream in;
            /// Номер строки, на которой был расположен текущий токен
            uint32_t line;

        private:

            /// Прочитать следующий токен
            Token readToken();

            /// Прочитать токен строки
            Token readString();

            /// Прочитать токен комментария
            Token readComment();
        };
    }
}
