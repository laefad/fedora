
#include <Token.h>

#include <utility>

#include "Parser.h"
#include "StaticUtils.h"

namespace fedora {

    Parser::Parser(const std::string &fileName, std::ifstream &fin, AnalyzerStrategy& analyzer1) : fin(fin), analyzerStrategy(analyzer1) {
        fin = std::ifstream(fileName, std::ios_base::in);

        if (!fin.is_open()) // если файл не открыт
            std::cout << "Файл "<<fileName<<" не может быть открыт!"; // сообщить об этом
    }

    void Parser::readFile() {
        // Write tokens to use them in exceptions
        fedora::TokensHolder* tokensHolder = fedora::TokensHolder::GetInstance();

        while (!fin.eof()){
            Token tmp = readToken();
            // TODO Добавить в токен функцию, которая будет возвращать, что длина равна единице? Это нужно для красоты. Типа bool isChar(){return data.length()==1;}
            if (!tmp.isEmpty || (tmp.data.length() == 1 && tmp.data == L"\n"))
                tokensHolder->add(tmp);

            if (!tmp.isEmpty) {
                analyzerStrategy.analyzeNext(tmp);
            }
        }
        int a = 1+1;
    }

    Token Parser::readToken() {
        std::wstring res;
        wchar_t tmp = L'F';
        while(!fedora::StaticUtils::isDelimiter(tmp) && !isIgnored(tmp) && !fin.eof()){
            tmp = fin.get();
            if (!isIgnored(tmp))
                res += tmp;
        }

        // Если на конце токена ()[], то выделим их как отдельный токен в следующей итерации
        if (res.length() > 1 && StaticUtils::isDelimiter(res.at(res.length()-1))) {
            res = res.substr(0, res.size()-1);
            //res.pop_back();
            fin.seekg(fin.tellg().operator-(1));
        }

        Token token = Token(res);

        // Если данные пусты, значит токен пустой
        if (res.length() == 0 || (res.length() == 1 && res.at(0) == L'\n'))
            token.isEmpty = true;

        return token;
    }

//    bool Parser::analyzeToken(Token & token) {
//        std::wcout<<token.data<<std::endl;
//        return analyzer.analyzeNext(token);
//    }

    bool Parser::isIgnored(wchar_t & tmp) {
        // Символы, которые мы игнорируем
        const std::wstring ignoredSymbols = L"\t\r \377"; // Возможно, \377 - это символ окончания файла // TODO Вынести во внушнюю константу
        return ignoredSymbols.find(tmp) != std::wstring::npos;
    }

    Token::Token(std::wstring data) {
        this->data = std::move(data);
    }

    bool operator==(Token &lhs, Token &rhs) {
        return lhs.data == rhs.data || (lhs.isEmpty && rhs.isEmpty);
    }
}