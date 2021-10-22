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

#include "Runtime.h"

#include <bitset>
#include <functional>
#include <optional>

using namespace fedora;

// TODO разбить на файлы после окончательного формирования классов и их интерфейсов 

class TestUtils {
    public:

    static void clean() {
        fedora::Utils::SingletonsCleaner *cleaner = fedora::Utils::SingletonsCleaner::GetInstance();
        cleaner->cleanThemAll();
    }

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

    template <class _Elem = char, 
              class _Traits = std::char_traits<_Elem>, 
              class _Alloc = std::allocator<_Elem>
             >
    static std::string getstrbits(const std::basic_string<_Elem, _Traits, _Alloc>& s) {
        std::stringstream ret;
        const constexpr int digits = std::numeric_limits<_Elem>::digits + std::numeric_limits<_Elem>::is_signed;
        for (auto c : s) 
            ret << std::bitset<digits>(c).to_string() << "_";
        return ret.str();
    }

    static fedora::ContextBuilder genBuilder(std::u8string code, bool verbose=false){
        using fedora::parser::Parser;
        using fedora::parser::Utf8istream;
        using fedora::parser::TokensHolder;

        // тест реальной программы
        Settings *setting = Settings::GetInstance();
        if (verbose)
            setting->setLogLevel(settings::LogLevel::LOG_VERBOSE);
        else
            setting->setLogLevel(settings::LogLevel::LOG_WARNING);

        Parser parser = Parser(parser::Utf8istream::fromString(code));
        TokensHolder tokensHolder = parser.parse();
        fedora::ContextBuilder builder = fedora::ContextBuilder();
        fedora::AnalyzerStrategy analyzer = fedora::AnalyzerStrategy(builder);
        for (auto it = tokensHolder.begin(); it < tokensHolder.end(); ++it) {
            analyzer.analyzeNext(*it);
        }

        setting->setLogLevel(settings::LogLevel::LOG_VERBOSE);

        return builder;
    }

    static bool checkIfRetContains(fedora::ContextBuilder& builder, const std::u8string& funName, const std::u8string& contains, bool log=false){
        if (builder.getContext()->at(funName) != nullptr) {
            std::shared_ptr<fedora::context::Function> & list = builder.getContext()->at(funName);

            using fef = fedora::context::FeFunction;
            auto fe = dynamic_cast<fef *>(list.get());
            if (log)
             Logger::logV(fe->logRet());
            if (fe->logRet().find(contains) != std::u8string::npos)
                return true;
            else
                return false;
        } else {
           return false;
        }
    }
};

template<typename... Args>
class Test {
    protected:
        size_t num;
        std::u8string header;
        std::u8string about;
        std::function<bool(Args...)> testFunction;
        bool logging;
    public:
        Test(size_t num,
            std::u8string header, 
            std::u8string about,
            std::function<bool(Args...)> f):
            num(num), 
            header(header),
            about(about),
            testFunction(f),
            logging(false)
        {}

        void setLogging (bool logging) {
            this->logging = logging;
        }

        std::optional<std::u8string> test(Args... args) const {
            if (logging) {
                Logger::logV(u8"Test " + StaticUtils::i2u8s(num));
                Logger::logV(header + u8"\n" + about);
            }

            bool res = false;

            try {
                TestUtils::clean();
                res = testFunction(args...);
                TestUtils::clean();
            } catch (std::exception e) {
                if (logging) 
                    Logger::logV(u8"Test " + StaticUtils::i2u8s(num) + u8" failed.");

                return std::make_optional(u8"Test " + StaticUtils::i2u8s(num) + u8"failed, "
                                          + u8"\n" + StaticUtils::s2u8s(e.what()));
            }

            if (res) {
                if (logging) 
                    Logger::logV(u8"Test " + StaticUtils::i2u8s(num) + u8" complete.");
                
                return std::nullopt;
            } else {
                if (logging) 
                    Logger::logV(u8"Test " + StaticUtils::i2u8s(num) + u8" failed.");

                return std::make_optional(u8"Test " + StaticUtils::i2u8s(num) + u8" failed without errors.");
            }
        }
};

class TestingSetup {
    public:
        static void setup();
};

