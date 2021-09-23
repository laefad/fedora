#pragma once

#include <memory>
#include <vector>
#include <map>

namespace fedora {
    namespace context {
        class Function : public std::enable_shared_from_this<Function> {
        public:
            using Context = std::map<std::u8string, std::shared_ptr<Function>>;
        protected:
            std::shared_ptr<Function> parent;
            std::u8string name = u8"";
        public:
            explicit Function(std::shared_ptr<Function> parent, std::u8string name) : 
                parent(std::move(parent)),
                name(std::move(name))
            {}

            std::u8string getName() const {
                return name;
            }

            // По умолчанию возвращаем пустой контекст
            virtual const std::shared_ptr<Context> getContext() const {
                return nullptr;
            }

            // TODO add realization
            virtual std::shared_ptr<Function> find(std::u8string name) {
                return nullptr;
            }
        };
    }
}