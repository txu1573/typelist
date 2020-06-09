#include <iostream>
#include <typeinfo>
#include "type_list.h"

void typelists_test()
{
    typedef TYPELIST_0() TL0;
    typedef TYPELIST_3(char,int,double) TL3;
    typedef TYPELIST_3(char,int,double) TL3_1;
    //Length
    std::cout<<Length<TL0>::value<<std::endl;
    std::cout<<Length<TL3>::value<<std::endl;

    //TypeAt
    typedef TypeAt<TL3,0>::Result Parm1;
    typedef TypeAt<TL3,1>::Result Parm2;
    typedef TypeAt<TL3,2>::Result Parm3;

    typedef TypeAtNonStrict<TL3,3,NullType>::Result TEST_TYPE;

    std::cout<<"Parm1 Type:"<<typeid(Parm1).name() <<" sizeof : "<< sizeof(Parm1)<<std::endl;
    std::cout<<"Parm2 Type:"<<typeid(Parm2).name() <<" sizeof : "<< sizeof(Parm2)<<std::endl;
    std::cout<<"Parm3 Type:"<<typeid(Parm3).name() <<" sizeof : "<< sizeof(Parm3)<<std::endl;
    std::cout<<"TEST_TYPE Type:"<<typeid(TEST_TYPE).name() <<" sizeof : "<< sizeof(TEST_TYPE)<<std::endl;

    //IndexOf
    std::cout<<"char indexof TL3 :"<<IndexOf<TL3,char>::value<<std::endl;
    std::cout<<"int indexof TL3 :"<<IndexOf<TL3,int>::value<<std::endl;
    std::cout<<"float indexof TL3 :"<<IndexOf<TL3,float>::value<<std::endl;

    //Append
    typedef Append<TL3,int> TL4;//TL4不是一个TypeList
    typedef Append<TL3_1,TYPELIST_2(float,double)> TL5;
    std::cout<<"TL4 Length  :"<<Length<TL4::Result>::value<<std::endl;
    std::cout<<"TL5 Length  :"<<Length<TL5::Result>::value<<std::endl;

    //Reverse
    std::cout<<"Reverse result:"<<typeid(Reverse<TL3>::Result).name()<<std::endl;
}

int main()
{
    typelists_test();
}
