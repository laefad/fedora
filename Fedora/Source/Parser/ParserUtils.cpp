
#include "Parser/ParserUtils.h"

namespace fedora {

    namespace parser {

        const std::u8string ParserUtils::ignoredSymbols = u8"\n\t\r \377";
        const std::u8string ParserUtils::delimiterSymbols = u8"()[]=";
        const std::u8string ParserUtils::functionDeclaration = u8"let";
        const std::u8string ParserUtils::functionContextDeclaration = u8"where";
        const std::u8string ParserUtils::forceCall = u8"force";
        const std::u8string ParserUtils::null = u8"null";

        bool ParserUtils::isDelimiter(char8_t tmp) {
            return ParserUtils::delimiterSymbols.find(tmp) != std::u8string::npos;
        }

        bool ParserUtils::isNewLine(char8_t tmp) {
            return tmp == u8'\n';
        }

        bool ParserUtils::isQuote(char8_t tmp) {
            return tmp == u8'\"';
        }

        bool ParserUtils::isComment(char8_t tmp) {
            return tmp == u8'#';
        }

        bool ParserUtils::isIgnored(char8_t tmp) {
            return ParserUtils::ignoredSymbols.find(tmp) != std::u8string::npos;
        }

        bool ParserUtils::isTokenANumber(Token const &t) {
            auto data = t.getData();
            bool hasDot = false;

            for (unsigned i = 0, len = data.length(); i < len; ++i) {
                auto chr = data.at(i);

                if (isdigit(chr))
                    continue;

                if (chr != u8'.') {
                    if (i != 0 || (chr != u8'+' && chr != u8'-'))
                        return false;
                } else if (hasDot || i == 0 || i == len - 1)
                    return false;
                else
                    hasDot = true;
            }
            return true;
        }

        bool ParserUtils::isTokenAName(Token const &t) {
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

        bool ParserUtils::isTokenAListOpen(Token const &t) {
            return t.isChar(u8'[');
        }

        bool ParserUtils::isTokenAListClose(Token const &t) {
            return t.isChar(u8']');
        }

        bool ParserUtils::isTokenAFunctionDeclaration(Token const &t) {
            return t.getData() == functionDeclaration;
        }

        bool ParserUtils::isTokenAFunctionContextDeclaration(Token const &t) {
            return t.getData() == functionContextDeclaration;
        }

        bool ParserUtils::isTokenAFunctionReturnableDeclaration(Token const &t) {
            return t.isChar(u8'=');
        }

        bool ParserUtils::isTokenACallOpen(Token const &t) {
            return t.isChar(u8'(');
        }

        bool ParserUtils::isTokenACallClose(Token const &t) {
            return t.isChar(u8')');
        }

        bool ParserUtils::isTokenAForceCall(Token const &t) {
            return t.getData() == forceCall;
        }

        bool ParserUtils::isTokenNull(const Token &t) {
            return t.getData() == null;
        }

        std::u8string ParserUtils::format(std::vector<Token> vec, bool print_lines) {
            std::u8string buff;
            size_t line = -1;

            for (Token const &t : vec) {
                if (line != -1) {
                    if (t.getLine() > line)
                        buff += u8'\n';
                    else
                        buff += u8' ';
                }

                if (print_lines && line != t.getLine()) {
                    buff += t.getLine();
                    buff += u8" | ";
                }

                buff += t.getData();

                line = t.getLine();
            }

            return buff;
        }

    }
}
