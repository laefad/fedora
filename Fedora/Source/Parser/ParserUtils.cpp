
#include "Parser/ParserUtils.h"

namespace fedora {

    namespace parser {

        const std::wstring ParserUtils::ignoredSymbols = L"\n\t\r \377";
        const std::wstring ParserUtils::delimiterSymbols = L"()[]=";
        const std::wstring ParserUtils::functionDeclaration = L"let";
        const std::wstring ParserUtils::functionContextDeclaration = L"where";
        const std::wstring ParserUtils::forceCall = L"force";
        const std::wstring ParserUtils::null = L"null";

        bool ParserUtils::isDelimiter(wchar_t tmp) {
            return ParserUtils::delimiterSymbols.find(tmp) != std::wstring::npos;
        }

        bool ParserUtils::isNewLine(wchar_t tmp) {
            return tmp == L'\n';
        }

        bool ParserUtils::isQuote(wchar_t tmp) {
            return tmp == L'\"';
        }

        bool ParserUtils::isComment(wchar_t tmp) {
            return tmp == L'#';
        }

        bool ParserUtils::isIgnored(wchar_t tmp) {
            return ParserUtils::ignoredSymbols.find(tmp) != std::wstring::npos;
        }

        bool ParserUtils::isTokenANumber(Token const& t) {
            auto data = t.getData();
            bool hasDot = false;

            for (unsigned i = 0, len = data.length(); i < len; ++i) {
                auto chr = data.at(i);

                if (isdigit(chr))
                    continue;

                if (chr != L'.') {
                    if (i != 0 || (chr != L'+' && chr != L'-'))
                        return false;
                } else if (hasDot || i == 0 || i == len - 1)
                    return false;
                else
                    hasDot = true;
            }
            return true;
        }

        bool ParserUtils::isTokenAName(Token const& t) {
            return
                !isTokenANumber(t) &&
                !isTokenAListOpen(t) &&
                !isTokenAListClose(t) &&
                !isTokenAFunctionDeclaration(t) &&
                !isTokenAFunctionContextDeclaration(t) &&
                !isTokenAFunctionReturnableDeclaration(t) &&
                !isTokenACallOpen(t) &&
                !isTokenACallClose(t) &&
                !isTokenAForceCall(t);
        }

        bool ParserUtils::isTokenAListOpen(Token const& t) {
            return t.isChar(L'[');
        }

        bool ParserUtils::isTokenAListClose(Token const& t) {
            return t.isChar(L']');
        }

        bool ParserUtils::isTokenAFunctionDeclaration(Token const& t) {
            return t.getData() == functionDeclaration;
        }

        bool ParserUtils::isTokenAFunctionContextDeclaration(Token const& t) {
            return t.getData() == functionContextDeclaration;
        }

        bool ParserUtils::isTokenAFunctionReturnableDeclaration(Token const& t) {
            return t.isChar(L'=');
        }

        bool ParserUtils::isTokenACallOpen(Token const& t) {
            return t.isChar(L'(');
        }

        bool ParserUtils::isTokenACallClose(Token const& t) {
            return t.isChar(L')');
        }

        bool ParserUtils::isTokenAForceCall(Token const& t) {
            return t.getData() == forceCall;
        }

        bool ParserUtils::isTokenNull(const Token &t) {
            return t.getData() == null;
        }

        std::wstring ParserUtils::format(std::vector<Token> vec, bool print_lines) {
            std::wstring buff;
            size_t line = -1;

            for (Token const& t : vec) {
                if (line != -1) {
                    if (t.getLine() > line)
                        buff += L'\n';
                    else 
                        buff += L' ';
                }

                if (print_lines && line != t.getLine()) {
                    buff += t.getLine();
                    buff += L" | ";
                }

                buff += t.getData();

                line = t.getLine();
            }

            return buff;
        }

    }
}
