#pragma once

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <Analyzers/AnalyzerStrategy.h>

#include "Context.h"
#include "Token.h"

namespace fedora {
    /// Класс для парсинга файла на токены
    class Parser {
    private:
        /// Файловый поток
        std::ifstream& fin;

        AnalyzerStrategy& analyzerStrategy;

        /// Прочитать следующий токен
        Token readToken();

        /// Игнорируем ли мы символ или нет // TODO Вынести в [StaticUtils]
        static bool isIgnored(wchar_t &);
    public:
        Parser(const std::string &, std::ifstream &, AnalyzerStrategy&);

        /// Прочитать весь файл и сохранить токены
        //TODO Читать файл через getLine, чтобы сохранять номера строк для каждого токена. Это поможет выдавать пользователям ошибку с указанием на какой строке они ошиблись
        void readFile();

        // Деструкт
        ~Parser() {
            fin.close();
        }
    };
}
