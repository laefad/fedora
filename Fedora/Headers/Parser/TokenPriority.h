#pragma once

namespace fedora {
    namespace parser {
        enum TokenPriority {
            Whitespace,
            Common,
            KeyWord,
            Delimeter
        };
    }
}