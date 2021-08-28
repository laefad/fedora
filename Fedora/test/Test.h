#ifndef FEDORA_TEST_H
#define FEDORA_TEST_H

#include "Builder/ContextBuilder.h"
#include "Stack/StackHolder.h"
#include "Parser/Parser.h"
#include "Parser/TokensHolder.h"
#include "Types/List.h"
#include "Parser/Token.h"

using namespace fedora;

class ContextBuildTester {
public:
    static void test() {
        //test1();
        test2();
        //test3();
        test4();
        test5();
        test6();
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

    static void test4() {
        std::shared_ptr<types::List> a = std::make_shared<types::List>(std::make_shared<types::Number>(0.0));
        types::List b = types::List::addNewItemToTheBeginning(std::make_shared<types::Number>(2.0), a);
        b = types::List::addNewItemToTheBeginning(std::make_shared<types::Number>(2.0),
                                                  std::make_shared<types::List>(b));
        types::List c = types::List::addNewItemToTheEnd(std::make_shared<types::Number>(3.0),
                                                        std::make_shared<types::List>(b));
        // TODO Я проверял работу через дебаггер, но хорошо бы сделать тест кодом
        Logger::logV("test 4 completed");
    }

    static void test5() {
        clean();
        Settings *setting = Settings::GetInstance();
        setting->setLogLevel(settings::LogLevel::LOG_WARNING);

        parser::Token mLet = parser::Token(L"let");
        mLet.setType(parser::TokenType::FunctionDeclaration);

        parser::Token mA = parser::Token(L"a");
        mA.setType(parser::TokenType::Name);

        parser::Token mB = parser::Token(L"b");
        mB.setType(parser::TokenType::Name);

        parser::Token mReturns = parser::Token(L"=");
        mReturns.setType(parser::TokenType::FunctionReturnableDeclaration);

        parser::Token mOne = parser::Token(L"1");
        mOne.setType(parser::TokenType::Number);


        fedora::ContextBuilder builder = fedora::ContextBuilder();
        fedora::AnalyzerStrategy analyzer = fedora::AnalyzerStrategy(builder);

        analyzer.analyzeNext(mLet);
        analyzer.analyzeNext(mA);
        analyzer.analyzeNext(mReturns);
        analyzer.analyzeNext(mOne);

        analyzer.analyzeNext(mLet);
        analyzer.analyzeNext(mB);
        analyzer.analyzeNext(mReturns);
        analyzer.analyzeNext(mOne);

        if (builder.getPackage()->getContext()->count(mA.getData()) == 1 &&
            builder.getPackage()->getContext()->count(mB.getData()) == 1)
            Logger::logW("test 5 completed");
        else
            Logger::logW("test 5 FAILED");
        clean();
    }

    static void test6() {
        using fedora::types::BasicType;
        using fedora::types::List;
        using fedora::types::Number;

        bool success = true;

        std::shared_ptr<BasicType> num = std::make_shared<Number>(1.0);

        std::shared_ptr<List> lst = std::make_shared<List>(num);

        //Logger::logV(lst->eval());
        success = (lst->eval()) == L"[1.000000]";

        std::shared_ptr<BasicType> num2 = std::make_shared<Number>(32.0);

        List lst2 = List::addNewItemToTheBeginning(num2, lst);

        //Logger::logV(lst2.eval());
        success = (lst2.eval()) == L"[32.000000 1.000000]";

        List lst3;

        //Logger::logV(lst3.eval());
        success = (lst3.eval()) == L"[]";

        if (success)
            Logger::logV("test 6 completed");
        else
            Logger::logV("test 6 failed");

        // try {
        //     throw exception::BuilderException(L"text", L"test()");
        // } catch (exception::BuilderException e) {
        //     e.what();
        // }

        //throw exception::BuilderException(L"text", L"test()");
    }

    static void clean() {
        fedora::Utils::SingletonsCleaner *cleaner1 = fedora::Utils::SingletonsCleaner::GetInstance();
        cleaner1->cleanThemAll();
    }
};



#endif //FEDORA_TEST_H
