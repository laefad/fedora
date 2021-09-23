#pragma once

#include <string>
#include <vector>
#include <map>

#include "Token.h"
#include "TokenPriority.h"

namespace fedora {

    namespace parser {
        class ParserUtils {
        public:

            static const std::vector<std::tuple<TokenPriority, std::u8string, TokenType>> tokenMaping;

            /// Вернуть тип токена, исходя из его содержимого.
            /// Текущий тип токена не влияет на определение.
            static TokenType determineTokenType(const Token &t);

            /// Является ли символ разделителем между токенами
            static bool isDelimiter(const std::u8string &u8str);

            /// Является ли символ пробельным
            static bool isIgnored(const std::u8string &u8str);

            /// Является ли символ -- символом перевода строки?
            static bool isNewLine(const std::u8string &u8str);

            /// Является ли символ -- кавычкой ["]?
            static bool isQuote(const std::u8string &u8str);

            /// Является ли символ -- символом комментария[#]?
            static bool isComment(const std::u8string &u8str);

            /// Является ли символ -- числом [+-][0-9]+([.]{1}[0-9]+){0,1}
            static bool isTokenANumber(Token const &t);

            /// Является ли токен -- именем
            static bool isTokenAName(Token const &t);

            /// Форматирует вектор Токенов в код, с указанием линий [print_lines == true]
            static std::u8string format(std::vector<Token>, bool print_lines = false);
        };
    }
}
