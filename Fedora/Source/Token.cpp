#include <Token.h>

namespace fedora {

    Token::Token(std::wstring data, uint32_t line): 
        data(std::move(data)), 
        line(line)
    {}

    Token::Token(std::wstring data):
        Token(data, 0)
    {}

    std::wstring Token::getData() const {
        return data;
    }

    uint32_t Token::getLine() const {
        return line;
    }

    bool Token::isChar() const {
        return data.length() == 1;
    }

    bool Token::isChar(wchar_t wchr) const {
        return isChar() && wchr == data.at(0);
    }

    bool operator==(Token const& lhs, Token const& rhs) {
        return lhs.data == rhs.data;
    }

}
