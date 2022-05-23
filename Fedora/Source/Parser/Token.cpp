#include <string>

#include "Parser/Token.h"

namespace fedora::parser {
    Token::Token(std::u8string data, size_t line, TokenType tokenType) :
        data(std::move(data)),
        line(line),
        tokenType(tokenType) {}

    Token::Token(std::u8string data, TokenType tokenType) :
        Token(data, 0, tokenType) {}

    Token::Token(std::u8string data, size_t line) :
        Token(data, line, TokenType::None) {}

    Token::Token(std::u8string data) :
        Token(data, 0, TokenType::None) {}

    std::u8string const& Token::getData() const {
        return data;
    }

    size_t Token::getLine() const {
        return line;
    }

    TokenType Token::getType() const {
        return tokenType;
    }

    void Token::setType(TokenType type) {
        tokenType = type;
    }

    /// TODO add tokenType comparsion
    bool operator==(Token const& lhs, Token const& rhs) {
        return lhs.data == rhs.data;
    }
}
