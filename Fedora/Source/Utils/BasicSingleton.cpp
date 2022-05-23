#include "Utils/BasicSingleton.h"
#include "Utils/SingletonsCleaner.h"

namespace fedora {
    void BasicSingleton::addToCleaner() {
        Utils::SingletonsCleaner* cleaner = Utils::SingletonsCleaner::GetInstance();
        cleaner->addToSingletons(this);
    }
}
