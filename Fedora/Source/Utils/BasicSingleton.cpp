//
// Created on 31.07.2021.
//

#include "Utils/BasicSingleton.h"
#include "Utils/SingletonsCleaner.h"

namespace fedora{
    namespace Utils{
//        void BasicSingleton::addToCleaner() {
//            //SingletonsCleaner * settings = fedora::Settings::GetInstance();
//        }
    }
    /// Initializing
    //BasicSingleton *BasicSingleton::instance = nullptr;

//    BasicSingleton *BasicSingleton::GetInstance() {
//        if (instance == nullptr) {
//            instance = new BasicSingleton();
//        }
//        return instance;
//    }

    void BasicSingleton::addToCleaner() {
        Utils::SingletonsCleaner* cleaner = Utils::SingletonsCleaner::GetInstance();
        cleaner->addToSingletons(this);
    }
}
