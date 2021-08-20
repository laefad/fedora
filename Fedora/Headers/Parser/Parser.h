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

            /// Тип исходящего потока 
            enum Type {
                File,
                String 
            };

            // TODO добавить фабрику с потоком. 

            /// При указании Type::File - data - имя файла с кодом
            /// При указании Type::String - data - строка с кодом
            // TODO два отдельных метода лучше наверное...
            static Parser make(Type type, std::wstring data);
        
        public:
            /// 
            TokensHolder parse();

        private:
            /// Входящий поток
            std::unique_ptr<std::wistream> in;
            /// Номер строки, на которой был расположен текущий токен
            uint32_t line;

        private:
            explicit Parser(std::unique_ptr<std::wistream> in);

            /// Прочитать следующий токен
            Token readToken();

            /// Прочитать токен строки
            Token readString();

            /// Пропускать символы, пока не встретим символ комментария
            void readComment();

            /// Устанавливает тип токена, в зависимости от его содержимого
            void determineAndSetTokenType(Token & t);
        };
    }
}
