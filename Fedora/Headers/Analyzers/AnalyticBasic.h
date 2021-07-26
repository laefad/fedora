//
// Created on 23.07.2021.
//
#pragma once

#include <memory>
#include <utility>
#include <vector>
#include "Token.h"

namespace fedora{
    namespace analytic {
        /// Базовый класс анализатора токена
        class AnalyticBasic {
        private:
            std::vector<Token> tokens;
        public:
            explicit AnalyticBasic(std::vector<Token> tokens): tokens(std::move(tokens)){};

            virtual std::shared_ptr<AnalyticBasic> analyzeToken(Token&)=0;
            virtual void throwException(const std::wstring& msg, const std::string& funcName)=0;

            // TODO Вынести все функции в cpp файл
            std::vector<Token>& getTokens(){
                return tokens;
            }

            void addToken(const Token& token){
                tokens.push_back(token);
            }
        };
    }
}
