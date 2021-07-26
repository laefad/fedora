//
// Created on 26.07.2021.
//
#pragma once
#include "Token.h"
#include <vector>

/**
 * @brief Это класс, который будет хранить в себе все спаршеные токены. Реализован через паттерн Singleton
 */
 namespace fedora {
     class TokensHolder {

         /**
          * Конструктор Одиночки всегда должен быть скрытым, чтобы предотвратить
          * создание объекта через оператор new.
          */
     protected:
         TokensHolder() {}

         static TokensHolder *singleton_;
         std::vector<Token> tokens;
     public:

         /**
          * Одиночки не должны быть клонируемыми.
          */
         TokensHolder(TokensHolder &other) = delete;

         /**
          * Singletons should not be assignable.
          */
         void operator=(const TokensHolder &) = delete;

         /**
          * Это статический метод, управляющий доступом к экземпляру одиночки. При
          * первом запуске, он создаёт экземпляр одиночки и помещает его в
          * статическое поле. При последующих запусках, он возвращает клиенту объект,
          * хранящийся в статическом поле.
          */
         static TokensHolder *GetInstance();

         void add(const Token& a) {
             tokens.push_back(a);
         }

         std::vector<Token>& getAll(){
             return tokens;
         }
     };

     TokensHolder *TokensHolder::singleton_ = nullptr;

     TokensHolder *TokensHolder::GetInstance() {
         if (singleton_ == nullptr) {
             singleton_ = new TokensHolder();
         }
         return singleton_;
     }
 }
