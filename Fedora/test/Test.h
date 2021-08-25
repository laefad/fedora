#ifndef FEDORA_TEST_H
#define FEDORA_TEST_H

#include "Builder/ContextBuilder.h"
#include "Stack/StackHolder.h"
#include "Parser/Parser.h"
#include "Parser/TokensHolder.h"
#include "Types/List.h"

using namespace fedora;

class ContextBuildTester {
public:
    static void test() {
        //test1();
        test2();
        //test3();
        test4();
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

    static void test4(){
        std::shared_ptr<types::List> a = std::make_shared<types::List>(std::make_shared<types::Number>());
        types::List b = types::List::addNewItemToTheBeginning(std::make_shared<types::Number>(2.0), a);
        b = types::List::addNewItemToTheBeginning(std::make_shared<types::Number>(2.0), std::make_shared<types::List>(b));
        types::List c = types::List::addNewItemToTheEnd(std::make_shared<types::Number>(3.0), std::make_shared<types::List>(b));
        // TODO Я проверял работу через дебаггер, но хорошо бы сделать тест кодом
        Logger::logV("test 4 completed");
    }

    static void clean() {
        fedora::Utils::SingletonsCleaner *cleaner1 = fedora::Utils::SingletonsCleaner::GetInstance();
        cleaner1->cleanThemAll();
    }
};

#endif //FEDORA_TEST_H
