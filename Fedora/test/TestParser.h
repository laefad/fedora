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
        test0();
        test1();
        test2();
        test3();
        test4();
        test5();
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

    static void test0() {
        if (parser::ParserUtils::isIgnored(u8" "))
            Logger::logV(u8"test 0.1 complete");
        else 
            Logger::logV(u8"test 0.1 failed");

        if (parser::ParserUtils::isIgnored(u8"\n"))
            Logger::logV(u8"test 0.2 complete");
        else 
            Logger::logV(u8"test 0.2 failed");

        if (parser::ParserUtils::isIgnored(u8"\r"))
            Logger::logV(u8"test 0.3 complete");
        else 
            Logger::logV(u8"test 0.3 failed");
        
        if (parser::ParserUtils::isIgnored(u8"\t"))
            Logger::logV(u8"test 0.4 complete");
        else 
            Logger::logV(u8"test 0.4 failed");
    }

    static void test1() {
        using parser::ParserUtils;

        char8_t ch1 = u8'\x7f';
        char8_t ch2 = u8'\xdf';
        char8_t ch3 = u8'\xef';
        char8_t ch4 = u8'\xf7';

        if (ParserUtils::amountOfBytesInCharsSequence(ch1) == 1)
            Logger::logV(u8"Test 1.1 completed");
        else 
             Logger::logV(u8"Test 1.1 failed");

        if (ParserUtils::amountOfBytesInCharsSequence(ch2) == 2)
            Logger::logV(u8"Test 1.2 completed");
        else 
             Logger::logV(u8"Test 1.2 failed");

        if (ParserUtils::amountOfBytesInCharsSequence(ch3) == 3)
            Logger::logV(u8"Test 1.3 completed");
        else 
             Logger::logV(u8"Test 1.3 failed");

        if (ParserUtils::amountOfBytesInCharsSequence(ch4) == 4)
            Logger::logV(u8"Test 1.4 completed");
        else 
            Logger::logV(u8"Test 1.4 failed");
    }

    static void test2() { 
        #if defined(__linux__) || defined(__APPLE__)
        TEST(2, 
             u8"Testing file parsing...", 
             Parser::makeFileParser(u8"./../programs/tokensTest.fe"),
             28);
        # elif defined(_WIN32) 
        TEST(2, 
             u8"Testing file parsing...", 
             Parser::makeFileParser(u8"./../../programs/tokensTest.fe"),
             28);
        # endif
    }

    static void test3() { 
        TEST(3, 
            u8"Testing string parsing...", 
            Parser::makeStringParser(u8"let a = 89 let it be where let a = 0 = +(be it a)"),
            19);
    }

    static void test4() {

        try {
            TEST(4, 
                u8"Testing empty file parsing...", 
                Parser::makeFileParser(u8"asdasde.fe"),
                0);
        } catch (ParserException e) {
            SUCCESS_LOG(u8"Test " + StaticUtils::s2u8s(std::to_string(3)) + u8" completed")
        }
    }

    static void test5() {
        INIT

        Logger::logV(u8"Test 5\nTesting tokenolder get line...");

        //linux build file path
        #if defined(__linux__) || defined(__APPLE__)
        Parser parser = Parser::makeFileParser(u8"./../programs/tokensTest.fe");
        # elif defined(_WIN32)
        Parser parser = Parser::makeFileParser(u8"./../../programs/tokensTest.fe");
        # endif
        TokensHolder tokensHolder = parser.parse();

        auto lines = tokensHolder.getLines(1, 1);

        if (lines.size() != 6) {
            FAILED_LOG(u8"Test 5 failed: got " + 
                    StaticUtils::s2u8s(std::to_string(lines.size())) + u8" tokens, but expected 6.");

            PRINT_TOKENS_FROM_TOKENHOLDER(lines);
        } else
            SUCCESS_LOG(u8"Test 5 completed");
    }

    // parser = Parser::makeStringParser(L"中 国 a");

    // try {
    //     tokensHolder = parser.parse();
    // } catch (FException e) {
    //     Logger::logE(e.what());
    // }
};
