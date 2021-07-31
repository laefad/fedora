//
// Created on 31.07.2021.
//

#pragma once
#include "Utils/SettingsSingleton.h"
#include "Utils/TokensHolder.h"

namespace fedora{
    namespace Utils{
        /**
         * Clean singletons by their pointers
         *
         * @brief
         * Utility to save us from memory leak
         *
         * @note
         * We need to update [cleanThemAll] method every time we add new global singleton
         *
         */
        class SingletonsCleaner{
        public:
            static void cleanThemAll();
        };

        void SingletonsCleaner::cleanThemAll() {
            // TODO Можем ли мы наследовать все синглтоны от одного предка, добавлять их в массив синглтон клинера в их конструкторах, а здесь только очищать, проходя по массиву?

            // Init settings singleton
            fedora::Settings * settings = fedora::Settings::GetInstance();
            // clean it
            delete settings;

            // Init tokens singleton
            fedora::TokensHolder * a = fedora::TokensHolder::GetInstance();
            // clean it
            delete a;
        }
    }
}
