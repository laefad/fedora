//
// Created on 20.07.2021.
//

#include "Analyzer.h"
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

    bool Analyzer::readName(Token &) {
        return false;
    }
}
