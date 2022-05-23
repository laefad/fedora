#pragma once

#include <memory>
#include <vector>

#include "Parser/Token.h"
#include "Utils/SettingsSingleton.h"
#include "Builder/ContextBuilder.h"

namespace fedora::analytic {
    /// Базовый класс анализатора токена
    class AnalyticBasic : public std::enable_shared_from_this<AnalyticBasic> {
    protected:
        /// Бросить ошибку в случае ошибки синтаксиса
        void throwException(std::u8string msg, std::u8string funcName);

        /// Log something as u8string
        static void log(const std::u8string& msg, fedora::settings::LogLevel level);

    public:
        AnalyticBasic() = default;

        /// Проанализировать прочитаный токен
        virtual std::shared_ptr<AnalyticBasic> analyzeToken(parser::Token const&, ContextBuilder&) = 0;

        /// Получить имя файла с кодом. Используется для вывода сообщения об ошибке
        virtual std::u8string getClassFileName() = 0;
    };
}
