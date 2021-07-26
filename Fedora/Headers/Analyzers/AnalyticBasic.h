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
            std::vector<Token> tokensFromPreviousStep;
        public:
            explicit AnalyticBasic(std::vector<Token>);

            virtual std::shared_ptr<AnalyticBasic> analyzeToken(Token&)=0;
            virtual void throwException(const std::wstring& msg, const std::string& funcName)=0;

            std::vector<Token>& getTokens();
        };
        // ? TODO Вынести реализацию в cpp файл??
        std::vector<Token> &AnalyticBasic::getTokens() {
            return tokensFromPreviousStep;
        }

        AnalyticBasic::AnalyticBasic(std::vector<Token> tokens) :tokensFromPreviousStep(std::move(tokens)){}
    }
}
