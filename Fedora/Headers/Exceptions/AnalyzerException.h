//
// Created on 24.07.2021.
//
#pragma once

#include "FException.h"
#include "StaticUtils.h"

namespace fedora {

    class AnalyzerException {

    public:
        AnalyzerException(const std::string& msg, const std::string& file_, const std::string& func_) {
            std::string text = "AnalyzerException\n\tFile: "+file_+"\n\tFunc: "+func_+"\n\tError: "+msg;
            throw FException(text);
        }

        AnalyzerException(const std::wstring& msg, const std::string& file_, const std::string& func_) {
            std::string text = "AnalyzerException\n\tFile: "+file_+"\n\tFunc: "+func_+"\n\tError: "+StaticUtils::ws2s(msg);
            throw FException(text);
        }
    };
}
