#include "Parser.h"
namespace fedora {

    Parser::Parser(const std::string &fileName, std::ifstream &fin) : fin(fin) {
        fin = std::ifstream(fileName, std::ios_base::in);

        if (!fin.is_open()) // если файл не открыт
            std::cout << "Файл "<<fileName<<" не может быть открыт!"; // сообщить об этом
    }

    void Parser::readFile() {
        char tmp;
        fin >> tmp;
        std::cout << tmp; // напечатали это слово
    }
}