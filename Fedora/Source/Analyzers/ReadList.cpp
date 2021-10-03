
#include "Analyzers/ReadList.h"
#include "Analyzers/ReadFunArgs.h"
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadAfterListEnd.h"

namespace fedora {
    namespace analytic {

        /**
         *
         * @example case 1: Add number in list
         * [ ... 1 ... ]
         *
         * @example case 2: Add string in list
         * [ ... "lol" ... ]
         *
         * @example case 3: Add list in list
         * [ ... [ ... ] ... ]
         *
         * @example case 4: Add function in list
         * [ ... main... ]
         *
         * @example case 5: Add forceCall in list
         * [ ... force main... ]
         *
         * @example case 6: List finish
         * ... ]
         */
        std::shared_ptr<AnalyticBasic> ReadList::analyzeToken(parser::Token const &t, ContextBuilder &b) {
            using fedora::parser::TokenType;
            log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            if (t.getType() == TokenType::Number) {
                // if number
                b.addSimpleTypeInList(t);
                return shared_from_this();
            } else if (t.getType() == TokenType::String) {
                // if string
                b.addSimpleTypeInList(t);
                return shared_from_this();
            } else if (t.getType() == TokenType::Null) {
                // if null
                b.addSimpleTypeInList(t);
                return shared_from_this();
            }

            if (t.getType() == TokenType::Name) {
                b.addFunCallInList(t);
                return std::make_shared<ReadCallArgs>();
            }
            // "[" if list start
            if (t.getType() == TokenType::ListOpen) {
                return shared_from_this();
            }

            // "]" if list end
            if (t.getType() == TokenType::ListClose) {
                b.endList();
                return std::make_shared<ReadAfterListEnd>();
            } else {
                throwException(u8"Expected a list member, but got token = " 
                               + t.getData(),
                               u8"analyzeToken(Token&)");
                // TODO Вызывать сервис очистки синглтонов перед экстренным завершением программы
            }
            // Если строка, число, список или закрытая скобка
            //return chooseReturn(t);
        }

        std::u8string ReadList::getClassFileName() {
            return u8"ReadList.h";
        }

    }
}
