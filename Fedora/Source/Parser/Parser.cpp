
#include "Parser/Parser.h"
#include "Parser/ParserUtils.h"
#include "Utils/Logger.h"
#include "Exceptions/ParserException.h"
#include "StaticUtils.h"

#include <experimental/filesystem>

namespace fedora {
    namespace parser {

        Parser::Parser(std::unique_ptr<std::wistream> in) :
                in(std::move(in)),
                line(0) {}

        Parser Parser::makeFileParser(const std::wstring &fileName) {
            auto in = std::make_unique<std::wifstream>(StaticUtils::ws2s(fileName), std::ios_base::in);

            if (!in->good())
                throw ParserException(L"Parser::makeFileParser - file [" + fileName + L"] doesn't exist.");

            return Parser(std::move(in));
        }

        Parser Parser::makeStringParser(std::wstring wstr) {
            return Parser(std::make_unique<std::wstringstream>(wstr));
        }

        Parser Parser::makeStreamParser(std::unique_ptr<std::wistream> in) {
            Logger::logW("Parser::makeStreamParser may cause errors. Don't use it.");
            return Parser(std::move(in));
        }

        TokensHolder Parser::parse() {
            TokensHolder tokensHolder = TokensHolder();

            if (!in->good()) {
                fedora::Logger::logW("Parser::parse - empty source");
                return tokensHolder;
            }

            while (!in->eof()) {
                Token t = readToken();

                if (t.getType() == TokenType::Comment) {
                    //Logger::logV(L"Comment " + t.getData());
                    continue;
                } else if (t.getType() == TokenType::Empty) {
                    //Logger::logV(L"Empty " + std::to_wstring(t.getLine()));
                    continue;
                }

                if (t.getType() == TokenType::None)
                    determineAndSetTokenType(t);

                tokensHolder.add(t);
            }

            return tokensHolder;
        }

        Token Parser::readString() {
            std::wstring res;
            size_t initLine = line;
            wchar_t tmp;

            do {
                tmp = in->get();

                if (in->eof())
                    throw ParserException(L"Parser::readString - not closed string");

                res += tmp;

                if (ParserUtils::isNewLine(tmp))
                    ++line;

            } while (!ParserUtils::isQuote(tmp));

            return Token(L'\"' + res, initLine, TokenType::String);
        }

        Token Parser::readComment() {
            std::wstring res;
            size_t initLine = line;
            wchar_t tmp;

            do {
                tmp = in->get();

                if (in->eof())
                    throw ParserException(L"Parser::readComment - not closed comment");

                res += tmp;

                if (ParserUtils::isNewLine(tmp))
                    ++line;

            } while (!ParserUtils::isComment(tmp));

            return Token(L'#' + res, initLine, TokenType::Comment);
        }

        Token Parser::readToken() {
            std::wstring res;
            wchar_t tmp;

            while (true) {
                tmp = in->get();

                if (in->eof()) {
                    if (!res.empty())
                        return Token(res, line);
                    else
                        return Token(res, line, TokenType::Empty);
                }

                if (!ParserUtils::isIgnored(tmp) && !ParserUtils::isComment(tmp))
                    res += tmp;
                else if (ParserUtils::isNewLine(tmp))
                    ++line;
                else if (ParserUtils::isComment(tmp))
                    return readComment();

                if (ParserUtils::isQuote(tmp))
                    return readString();

                if (ParserUtils::isDelimiter(tmp))
                    return Token(res, line);

                tmp = in->peek();

                if ((ParserUtils::isDelimiter(tmp) ||
                     ParserUtils::isQuote(tmp) ||
                     ParserUtils::isIgnored(tmp)) &&
                    !res.empty())
                    return Token(res, line);
            }
        }

        void Parser::determineAndSetTokenType(Token &t) {

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
            else if (ParserUtils::isTokenNull(t))
                t.setType(TokenType::Null);
            else
                t.setType(TokenType::Name);

        }
    }
}