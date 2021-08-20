
#include "Parser/Parser.h"
#include "Parser/ParserUtils.h"
#include "Utils/Logger.h"
#include "Exceptions/FException.h"
#include "StaticUtils.h"

namespace fedora {
    namespace parser {

        Parser::Parser(std::unique_ptr<std::wistream> in):
            in(std::move(in)),
            line(0)
        {}

        Parser Parser::makeFileParser(std::wstring fileName) {
            return Parser(std::make_unique<std::wifstream>(StaticUtils::ws2s(fileName), std::ios_base::in));
        }

        Parser Parser::makeStringParser(std::wstring wstr) {
            return Parser(std::make_unique<std::wstringstream>(wstr));
        }

        Parser Parser::makeStreamParser(std::unique_ptr<std::wistream> in) {
            return Parser(std::move(in));
        }

        TokensHolder Parser::parse() {

            TokensHolder tokensHolder = TokensHolder();

            if (!in->good()) {
                fedora::Logger::logE("Parser::parse -- parse error or empty source");
                //TODO error ??
                return tokensHolder;
            }

            while (!in->eof()) {
                Token t = readToken();

                if (t.getType() == TokenType::None)
                    determineAndSetTokenType(t);

                tokensHolder.add(t);
            }

            return tokensHolder;
        }

        Token Parser::readString() {
            std::wstring res;
            uint32_t initLine = line;
            wchar_t tmp;

            if (in->eof())
                throw FException("Parser::readString");
                //TODO add error

            do {
                tmp = in->get();
                res += tmp;
                if (ParserUtils::isNewLine(tmp))
                    ++line;
            } while (!ParserUtils::isQuote(tmp) && !in->eof());

            if (!ParserUtils::isQuote(tmp) && in->eof())
                throw FException("Parser::readString not closed");
            // TODO add error

            return Token(L'\"' + res, initLine, TokenType::String);
        }

        void Parser::readComment() {
            wchar_t tmp;

            if (in->eof())
                throw FException("Parser::readComment");
                //TODO add error

            do {
                tmp = in->get();
                if (ParserUtils::isNewLine(tmp))
                    ++line;
            } while (!ParserUtils::isComment(tmp) && !in->eof());

            if (!ParserUtils::isComment(tmp) && in->eof())
                throw FException("Parser::readComment not closed");
            // TODO add error
        }

        Token Parser::readToken() {
            std::wstring res; // token data
            wchar_t tmp; // current symbol

            while (!in->eof()) {
                tmp = in->get();

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

                if (in->eof()) {
                    if (!res.empty())
                        return Token(res, line);
                    else 
                        throw FException("Parser::readToken empty token");
                }

                tmp = in->peek();

                if ((ParserUtils::isDelimiter(tmp) ||
                        ParserUtils::isQuote(tmp) ||
                        ParserUtils::isIgnored(tmp)) &&
                    !res.empty())
                    return Token(res, line);
            }

            //empty token check     
            if (!res.empty())
                return Token(res, line);
            else 
                throw FException("Parser::readToken empty token");           
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