// TODO подумать, может лучше перейти от статического класса к обычному, 
// тогда в setup можно будет передавать объект и не надо будет тащить setup внутрь
class Tester {
    protected:
        inline static std::vector<Test<>> tests = std::vector<Test<>>();
    public:
        static void testing(bool logging = false) {
            size_t successful = 0;
            TestingSetup::setup();
            for (size_t i = 0, size = Tester::tests.size(); i < size; ++i) {
                auto test = tests[i];
                test.setLogging(logging);
                auto res = test.test();
                if (res) {
                    Logger::logV(u8"\u001b[31mTest failed: " + res.value() + u8"\u001b[0m");
                } else {
                    ++successful;
                }
                if (logging && (i != size - 1)) {
                    Logger::logV(u8"----------------------------");
                }
            }

            Logger::logV(u8"Tests passed " + StaticUtils::i2u8s(successful) 
                         + u8"/" + StaticUtils::i2u8s(tests.size()));
        }

        static void addTest(Test<> t) {
            Tester::tests.push_back(t);
        }
};

// TODO избавится от этого класса
class ContextBuildTester {
public:
    static void test() {
        Logger::logV(u8"Testing main fedora functions");
        Tester::testing(/*true*/);

        // test1();
        // test10();
    }

private:

    // TODO он вообще еще актуален??
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

    // TODO работает, но просто захламляет вывод в любом случае, ибо это тест на отображение 
    // static void test10() {
    //     Logger::logV(u8"------Error handling test----");
    //     try {
    //         throw BuilderException(
    //                     u8"You're trying to convert token to BasicType, but token is not a primitive type instance.",
    //                     u8"ContextBuilder::t2Bt(const parser::Token&)");
    //     } catch (BuilderException fe) {
    //         Logger::logV(fe.whatu8());
    //     }

    //     try {
    //         throw FException(u8"🅰  🅱  🅾  🅱  🅰");
    //     } catch (FException fe) {
    //         Logger::logV(fe.whatu8());
    //     }

    //     Logger::logV(u8"----Error handling test end---");
    // }

};


