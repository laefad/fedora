#pragma once

#include "Parser/Parser.h"
#include "Parser/ParserUtils.h"
#include "Parser/TokensHolder.h"

#include "Exceptions/ParserException.h"

using namespace fedora;

#define PRINT_DELLINE 1

#ifndef PRINT_DELLINE
#define DELLINE 
    const std::u8string delLine(u8" "); 
#else 
#define DELLINE 
    const std::u8string delLine(u8"\033[F\033[K");
#endif

#define INIT using fedora::parser::TokensHolder; \
        using fedora::parser::Parser; \
        DELLINE
        

#define BEFORE_LOG(header, about) \
Logger::logV(header);\
Logger::logV(about);

#define FAILED_LOG(text) Logger::logV(delLine + delLine + text);

#define SUCCESS_LOG(text) Logger::logV(delLine + delLine + text);

#define PRINT_TOKENS_FROM_TOKENHOLDER(th) \
Logger::logV(u8"Tokens: " + th2u8s(th)); 

#define TEST(test_num, about, _parser, tokens_amount) \
    INIT \
    BEFORE_LOG(u8"Test " + StaticUtils::s2u8s(std::to_string(test_num)), about);\
    Parser parser = _parser;\
    TokensHolder tokensHolder = parser.parse();\
    if (tokensHolder.size() != tokens_amount) {\
        FAILED_LOG(u8"Test " + StaticUtils::s2u8s(std::to_string(test_num)) + u8" failed: got " + \
                StaticUtils::s2u8s(std::to_string(tokensHolder.size())) \
                                + u8" tokens, but expected " \
                                + StaticUtils::s2u8s(std::to_string(tokens_amount)));\
        PRINT_TOKENS_FROM_TOKENHOLDER(tokensHolder);\
    } else\
        SUCCESS_LOG(u8"Test " + StaticUtils::s2u8s(std::to_string(test_num)) + u8" completed")


class ParserTester {
public:

    static void test() {
        Logger::logV(u8"-----TEST PARSER-----");
        test1();
        test2();
        test3();
        test4();
        // test unicode parsing 
        Logger::logV(u8"---END TEST PARSER---");
    }

private:

    static std::u8string th2u8s(parser::TokensHolder const& th) {
        std::u8string buf;

        for (parser::Token t : th) {
            buf += t.getData(); 
            buf += u8", ";
        }
        
        return buf;
    }

    static std::u8string th2u8s(std::vector<fedora::parser::Token> const& th) {
        std::u8string buf;

        for (parser::Token t : th) {
            buf += t.getData(); 
            buf += u8", ";
        }
        
        return buf;
    }

    static void test1() { 
        TEST(1, 
             u8"Testing file parsing...", 
             Parser::makeFileParser(u8"./../programs/tokensTest.fe"),
             28);
    }

    static void test2() { 
        TEST(2, 
            u8"Testing string parsing...", 
            Parser::makeStringParser(u8"let a = 89 let it be where let a = 0 = +(be it a)"),
            19);
    }

    static void test3() {
        try {
            TEST(3, 
                u8"Testing empty file parsing...", 
                Parser::makeFileParser(u8"asdasde.fe"),
                0);
        } catch (ParserException e) {
            SUCCESS_LOG(u8"Test " + StaticUtils::s2u8s(std::to_string(3)) + u8" completed")
        }
    }

    static void test4() {
        INIT

        Logger::logV(u8"Test 4\nTesting tokenolder get line...");

        //linux build file path
        Parser parser = Parser::makeFileParser(u8"./../programs/tokensTest.fe");
        TokensHolder tokensHolder = parser.parse();

        auto lines = tokensHolder.getLines(1, 1);

        if (lines.size() != 6) {
            FAILED_LOG(u8"Test 4 failed: got " + 
                    StaticUtils::s2u8s(std::to_string(lines.size())) + u8" tokens, but expected 6.");

            PRINT_TOKENS_FROM_TOKENHOLDER(lines);
        } else
            SUCCESS_LOG(u8"Test 4 completed");
    }

    // parser = Parser::makeStringParser(L"中 国 a");

    // try {
    //     tokensHolder = parser.parse();
    // } catch (FException e) {
    //     Logger::logE(e.what());
    // }
};
