//
// Created on 23.07.2021.
//
#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <iostream>
#include "Token.h"
#include "Utils/SettingsSingleton.h"

namespace fedora {
    namespace analytic {
        /// Базовый класс анализатора токена
        class AnalyticBasic : public std::enable_shared_from_this<AnalyticBasic> {
        private:
            /// Храним токены, которые нужны для обработки текущей ситуации
            std::vector<Token> tokens;

        protected:
            /// Бросить ошибку в случае ошибки синтаксиса
            void throwException(const std::wstring &msg, const std::string &funcName);

            /// Log something as string
            static void log(const std::string& msg, fedora::settings::LogLevel level);

            /// @overload log for wstring
            static void log(const std::wstring& msg, fedora::settings::LogLevel level);
        public:
            explicit AnalyticBasic(std::vector<Token> tokens) : tokens(std::move(tokens)) {};

            /// Проанализировать прочитаный токен
            virtual std::shared_ptr<AnalyticBasic> analyzeToken(Token &) = 0;

            /// Получить текущие токены
            std::vector<Token> &getTokens();

            /// Добавить токен в список прочитаных
            void addToken(const Token &token);

             /// Получить имя файла с кодом. Используется для вывода сообщения об ошибке
             virtual std::string getFileName()=0;
        };
    }
}
