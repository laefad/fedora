#include <algorithm>
#include <iterator>

#include "Parser/TokensHolder.h"

namespace fedora::parser {
    TokensHolder::TokensHolder() :
        tokens(std::vector<Token>()) {}

    // TODO а корректно использовать ссылку константную ??? 
    void TokensHolder::add(const Token& a) {
        tokens.push_back(a);
    }

    size_t TokensHolder::size() {
        return tokens.size();
    }

    std::vector<Token> TokensHolder::getLines(size_t line, size_t range) {

        // get [line-range;line+range] lines
        auto is_lineX = [line, range](Token const& t) {
            auto b = t.getLine();
            auto abs = line > b ? line - b : b - line;
            return abs <= range;
        };

        // По линиям токены отсортированы! можно было бы искать бинарно опорный элемент

        // Находим первый удовлетворяющий элемент
        auto start = std::find_if(tokens.begin(), tokens.end(), is_lineX);
        // Находим последний удовлетворяющий элемент
        auto end = std::find_if_not(start, tokens.end(), is_lineX);

        std::vector<Token> to_vector;
        std::copy(start, end, std::back_inserter(to_vector));

        return to_vector;
    }
}
