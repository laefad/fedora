//
// Created on 20.07.2021.
//

#include "Analyzer.h"
#include "StaticUtils.h"
#include <iostream>

namespace fedora {
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
                break;
            case READING_FUNCTION_RESULT:
                break;
        }
    }

    bool Analyzer::waitingForFunction(Token &token) {
        bool res = false;

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

    bool Analyzer::readName(Token & token) {
        bool error = false;
        for (size_t i=0;i<allKeyWords.size();++i){
            if (token.data == allKeyWords.at(i))
                error = true;
        }
        if (token.data.length() == 1 && fedora::StaticUtils::isDelimiter(token.data.at(0)))
            error = true;
        if (error) {
            std::wstring a = L"Analyzer.h readName\n";
            throw FException(a+L"Expected function name, but got delimiter or keyword:\ntoken.data = \"" + token.data + L"\"");
        }
        if (!error)
            state = READING_ARGS_LIST;
        return !error;
    }

    bool Analyzer::readArgs(Token & token) {
        bool error = false;
        for (size_t i=0;i<allKeyWords.size();++i){
            if (token.data == allKeyWords.at(i))
                error = true;
        }
        if (token.data.length() == 1 && fedora::StaticUtils::isDelimiter(token.data.at(0)))
            error = true;
        // TODO Брать токен откуда-то, а не строкой
        if (token.data == L"where"){
            state = READING_FUNCTION_BODY;
            return true;
        }

        if (token.data == L"="){
            state = READING_FUNCTION_RESULT;
            return true;
        }

        if (error) {
            std::wstring a = L"Analyzer.h readArgs\n";
            throw FException(a+L"Expected function argument, but got delimiter or keyword:\ntoken.data = \"" + token.data + L"\"");
        }
        return !error;
    }

    bool Analyzer::readFunBody(Token &) {
        throw FException("readFunBody not implemented");
    }

    bool Analyzer::readFunRes(Token &) {
        return false;
    }
}
