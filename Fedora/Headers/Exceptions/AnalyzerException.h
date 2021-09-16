#pragma once

#include "FException.h"

namespace fedora {

    class AnalyzerException : public FException {
    protected:
        std::u8string construct(std::u8string file,
                                std::u8string func, 
                                std::u8string text) const {
            std::u8string buf;

            buf += u8"AnalyzerException";
            buf += u8"\n\tFile: ";
            buf += file;
            buf += u8"\n\tFunc: ";
            buf += func;
            buf += u8"\n\tError: ";
            buf += text;

            return buf;
        }

        // TODO Мы можем показывать кол-во последних токенов в сообщении об ошибке
        // parser::ParserUtils::format(tokensHolder.getLines(3,1))

    public:
        AnalyzerException(std::u8string text, std::u8string file, std::u8string func) :
                FException(std::move(construct(file, func, text)))
        {}
    };
}
