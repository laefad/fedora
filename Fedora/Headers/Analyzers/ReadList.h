
#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        namespace readList {
            enum readMode {
                /// @example main([1 2 3])
                READ_FUNCTION_ARG,

                /// @example let main = [1 2 3]
                READ_FUNCTION_RETURN
            };
        }

        /**
         * Прочитать ключевые слова при объявлении функции
         */
        class ReadList : public AnalyticBasic {
        private:
            readList::readMode mode;
        public:
            explicit ReadList(std::vector<Token>, readList::readMode);
            explicit ReadList(std::vector<Token>);


            /// Определение родительского метода анализа токена
            /// @brief По факту является фабричным методом
            std::shared_ptr<AnalyticBasic> analyzeToken(Token const&) override;

            /// Определение метода получения файла
            std::string getFileName() override;

            /// Вернуть указатель на экземпляр класса для следующего этапа
            std::shared_ptr<AnalyticBasic> chooseReturn(Token const&);

        };
    }
}
