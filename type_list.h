#ifndef TYPE_LISTS_H_
#define TYPE_LISTS_H_


#include <iostream>
#include <string>
// #include "typetraits.h"

class NullType {};
/*
TypeLists 内部没有任何数值（value)，他们的实体是空的，不含有任何状态，也未定义任何函数。
执行期间TypeLists也不带任何数值，他们存在的理由只是为了携带型别信息。TypeLists 并未打算被具
现化。因此，当我们说“a TypeListL”，实际指的是一个typelist型别，不是一个typelist 对象。
规定 typelist 必须以NullType(类）结尾，NullType可被视为一个结束符号，类似于c字符串的\0功能，
定义一个只有一个元素的typelist如下：
typedef Typelist<int,NullType> OneTypeOnly.
*/
template<class T,class U>
struct Typelist
{
    typedef T Head;
    typedef U Tail;
};
//通过定义宏 将typelist线性化
#define TYPELIST_0() NullType
#define TYPELIST_1(T1) Typelist<T1,TYPELIST_0()>
#define TYPELIST_2(T1,T2) Typelist<T1,TYPELIST_1(T2)>
#define TYPELIST_3(T1,T2,T3) Typelist<T1,TYPELIST_2(T2,T3)>
#define TYPELIST_4(T1,T2,T3,T4) Typelist<T1,TYPELIST_3(T2,T3,T4)>
#define TYPELIST_5(T1,T2,T3,T4,T5) Typelist<T1,TYPELIST_4(T2,T3,T4,T5)>

//计算TypeList长度
//大多数Typelist的操作都是基于递归，递归终止条件通过模板特化实现。
template<class TList>struct Length;
template<>struct Length<NullType>//Length的全特化，即，只匹配NullType。
{
    enum{value = 0};
};
template<class T,class U>
struct Length<Typelist<T,U> >//Length的扁特化，可匹配任何TypeList<T,U>类型，包括U同时也是Typelist的复合情况。
{
    enum{value = 1+Length<U>::value};
};
//2 索引式访问
template <class TList,unsigned int index> struct TypeAt;
template<class Head,class Tail>
struct TypeAt<Typelist<Head,Tail>,0>
{
    typedef Head Result;
};
template<class Head,class Tail,unsigned int i>
struct TypeAt<Typelist<Head,Tail> ,i>
{
    typedef typename TypeAt<Tail,i-1>::Result Result;
};

//类似TypeAt功能，不过TypeAtNonStrict对逾界访问更加宽容。
//比如TypeList的个数是3，那么你不能使用TypeAt<TL3,3>::Result，这样会编译错误。
//但是TypeAtNonStrict<TL3,3,NullType>::Result可以，如果不存在索引为3的type，那么结果是第三个引数即NullType
template <class TList, unsigned int i, typename DefType = NullType>
struct TypeAtNonStrict
{
    typedef DefType Result;
};
template <class T, class U, typename DefType>
struct TypeAtNonStrict< Typelist<T, U>, 0, DefType >
{
    typedef T Result;
};
template <class T, class U, unsigned int i, typename DefType>
struct TypeAtNonStrict< Typelist<T, U>, i, DefType >
{
    typedef typename TypeAtNonStrict<U, i - 1, DefType>::Result Result;
};

//3 查找TypeList
template<class TList,class T> struct IndexOf;//声明
template<class T>
struct IndexOf<NullType,T>//如果TList为NullType，那么令value = -1；
{
    enum{value = -1};
};
template<class Tail,class T>
struct IndexOf<Typelist<T,Tail> ,T>//如果T是TList中的头端，那么令value= 0；
{
    enum{value = 0};
};
template<class Head,class Tail,class T>//将IndexOf施于TList尾端和T，并将结果置于一个临时变量temp
struct IndexOf<Typelist<Head,Tail> ,T>//如果temp为-1，令value为-1，否则令value为1+temp
{
private:
    enum{temp = IndexOf<Tail,T>::value};//temp要先于value声明定义。
public:
    enum{value = temp == -1 ? -1 : temp + 1};
};

//4 附加元素到typelist
template <class Tlist,class T>struct Append;//声明
template<>struct Append<NullType,NullType>//如果TList是NULL而且T是NULL，那么令Result为NullType
{
    typedef NullType Result;
};
template <class T> struct Append<NullType,T> //如果TList是NullType，且T是type(非typelist),
{                                           //那么Result将是"只含有唯一元素的T";
    typedef TYPELIST_1(T) Result;
};
template <class Head,class Tail>
struct Append<NullType,Typelist<Head,Tail> >// 如果TList是NullType，且T是一个typelist，那么Result便是T本身
{
    typedef Typelist<Head,Tail> Result;
};
template<class Head,class Tail,class T>//否则，如果Tlist是non-null，那么result将是个typelist，以TList::Head
struct Append<Typelist<Head,Tail>,T>   //为起头端，并以T附加到TList::Tail的结果为其尾端。
{
    typedef Typelist<Head,typename Append<Tail,T>::Result> Result;
};

//5 Reverse
template <class TList> struct Reverse;
template <>struct Reverse<NullType>
{
    typedef NullType Result;
};
template <class Head, class Tail>
struct Reverse< Typelist<Head, Tail> >
{
    typedef typename Append<
        typename Reverse<Tail>::Result, Head>::Result Result;
};


#endif
