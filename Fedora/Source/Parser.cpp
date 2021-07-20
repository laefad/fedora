#include "Parser.h"
#include "vector"
namespace fedora {

    Parser::Parser(const std::string &fileName, std::ifstream &fin, Analyzer& analyzer1) : fin(fin), analyzer(analyzer1) {
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
        std::wstring res;
        wchar_t tmp = L'F';
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
        std::wcout<<token.data<<std::endl;
        analyzer.analyzeNext(token);
    }

    bool Parser::isIgnored(wchar_t & tmp) {
        // Символы, которые мы игнорируем
        const std::wstring ignoredSymbols = L"\n\t\r \377"; // Возможно, \377 - это символ окончания файла
        return ignoredSymbols.find(tmp) != std::wstring::npos;
    }

    bool Parser::isDelimiter(wchar_t & tmp) {
        // Символы, которые мы считаем разделителями на токены
        const std::wstring ignoredSymbols = L"()[]:#";
        return ignoredSymbols.find(tmp) != std::wstring::npos;
    }

    Token::Token(std::wstring& data) {
        this->data = data;
    }
}