#ifndef FEDORA_TEST_H
#define FEDORA_TEST_H

#include "Builder/ContextBuilder.h"
#include "Stack/StackHolder.h"
#include "Parser/Utf8istream.h"
#include "Parser/Parser.h"
#include "Parser/ParserUtils.h"
#include "Parser/TokensHolder.h"
#include "Types/List.h"
#include "Parser/Token.h"

#include <bitset>

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
        test7();
        test8();
        test9();
        test10();
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

        Token mName = Token(u8"main");
        Token mOne = Token(u8"1");

        builder.notifyWeStartForceCall();
        auto forceName = mOne.getData();
        builder.setForceName(forceName);
        //StackHolder *s = StackHolder::GetInstance();
        clean();
        Logger::logV(u8"test 2 completed");
    }

    static void test4() {
        std::shared_ptr<types::List> a = std::make_shared<types::List>(std::make_shared<types::Number>(0.0));
        auto b = types::List::addNewItemToTheBeginning(std::make_shared<types::Number>(2.0), a);
        b = types::List::addNewItemToTheBeginning(std::make_shared<types::Number>(2.0), b);
        auto c = types::List::addNewItemToTheEnd(std::make_shared<types::Number>(3.0), b);
        // TODO Я проверял работу через дебаггер, но хорошо бы сделать тест кодом
        Logger::logV(u8"test 4 completed");
    }

    static void test5() {
        clean();
        Settings *setting = Settings::GetInstance();
        setting->setLogLevel(settings::LogLevel::LOG_WARNING);

        parser::Token mLet = parser::Token(u8"let");
        mLet.setType(parser::TokenType::FunctionDeclaration);

        parser::Token mA = parser::Token(u8"a");
        mA.setType(parser::TokenType::Name);

        parser::Token mB = parser::Token(u8"b");
        mB.setType(parser::TokenType::Name);

        parser::Token mReturns = parser::Token(u8"=");
        mReturns.setType(parser::TokenType::FunctionReturnableDeclaration);

        parser::Token mOne = parser::Token(u8"1");
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
            Logger::logW(u8"test 5 completed");
        else
            Logger::logW(u8"test 5 FAILED");
        clean();
    }

    static void test6() {
        using fedora::types::BasicType;
        using fedora::types::List;
        using fedora::types::Number;

        bool success = true;

        std::shared_ptr<BasicType> num = std::make_shared<Number>(1.0);

        std::shared_ptr<List> lst = std::make_shared<List>(num);

        // Logger::logV(lst->eval());
        if (lst->eval() != u8"[1.000000]"){
            success = false;
            Logger::logV(u8"Failed 6.1");
            Logger::logV(lst->eval());
        }

        std::shared_ptr<BasicType> num2 = std::make_shared<Number>(32.0);

        auto lst2 = List::addNewItemToTheBeginning(num2, lst);

        // Logger::logV(lst2.eval());
        if (lst2->eval() != u8"[32.000000 1.000000]"){
            success = false;
            Logger::logV(u8"Failed 6.2");
            Logger::logV(lst2->eval());
        }

        auto lst25 = List::addNewItemToTheEnd(num2, lst2);

        // Logger::logV(lst25.eval());
        if (lst25->eval() != u8"[32.000000 1.000000 32.000000]"){
            success = false;
            Logger::logV(u8"Failed 6.3");
            Logger::logV(lst25->eval());
        }

        List lst3;

        //Logger::logV(lst3.eval());
        if (lst3.eval() != u8"[]"){
            success = false;
            Logger::logV(u8"Failed 6.4");
            Logger::logV(lst3.eval());
        }

        if (success)
            Logger::logV(u8"test 6 completed");
        else
            Logger::logV(u8"test 6 failed");

        // try {
        //     throw exception::BuilderException(L"text", L"test()");
        // } catch (exception::BuilderException e) {
        //     e.what();
        // }

        //throw exception::BuilderException(L"text", L"test()");
    }

    static void test7() {
        clean();
        Settings *setting = Settings::GetInstance();
        setting->setLogLevel(settings::LogLevel::LOG_WARNING);

        parser::Token mLet = parser::Token(u8"let");
        mLet.setType(parser::TokenType::FunctionDeclaration);

        parser::Token mA = parser::Token(u8"a");
        mA.setType(parser::TokenType::Name);

        parser::Token mWhere = parser::Token(u8"where");
        mWhere.setType(parser::TokenType::FunctionContextDeclaration);

        parser::Token mB = parser::Token(u8"b");
        mB.setType(parser::TokenType::Name);

        parser::Token mReturns = parser::Token(u8"=");
        mReturns.setType(parser::TokenType::FunctionReturnableDeclaration);

        parser::Token mOne = parser::Token(u8"1");
        mOne.setType(parser::TokenType::Number);


        fedora::ContextBuilder builder = fedora::ContextBuilder();
        fedora::AnalyzerStrategy analyzer = fedora::AnalyzerStrategy(builder);

        analyzer.analyzeNext(mLet);
        analyzer.analyzeNext(mA);
        analyzer.analyzeNext(mWhere);

        analyzer.analyzeNext(mLet);
        analyzer.analyzeNext(mB);
        analyzer.analyzeNext(mReturns);
        analyzer.analyzeNext(mOne);

        analyzer.analyzeNext(mReturns);
        analyzer.analyzeNext(mOne);


        if (builder.getPackage()->getContext()->count(mA.getData()) == 1 &&
            (*(builder.getPackage()->getContext()))[mA.getData()]->getContext()->count(mB.getData()) == 1)
            Logger::logW(u8"test 7 completed");
        else
            Logger::logW(u8"test 7 FAILED");

        clean();
    }

    static void test8() {
        using fedora::parser::Parser;
        using fedora::parser::Utf8istream;
        using fedora::parser::TokensHolder;

        // тест реальной программы
        Settings *setting = Settings::GetInstance();
        setting->setLogLevel(settings::LogLevel::LOG_WARNING);

#if defined(__linux__) || defined(__APPLE__)
        auto source = Utf8istream::fromFile(u8"./../programs/current_features.fe");
# elif defined(_WIN32)
        auto source = Utf8istream::fromFile(u8"./../../programs/current_features.fe");
# endif
        Parser parser = Parser(std::move(source));
        TokensHolder tokensHolder = parser.parse();
        fedora::ContextBuilder builder = fedora::ContextBuilder();
        fedora::AnalyzerStrategy analyzer = fedora::AnalyzerStrategy(builder);
        for (auto it = tokensHolder.begin(); it < tokensHolder.end(); ++it) {
            analyzer.analyzeNext(*it);
        }

        setting->setLogLevel(settings::LogLevel::LOG_VERBOSE);
    
        if (builder.getPackage()->getContext()->at(u8"a") != nullptr){
            std::shared_ptr<fedora::context::Function> & list = builder.getPackage()->getContext()->at(u8"a");

            using fef = fedora::context::FeFunction;
            auto fe = dynamic_cast<fef *>(list.get());
            if (fe->logRet() == u8"[1.000000 2.000000 \"🤡\"]")
                Logger::logV(u8"test 8 completed");
            else
                Logger::logV(u8"test 8 failed");
        }else{
            Logger::logV(u8"test 8 failed");
        }

        clean();
    }

    //! Не удалять эту функцию!
    static void logAllContext(std::shared_ptr<fedora::context::Function::Context> context, size_t level = 0) {
        using fef = fedora::context::FeFunction;
        using fefptr = std::shared_ptr<fef>;

//        auto fefunction = dynamic_cast<fef *>(context->at(u8"a").get());
//        if (fefunction->getReturnable()->getData()->type() == fedora::types::LIST){
//            auto actualList = static_cast<types::List>(fefunction->getReturnable()->getData());
//
//            Logger::logV(actualList.eval());
//        }

        for (auto [name, f] : *context) {
            auto fe = dynamic_cast<fef *>(f.get());

            std::u8string res = u8"";
            for (auto i = 0; i < level; ++i, res += u8"\t");
            res += u8"[";
            res += name;
            res += u8"] => ";
            res += fe->logRet();

            Logger::logV(res);
            logAllContext(fe->getContext(), level + 1);
        }
    }

    static void test9() {
        Logger::logV(u8"😀");
        // std::cout << ContextBuildTester::getstrbits<char8_t>(std::u8string(u8"¢")) << std::endl;
        // std::cout << ContextBuildTester::getstrbits(std::string("¢")) << std::endl;
        // std::cout << std::hex << (int)u8'ö' << std::endl;
        // std::cout << std::hex << (int)'ö' << std::endl;

        std::u8string data = u8"biba";
        std::string result = StaticUtils::u8s2s(data);

        if (getstrbits<char8_t>(data) == getstrbits<char>(result))
            Logger::logV(u8"Test 9.1 completed");
        else 
            Logger::logV(u8"Test 9.1 failed");

        data = u8"öʧधᐇ";
        result = StaticUtils::u8s2s(data);

        if (getstrbits<char8_t>(data) == getstrbits<char>(result))
            Logger::logV(u8"Test 9.2 completed");
        else 
             Logger::logV(u8"Test 9.2 failed");


        std::string data2 = "biba";
        std::u8string result2 = StaticUtils::s2u8s(data2);

        if (getstrbits<char>(data2) == getstrbits<char8_t>(result2))
            Logger::logV(u8"Test 9.3 completed");
        else 
             Logger::logV(u8"Test 9.3 failed");

        data2 = "öʧधᐇ";
        result2 = StaticUtils::s2u8s(data2);

        if (getstrbits<char>(data2) == getstrbits<char8_t>(result2))
            Logger::logV(u8"Test 9.4 completed");
        else 
            Logger::logV(u8"Test 9.4 failed");

    }

    static void test10() {
        Logger::logV(u8"------Error handling test----");
        try {
            throw BuilderException(
                        u8"You're trying to convert token to BasicType, but token is not a primitive type instance.",
                        u8"ContextBuilder::t2Bt(const parser::Token&)");
        } catch (BuilderException fe) {
            Logger::logV(fe.whatu8());
        }

        try {
            throw FException(u8"🅰  🅱  🅾  🅱  🅰");
        } catch (FException fe) {
            Logger::logV(fe.whatu8());
        }

        Logger::logV(u8"----Error handling test end---");
    }

    //for 9 test 
    template <class _Elem = char, 
              class _Traits = std::char_traits<_Elem>, 
              class _Alloc = std::allocator<_Elem>
             >
    static std::string getstrbits(const std::basic_string<_Elem, _Traits, _Alloc>& s) {
        std::stringstream ret;
        //const constexpr int digits = std::numeric_limits<_Elem>::digits + std::numeric_limits<_Elem>::is_signed;
        for (auto c : s) 
            ret << std::bitset<8>(c).to_string() << "_";
        return ret.str();
    }

    static void clean() {
        fedora::Utils::SingletonsCleaner *cleaner1 = fedora::Utils::SingletonsCleaner::GetInstance();
        cleaner1->cleanThemAll();
    }
};


#endif //FEDORA_TEST_H
