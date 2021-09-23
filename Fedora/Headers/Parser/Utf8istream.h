#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <filesystem>

#include "Exceptions/ParserException.h"

namespace fedora::parser {
    class Utf8istream {
    public:
        using Symbol = std::u8string;
    protected:
        std::unique_ptr<std::istream> in; 
    private:
        explicit Utf8istream(std::unique_ptr<std::istream>);
    public:
        static Utf8istream fromString(std::u8string);
        static Utf8istream fromFile(std::filesystem::path);
        static Utf8istream fromStream(std::unique_ptr<std::istream>);
    
        Symbol get();
        Symbol peek();
        bool eof();
        bool good();
    protected:
        /// Количество байт в символе, ибо char8_t может являться лишь частью символа
        static size_t amountOfBytesInCharsSequence(char8_t chr);

    };
}
