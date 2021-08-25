#pragma once

#include "Stack/StackHolder.h"
#include "Parser/Parser.h"
#include "Parser/ParserUtils.h"
#include "Parser/TokensHolder.h"

using namespace fedora;

class ParserTester {
public:

    static void test() {
        Logger::logV(L"-----TEST PARSER-----");
        test1();
        test2();
        test3();
        test4();
        // test unicode parsing 
        Logger::logV(L"---END TEST PARSER---");
    }

private:

    // TODO а может макрос ?
    // Без вычисления bool ПОСЛЕ вывода header и about не имеет смысла
    // static void patternOutput(
    //     std::wstring header, 
    //     std::wstring about, 
    //     bool result,
    //     size_t linesToDelete, 
    //     std::wstring sucess, 
    //     std::wstring fail
    // ) {
        
    // }

    static void test1() { 
        using fedora::parser::TokensHolder;
        using fedora::parser::Parser;
        const std::wstring delLine(L"\033[F\033[K");

        Logger::logV(L"Test 1\nTesting file parsing...");

        //linux build file path
        Parser parser = Parser::makeFileParser(L"./../programs/tokensTest.fe");
        TokensHolder tokensHolder = parser.parse();

        if (tokensHolder.size() != 29) {
            Logger::logV(delLine + delLine + L"Test 1 failed: got " + 
                    std::to_wstring(tokensHolder.size()) + L" tokens, but expected 29.");

            std::wstring temp;

            for (parser::Token t : tokensHolder.getData())
                temp += t.getData() + L", ";

            Logger::logV(std::wstring(L"Tokens: ") + temp);
            
        } else
            Logger::logV(delLine + delLine + L"Test 1 completed");
    }

    static void test2() { 
        using fedora::parser::TokensHolder;
        using fedora::parser::Parser;
        const std::wstring delLine(L"\033[F\033[K");

        Logger::logV(L"Test 2\nTesting string parsing...");

        Parser parser = Parser::makeStringParser(L"let a = 89 let it be where let a = 0 = +(be it a)");
        TokensHolder tokensHolder = parser.parse();

        if (tokensHolder.size() != 20) {
            Logger::logV(delLine + delLine + L"Test 2 failed: got " + 
                    std::to_wstring(tokensHolder.size()) + L" tokens, but expected 20.");

            std::wstring temp;

            for (parser::Token t : tokensHolder.getData())
                temp += t.getData() + L", ";

            Logger::logV(std::wstring(L"Tokens: ") + temp);
        } else
            Logger::logV(delLine + delLine + L"Test 2 completed");
    }

    static void test3() {
        using fedora::parser::TokensHolder;
        using fedora::parser::Parser;
        const std::wstring delLine(L"\033[F\033[K");

        Logger::logV(L"Test 3\nTesting empty file parsing...");

        Parser parser = Parser::makeFileParser(L"asdasde.fe");
        TokensHolder tokensHolder = parser.parse();

        if (tokensHolder.size() != 0)
            Logger::logV(delLine + delLine + L"Test 3 failed, file exist or parser totally broken");
        else
            Logger::logV(delLine + delLine + L"Test 3 completed");
    }

    static void test4() {
        using fedora::parser::TokensHolder;
        using fedora::parser::Parser;
        const std::wstring delLine(L"\033[F\033[K");

        Logger::logV(L"Test 4\nTesting tokenolder get line...");

        //linux build file path
        Parser parser = Parser::makeFileParser(L"./../programs/tokensTest.fe");
        TokensHolder tokensHolder = parser.parse();

        auto lines = tokensHolder.getLines(1, 1);

        if (lines.size() != 6) {
            Logger::logV(delLine + delLine + L"Test 4 failed: got " + 
                    std::to_wstring(lines.size()) + L" tokens, but expected 6.");

            std::wstring temp;

            for (parser::Token t : lines)
                temp += t.getData() + L", ";

            Logger::logV(std::wstring(L"Tokens: ") + temp);
        } else
            Logger::logV(delLine + delLine + L"Test 4 completed");
    }

    // parser = Parser::makeStringParser(L"中 国 a");

    // try {
    //     tokensHolder = parser.parse();
    // } catch (FException e) {
    //     Logger::logE(e.what());
    // }
};
