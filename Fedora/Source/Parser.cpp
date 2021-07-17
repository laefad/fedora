#include "Parser.h"
namespace fedora {

    Parser::Parser(const std::string &fileName, std::ifstream &fin) : fin(fin) {
        fin = std::ifstream(fileName, std::ios_base::in);

        if (!fin.is_open()) // если файл не открыт
            std::cout << "Файл "<<fileName<<" не может быть открыт!"; // сообщить об этом
    }

    void Parser::readFile() {
        while (!fin.eof()){
            Token tmp = readToken();
            if (!tmp.isEmpty)
            analyzeToken(tmp);
        }
    }

    Token Parser::readToken() {
        std::string res;
        char tmp = 'F';
        while(tmp != ' ' && !fin.eof()){
            tmp = fin.get();
            if (!isIgnored(tmp))
                res += tmp;
        }
        Token token = Token(res);
        if (res == " ")
            token.isEmpty = true;
        return token;
    }

    void Parser::analyzeToken(Token & token) {
        std::cout<<token.data<<std::endl;
    }

    bool Parser::isIgnored(char & tmp) {
        // Символы, которые мы игнорируем
        const std::string ignoredSymbols = "\n\t\r ";
        return ignoredSymbols.find(tmp) != std::string::npos;
    }

    Token::Token(std::string& data) {
        this->data = data;
    }
}