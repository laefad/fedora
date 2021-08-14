#pragma once

#include <memory>
#include <vector>

#include "Token.h"
#include "Utils/SettingsSingleton.h"
#include "Builder/ContextBuilder.h"

namespace fedora {
    namespace analytic {
        /// Базовый класс анализатора токена
        class AnalyticBasic : public std::enable_shared_from_this<AnalyticBasic> {
        protected:
            /// Бросить ошибку в случае ошибки синтаксиса
            void throwException(const std::wstring &msg, const std::string &funcName);

            /// Log something as string
            static void log(const std::string &msg, fedora::settings::LogLevel level);

            /// @overload log for wstring
            static void log(const std::wstring &msg, fedora::settings::LogLevel level);

        public:
            AnalyticBasic() = default;

            /// Проанализировать прочитаный токен
            virtual std::shared_ptr<AnalyticBasic> analyzeToken(Token const &, ContextBuilder &) = 0;

            /// Получить имя файла с кодом. Используется для вывода сообщения об ошибке
            virtual std::string getClassFileName() = 0;
        };
    }
}
