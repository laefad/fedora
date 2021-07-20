#pragma once

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include "Context.h"
#include "Token.h"
#include "Analyzer.h"

namespace fedora {
    /// Класс для парсинга файла на токены
    class Parser {
    private:
        /// Файловый поток
        std::ifstream& fin;

        Analyzer& analyzer;

        /// Прочитать следующий токен
        Token readToken();

        /// Распознать токен
        void analyzeToken(Token&);

        /// Игнорируем ли мы символ или нет
        static bool isIgnored(wchar_t &);

        /// Является ли символ разделителем между докенами
        static bool isDelimiter(wchar_t &);
    public:
        Parser(const std::string &, std::ifstream &, Analyzer&);

        /// Прочитать весь файл и сохранить токены
        void readFile();

        // Деструкт
        ~Parser() {
            fin.close();
        }
    };
}
