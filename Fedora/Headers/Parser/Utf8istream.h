#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <filesystem>

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

        /// Возвращает u8"", если достигнут конец потока
        Symbol get();

        /// Возвращает u8"", если достигнут конец потока
        Symbol peek();

        /// Проксирует вызовы настоящего потока [in]
        bool eof();

        /// Проксирует вызовы настоящего потока [in]
        bool good();
    protected:
        /// Количество байт в символе, ибо char8_t может являться лишь частью символа
        static size_t amountOfBytesInCharsSequence(char8_t chr);
    };
}
