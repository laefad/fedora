#pragma once

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include "Context.h"

namespace fedora {
    class Parser {
    private:
        std::ifstream& fin;
        void readToken();

        void analyzeToken();

    public:
        Parser(const std::string &fileName, std::ifstream &fin);

        void readFile();

        // Деструкт
        ~Parser() {
            fin.close();
        }
    };
}
