//
// Created on 23.07.2021.
//

#include <Analyzers/ReadName.h>
#include <Exceptions/AnalyzerException.h>
#include <KeyWords.h>
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {
        std::shared_ptr<AnalyticBasic> ReadKeyWord::analyzeToken(Token &t) {
            addToken(t); // Запомнить считаный токен

            if (AnalyticUtils::isTokenAPreFunKeyWord(t.data)) {
                // 2 пути:
                // 1. Получено Force и мы должны считать имя функции, аргументы и перейти к выполнению
                // 2. Получено Pure или другое ключевое слово и мы должны считывать ключевые слова дальше

                // Получено force
                if (t == force) {
                    // 2 пути:
                    // 1. Других ключевых слов нет (верный синтаксис) ((getTokens() пустой))
                    // 2. Объявлены другие ключевые слова. Можно их игнорировать и скомпилить без них,
                    //    а можно выдать ошибку. В данном случае будем выдавать ошибку
                    // TODO Мб продолжать компилить не смотря на избыточность синтаксиса и просто выводить WARNING в консоль?
                    if (getTokens().empty()) {
                        std::vector<Token> tokens = std::vector<Token>();
                        tokens.push_back(t);
                        return std::make_shared<ReadName>(tokens);
                    } else {
                        throwException(L"Do not declare the keyword FORCE with the others", "analyzeToken(Token &");
                    }
                } else {
                    // Продолжаем считывать
                    return shared_from_this();
                    return std::make_shared<ReadKeyWord>(getTokens());
                }
            } else {
                // Получено let
                if (t == let) {
                    // Передаём все наши накопленные данные в [ReadName]
                    return std::make_shared<ReadName>(getTokens());
                } else
                    throwException(L"Expected a pre-function key word, but got token = " + t.data,
                                   "analyzeToken(Token &)");
            }
        }

        void ReadKeyWord::throwException(const std::wstring &msg, const std::string &funcName) {
            throw AnalyzerException(msg, "ReadKeyWord.h", funcName);
        }
    }
}
