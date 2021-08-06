// ФАЙЛ ЗАКОНСЕРВИРОВАН
// Я хотел сначала сделать Returnable экземпляры для каждого типа, но потом подумал, что оно не особенно нужно.
// От ретурнабл треюуется лишь вернуть экхемпляр данных. Возврат строки ничем не отличается от возврата числа.
// Когда дело доходит до того, что нужно что-то посчитать, то лучше иметь дело с самим Type, чем с Returnable

//
// Created on 05.08.2021.
//
//
//#pragma once
//
//#include "Returnable.h"
//#include "Types/Number.h"
//
//namespace fedora {
//    namespace context {
//        class ReturnableNumber : public context::Returnable, public types::Number {
//            std::unique_ptr<fedora::types::BasicType> n ;
//        public:
//            explicit ReturnableNumber(double v) : n(v) {}
//
//            ReturnableNumber(Returnable returnable) {
//                if(){}
//            }
//
//            std::unique_ptr<fedora::types::BasicType> &get() override {
//                return std::man;
//            }
//
//            AdvancedType type() override{
//                return NUMBER;
//            }
//        };
//    }
//}

