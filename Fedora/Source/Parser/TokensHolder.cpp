
#include "Parser/TokensHolder.h"

#include <algorithm>

namespace fedora {
    namespace parser {
        TokensHolder::TokensHolder():
            tokens(std::vector<Token>())
        {}

        //TODO а корректно использовать ссылку константную ??? 
        void TokensHolder::add(const Token &a) {
            tokens.push_back(a);
        }

        std::vector<Token> &TokensHolder::getData() {
            return tokens;
        }

        size_t TokensHolder::size() {
            return tokens.size();
        }

        std::vector<Token> TokensHolder::getLines(size_t line, size_t lines_range = 2) {

            // get [t-2;t+2] lines
            auto is_lineX = [line, lines_range](Token const& t){
                auto b = t.getLine(); 
                auto abs = line > b ? line - b : b - line;
                return abs <= lines_range; 
            };

            // По линиям токены отсортированы! иожно было бы искать бинарно опорный элемент

            // Находим первый удовлетворяющий элемент
            auto start = std::find_if(tokens.begin(), tokens.end(), is_lineX);
            // Находим последний удовлетворяющий элемент
            auto end = std::find_if_not(start, tokens.end(), is_lineX);

            std::vector<Token> to_vector;
            std::copy(start, end, std::back_inserter(to_vector));

            return to_vector;
        }

    }
}

