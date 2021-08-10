//
// Created on 24.07.2021.
//
#pragma once

#include "FException.h"
#include "StaticUtils.h"

namespace fedora {

    // TODO Сделать наследование от FException
    class AnalyzerException {

        // static std::string addTokens(const std::string &t) {
        //     fedora::TokensHolder *a = fedora::TokensHolder::GetInstance();
        //     std::string tokens;
        //     // TODO Заменить на for i и перед первым не ставить пробел
        //     for (auto &token:a->getLast()) {
        //         if (!token.isEmpty()) {
        //             tokens += " ";
        //         }
        //         tokens += StaticUtils::ws2s(token.getData());
        //     }
        //     // TODO Мы можем показывать кол-во последних токенов в сообщении об ошибке в той части, где мы показываем токены. Кол-во токенов = min(fedora::TokensHolder::lastNum - кол-во пустых токенов, tokensHolder->getLast().length)
        //     //std::string num = std::to_string(fedora::TokensHolder::lastNum);
        //     return t+"\n\nLast "+" tokens:\n"+tokens;
        // }

    public:
        AnalyzerException(const std::string& msg, const std::string& file_, const std::string& func_) {
            std::string text = "AnalyzerException\n\tFile: "+file_+"\n\tFunc: "+func_+"\n\tError: "+msg;
            throw FException(text);
        }

        AnalyzerException(const std::wstring& msg, const std::string& file_, const std::string& func_) {
            std::string text = "AnalyzerException\n\tFile: "+file_+"\n\tFunc: "+func_+"\n\tError: "+StaticUtils::ws2s(msg);
            throw FException(text);
        }
    };
}
