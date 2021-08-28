#pragma once

#include <sstream>

#include "Stack/StackHolder.h"
#include "Parser/Parser.h"
#include "Parser/ParserUtils.h"
#include "Parser/TokensHolder.h"

using namespace fedora;

#define INIT using fedora::parser::TokensHolder; \
        using fedora::parser::Parser; \
        const std::wstring delLine(L"\033[F\033[K");

#define BEFORE_LOG(header, about) \
Logger::logV(header);\
Logger::logV(about);

#define FAILED_LOG(text) Logger::logV(delLine + delLine + text);

#define SUCCESS_LOG(text) Logger::logV(delLine + delLine + text);

#define PRINT_TOKENS_FROM_TOKENHOLDER(th) \
Logger::logV(L"Tokens: " + th2wstr(th)); 

#define TEST(test_num, about, _parser, tokens_amount) \
    INIT \
    BEFORE_LOG(L"Test " + std::to_wstring(test_num), about);\
    Parser parser = _parser;\
    TokensHolder tokensHolder = parser.parse();\
    if (tokensHolder.size() != tokens_amount) {\
        FAILED_LOG(L"Test " + std::to_wstring(test_num) + L" failed: got " + \
                std::to_wstring(tokensHolder.size()) \
                                + L" tokens, but expected " \
                                + std::to_wstring(tokens_amount));\
        PRINT_TOKENS_FROM_TOKENHOLDER(tokensHolder);\
    } else\
        SUCCESS_LOG(L"Test " + std::to_wstring(test_num) + L" completed")


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

    static std::wstring th2wstr(parser::TokensHolder const& th) {
        std::wstringstream buf;

        for (parser::Token t : th)
            buf << t.getData() << L", ";
        
        return buf.str();
    }

    static std::wstring th2wstr(std::vector<fedora::parser::Token> const& th) {
        std::wstringstream buf;

        for (parser::Token t : th)
            buf << t.getData() << L", ";
        
        return buf.str();
    }

    static void test1() { 
        TEST(1, 
             L"Testing file parsing...", 
             Parser::makeFileParser(L"./../programs/tokensTest.fe"),
             29);
    }

    static void test2() { 
        TEST(2, 
             L"Testing string parsing...", 
             Parser::makeStringParser(L"let a = 89 let it be where let a = 0 = +(be it a)"),
             20);
    }

    static void test3() {
        TEST(3, 
             L"Testing empty file parsing...", 
             Parser::makeFileParser(L"asdasde.fe"),
             0);
    }

    static void test4() {
        INIT

        Logger::logV(L"Test 4\nTesting tokenolder get line...");

        //linux build file path
        Parser parser = Parser::makeFileParser(L"./../programs/tokensTest.fe");
        TokensHolder tokensHolder = parser.parse();

        auto lines = tokensHolder.getLines(1, 1);

        if (lines.size() != 6) {
            FAILED_LOG(L"Test 4 failed: got " + 
                    std::to_wstring(lines.size()) + L" tokens, but expected 6.");

            PRINT_TOKENS_FROM_TOKENHOLDER(lines);
        } else
            SUCCESS_LOG(L"Test 4 completed");
    }

    // parser = Parser::makeStringParser(L"中 国 a");

    // try {
    //     tokensHolder = parser.parse();
    // } catch (FException e) {
    //     Logger::logE(e.what());
    // }
};
