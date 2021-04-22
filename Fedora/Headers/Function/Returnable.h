#pragma once

namespace fedora {
namespace function {

    class Returnable {
    public:
        virtual fedora::types::BasicType get() = 0;
    private:

    };
}
}