
#include <utility>

#include "Token.h"
#include "Parser.h"
#include "StaticUtils.h"
#include "Utils/Logger.h"

namespace fedora {

    Parser::Parser()
    {}

    // TODO создавать токенхолдер тут илил принимать по ссылке?
    void Parser::readFile(std::string const& fileName, TokensHolder & tokensHolder) {

        wif = std::wifstream(fileName, std::ios_base::in);

        if (!wif.is_open()) {
            fedora::Logger::logE("File " + fileName + " can not be opened!");
            //TODO error ??
            return;
        }

        while (!wif.eof()) {
            Token tmp = readToken();
            tokensHolder.add(tmp);
        }
    }

    Token Parser::readString() {
        std::wstring res;
        uint32_t initLine = line;
        wchar_t tmp;

        do {
            tmp = wif.get();
            res += tmp;
            if (StaticUtils::isNewLine(tmp))
                ++line;
        } while (!StaticUtils::isQuote(tmp) && !wif.eof());

        if (!StaticUtils::isQuote(tmp) && wif.eof())
            ;
            // TODO add error 
            //throw error

        return Token(L'\"' + res, initLine);
    }

    void Parser::readComment() {
        wchar_t tmp;

        do {
            tmp = wif.get();
            if (StaticUtils::isNewLine(tmp))
                ++line;
        } while (!StaticUtils::isComment(tmp) && !wif.eof());

        if (!StaticUtils::isComment(tmp) && wif.eof())
            ;
            // TODO add error 
            //throw error
    }

    Token Parser::readToken() {
        std::wstring res; // token data
        wchar_t tmp; // current symbol

        while(!wif.eof()) {
            tmp = wif.get();

            if (!StaticUtils::isIgnored(tmp) && !StaticUtils::isComment(tmp)) 
                res += tmp;
            else if (StaticUtils::isNewLine(tmp))
                ++line;
            else if (StaticUtils::isComment(tmp))
                readComment();
            
            if (StaticUtils::isQuote(tmp))
                return readString();

            if (StaticUtils::isDelimiter(tmp))
                return Token(res, line);

            tmp = wif.peek();

            // TODO eof check тут нужен или нет?
            if ( (StaticUtils::isDelimiter(tmp) ||
                  StaticUtils::isQuote(tmp) ||
                  StaticUtils::isIgnored(tmp)) &&
                  !res.empty() )
                return Token(res, line);
        }

        return Token(res, line);
    }

}