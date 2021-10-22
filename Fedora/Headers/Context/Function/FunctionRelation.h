#pragma once

namespace fedora::context { 
    /// Определяет тип элемента в контексте
    enum FunctionRelation {
        Any,
        Subling,
        Parent,
        Self,
        Child
    };
}
