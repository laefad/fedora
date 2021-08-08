#include <Token.h>

namespace fedora {

    Token::Token(std::wstring data) 
        : data(std::move(data)) 
    {}

    std::wstring & Token::getData() {
        return data;
    }

    bool operator==(Token & lhs, Token & rhs) {
        return lhs.data == rhs.data || (lhs.isEmpty() && rhs.isEmpty());
    }

    // Токен пуст, если пусты данные в нем 
    // [или это перенос строки] 
    // [или это не пойми что]
    bool Token::isEmpty() const {
        return data.empty() 
            || data.length() == 1 && data[0] == L'\n' // TODO читать нормально \n и убрать отсюда
            || data.at(0) < 0; // а это что за дикость ??
    }
}