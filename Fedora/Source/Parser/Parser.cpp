
#include "Parser/Parser.h"
#include "Parser/ParserUtils.h"
#include "Utils/Logger.h"
#include "Exceptions/ParserException.h"
#include "StaticUtils.h"

namespace fedora {
    namespace parser {

        Parser::Parser(Utf8istream in):
            in(std::move(in)),
            line(0) 
        {}

        TokensHolder Parser::parse() {
            TokensHolder tokensHolder = TokensHolder();

            if (!in.good()) {
                fedora::Logger::logW(u8"Parser::parse - empty source");
                return tokensHolder;
            }

            while (!in.eof()) {
                Token t = readToken();

                if (t.getType() == TokenType::Comment) {
                    continue;
                } 
                if (t.getType() == TokenType::Empty) {
                    continue;
                }

                if (t.getType() == TokenType::None)
                    t.setType(ParserUtils::determineTokenType(t));

                tokensHolder.add(t);
            }

            return tokensHolder;
        }

        Token Parser::readString() {
            std::u8string res;
            size_t initLine = line;
            std::u8string tmp;

            do {
                
                tmp = in.get();
                //Logger::logV(u8"get:" + tmp);
                if (in.eof())
                    throw ParserException(u8"Parser::readString - not closed string");

                res += tmp;

                if (ParserUtils::isNewLine(tmp))
                    ++line;

            } while (!ParserUtils::isQuote(tmp));

            return Token(u8'\"' + res, initLine, TokenType::String);
        }

        Token Parser::readComment() {
            std::u8string res;
            size_t initLine = line;
            std::u8string tmp;

            do {

                tmp = in.get();
                //Logger::logV(u8"get:" + tmp);
                if (in.eof())
                    throw ParserException(u8"Parser::readComment - not closed comment");

                res += tmp;

                if (ParserUtils::isNewLine(tmp))
                    ++line;

            } while (!ParserUtils::isComment(tmp));

            return Token(u8'#' + res, initLine, TokenType::Comment);
        }

        Token Parser::readToken() {
            std::u8string res;
            std::u8string tmp;

            while (true) {

                tmp = in.get();
                //Logger::logV(u8"get:" + tmp);

                if (in.eof()) {
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

                tmp = in.peek();
                //Logger::logV(u8"Peeked: " + tmp);

                if ((ParserUtils::isDelimiter(tmp) ||
                     ParserUtils::isQuote(tmp) ||
                     ParserUtils::isIgnored(tmp)) &&
                    !res.empty())
                    return Token(res, line);
            }
        }

    }
}