void TestingSetup::setup() {
    Tester::addTest(Test<>(
        1,
        u8"Testing Context Builder.",
        u8"Try to create simple force call.",
        [] () -> bool {
            using parser::Token;
            ContextBuilder builder = ContextBuilder();

            Token mName = Token(u8"main");
            Token mOne = Token(u8"1");

            builder.notifyWeStartForceCall();
            auto forceName = mOne.getData();
            builder.setForceName(forceName);
            //StackHolder *s = StackHolder::GetInstance();
            return true;
        }
    ));

    Tester::addTest(Test<>(
        2,
        u8"Testing List static functions.",
        u8"Try adding the numbers at the beginning of the list and at the end of the list.",
        [] () -> bool {
            std::shared_ptr<types::List> a = std::make_shared<types::List>(std::make_shared<types::Number>(0.0));
            auto b = types::List::addNewItemToTheBeginning(std::make_shared<types::Number>(2.0), a);
            b = types::List::addNewItemToTheBeginning(std::make_shared<types::Number>(2.0), b);
            auto c = types::List::addNewItemToTheEnd(std::make_shared<types::Number>(3.0), b);
            // TODO Я проверял работу через дебаггер, но хорошо бы сделать тест кодом
            return true;
        }
    ));

    Tester::addTest(Test<>(
        3,
        u8"Тестируем создание функции и проверяем ее контекст.",
        u8"Вручную создаем функцию с помощью токенов.",
        [] () -> bool {
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

            if (builder.getContext()->count(mA.getData()) == 1 &&
                builder.getContext()->count(mB.getData()) == 1)
                return true;
            else
                return false;
        }
    ));

    Tester::addTest(Test<>(
        4,
        u8"Тестируем добавление элементов в список.",
        // TODO тоже самое, что в тесте 2 ??
        u8"Вручную создаем элементы и добавляем их в список.",
        [] () -> bool {
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

            return success;

            // if (success)
            //     Logger::logV(u8"test 6 completed");
            // else
            //     Logger::logV(u8"test 6 failed");

            // try {
            //     throw exception::BuilderException(L"text", L"test()");
            // } catch (exception::BuilderException e) {
            //     e.what();
            // }

            //throw exception::BuilderException(L"text", L"test()");
        }
    ));

    Tester::addTest(Test<>(
        5,
        u8"Тестируем создание функции и проверяем ее возвращаемое",
        u8"Вручную создаем функцию с помощью токенов.",
        [] () -> bool {
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


            if (builder.getContext()->count(mA.getData()) == 1 &&
                (*(builder.getContext()))[mA.getData()]->getContext()->count(mB.getData()) == 1)
                return true;
            else
                return false;
        }
    ));

    Tester::addTest(Test<>(
        6,
        u8"Тестирование чтения и сборки настоящей программы.",
        u8"Программа находится в файле programs/current_features.fe",
        [] () -> bool {
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

            // logAllContext(builder.getPackage()->getContext());
        
            if (builder.getContext()->at(u8"a") != nullptr){
                std::shared_ptr<fedora::context::Function> & list = builder.getContext()->at(u8"a");

                using fef = fedora::context::FeFunction;
                auto fe = dynamic_cast<fef *>(list.get());
                // Logger::logV(fe->logRet());
                if (fe->logRet() == u8"[1.000000 2.000000 \"🤡\"]")
                    return true;
                else
                    return false;
            } else {
                return false;
            }
        }
    ));

    Tester::addTest(Test<>(
        7,
        u8"Тестирование конверсации string в u8string.",
        u8"Протестированы символы аски, иероглифы и смайлик.",
        [] () -> bool {
            //Logger::logV(u8"😀");
            // std::cout << ContextBuildTester::getstrbits<char8_t>(std::u8string(u8"¢")) << std::endl;
            // std::cout << ContextBuildTester::getstrbits(std::string("¢")) << std::endl;
            // std::cout << std::hex << (int)u8'ö' << std::endl;
            // std::cout << std::hex << (int)'ö' << std::endl;

            std::u8string data = u8"biba";
            std::string result = StaticUtils::u8s2s(data);

            if (TestUtils::getstrbits<char8_t>(data) != TestUtils::getstrbits<char>(result))
                return false;

            data = u8"öʧधᐇ";
            result = StaticUtils::u8s2s(data);

            if (TestUtils::getstrbits<char8_t>(data) != TestUtils::getstrbits<char>(result))
                return false;

            std::string data2 = "biba";
            std::u8string result2 = StaticUtils::s2u8s(data2);

            if (TestUtils::getstrbits<char>(data2) != TestUtils::getstrbits<char8_t>(result2))
                return false;

            data2 = "öʧधᐇ";
            result2 = StaticUtils::s2u8s(data2);

            if (TestUtils::getstrbits<char>(data2) != TestUtils::getstrbits<char8_t>(result2))
                return false;

            return true;
        }
    ));

    Tester::addTest(Test<>(
        8,
        u8"Тестирование добавления аргументов в фанколл",
        u8"Добавлены примитивные типы: нулл, числа и строка",
        [] () -> bool {
            fedora::ContextBuilder builder = TestUtils::genBuilder(u8"let fn = my_int(1 null \"yo\" 1 1)");

            return TestUtils::checkIfRetContains(builder, u8"fn", u8"my_int(1.000000 null \"yo\" 1.000000 1.000000)");
        }
    ));

    // Tester::addTest(Test<>(
    //     9,
    //     u8"Добавление списка как аргумент фанколла",
    //     u8"В том числе рекурсивное",
    //     [] () -> bool {
    //         Settings *setting = Settings::GetInstance();
    //         setting->setLogLevel(settings::LogLevel::LOG_VERBOSE);

    //         fedora::ContextBuilder builder = TestUtils::genBuilder(u8"let fn = my_fun(1 [] [ my_int(1 []) ])", true);

    //         return TestUtils::checkIfRetContains(builder, u8"fn", u8"my_fun(1.000000 [] [my_int(1 [])])", true);
    //     }
    // ));

    // Tester::addTest(Test<>(
    //     10,
    //     u8"Вложенный список",
    //     u8"В список можно добавить любые примитивые и продвинутые типы",
    //     [] () -> bool {
    //         Settings *setting = Settings::GetInstance();
    //         setting->setLogLevel(settings::LogLevel::LOG_VERBOSE);

    //         fedora::ContextBuilder builder = TestUtils::genBuilder(u8"let fn = [1 [null [my_int] my_str(1 2)[]]]", true);

    //         return TestUtils::checkIfRetContains(builder, u8"fn", u8"my_int(1.000000 null \"yo\" 1.000000 1.000000)");
    //     }
    // ));

    Tester::addTest(Test<>(
        11,
        u8"Тестирование рантайма",
        u8"Надо написать нормальное описание потом",
        [] () -> bool {
            Settings::GetInstance()->setLogLevel(settings::LogLevel::LOG_ERROR);

            auto code = u8"let main = log(\"Ну как с Федорой обстоят вопросы?\")";
            auto source = parser::Utf8istream::fromString(std::move(code));
            auto parser = parser::Parser(std::move(source));
            auto tokensHolder = parser.parse();
            auto builder = fedora::ContextBuilder();
            auto analyzer = fedora::AnalyzerStrategy(builder);
            for (auto it = tokensHolder.begin(); it < tokensHolder.end(); ++it) {
                analyzer.analyzeNext(*it);
            }

            auto sh = StackHolder();
            sh.addForceCall(
                StackHolder::Call(
                    std::make_shared<types::UnbindedFunCall>(
                        u8"main",
                        types::UnbindedFunCall::FunCallArguments {
                            std::make_shared<types::Null>()
                        }
                    )
                )
            );

            auto ctx = *builder.getContext();

            Runtime::execute(sh, ctx);

            return true;
        }
    ));

    // шаблон (база), не трогать
    // Tester::addTest(Test<>(
    //     9,
    //     u8"",
    //     u8"",
    //     [] () -> bool {
            
            
    //     }
    // ));
}


