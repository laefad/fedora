//
// Created on 21.07.2021.
//

#pragma once

#include "Utils/TokensHolder.h"
#include "StaticUtils.h"

namespace fedora {
    class FException : public std::exception {
    private:
        std::string addTokens(const std::string t) const {
            fedora::TokensHolder* a = fedora::TokensHolder::GetInstance();
            std::string tokens;
            // TODO Заменить на for i и перед первым не ставить пробел
            for (auto& token:a->getLast()){
                if (!token.isEmpty){
                    tokens += " ";
                }
                tokens +=  StaticUtils::ws2s(token.data);
            }
            // TODO Мы можем показывать кол-во последних токенов в сообщении об ошибке в той части, где мы показываем токены. Кол-во токенов = min(fedora::TokensHolder::lastNum - кол-во пустых токенов, tokensHolder->getLast().length)
            //std::string num = std::to_string(fedora::TokensHolder::lastNum);
            return t+"\n\nLast "+" tokens:\n"+tokens;
        }
    protected:
        std::string text;
    public:
        explicit FException(const std::wstring& ss) noexcept(false){
            text = addTokens(StaticUtils::ws2s(ss));
        }

        explicit FException(std::string ss) noexcept(false) : text(addTokens(std::move(ss))){}

        ~FException() noexcept override = default;
        // TODO Заменить text в этой переменной на функцию, которая будет переопределяться в child классах
        const char *what() const noexcept override { return text.c_str(); }
    };
}
