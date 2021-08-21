#include <iostream>
#include <memory>

#include "Parser/Parser.h"
#include "Analyzers/AnalyzerStrategy.h"
#include "Utils/SettingsSingleton.h"
#include "Utils/SingletonsCleaner.h"

#include "test/Test.h"

#include "Context/Function/Function.h"
#include "Builder/ContextBuilder.h"

namespace fedora {

    //class Macros {
    //private:
    //    fedora::Context* context;
    //    std::wstring pattern;
    //    fedora::Returnable* returnable;
    //    fedora::Arguments* args;
    //};

    /*
    let f a b => a + b

    Function{
        context = *ptr        //указатель на базовые функции языка
        selfContext = nullptr //Мы ничего не определяли внутри
        returnable = <Rawcode>//Просто неспаршеная строка
        args = {a: 0, b 1}    //хз пока как сделать аргументя, чтобы потом 
                                их можно было заменить на конкретные значения
    }
    */

}

const bool is_test = true;

//std::shared_ptr<context::Function> a_test(){
//    return std::make_shared<context::Function>(nullptr);
//}
//
//std::shared_ptr<analytic::ReadName> b_test(){
//    return std::make_shared<analytic::ReadName>(std::vector<Token>());
//}

//            instance->addToCleaner();           // <- Here we add our new instance to cleaner


int main(int argc, char *argv[]) {
    // Режим тестирования
    if (is_test) {
        Logger::logV("lol");
//        fedora::builder::BuildableFunction b = fedora::builder::BuildableFunction(nullptr);
//        b.setContextFinished();
//        fedora::context::Function *a = &b;
//
//        fedora::builder::BuildableFunction* c = static_cast<fedora::builder::BuildableFunction*>(a);
//        bool t = c->isContextFinished();
//        std::wcout<<t;
        ContextBuildTester::test();
        return 0;
    } else {
        if (argc == 1) {
            std::cout << "You have not entered any arguments" << std::endl;
            return 0;
        }

        // Инициализируем настройки
        fedora::Settings *settings = fedora::Settings::GetInstance();
        settings->setLogLevel(fedora::settings::LOG_VERBOSE);

        // Получаем имя файла
        std::string path = argv[1];
        std::cout << "Args amount: " << argc << std::endl
                  << "Path to file: " << path << std::endl;

        fedora::ContextBuilder builder = fedora::ContextBuilder();

        // Инициализируем анализатор
        fedora::AnalyzerStrategy analyzer = fedora::AnalyzerStrategy(builder);

        // Инициализируем парсер файла
        //fedora::Parser parser = fedora::Parser(path, TokensHolder());
        //parser.readFile();

        // Clean singleton utils
        fedora::Utils::SingletonsCleaner *cleaner = fedora::Utils::SingletonsCleaner::GetInstance();
        cleaner->cleanThemAll();

        return 0;
    }
}