#endif //FEDORA_TEST_H

// AYANAMI REI                           __.-"..--,__
//                                __..---"  | _|    "-_\
//                         __.---"          | V|::.-"-._D
//                    _--"".-.._   ,,::::::'"\/""'-:-:/
//               _.-""::_:_:::::'-8b---"            "'
//            .-/  ::::<  |\::::::"\
//            \/:::/::::'\\ |:::b::\
//            /|::/:::/::::-::b:%b:\|
//             \/::::d:|8:::b:"%%%%%\
//             |\:b:dP:d.:::%%%%%"""-,
//              \:\.V-/ _\b%P_   /  .-._
//              '|T\   "%j d:::--\.(    "-.
//              ::d<   -" d%|:::do%P"-:.   "-,
//              |:I _    /%%%o::o8P    "\.    "\
//               \8b     d%%%%%%P""-._ _ \::.    \
//               \%%8  _./Y%%P/      .::'-oMMo    )
//                 H"'|V  |  A:::...:odMMMMMM(  ./
//                 H /_.--"JMMMMbo:d##########b/
//              .-'o      dMMMMMMMMMMMMMMP""
//            /" /       YMMMMMMMMM|
//          /   .   .    "MMMMMMMM/
//          :..::..:::..  MMMMMMM:|
//           \:/ \::::::::JMMMP":/
//            :Ao ':__.-'MMMP:::Y
//            dMM"./:::::::::-.Y
//           _|b::od8::/:YM::/
//           I HMMMP::/:/"Y/"
//            \'""'  '':|
//             |    -::::\
//             |  :-._ '::\
//             |,.|    \ _:"o
//             | d" /   " \_:\.
//             ".Y. \       \::\
//              \ \  \      MM\:Y
//               Y \  |     MM \:b
//               >\ Y      .MM  MM
//               .IY L_    MP'  MP
//               |  \:|   JM   JP
//               |  :\|   MP   MM
//               |  :::  JM'  JP|
//               |  ':' JP   JM |
//               L   : JP    MP |
//               0   | Y    JM  |
//               0   |     JP"  |
//               0   |    JP    |
//               m   |   JP     #
//               I   |  JM"     Y
//               l   |  MP     :"
//               |\  :-       :|
//               | | '.\      :|
//               | | "| \     :|
//                \    \ \    :|
//                |  |  | \   :|
//                |  |  |   \ :|
//                |   \ \    | '.
//                |    |:\   | :|
//                \    |::\..|  :\
//                 ". /::::::'  :||
//                   :|::/:::|  /:\
//                   | \/::|: \' ::|
//                   |  :::||    ::|
//                   |   ::||    ::|
//                   |   ::||    ::|
//                   |   ::||    ::|
//                   |   ': |    .:|
//                   |    : |    :|
//                   |    : |    :|
//                   |    :||   .:|
//                   |   ::\   .:|
//                  |    :::  .::|
//                 /     ::|  :::|
//              __/     .::|   ':|
//     ...----""        ::/     ::
//    /m_  AMm          '/     .:::
//    ""MmmMMM#mmMMMMMMM"     .:::m
//       """YMMM""""""P        ':mMI
//                _'           _MMMM
//            _.-"  mm   mMMMMMMMM"
//           /      MMMMMMM""
//           mmmmmmMMMM"
