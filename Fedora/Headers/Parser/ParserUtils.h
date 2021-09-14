#pragma once

#include <string>
#include <vector>

#include "Token.h"

namespace fedora {

    namespace parser {
        class ParserUtils {
        public:
            static const std::u8string ignoredSymbols;
            static const std::u8string delimiterSymbols;
            static const std::u8string functionDeclaration;
            static const std::u8string functionContextDeclaration;
            static const std::u8string forceCall;
            static const std::u8string null;

            /// Является ли символ разделителем между токенами
            static bool isDelimiter(char8_t wchr);

            /// Является ли символ пробельным
            static bool isIgnored(char8_t wchr);

            /// Является ли символ -- символом перевода строки?
            static bool isNewLine(char8_t wchr);

            /// Является ли символ -- кавычкой "?
            static bool isQuote(char8_t wchr);

            /// Является ли символ -- символом комментария[#]?
            static bool isComment(char8_t wchr);

            static bool isTokenANumber(Token const &t);

            static bool isTokenAName(Token const &t);

            static bool isTokenNull(Token const &t);

            static bool isTokenAListOpen(Token const &t);

            static bool isTokenAListClose(Token const &t);

            static bool isTokenAFunctionDeclaration(Token const &t);

            static bool isTokenAFunctionContextDeclaration(Token const &t);

            static bool isTokenAFunctionReturnableDeclaration(Token const &t);

            static bool isTokenACallOpen(Token const &t);

            static bool isTokenACallClose(Token const &t);

            static bool isTokenAForceCall(Token const &t);

            static std::u8string format(std::vector<Token>, bool print_lines = false);
        };
    }
}
