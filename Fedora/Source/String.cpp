#include "String.h"
namespace fedora {
    namespace types {

        std::wstring String::eval() {
            return L'\"' + this->value + L'\"';
        };

    }
}