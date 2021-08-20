#ifndef FEDORA_TEST_H
#define FEDORA_TEST_H

#include "Builder/ContextBuilder.h"
#include "Stack/StackHolder.h"
#include "Parser/Parser.h"
#include "Parser/TokensHolder.h"

using namespace fedora;

class ContextBuildTester {
public:
    static void test() {
        //test1();
        test2();
        test3();
    }

private:
    /**
     * let a = 1
     */
    // static void test1() {
    //     ContextBuilder builder = ContextBuilder();

    //     Token mPure = Token(L"pure");
    //     Token mLet = Token(L"let");
    //     Token mA = Token(L"a");
    //     Token mReturn = Token(L"=");
    //     Token mOne = Token(L"1");

    //     KeyWord mPure2 = Token(L"pure");
    //     KeyWord mPure3 = KeyWord(mPure);

    //     bool a = mPure == mPure2;
    //     bool b = mPure2 == mPure;
    //     bool c = mPure2 == mPure2;

    //     builder.addFunctionDeclarationToken(mPure2);
    //     builder.notifyWeGotLetToken();
    //     builder.setFunctionName(mA);
    //     builder.notifyWeSetReturnable();
    //     auto num = mOne.getData();
    //     builder.addReturnableNumber(num);
    //     clean();
    //     Logger::logV("test1 completed");
    // }

    static void test2() {
        using parser::Token;
        ContextBuilder builder = ContextBuilder();

        Token mName = Token(L"main");
        Token mOne = Token(L"1");

        builder.notifyWeStartForceCall();
        auto forceName = mOne.getData();
        builder.setForceName(forceName);
        StackHolder *s = StackHolder::GetInstance();
        clean();
        Logger::logV("test2 completed");
    }

    static void test3() {
        using fedora::parser::TokensHolder;
        using fedora::parser::Parser;
        
        Parser parser = Parser::make(Parser::Type::File, L"./../programs/tokensTest.fe");
        TokensHolder tokensHolder = parser.parse();

        if (tokensHolder.size() != 29)
            Logger::logV("test 3.1 failed");
        else
            Logger::logV("test 3.1 completed");

        parser = Parser::make(Parser::Type::File, L"asdasde.fe");
        tokensHolder = parser.parse();

        if (tokensHolder.size() != 0)
            Logger::logV("test 3.2 failed");
        else
            Logger::logV("test 3.2 completed");

        parser = Parser::make(Parser::Type::String, L"let a = 89 let it be where let a = 0 = +(be it a)");
        tokensHolder = parser.parse();

        if (tokensHolder.size() != 20)
            Logger::logV("test 3.3 failed");
        else
            Logger::logV("test 3.3 completed");

        // Logger::logV(L"amount of tokens = " + std::to_wstring(tokensHolder.size()));
        // for (parser::Token t : tokensHolder.getData())
        // {
        //     Logger::logV(t.getData());
        // }
    }

    static void clean() {
        fedora::Utils::SingletonsCleaner *cleaner1 = fedora::Utils::SingletonsCleaner::GetInstance();
        cleaner1->cleanThemAll();
    }
};

#endif //FEDORA_TEST_H
