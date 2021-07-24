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

        analytic::Analyzer& analyzer;

        /// Прочитать следующий токен
        Token readToken();

        /// Распознать токен
        /// @return True, если он встаёт в текущий контекст
        bool analyzeToken(Token&);

        /// Игнорируем ли мы символ или нет
        static bool isIgnored(wchar_t &);
    public:
        Parser(const std::string &, std::ifstream &, analytic::Analyzer&);

        /// Прочитать весь файл и сохранить токены
        //TODO Читать файл через getLine, чтобы сохранять номера строк для каждого токена. Это поможет выдавать пользователям ошибку с указанием на какой строке они ошиблись
        void readFile();

        // Деструкт
        ~Parser() {
            fin.close();
        }
    };
}
