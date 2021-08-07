//
// Created on 02.08.2021.
//

#ifndef FEDORA_TEST_H
#define FEDORA_TEST_H

#include <Builder/ContextBuilder.h>
#include "Stack/StackHolder.h"

using namespace fedora;

class ContextBuildTester {
public:
    static void test() {
        test1();
        test2();
    }

private:
    /**
     * let a = 1
     */
    static void test1() {
        Logger::logV("test1 started");
        ContextBuilder *builder = ContextBuilder::GetInstance();

        Token mPure = Token(L"pure");
        Token mLet = Token(L"let");
        Token mA = Token(L"a");
        Token mReturn = Token(L"=");
        Token mOne = Token(L"1");

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

        Token mName = Token(L"main");
        Token mOne = Token(L"1");

        builder->notifyWeStartForceCall();
        builder->setForceName(mName.getData());
        StackHolder *s = StackHolder::GetInstance();
        clean();
    }

    static void clean() {
        fedora::Utils::SingletonsCleaner *cleaner1 = fedora::Utils::SingletonsCleaner::GetInstance();
        cleaner1->cleanThemAll();
    }
};

#endif //FEDORA_TEST_H
