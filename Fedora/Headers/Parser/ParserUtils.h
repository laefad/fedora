#pragma once

#include <string>
#include <vector>

#include "Token.h"

namespace fedora {

    namespace parser {
        class ParserUtils {
        public:
            static const std::wstring ignoredSymbols;
            static const std::wstring delimiterSymbols;
            static const std::wstring functionDeclaration;
            static const std::wstring functionContextDeclaration;
            static const std::wstring forceCall;
            static const std::wstring null;

            /// Является ли символ разделителем между токенами
            static bool isDelimiter(wchar_t wchr);

            /// Является ли символ пробельным
            static bool isIgnored(wchar_t wchr);

            /// Является ли символ -- символом перевода строки?
            static bool isNewLine(wchar_t wchr);

            /// Является ли символ -- кавычкой "?
            static bool isQuote(wchar_t wchr);

            /// Является ли символ -- символом комментария[#]?
            static bool isComment(wchar_t wchr);

            static bool isTokenANumber(Token const& t);
            static bool isTokenAName(Token const& t);
            static bool isTokenNull(Token const& t);
            static bool isTokenAListOpen(Token const& t);
            static bool isTokenAListClose(Token const& t);

            static bool isTokenAFunctionDeclaration(Token const& t);
            static bool isTokenAFunctionContextDeclaration(Token const& t);
            static bool isTokenAFunctionReturnableDeclaration(Token const& t);
            static bool isTokenACallOpen(Token const& t);
            static bool isTokenACallClose(Token const& t);
            static bool isTokenAForceCall(Token const& t);

            static std::wstring format(std::vector<Token>, bool print_lines = false);
        };
    }
}
