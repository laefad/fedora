//
// Created on 28.07.2021.
//

#include "Utils/TokensHolder.h"

namespace fedora{
    /// Initialization
    TokensHolder *TokensHolder::singleton_ = nullptr;

    TokensHolder *TokensHolder::GetInstance() {
        if (singleton_ == nullptr) {
            singleton_ = new TokensHolder();
        }
        return singleton_;
    }

    void TokensHolder::add(const Token &a) {
        // TODO Мб стоит очищать массив и убирать лишние токены?
        tokens.push_back(a);
    }

    std::vector<Token> TokensHolder::getLast() {
        if (tokens.size() <= lastNum)
            return tokens;
        else {
            std::vector<Token> res = std::vector<Token>();
            for (size_t i=tokens.size()-lastNum;i<tokens.size();++i)
                res.push_back(tokens[i]);
            return res;
        }

    }
}

