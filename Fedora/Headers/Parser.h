#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Analyzers/AnalyzerStrategy.h"
#include "Token.h"

namespace fedora {

    /// TODO сделать чтение как из строки, так и из файла
    /// Класс для парсинга файла на токены
    class Parser {
    private:
        /// Файловый поток
        std::wifstream wif;
        /// Номер строки, на которой был расположен текущий токен
        uint32_t line;

        /// Прочитать следующий токен
        Token readToken();

        /// Прочитать токен строки
        Token readString();

        /// Пропускать символы, пока не встретим символ комментария
        void readComment();
    public:
        Parser();

        /// Прочитать весь файл и сохранить токены
        void readFile(std::string const& fileName, TokensHolder & tokensHolder);
    };
}
