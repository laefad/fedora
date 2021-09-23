
#include <fstream>
#include <sstream>

#include "Parser/Utf8istream.h"
#include "Exceptions/ParserException.h"

#include "Utils/Logger.h"

namespace fedora::parser {

    Utf8istream::Utf8istream(std::unique_ptr<std::istream> in):
        in(std::move(in))
    {}

    Utf8istream Utf8istream::fromString(std::u8string str) {
        return Utf8istream(std::make_unique<std::stringstream>(StaticUtils::u8s2s(str)));
    }

    Utf8istream Utf8istream::fromFile(std::filesystem::path path) {
        auto in = std::make_unique<std::ifstream>(path);

        if (!in->good())
            throw ParserException(u8"Parser::makeFileParser - file [" + path.u8string() + u8"] doesn't exist.");

        return Utf8istream(std::move(in));
    }

    Utf8istream Utf8istream::fromStream(std::unique_ptr<std::istream> in) {
        Logger::logW(u8"Parser::makeStreamParser may cause errors. Don't use it.");
        return Utf8istream(std::move(in));
    }

    size_t Utf8istream::amountOfBytesInCharsSequence(char8_t chr) {
        /// check 0xxxxxxx - 1 byte char
        if ((chr & 0b1000'0000) == 0b0000'0000) {
            return 1;
        /// check 110xxxx - 2 byte char
        } else if ((chr & 0b1110'0000) == 0b1100'0000) {
            return 2;
        /// check 1110xxxx - 3 byte char
        } else if ((chr & 0b1111'0000) == 0b1110'0000) {
            return 3;
        /// check 11110xxx - 4 byte char
        } else if ((chr & 0b1111'1000) == 0b1111'0000) {
            return 4;
        } else {
            throw new ParserException(u8"Utf8istream::amountOfBytesInCharsSequence bad byte.");
        }
    }

    bool Utf8istream::good() {
        // TODO нужны ли тут какие еще проверки, почитать про good 
        return in->good();
    }

    bool Utf8istream::eof() {
        // TODO нужны ли тут какие еще проверки, почитать про eof 
        return in->eof();
    }

    // TODO !important PEEK DOESN't WORK CORRECT
    Utf8istream::Symbol Utf8istream::peek() {
        // TODO add eof check
        // auto buff = in->rdbuf();
        // char8_t currentByte = buff->sgetc();
        // // TODO check byte ??

        // auto size = amountOfBytesInCharsSequence(currentByte);
        // Logger::logV(u8"Peek size = " + StaticUtils::i2u8s(size));
        // auto temp = new char [size];
        // auto result = buff->sgetn(temp, size);

        // if (result != size)
        //     throw new ParserException(u8"Utf8istream::peek buff->sgetn failed.");
        // else
        //     buff->sputn(temp, size);
        //     //buff->gbump(-size);
        
        // return StaticUtils::s2u8s(temp);

        return std::u8string() + ((char8_t)in->peek());
    }

    Utf8istream::Symbol Utf8istream::get() {
        std::u8string res;
        size_t bytesInChar = 0;
        char8_t tmp;

        while (true) {
            tmp = in->get();

            if (in->eof())
                if (res.empty())
                    return u8"";

            // TODO try catch ?
            if (bytesInChar == 0) {
                bytesInChar = amountOfBytesInCharsSequence(tmp);
            }

            res += tmp;

            if (res.length() == bytesInChar)
                return res;
        }
    }
}
