#pragma once

#include <string>
#include <memory>

namespace fedora {
    namespace types {

        enum Type { // TODO Перенести это в BasicType!!!!!!!!!!!
            NUMBER,
            STRING,
            LIST,
            FUN_CALL,
            NULL_,
        };

        class BasicType : public std::enable_shared_from_this<BasicType> {
        public:
            // Преобразование в строку
            virtual std::wstring eval() = 0;

            virtual Type type() = 0;
        };

    }
}
