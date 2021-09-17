
#include "Parser/Parser.h"
#include "Parser/ParserUtils.h"
#include "Utils/Logger.h"
#include "Exceptions/ParserException.h"
#include "StaticUtils.h"

namespace fedora {
    namespace parser {

        Parser::Parser(std::unique_ptr<std::istream> in) :
                //TODO !important u8istream
                in(std::move(in)),
                line(0) {}

        Parser Parser::makeFileParser(const std::u8string &fileName) {
            //TODO !important u8ifstream
            auto in = std::make_unique<std::ifstream>(StaticUtils::u8s2s(fileName), std::ios_base::in);

            if (!in->good())
                throw ParserException(u8"Parser::makeFileParser - file [" + fileName + u8"] doesn't exist.");

            return Parser(std::move(in));
        }

        Parser Parser::makeStringParser(std::u8string str) {
            //TODO !important u8stringstream
            return Parser(std::make_unique<std::stringstream>(StaticUtils::u8s2s(str)));
        }

        Parser Parser::makeStreamParser(std::unique_ptr<std::istream> in) {
            //TODO !important u8istream
            Logger::logW(u8"Parser::makeStreamParser may cause errors. Don't use it.");
            return Parser(std::move(in));
        }

        TokensHolder Parser::parse() {
            TokensHolder tokensHolder = TokensHolder();

            if (!in->good()) {
                fedora::Logger::logW(u8"Parser::parse - empty source");
                return tokensHolder;
            }

            while (!in->eof()) {
                Token t = readToken();

                if (t.getType() == TokenType::Comment) {
                    //Logger::logV(u8"Comment " + t.getData());
                    continue;
                } else if (t.getType() == TokenType::Empty) {
                    //Logger::logV(u8"Empty " + t.getData());
                    continue;
                }

                if (t.getType() == TokenType::None)
                    t.setType(ParserUtils::determineTokenType(t));

                //Logger::logV(u8"Token "  + t.getData());

                tokensHolder.add(t);
            }

            return tokensHolder;
        }

        std::u8string Parser::readChar(bool eofOk) {
            std::u8string res;
            size_t bytesInChar = 0;
            char8_t tmp;

            while (true) {
                tmp = in->get();

                if (in->eof())
                    if (res.empty() && eofOk)
                        return res;
                    else
                        throw ParserException(u8"Parser::readChar - eof");

                if (bytesInChar == 0) {
                    bytesInChar = ParserUtils::amountOfBytesInCharsSequence(tmp);
                    //Logger::logV(u8"Char size = " + StaticUtils::i2u8s(bytesInChar));
                }

                res += tmp;

                if (res.length() == bytesInChar)
                    return res;
            }
        }

        Token Parser::readString() {
            std::u8string res;
            size_t initLine = line;
            std::u8string tmp;

            do {
                
                try {
                    tmp = readChar(false);
                    //Logger::logV(u8"Parser::readString: " + tmp);
                } catch (ParserException e) {
                    // TODO re-use e
                    throw ParserException(u8"Parser::readString - not closed string");
                }

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

                try {
                    tmp = readChar(false);
                    //Logger::logV(u8"Parser::readComment: " + tmp);
                } catch (ParserException e) {
                    // TODO re-use e
                    throw ParserException(u8"Parser::readComment - not closed comment");
                }

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

                tmp = readChar();
                //Logger::logV(u8"Parser::readToken: " + tmp);

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

    }
}