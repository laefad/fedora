//
// Created on 20.07.2021.
//

#include "Analyzer.h"
#include "StaticUtils.h"
#include <iostream>
#include <Exceptions/AnalyzerException.h>

namespace fedora {
    namespace analytic {
        Analyzer::Analyzer() {
            state = WAITING_FOR_FUNCTION;
        }

        bool Analyzer::analyzeNext(Token &token) {
            bool res = false;
            switch (state) {
                case WAITING_FOR_FUNCTION:
                    res = waitingForFunction(token);
                    break;
                case READING_NAME:
                    res = readName(token);
                    break;
                case READING_ARGS_LIST:
                    res = readArgs(token);
                    break;
                case READING_FUNCTION_BODY:
                    res = readFunBody(token);
                    break;
                case READING_FUNCTION_RESULT:
                    res = readFunRes(token);
                    break;
            }
        }

        bool Analyzer::waitingForFunction(Token &token) {
            bool res = false;

            //throw AnalyzerException(L"Analyzer.h waitingForFunction()data = " + token.data, L"Analyzer.h", L"waitingForFunction");

            // TODO Брать токены не как строки, а откуда-то
            if (token.data == L"pure" || token.data == L"force") {
                tmpTokens.push_back(token);
                res = true;
            }

            if (token.data == L"let") {
                tmpTokens.push_back(token);
                state = READING_NAME;
                res = true;
            }

            if (token.data == L"using") {
                std::cout << "Need to implement using in WaitingForFunction" << std::endl;
            }

            if (token.data == L"import") {
                std::cout << "Need to implement import in WaitingForFunction" << std::endl;
            }

            if (!res) {
                throw FException(L"Analyzer.h waitingForFunction()data = " + token.data +
                                 L"\"\nERROR: Keyword expected, but not found. This rule may be not strict in MACROS++ edition.\n");
            }
            return res;
        }

        bool Analyzer::readName(Token &token) {
            bool error = false;
            for (auto &allKeyWord : allKeyWords) {
                if (token.data == allKeyWord)
                    error = true;
            }
            if (token.data.length() == 1 && fedora::StaticUtils::isDelimiter(token.data.at(0)))
                error = true;
            if (error) {
                std::wstring a = L"Analyzer.h readName\n";
                throw FException(
                        a + L"Expected function name, but got delimiter or keyword:\ntoken.data = \"" + token.data +
                        L"\"");
            }
            if (!error)
                state = READING_ARGS_LIST;
            return !error;
        }

        bool Analyzer::readArgs(Token &token) {
            bool error = false;
            for (auto &allKeyWord : allKeyWords) {
                if (token.data == allKeyWord)
                    error = true;
            }
            if (token.data.length() == 1 && fedora::StaticUtils::isDelimiter(token.data.at(0)))
                error = true;
            // TODO Брать токен откуда-то, а не строкой
            if (token.data == L"where") {
                state = READING_FUNCTION_BODY;
                return true;
            }

            // TODO Брать токен откуда-то, а не строкой. Вынести знак как токен завершения тела фукции
            if (token.data == L"=") {
                state = READING_FUNCTION_RESULT;
                return true;
            }

            if (error) {
                std::wstring a = L"Analyzer.h readArgs\n";
                throw FException(
                        a + L"Expected function argument, but got delimiter or keyword:\ntoken.data = \"" + token.data +
                        L"\"");
            }
            return !error;
        }

        bool Analyzer::readFunBody(Token &) {
            throw FException("readFunBody not implemented");
        }

        bool Analyzer::readFunRes(Token &t) {
            // Здесь у нас 4 пути:
            // 1. Перед нами число
            // 2. Перед нами строка
            // 3. Перед нами список
            // 4. Перед нами FunCall

            bool res = false;
            // Если цифра
            res = checkIfNum(t);
            // Если строка
            if (!res) {
                bool tmp = checkIfString(t);
                if (tmp)
                    res = true;
            }
            // Если список
            if (!res) {
                bool tmp = checkIfList(t);
                if (tmp) {
                    res = true;
                    state = READING_FUNCTION_RESULT_LIST;
                }
            }

            state = READING_FUNCTION_RESULT_FUNCALL;
            return res;
        }

        bool Analyzer::checkIfNum(Token &t) {
            // Проверим, что все символы токена - это цифры
            bool f = true;
            for (auto &chr :t.data) {
                if (!isdigit(chr))
                    f = false;
            }
            return f;
        }

        bool Analyzer::checkIfString(Token &t) {
            return t.data.at(0) == L'\"' && t.data.at(t.data.length() - 1) == L'\"';
        }

        bool Analyzer::checkIfList(Token &t) {
            return t.data.length() == 1 && t.data.at(0) == L'[';
        }
    }
}
