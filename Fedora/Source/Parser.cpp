#include "Parser.h"
#include "vector"
namespace fedora {

    Parser::Parser(const std::string &fileName, std::ifstream &fin) : fin(fin) {
        fin = std::ifstream(fileName, std::ios_base::in);

        if (!fin.is_open()) // если файл не открыт
            std::cout << "Файл "<<fileName<<" не может быть открыт!"; // сообщить об этом
    }

    void Parser::readFile() {
        std::vector<Token> tokens = std::vector<Token>();

        while (!fin.eof()){
            Token tmp = readToken();
            if (!tmp.isEmpty) {
                analyzeToken(tmp);
                tokens.push_back(tmp);
            }
        }
        int a = 1+1;
    }

    Token Parser::readToken() {
        std::string res;
        char tmp = 'F';
        while(!isDelimiter(tmp) && !isIgnored(tmp) && !fin.eof()){
            tmp = fin.get();
            if (!isIgnored(tmp))
                res += tmp;
        }

        // Если на конце токена ()[], то выделим их как отдельный токен в следующей итерации
        if (res.length() > 1 && isDelimiter(res.at(res.length()-1))) {
            res = res.substr(0, res.size()-1);
            //res.pop_back();
            fin.seekg(fin.tellg().operator-(1));
        }

        Token token = Token(res);

        // Если данные пусты, значит токен пустой
        if (res.length() == 0)
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

    bool Parser::isDelimiter(char & tmp) {
        // Символы, которые мы считаем разделителями на токены
        const std::string ignoredSymbols = "()[]:#";
        return ignoredSymbols.find(tmp) != std::string::npos;
    }

    Token::Token(std::string& data) {
        this->data = data;
    }
}