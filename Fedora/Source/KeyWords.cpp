//
// Created on 24.07.2021.
//

#include "KeyWords.h"

namespace fedora {
    // TODO OPTIMIZATION. Можно передавать ссылку на vector, а не его копию
    std::vector<KeyWord> KeyWords::getPreFunKeyWords() {
        std::vector<KeyWord> res = std::vector<KeyWord>();
        res.push_back(pure);
        res.push_back(force);
        return res;
    }

    // TODO OPTIMIZATION. Можно передавать ссылку на vector, а не его копию
    std::vector<KeyWord> KeyWords::getAllKeyWords() {
        std::vector<KeyWord> res = std::vector<KeyWord>();
        res.push_back(pure);
        res.push_back(force);
        res.push_back(let);
        res.push_back(where);
        res.push_back(returns);
        res.push_back(import);
        res.push_back(using_);
        return res;
    }

    bool operator==(Token &lhs, KeyWord &rhs) {
        return lhs.getData() == rhs.getData() || (lhs.isEmpty && rhs.isEmpty);
    }

    bool operator==(KeyWord &lhs, Token &rhs) {
        return lhs.getData() == rhs.getData() || (lhs.isEmpty && rhs.isEmpty);
    }

    bool operator==(KeyWord &lhs, KeyWord &rhs) {
        return lhs.getData() == rhs.getData() || (lhs.isEmpty && rhs.isEmpty);
    }
}
