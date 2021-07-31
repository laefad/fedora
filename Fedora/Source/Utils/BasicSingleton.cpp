//
// Created on 31.07.2021.
//

#include "Utils/BasicSingleton.h"
#include "Utils/SingletonsCleaner.h"

namespace fedora {
    void BasicSingleton::addToCleaner() {
        Utils::SingletonsCleaner *cleaner = Utils::SingletonsCleaner::GetInstance();
        cleaner->addToSingletons(this);
    }
}
