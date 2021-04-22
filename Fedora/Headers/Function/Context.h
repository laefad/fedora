#pragma once
#include "Function.h"
#include <map>
#include <string>
#include <memory>

namespace fedora {
namespace function {

    class Contex {
    public: 
        std::shared_ptr<Function> get(std::wstring wname) {
            auto res = functions.find(wname);
            return res == functions.end() ? std::shared_ptr<Function>(nullptr) : res->second;
        }
    private:
        std::map<std::wstring, std::shared_ptr<Function>> functions;
        std::shared_ptr<Contex> parent;
    };

}
}
