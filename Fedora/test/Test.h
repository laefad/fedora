//
// Created on 02.08.2021.
//

#ifndef FEDORA_TEST_H
#define FEDORA_TEST_H

#include "Builder/ContextBuilder.h"
#include "Stack/StackHolder.h"
#include "Parser.h"
#include "Utils/TokensHolder.h"

using namespace fedora;

class ContextBuildTester {
public:
    static void test() {
        test1();
        test2();
        test3();
    }

private:
    /**
     * let a = 1
     */
    static void test1() {
        ContextBuilder *builder = ContextBuilder::GetInstance();

        Token mPure = Token(L"pure", -1);
        Token mLet = Token(L"let", -1);
        Token mA = Token(L"a", -1);
        Token mReturn = Token(L"=", -1);
        Token mOne = Token(L"1", -1);

        KeyWord mPure2 = KeyWord(L"pure");
        KeyWord mPure3 = KeyWord(mPure);

        bool a = mPure == mPure2;
        bool b = mPure2 == mPure;
        bool c = mPure2 == mPure2;

        builder->addFunctionDeclarationToken(mPure2);
        builder->notifyWeGotLetToken();
        builder->setFunctionName(mA.getData());
        builder->notifyWeSetReturnable();
        builder->addReturnableNumber(mOne.getData());
        clean();
        Logger::logV("test1 completed");
    }

    static void test2() {
        ContextBuilder *builder = ContextBuilder::GetInstance();

        Token mName = Token(L"main", -1);
        Token mOne = Token(L"1", -1);

        builder->notifyWeStartForceCall();
        builder->setForceName(mName.getData());
        StackHolder *s = StackHolder::GetInstance();
        clean();
        Logger::logV("test2 completed");
    }

    static void test3() {
        Parser parser = Parser();
        TokensHolder tokensHolder = TokensHolder();
        parser.readFile("./../programs/tokensTest.fe", tokensHolder);

        Logger::logV(L"amount of tokens = " + std::to_wstring(tokensHolder.size()));
        for (Token t : tokensHolder.getData())
        {
            Logger::logV(t.getData());
        }
        
        Logger::logV("test3 completed");
    }

    static void clean() {
        fedora::Utils::SingletonsCleaner *cleaner1 = fedora::Utils::SingletonsCleaner::GetInstance();
        cleaner1->cleanThemAll();
    }
};

#endif //FEDORA_TEST_H
