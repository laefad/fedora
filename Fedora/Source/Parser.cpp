
#include <utility>

#include <Token.h>
#include "Parser.h"
#include "StaticUtils.h"

namespace fedora {

    Parser::Parser(const std::string &fileName, std::ifstream &fin, AnalyzerStrategy &analyzer1)
    : fin(fin), analyzerStrategy(analyzer1) {
        fin = std::ifstream(fileName, std::ios_base::in);

        if (!fin.is_open()) // если файл не открыт
            std::cout << "File " << fileName << " can not be opened!"; // сообщить об этом
    }

    void Parser::readFile() {
        bool noErrors = true;

        // Write tokens to use them in exceptions
        fedora::TokensHolder *tokensHolder = fedora::TokensHolder::GetInstance();

        while (!fin.eof() && noErrors) {
            Token tmp = readToken();
            // TODO Добавить в токен функцию, которая будет возвращать, что длина равна единице? Это нужно для красоты. Типа bool isChar(){return data.length()==1;}

            // if token is a carriage return -> push it to tokens holder // TODO Мб стоит убрать из этого услования !tmp.isEmpty()? Это условие избыточно и при будущих изменениях, вероятно, оно перестанет работать
            if (!tmp.isEmpty() || (tmp.getData().length() == 1 && tmp.getData() == L"\n"))
                tokensHolder->add(tmp);

            if (!tmp.isEmpty()) {
                noErrors = analyzerStrategy.analyzeNext(tmp);
            }
        }
        int a = 1 + 1;
    }

    Token Parser::readToken() {
        std::wstring res; // token data
        wchar_t tmp = L'F'; // current symbol
        while (!fedora::StaticUtils::isDelimiter(tmp) && !isIgnored(tmp) && !fin.eof()) {
            tmp = fin.get();
            if (!isIgnored(tmp))
                res += tmp;
        }

        // Если на конце токена ()[], то выделим их как отдельный токен в следующей итерации
        if (res.length() > 1 && StaticUtils::isDelimiter(res.at(res.length() - 1))) {
            res = res.substr(0, res.size() - 1);
            //res.pop_back();
            fin.seekg(fin.tellg().operator-(1));
        }

        Token token = Token(res);

        // Если данные пусты, значит токен пустой
        if (res.length() == 0 || (res.length() == 1 && res.at(0) == L'\n') || res.at(0) < 0)
            token.setEmpty(true);

        return token;
    }

    bool Parser::isIgnored(wchar_t &tmp) {
        // Символы, которые мы игнорируем
        const std::wstring ignoredSymbols = L"\t\r \377"; // Возможно, \377 - это символ окончания файла // TODO Вынести во внушнюю константу
        return ignoredSymbols.find(tmp) != std::wstring::npos;
    }

    Token::Token(std::wstring data) {
        this->data = std::move(data);
    }

    bool operator==(Token &lhs, Token &rhs) {
        return lhs.data == rhs.data || (lhs.isEmpty() && rhs.isEmpty());
    }

}