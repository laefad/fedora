
#include <Parser/Token.h>

namespace fedora {
    namespace parser { 
        Token::Token(std::wstring data, uint32_t line, TokenType tokenType):
            data(std::move(data)),
            line(line),
            tokenType(tokenType)
        {}

        Token::Token(std::wstring data, TokenType tokenType):
            Token(data, 0, tokenType)
        {}

        Token::Token(std::wstring data, uint32_t line):
            Token(data, line, TokenType::None)
        {}

        Token::Token(std::wstring data):
            Token(data, 0, TokenType::None)
        {}

        std::wstring const &Token::getData() const {
            return data;
        }

        uint32_t Token::getLine() const {
            return line;
        }

        TokenType Token::getType() const {
            return tokenType;
        }

        void Token::setType(TokenType type) {
            tokenType = type;
        }

        bool Token::isChar() const {
            return data.length() == 1;
        }

        bool Token::isChar(wchar_t wchr) const {
            return isChar() && wchr == data.at(0);
        }

        /// TODO add tokenType comparsion
        bool operator==(Token const &lhs, Token const &rhs) {
            return lhs.data == rhs.data;
        }
    }
}
