#pragma once

#include <string>

#include "Token.h"

namespace fedora {
    /// Токен, который мы прочитали и будем анализировать
    /// В классе можно сохранять контекст распрашеного токена для анализа
    class Token {
    private:

        /// Содержимое токена
        std::wstring data;
        /// Номер строки, на которой был расположен токен
        uint32_t line;

    public:

        explicit Token(std::wstring data, uint32_t line);

        explicit Token(std::wstring data);

        // TODO Корректно ли возвращать референс, а не саму строку, чтобы получить буст производительности?
        // Но сделай тогда его неизменяемым(если я правильно const понимаю): std::wstring const & 
        // Иначе сейчас можно менять содержимое по ссылке
        // UPD. Сделал конст
        std::wstring const &getData() const;

        /// Возвращает номер строки, на которой был расположн токен
        uint32_t getLine() const;

        /// Если токен состоит из 1 символа, то возвращает true
        bool isChar() const;


        /// Если токен состоит из 1 символа и этот символ равен wchar, то возвращает true
        bool isChar(wchar_t wchr) const;

        friend bool operator==(Token const &lhs, Token const &rhs);
    };
}
