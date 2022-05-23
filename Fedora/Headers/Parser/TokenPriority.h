#pragma once

namespace fedora::parser {
    enum TokenPriority {
        Whitespace,
        Common,
        KeyWord,
        Delimeter
    };
}
