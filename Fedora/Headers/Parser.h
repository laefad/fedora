#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Analyzers/AnalyzerStrategy.h"
#include "Token.h"

namespace fedora {
    /// Класс для парсинга файла на токены
    class Parser {
    private:
        /// Файловый поток
        std::ifstream fin;
        /// Хранилище обработанных токенов
        TokensHolder & tokensHolder;
        /// Номер строки, на которой был расположен текущий токен
        uint32_t line;

        /// Прочитать следующий токен
        Token readToken();

        Token readString();

        Token readComment();
    public:
        //TODO заменить на wifstream
        //TODO можем ли мы использовать константную ссылку на TokensHolder ?
        Parser(std::string const& fileName, TokensHolder & tokensHolder);

        /// Прочитать весь файл и сохранить токены
        void readFile();

        // Деструкт
        ~Parser() {
            // TODO Лишний код, поток закрывается при уничтожении объекта
            fin.close();
        }
    };
}
