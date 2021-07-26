#include <iostream>
#include <string>
#include <TokensHolder.h>
#include <Analyzers/AnalyticUtils.h>
#include "Parser.h"

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

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cout << "You have not entered any arguments" << std::endl;
        return 0;
    }

    // Получаем имя файла
    std::string path = argv[1];
    std::cout << "Args amount: " << argc <<std::endl
            << "Path to file: " << path << std::endl;

    // Создаём файловый поток
    std::ifstream fin;

    // Инициализируем анализатор
    fedora::AnalyzerStrategy analyzer = fedora::AnalyzerStrategy();

    // Инициализируем парсер файла
    fedora::Parser parser = fedora::Parser(path, fin, analyzer);
    parser.readFile();

    // Очищаем синглтон токенхолдера, чтобы не было течки
    fedora::TokensHolder* a = fedora::TokensHolder::GetInstance();
    delete a;

    return 0;
}
