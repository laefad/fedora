
#include <utility>

#include "Token.h"
#include "Parser.h"
#include "StaticUtils.h"

namespace fedora {

    // TODO а нам нужна инициализация и открытие потока прям сразу ? может разумнее сделать это в readFile ? 
    // TODO подумать над структурой риспользуемого парсера
    Parser::Parser(std::string const& fileName, TokensHolder & tokensHolder):
        fin(std::ifstream(fileName, std::ios_base::in)),
        tokensHolder(tokensHolder) 
    {

        // fin = std::ifstream(fileName, std::ios_base::in);

        if (!fin.is_open()) // если файл не открыт
            // TODO заменить на логгер, а так же необходимо залочить выполнение своих методов
            std::cout << "File " << fileName << " can not be opened!"; // сообщить об этом
    }

    void Parser::readFile() {
        while (!fin.eof()) {
            Token tmp = readToken();
            tokensHolder.add(tmp);
        }
    }

    Token Parser::readString() {
        std::wstring res;
        uint32_t initLine = line;
        wchar_t tmp;

        do {
            tmp = fin.get();
            res += tmp;
            if (StaticUtils::isNewLine(tmp))
                ++line;
        } while (!StaticUtils::isQuote(tmp) && !fin.eof());

        if (!StaticUtils::isQuote(tmp) && fin.eof())
            // TODO add error 
            //throw error

        return Token(L'\"' + res, initLine);
    }

    //TODO не возвращать токен комментов, а возвращаться в основной while для дальнейшего чтения
    Token Parser::readComment() {
        std::wstring res;
        uint32_t initLine = line;
        wchar_t tmp;

        do {
            tmp = fin.get();
            res += tmp;
            if (StaticUtils::isNewLine(tmp))
                ++line;
        } while (!StaticUtils::isComment(tmp) && !fin.eof());

        if (!StaticUtils::isComment(tmp) && fin.eof())
            // TODO add error 
            //throw error

        return Token(L'#' + res, initLine);
    }

    Token Parser::readToken() {
        std::wstring res; // token data
        wchar_t tmp; // current symbol

        while(!fin.eof()) {
            tmp = fin.get();

            if (!StaticUtils::isIgnored(tmp)) 
                res += tmp;
            else if (StaticUtils::isNewLine(tmp))
                ++line;

            if (StaticUtils::isComment(tmp))
                return readComment();
            
            if (StaticUtils::isQuote(tmp))
                return readString();

            if (StaticUtils::isDelimiter(tmp))
                return Token(res, line);

            tmp = fin.peek();

            // TODO eof check тут нужен или нет?
            if ( (StaticUtils::isDelimiter(tmp) ||
                  StaticUtils::isQuote(tmp) ||
                  StaticUtils::isComment(tmp)) &&
                  !res.empty() )
                return Token(res, line);
        }

        return Token(res, line);
    }

}