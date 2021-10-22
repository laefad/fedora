
#include "Types/List.h"

namespace fedora::types {

    List::List():
        ContextualComplement(),
        value(nullptr), 
        next(nullptr) 
    {}

    List::List(std::shared_ptr<BasicType> v):
        ContextualComplement(),
        value(std::move(v)),
        next(nullptr)
    {}

    List::List(std::shared_ptr<BasicType> v, std::shared_ptr<List> lst):
        ContextualComplement(),
        value(std::move(v)),
        next(lst)
    {}

    List::List(
        fedora::context::ContextualComplement::Context context,
        std::shared_ptr<BasicType> v,
        std::shared_ptr<List> lst
    ):
        ContextualComplement(context),
        value(std::move(v)),
        next(lst)
    {}

    std::shared_ptr<List> List::addNewItemToTheBeginning(
        std::shared_ptr<BasicType> v, 
        std::shared_ptr<List> lst
    ) {
        return std::make_shared<List>(std::move(v), std::move(lst));
    }

    std::shared_ptr<List> List::addNewItemToTheEnd(
        std::shared_ptr<BasicType> v,
        std::shared_ptr<List> lst
    ) {
        auto head = std::make_shared<List>(lst->value);
        auto new_lst = head;
        auto next = lst->next;

        while(next) {
            new_lst->next = std::make_shared<List>(next->value);
            new_lst = new_lst->next;
            next = next->next;
        }

        new_lst->next = std::make_shared<List>(v);

        return head;
    }

    Type List::type() {
        return types::LIST;
    }

    std::u8string List::eval() {
        std::shared_ptr<List> next = this->next;
        std::u8string buff;

        buff += u8'[';

        if (value)
            buff += value->eval();

        while (next) {
            if (next->value!= nullptr){
                buff += u8' ';
                buff += next->value->eval();
            }
            next = next->next;
        }

        buff += u8']';

        return buff;
    };

    std::shared_ptr<BasicType> List::getValue() {
        if (value)
            ContextualComplement::addContextToElement(value, std::make_shared<Context>(context));
        return value;
    }

    std::shared_ptr<List> List::getNext() {
        if (next)
            ContextualComplement::addContextToElement(next, std::make_shared<Context>(context));
        return next;
    }
}
