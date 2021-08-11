//
// Created on 23.07.2021.
//

#include <Analyzers/ReadName.h>
#include <Exceptions/AnalyzerException.h>
#include <KeyWords.h>
#include <Analyzers/ReadResult.h>
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {
        /**
         *
         * @param t - token we get
         * @param b - reference to context builder
         * @return next analyzer
         *
         * @example case 1: pure keyword
         * pure let a = 1
         * # we need to init new function and send "pure" keyword to context#
         *
         * @example case 2: force keyword
         * let a = null
         * force a
         * # we use this function to build package-level forceCall #
         *
         * @example case 3:
         * let a where
         *   let b = null
         *   # after function b finished, this function will read "=" token #
         *   # because after function there have to be declaration of another or the result of higher-level function #
         * = null
         *
         * @example where we DO NOT use this function
         * let a = null
         * let b = force a
         * # in this case, result resolver [ReadResult] will get the "force" token #
         */
        std::shared_ptr<AnalyticBasic> ReadKeyWord::analyzeToken(Token &t, ContextBuilder &b) {
            log("Class: " + getFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);


            // if we got an "equals"
            if (t == returns) {
                return std::make_shared<ReadResult>();
            }

            if (AnalyticUtils::isTokenAPreFunKeyWord(t.getData())) {
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
                    if (b.isCurrentFunctionForced()) {
//                        std::vector<Token> tokens = std::vector<Token>();
//                        tokens.push_back(t);
                        return std::make_shared<ReadName>();
                    } else {
                        throwException(L"Do not declare the keyword FORCE with the others", "analyzeToken(Token &");
                    }
                } else {
                    // Продолжаем считывать
                    return shared_from_this();
                }
            } else {
                // Получено let
                if (t == let) {
                    // Передаём все наши накопленные данные в [ReadName]
                    return std::make_shared<ReadName>();
                } else
                    throwException(L"Expected a pre-function key word, but got token = " + t.getData(),
                                   "analyzeToken(Token &)");
            }
        }

        std::string ReadKeyWord::getFileName() {
            return "ReadKeyWord.h";
        }
    }
}
