#pragma once

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include "Context.h"

namespace fedora {
    /// Токен, который мы прочитали и будем анализировать
    /// В классе можно сохранять контекст распрашеного токена для анализа
    class Token{
    public:
        Token(std::wstring& data);
        std::wstring data;
        bool isEmpty=false;
    };

    /// Класс для парсинга файла на токены
    class Parser {
    private:
        /// Файловый поток
        std::ifstream& fin;

        /// Прочитать следующий токен
        Token readToken();

        /// Распознать токен
        void analyzeToken(Token&);

        /// Игнорируем ли мы символ или нет
        static bool isIgnored(wchar_t &);

        /// Является ли символ разделителем между докенами
        static bool isDelimiter(wchar_t &);
    public:
        Parser(const std::string &fileName, std::ifstream &fin);

        /// Прочитать весь файл и сохранить токены
        void readFile();

        // Деструкт
        ~Parser() {
            fin.close();
        }
    };



//    /// результат чтения
//    typedef std::pair<Token, bool> tokenReadResult;
}
