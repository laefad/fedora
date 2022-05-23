#pragma once

namespace fedora::parser {
    /// TODO дать адекватные описания
    enum TokenType {
        Empty, // parser only type
        Comment, // parser only type
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
