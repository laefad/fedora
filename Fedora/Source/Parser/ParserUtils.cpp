
#include "Parser/ParserUtils.h"

#include "Utils/Logger.h"

namespace fedora {

    namespace parser {

        // TODO переписать на regex, но u8str не поддерживает его. Нужно обсуждение
        // TODO добавить сортировку по TokenPriority после инициализации
        const std::vector<std::tuple<TokenPriority, std::u8string, TokenType>> 
            ParserUtils::tokenMaping = {
                {TokenPriority::Whitespace, u8"\n", TokenType::Empty},
                {TokenPriority::Whitespace, u8"\t", TokenType::Empty},
                {TokenPriority::Whitespace, u8"\r", TokenType::Empty},
                {TokenPriority::Whitespace, u8" ", TokenType::Empty},

                {TokenPriority::KeyWord, u8"let", TokenType::FunctionDeclaration},
                {TokenPriority::KeyWord, u8"where", TokenType::FunctionContextDeclaration},
                {TokenPriority::KeyWord, u8"force", TokenType::ForceCall},
                {TokenPriority::KeyWord, u8"null", TokenType::Null},

                {TokenPriority::Delimeter, u8"=", TokenType::FunctionReturnableDeclaration},
                {TokenPriority::Delimeter, u8"(", TokenType::CallOpen},
                {TokenPriority::Delimeter, u8")", TokenType::CallClose},
                {TokenPriority::Delimeter, u8"[", TokenType::ListOpen},
                {TokenPriority::Delimeter, u8"]", TokenType::ListClose}
        };

        TokenType ParserUtils::determineTokenType(const Token &t) {
            for (const auto &elem : tokenMaping) {
                if (t.getData() == std::get<1>(elem)) 
                    return std::get<2>(elem);
            }

            //NUMBER CHECK 
            if (isTokenANumber(t))
                return TokenType::Number;

            //NAME CHECK 
            if (isTokenAName(t))
                return TokenType::Name;

            // TODO add error
            throw 2289;
        }

        size_t ParserUtils::amountOfBytesInCharsSequence(char8_t chr) {
            /// check 0xxxxxxx
            if ((chr & 0b1000'0000) == 0b0000'0000) {
                return 1;
            /// check 110xxxx
            } else if ((chr & 0b1110'0000) == 0b1100'0000) {
                return 2;
            /// check 1110xxxx
            } else if ((chr & 0b1111'0000) == 0b1110'0000) {
                return 3;
            /// check 11110xxx
            } else if ((chr & 0b1111'1000) == 0b1111'0000) {
                return 4;
            } else {
                //TODO error
                throw 2228;
            }
        }

        // TODO не используется
        bool ParserUtils::isSingleChar(const std::u8string &u8str) {
            size_t maxLen = 1;

            for (auto i = 0; i < u8str.length(); ++i) {
                if (i == 0)
                    maxLen = amountOfBytesInCharsSequence(u8str[i]);
                
                if (i == maxLen)
                    return false;
            }

            return true;
        }

        bool ParserUtils::isDelimiter(const std::u8string &u8str) {
            for (const auto &elem : tokenMaping) {
                if (std::get<0>(elem) == TokenPriority::Delimeter) 
                    if (u8str == std::get<1>(elem))
                        return true;
            }
            return false;
        }

        bool ParserUtils::isNewLine(const std::u8string &u8str) {
            return u8str == u8"\n";
        }

        bool ParserUtils::isQuote(const std::u8string &u8str) {
            return u8str == u8"\"";
        }

        bool ParserUtils::isComment(const std::u8string &u8str) {
            return u8str == u8"#";
        }

        bool ParserUtils::isIgnored(const std::u8string &u8str) {
            for (const auto &elem : tokenMaping) {
                if (std::get<0>(elem) == TokenPriority::Whitespace) 
                    if (u8str == std::get<1>(elem))
                        return true;
            }

            return false;
        }

        bool ParserUtils::isTokenANumber(Token const &t) {
            auto data = t.getData();
            bool hasDot = false;

            for (unsigned i = 0, len = data.length(); i < len; ++i) {
                auto chr = data.at(i);

                if (isdigit(chr))
                    continue;

                if (chr != u8'.') {
                    if (i != 0 || (chr != u8'+' && chr != u8'-'))
                        return false;
                } else if (hasDot || i == 0 || i == len - 1)
                    return false;
                else
                    hasDot = true;
            }
            return true;
        }

        bool ParserUtils::isTokenAName(Token const &t) {
            auto data = t.getData();

            for (unsigned i = 0, len = data.length(); i < len; ++i) {
                auto chr = data.at(i);

                if (i == 0)
                    if (isdigit(chr))
                        return false;

            }

            return true;
        }

        std::u8string ParserUtils::format(std::vector<Token> vec, bool print_lines) {
            std::u8string buff;
            size_t line = -1;

            for (Token const &t : vec) {
                if (line != -1) {
                    if (t.getLine() > line)
                        buff += u8'\n';
                    else
                        buff += u8' ';
                }

                if (print_lines && line != t.getLine()) {
                    buff += t.getLine();
                    buff += u8" | ";
                }

                buff += t.getData();

                line = t.getLine();
            }

            return buff;
        }

    }
}
