
#include "Parser/TokensHolder.h"

namespace fedora {
    namespace parser {
        TokensHolder::TokensHolder() {}

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

        // std::vector<Token> TokensHolder::getLast() {
        //     // if (tokens.size() <= lastNum)
        //     //     return tokens;
        //     // else {
        //     //     std::vector<Token> res = std::vector<Token>();
        //     //     for (size_t i = tokens.size() - lastNum; i < tokens.size(); ++i)
        //     //         res.push_back(tokens[i]);
        //     //     return res;
        //     // }

        // }
    }
}

