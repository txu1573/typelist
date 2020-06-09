#ifndef TYPELIST_TEST2_H
#define TYPELIST_TEST2_H

#include "type_list.h"

class TypeA;
class TypeB;
class TypeC;
typedef TYPELIST_3(TypeA, TypeB, TypeC) TL3;

template<typename T> struct Printer {};

template<>
struct Printer<TypeA>
{
    typedef TypeA Type;

    int getIndex() const { return IndexOf<TL3, Type>::value; }
};

template<>
struct Printer<TypeB>
{
    typedef TypeB Type;

    int getIndex() const { return IndexOf<TL3, Type>::value; }
};

template<>
struct Printer<TypeC>
{
    typedef TypeC Type;

    int getIndex() const { return IndexOf<TL3, Type>::value; }
};

void typelist_test2()
{
    Printer<TypeA> printer;

    switch (printer.getIndex())
    {
    case IndexOf<TL3, TypeA>::value:
        std::cout << "Do sth for type A" << std::endl;
        break;
    case IndexOf<TL3, TypeB>::value:
        std::cout << "Do sth for type B" << std::endl;
        break;
    case IndexOf<TL3, TypeC>::value:
        std::cout << "Do sth for type C" << std::endl;
        break;
    default:
        break;
    }
}

#endif // TYPELIST_TEST2_H
