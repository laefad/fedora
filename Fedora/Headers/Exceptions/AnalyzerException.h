//
// Created on 24.07.2021.
//
#pragma once

#include "FException.h"

namespace fedora {

    class AnalyzerException {

    public:
        AnalyzerException(std::string& msg, std::string& file_, std::string& func_) {
            std::string text = "AnalyzerException\n\tFile: "+file_+"\n\tFunc: "+func_+"\n\tError: "+msg;
            throw FException(text);
        }

        AnalyzerException(const std::wstring& msg, const std::wstring& file_, const std::wstring& func_) {
            std::wstring text = L"AnalyzerException\n\tFile: "+file_+L"\n\tFunc: "+func_+L"\n\tError: "+msg;
            throw FException(text);
        }
    };
}
