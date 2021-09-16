#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

#include "Parser/Token.h"
#include "Parser/TokensHolder.h"

namespace fedora {
    namespace parser {
        /// Класс для парсинга файла на токены
        class Parser {
        public:

            static Parser makeFileParser(const std::u8string &fileName);

            static Parser makeStringParser(std::u8string wstr);

            //TODO !important может быть неправильный тип stream
            static Parser makeStreamParser(std::unique_ptr<std::istream> in);

        public:
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
            std::unique_ptr<std::istream> in;
            /// Номер строки, на которой был расположен текущий токен
            uint32_t line;

        private:
            explicit Parser(std::unique_ptr<std::istream> in);

            /// Прочитать следующий токен
            Token readToken();

            /// Прочитать токен строки
            Token readString();

            /// Прочитать токен комментария
            Token readComment();

            /// Устанавливает тип токена, в зависимости от его содержимого
            static void determineAndSetTokenType(Token &t);
        };
    }
}
