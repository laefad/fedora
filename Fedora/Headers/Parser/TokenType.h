#pragma once

namespace fedora {
    namespace parser {
        /// TODO дать адекватные описания
        enum TokenType {
            None,
            String, // "wchar*"
            Number, // [-+]?[0-9]+.?[0-9]+
            Name, // any wchar seq without [,],),(,= chars and 0-9 in beginnig, and also not keyword
            ListOpen, // [
            ListClose, // ]
            FunctionDeclaration, // let
            FunctionContextDeclaration, // where
            FunctionReturnableDeclaration, // =
            CallOpen, // (
            CallClose, // )
            ForceCall, // force
            Null, // null
        };
    }
}

