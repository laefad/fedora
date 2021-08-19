
#include <utility>

#include "Parser/Token.h"
#include "Parser/Parser.h"
#include "Parser/ParserUtils.h"
#include "Utils/Logger.h"

namespace fedora {
    namespace parser {
        Parser::Parser() {}

        // TODO создавать токенхолдер тут илил принимать по ссылке?
        void Parser::readFile(std::string const &fileName, TokensHolder &tokensHolder) {

            wif = std::wifstream(fileName, std::ios_base::in);

            if (!wif.is_open()) {
                fedora::Logger::logE("File " + fileName + " can not be opened!");
                //TODO error ??
                return;
            }

            while (!wif.eof()) {
                Token t = readToken();

                if (t.getType() == TokenType::None)
                    determineAndSetTokenType(t);

                tokensHolder.add(t);
            }
        }

        Token Parser::readString() {
            std::wstring res;
            uint32_t initLine = line;
            wchar_t tmp;

            do {
                tmp = wif.get();
                res += tmp;
                if (ParserUtils::isNewLine(tmp))
                    ++line;
            } while (!ParserUtils::isQuote(tmp) && !wif.eof());

            if (!ParserUtils::isQuote(tmp) && wif.eof());
            // TODO add error
            //throw error

            return Token(L'\"' + res, initLine, TokenType::String);
        }

        void Parser::readComment() {
            wchar_t tmp;

            do {
                tmp = wif.get();
                if (ParserUtils::isNewLine(tmp))
                    ++line;
            } while (!ParserUtils::isComment(tmp) && !wif.eof());

            if (!ParserUtils::isComment(tmp) && wif.eof());
            // TODO add error
            //throw error
        }

        Token Parser::readToken() {
            std::wstring res; // token data
            wchar_t tmp; // current symbol

            while (!wif.eof()) {
                tmp = wif.get();

                if (!ParserUtils::isIgnored(tmp) && !ParserUtils::isComment(tmp))
                    res += tmp;
                else if (ParserUtils::isNewLine(tmp))
                    ++line;
                else if (ParserUtils::isComment(tmp))
                    readComment();

                if (ParserUtils::isQuote(tmp))
                    return readString();

                if (ParserUtils::isDelimiter(tmp))
                    return Token(res, line);

                tmp = wif.peek();

                // TODO eof check тут нужен или нет?
                if ((ParserUtils::isDelimiter(tmp) ||
                        ParserUtils::isQuote(tmp) ||
                        ParserUtils::isIgnored(tmp)) &&
                    !res.empty())
                    return Token(res, line);
            }

            return Token(res, line);
        }

        void Parser::determineAndSetTokenType(Token & t) {
            
            if (ParserUtils::isTokenACallOpen(t))
                t.setType(TokenType::CallOpen);
            else if (ParserUtils::isTokenACallClose(t))
                t.setType(TokenType::CallClose);
            else if (ParserUtils::isTokenAListOpen(t))
                t.setType(TokenType::ListOpen);
            else if (ParserUtils::isTokenAListClose(t))
                t.setType(TokenType::ListClose);
            
            else if (ParserUtils::isTokenAFunctionDeclaration(t))
                t.setType(TokenType::FunctionDeclaration);
            else if (ParserUtils::isTokenAFunctionContextDeclaration(t))
                t.setType(TokenType::FunctionContextDeclaration);
            else if (ParserUtils::isTokenAFunctionReturnableDeclaration(t))
                t.setType(TokenType::FunctionReturnableDeclaration);
            
            else if (ParserUtils::isTokenANumber(t))
                t.setType(TokenType::Number);
            
            else if (ParserUtils::isTokenAForceCall(t))
                t.setType(TokenType::ForceCall);

            else 
                t.setType(TokenType::Name);

        }
    }
}