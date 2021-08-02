//
// Created  on 31.07.2021.
//

#pragma once

namespace fedora {
    /**
     * Use this class to make singleton auto-deletable
     *
     * @example @code
     * class MySingleton : public BasicSingleton {
     *     private:
     *     MySingleton() = default;
     *
     *     /// Main instance
     *     static MySingleton *instance;
     *
     *     public:
     *     /// Singleton instance getter
     *     static MySingleton *GetInstance();
     * }
     *
     * /// Simple instance getter
     * MySingleton *MySingleton::GetInstance() {
     *      if (instance == nullptr) {
     *          instance = new MySingleton();
     *          instance->addToCleaner();           // <- Here we add our new instance to cleaner
     *      }
     *      return instance;
     * }
     */
    class BasicSingleton {
    protected:
        /// Here we need a protected constructor, so derived classes will be able to create instances
        BasicSingleton() = default;

    public:
        /// Singleton can't be copied
        BasicSingleton(BasicSingleton &other) = delete;

        /// Singletons should not be assignable.
        void operator=(const BasicSingleton &) = delete;

        // TODO Хорошо бы в бейсик впихнуть getInstance()

        /**
         * Add current instance to cleaner.
         *
         * @brief
         * This instance will be deleted when @see SingletonsCleaner will execute clean method
         */
        void addToCleaner();
    };
}