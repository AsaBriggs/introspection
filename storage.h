#ifndef INCLUDED_STORAGE
#define INCLUDED_STORAGE

#ifndef INCLUDED_DETECT_TRAITS
#include "detect_traits.h"
#endif

#ifndef INCLUDED_METAPROGRAMMING
#include "metaprogramming.h"
#endif

namespace intro {

// Each storage struct is an aggregate, with a nested typedef type to itself
// as well as having introspection enabled and a static function make that
// allows uniform construction of an instance. Note that make takes parameters
// that must be convertible to the underlying values, thus allowing the Ref to decay to
// the correct value

template<typename Tag=DefaultTag>
struct empty_type
{
    typedef empty_type type;
    typedef true_type IntrospectionEnabled;

    static inline type make()
    {
        type tmp = {};
        return tmp;
    }
};

template<typename T0, typename Tag=DefaultTag>
struct singleton
{
    typedef singleton type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0> IntrospectionItems;

    T0 m0;

    template<typename P0>
    static inline type make(P0 const& p0)
    {
        type tmp = {p0};
        return tmp;
    }
};

template<typename T0, typename T1, typename Tag=DefaultTag>
struct pair
{
    typedef pair type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1> IntrospectionItems;

    T0 m0;
    T1 m1;

    template<typename P0, typename P1>
    static inline type make(P0 const& p0, P1 const& p1)
    {
        type tmp = {p0, p1};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename Tag=DefaultTag>
struct triple
{
    typedef triple type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1, T2> IntrospectionItems;

    T0 m0;
    T1 m1;
    T2 m2;

    template<typename P0, typename P1, typename P2>
    static inline type make(P0 const& p0, P1 const& p1, P2 const& p2)
    {
        type tmp = {p0, p1, p2};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename Tag=DefaultTag>
struct quadruple
{
    typedef quadruple type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1, T2, T3> IntrospectionItems;

    T0 m0;
    T1 m1;
    T2 m2;
    T3 m3;

    template<typename P0, typename P1, typename P2, typename P3>
    static inline type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3)
    {
        type tmp = {p0, p1, p2, p3};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename Tag=DefaultTag>
struct quintuple
{
    typedef quintuple type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1, T2, T3, T4> IntrospectionItems;

    T0 m0;
    T1 m1;
    T2 m2;
    T3 m3;
    T4 m4;

    template<typename P0, typename P1, typename P2, typename P3, typename P4>
    static inline type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4)
    {
        type tmp = {p0, p1, p2, p3, p4};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename Tag=DefaultTag>
struct sextuple
{
    typedef sextuple type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1, T2, T3, T4, T5> IntrospectionItems;

    T0 m0;
    T1 m1;
    T2 m2;
    T3 m3;
    T4 m4;
    T5 m5;

    template<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
    static inline type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5)
    {
        type tmp = {p0, p1, p2, p3, p4, p5};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename Tag=DefaultTag>
struct septuple
{
    typedef septuple type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1, T2, T3, T4, T5, T6> IntrospectionItems;

    T0 m0;
    T1 m1;
    T2 m2;
    T3 m3;
    T4 m4;
    T5 m5;
    T6 m6;

    template<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
    static inline type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6)
    {
        type tmp = {p0, p1, p2, p3, p4, p5, p6};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename Tag=DefaultTag>
struct octuple
{
    typedef octuple type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1, T2, T3, T4, T5, T6, T7> IntrospectionItems;

    T0 m0;
    T1 m1;
    T2 m2;
    T3 m3;
    T4 m4;
    T5 m5;
    T6 m6;
    T7 m7;

    template<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
    static inline type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7)
    {
        type tmp = {p0, p1, p2, p3, p4, p5, p6, p7};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename Tag=DefaultTag>
struct nonuple
{
    typedef nonuple type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1, T2, T3, T4, T5, T6, T7, T8> IntrospectionItems;

    T0 m0;
    T1 m1;
    T2 m2;
    T3 m3;
    T4 m4;
    T5 m5;
    T6 m6;
    T7 m7;
    T8 m8;

    template<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
    static inline type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8)
    {
        type tmp = {p0, p1, p2, p3, p4, p5, p6, p7, p8};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename Tag=DefaultTag>
struct decuple
{
    typedef decuple type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> IntrospectionItems;

    T0 m0;
    T1 m1;
    T2 m2;
    T3 m3;
    T4 m4;
    T5 m5;
    T6 m6;
    T7 m7;
    T8 m8;
    T9 m9;

    template<typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
    static inline type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8, P9 const& p9)
    {
        type tmp = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9};
        return tmp;
    }
};

GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionEnabled)

template<typename T>
struct IntrospectionEnabled :
    and_<HasMemberType_IntrospectionEnabled<T>,
         GetMemberType_IntrospectionEnabled<T> >
{};

GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionStorageTag)

template<typename T>
struct IntrospectionStorageTag :
    eval_if<HasMemberType_IntrospectionStorageTag<T>,
            GetMemberType_IntrospectionStorageTag<T>,
            DefaultTag>
{};

// Add typedef IntrospectionIndirectStorage and hold the data
// in a visible member called m0.
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionIndirectStorage)

template<typename T>
struct IntrospectionIndirectStorage :
    eval_if<HasMemberType_IntrospectionIndirectStorage<T>,
            GetMemberType_IntrospectionIndirectStorage<T>,
            false_type>
{};

// Assumed to be an array of the types
// Note that this is used in preference to IntrospectionItemX.
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionItems)

GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionItem0)
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionItem1)
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionItem2)
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionItem3)
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionItem4)
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionItem5)
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionItem6)
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionItem7)
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionItem8)
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionItem9)


namespace impl {

namespace HasItem {

template<typename T, typename Index>
struct HasNumberedIntrospectionItem;

template<typename T>
struct HasNumberedIntrospectionItem<T, Integer<0> > : HasMemberType_IntrospectionItem0<T> {};

template<typename T>
struct HasNumberedIntrospectionItem<T, Integer<1> > : HasMemberType_IntrospectionItem1<T> {};

template<typename T>
struct HasNumberedIntrospectionItem<T, Integer<2> > : HasMemberType_IntrospectionItem2<T> {};

template<typename T>
struct HasNumberedIntrospectionItem<T, Integer<3> > : HasMemberType_IntrospectionItem3<T> {};

template<typename T>
struct HasNumberedIntrospectionItem<T, Integer<4> > : HasMemberType_IntrospectionItem4<T> {};

template<typename T>
struct HasNumberedIntrospectionItem<T, Integer<5> > : HasMemberType_IntrospectionItem5<T> {};

template<typename T>
struct HasNumberedIntrospectionItem<T, Integer<6> > : HasMemberType_IntrospectionItem6<T> {};

template<typename T>
struct HasNumberedIntrospectionItem<T, Integer<7> > : HasMemberType_IntrospectionItem7<T> {};

template<typename T>
struct HasNumberedIntrospectionItem<T, Integer<8> > : HasMemberType_IntrospectionItem8<T> {};

template<typename T>
struct HasNumberedIntrospectionItem<T, Integer<9> > : HasMemberType_IntrospectionItem9<T> {};

// Alllows IntrospectionArityLoop to terminate
template<typename T>
struct HasNumberedIntrospectionItem<T, Integer<10> > : false_type {};

template<typename T, typename Index>
struct HasArrayIntrospectionItem :
    not_<is_same<ArrayNoArg, typename ArrayIndex<typename GetMemberType_IntrospectionItems<T>::type, Index>::type > >
{};

template<typename T>
struct HasArrayIntrospectionItem<T, Integer<10> > : false_type {};

} // namespace HasItem

template<typename T, typename Index>
struct HasIntrospectionItem_Impl :
     eval_if<HasMemberType_IntrospectionItems<T>,
             HasItem::HasArrayIntrospectionItem<T, Index>,
             HasItem::HasNumberedIntrospectionItem<T, Index> >
{};

namespace GetItem {

template<typename T, typename Index>
struct GetNumberedIntrospectionItem;

template<typename T>
struct GetNumberedIntrospectionItem<T, Integer<0> > : GetMemberType_IntrospectionItem0<T> {};

template<typename T>
struct GetNumberedIntrospectionItem<T, Integer<1> > : GetMemberType_IntrospectionItem1<T> {};

template<typename T>
struct GetNumberedIntrospectionItem<T, Integer<2> > : GetMemberType_IntrospectionItem2<T> {};

template<typename T>
struct GetNumberedIntrospectionItem<T, Integer<3> > : GetMemberType_IntrospectionItem3<T> {};

template<typename T>
struct GetNumberedIntrospectionItem<T, Integer<4> > : GetMemberType_IntrospectionItem4<T> {};

template<typename T>
struct GetNumberedIntrospectionItem<T, Integer<5> > : GetMemberType_IntrospectionItem5<T> {};

template<typename T>
struct GetNumberedIntrospectionItem<T, Integer<6> > : GetMemberType_IntrospectionItem6<T> {};

template<typename T>
struct GetNumberedIntrospectionItem<T, Integer<7> > : GetMemberType_IntrospectionItem7<T> {};

template<typename T>
struct GetNumberedIntrospectionItem<T, Integer<8> > : GetMemberType_IntrospectionItem8<T> {};

template<typename T>
struct GetNumberedIntrospectionItem<T, Integer<9> > : GetMemberType_IntrospectionItem9<T> {};

template<typename T, typename Index>
struct GetArrayIntrospectionItem :
    ArrayIndex<typename GetMemberType_IntrospectionItems<T>::type, Index>
{};

} // namespace GetItem

template<typename T, typename Index>
struct GetIntrospectionItem_Impl : eval_if<HasMemberType_IntrospectionItems<T>,
                                           GetItem::GetArrayIntrospectionItem<T, Index>,
                                           GetItem::GetNumberedIntrospectionItem<T, Index> >
{};

namespace Arity {

template<typename T, typename CurrentArity>
struct IntrospectionArityLoop;

// Count upwards; higher Arity is less likely.
// Note that Indexing is zero based, and that CurrentArity suggests 0..CurrentArity-1 (inclusive) are available
template<typename T, typename CurrentArity>
struct IntrospectionArityLoop : eval_if<HasIntrospectionItem_Impl<T, CurrentArity>,
                                        IntrospectionArityLoop<T, typename Successor<CurrentArity>::type>,
                                        CurrentArity>
{};

template<typename T>
struct IntrospectionArityArray : ArraySize<typename GetMemberType_IntrospectionItems<T>::type>
{};

} // namespace Arity

template<typename T>
struct IntrospectionArity_Impl : eval_if<IntrospectionEnabled<T>,
                                         eval_if<HasMemberType_IntrospectionItems<T>,
                                                 Arity::IntrospectionArityArray<T>,
                                                 Arity::IntrospectionArityLoop<T, Integer<0> > >,
                                         Integer<0> >
{};

namespace GetItems {

template<typename T, typename Arity, typename Index, typename CurrentArray>
struct GenerateIntrospectionItems_Loop;

template<typename T, typename Arity, typename CurrentArray>
struct GenerateIntrospectionItems_Loop<T, Arity, Arity, CurrentArray> : CurrentArray {};

template<typename T, typename ArityMinusOne, typename Index, typename CurrentArray>
struct GenerateIntrospectionItems_Loop : 
    GenerateIntrospectionItems_Loop<T, ArityMinusOne, typename Successor<Index>::type,
        typename ArrayConcat<CurrentArray, Array< typename GetItem::GetNumberedIntrospectionItem<T, Index>::type> >::type>
{};

template<typename T>
struct GenerateIntrospectionItems_DeduceArity :
    GenerateIntrospectionItems_Loop<T, typename IntrospectionArity_Impl<T>::type, Integer<0>, Array<> > {};

} // namespace GetItems

template<typename T>
struct GenerateIntrospectionItems_Impl : eval_if<HasMemberType_IntrospectionItems<T>,
                                                 GetMemberType_IntrospectionItems<T>,
                                                 GetItems::GenerateIntrospectionItems_DeduceArity<T> >
{};

} // namespace impl

template<typename T, typename Index>
struct HasIntrospectionItem : impl::HasIntrospectionItem_Impl<T, Index> {};

template<typename T, typename Index>
struct GetIntrospectionItem : impl::GetIntrospectionItem_Impl<T, Index> {};

template<typename T>
struct IntrospectionArity : impl::IntrospectionArity_Impl<T> {};

template<typename T>
struct GenerateIntrospectionItems : impl::GenerateIntrospectionItems_Impl<T> {};

namespace impl {

namespace GenerateStorageNS {

template<typename Array, typename Tag>
struct GenerateStorageFromArray;

template<typename Tag>
struct GenerateStorageFromArray<Array<>, Tag>
{
    typedef empty_type<Tag> type;
};

template<typename Tag, typename T0>
struct GenerateStorageFromArray<Array<T0>, Tag>
{
    typedef singleton<T0, Tag> type;
};

template<typename Tag, typename T0, typename T1>
struct GenerateStorageFromArray<Array<T0, T1>, Tag>
{
    typedef pair<T0, T1, Tag> type;
};

template<typename Tag, typename T0, typename T1, typename T2>
struct GenerateStorageFromArray<Array<T0, T1, T2>, Tag>
{
    typedef triple<T0, T1, T2, Tag> type;
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3>
struct GenerateStorageFromArray<Array<T0, T1, T2, T3>, Tag>
{
    typedef quadruple<T0, T1, T2, T3, Tag> type;
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4>
struct GenerateStorageFromArray<Array<T0, T1, T2, T3, T4>, Tag>
{
    typedef quintuple<T0, T1, T2, T3, T4, Tag> type;
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct GenerateStorageFromArray<Array<T0, T1, T2, T3, T4, T5>, Tag>
{
    typedef sextuple<T0, T1, T2, T3, T4, T5, Tag> type;
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct GenerateStorageFromArray<Array<T0, T1, T2, T3, T4, T5, T6>, Tag>
{
    typedef septuple<T0, T1, T2, T3, T4, T5, T6, Tag> type;
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct GenerateStorageFromArray<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Tag>
{
    typedef octuple<T0, T1, T2, T3, T4, T5, T6, T7, Tag> type;
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct GenerateStorageFromArray<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Tag>
{
    typedef nonuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, Tag> type;
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct GenerateStorageFromArray<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Tag>
{
    typedef decuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, Tag> type;
};

} // namespace GenerateStorageNS

template<typename T, typename Enabled>
struct GenerateStorage_Impl;

template<typename T>
struct GenerateStorage_Impl<T, false_type> {};

template<typename T>
struct GenerateStorage_Impl<T, true_type> :
    GenerateStorageNS::GenerateStorageFromArray<typename GenerateIntrospectionItems_Impl<T>::type,
                                              typename IntrospectionStorageTag<T>::type>
{};

} // namespace impl

template<typename T>
struct GenerateStorage : impl::GenerateStorage_Impl<T, typename IntrospectionEnabled<T>::type > {};

// OK, how to generate a function to call the appropriate make_storage?

namespace impl {

template<typename T, typename Index>
struct DefaultGet;

#define MAKE_DEFAULT_GET_N(Idx)\
template<typename T>\
struct DefaultGet<T, Integer< Idx > >\
{\
    typedef DefaultGet type;\
    typedef Integer< Idx > Index;\
    typedef true_type IntrospectionEnabled;\
    typedef T input_type_0;\
    typedef typename GetIntrospectionItem<T, Index>::type codomain_type;\
\
    inline\
    typename make_const_ref<codomain_type>::type operator()(typename parameter_type<T>::type x) const\
    {\
        return x.m##Idx;\
    }\
};

MAKE_DEFAULT_GET_N(0)
MAKE_DEFAULT_GET_N(1)
MAKE_DEFAULT_GET_N(2)
MAKE_DEFAULT_GET_N(3)
MAKE_DEFAULT_GET_N(4)
MAKE_DEFAULT_GET_N(5)
MAKE_DEFAULT_GET_N(6)
MAKE_DEFAULT_GET_N(7)
MAKE_DEFAULT_GET_N(8)
MAKE_DEFAULT_GET_N(9)

#undef MAKE_DEFAULT_GET_N

} // namespace impl

template<typename T, typename Index>
struct Get : impl::DefaultGet<T, Index> {};

namespace impl {

template<typename T>
inline
typename enable_if<IntrospectionIndirectStorage<T>, typename GenerateStorage<T>::type>::type const& get_storage(T const& x)
{
    return x.m0;
}

template<typename T>
inline
typename disable_if<IntrospectionIndirectStorage<T>, T>::type const& get_storage(T const& x)
{
    return x;
}

// Note that T may be const-qualified
template<typename T, typename Proc, typename Index, typename Arity>
struct Visit1;

template<typename T, typename Proc, typename Arity>
struct Visit1<T, Proc, Arity, Arity>
{
    typedef Visit1 type;
    typedef true_type IntrospectionEnabled;
    typedef typename deduce_input_type<T&>::type input_type_0;
    typedef Proc input_type_1;
    typedef Proc codomain_type;

    inline Proc
    operator()(input_type_0 x, Proc p)
    {
        return p;
    }
};

template<typename T, typename Proc, typename Index, typename Arity>
struct Visit1
{
    typedef Visit1 type;
    typedef true_type IntrospectionEnabled;
    typedef typename deduce_input_type<T&>::type input_type_0;
    typedef Proc input_type_1;
    typedef Proc codomain_type;

    inline Proc
    operator()(input_type_0 x, Proc p)
    {
        typedef typename Get<T, Index>::type Getter;
        p(Getter()(x), Index());
        return Visit1<T, Proc, typename Successor<Index>::type, Arity>()(x, p);
    }
};

// Note that T may be const-qualified
template<typename T, typename Proc, typename Index, typename Arity>
struct Visit2;

template<typename T, typename Proc, typename Arity>
struct Visit2<T, Proc, Arity, Arity>
{
    typedef Visit2 type;
    typedef true_type IntrospectionEnabled;
    typedef typename deduce_input_type<T&>::type input_type_0;
    typedef typename deduce_input_type<T&>::type input_type_1;
    typedef Proc input_type_2;
    typedef Proc codomain_type;

    inline Proc
    operator()(input_type_0 x, input_type_1 y, Proc p)
    {
        return p;
    }
};

template<typename T, typename Proc, typename Index, typename Arity>
struct Visit2
{
    typedef Visit2 type;
    typedef true_type IntrospectionEnabled;
    typedef typename deduce_input_type<T&>::type input_type_0;
    typedef typename deduce_input_type<T&>::type input_type_1;
    typedef Proc input_type_2;
    typedef Proc codomain_type;

    inline Proc
    operator()(input_type_0 x, input_type_1 y, Proc p)
    {
        typedef typename Get<T, Index>::type Getter;
        p(Getter()(x), Getter()(y), Index());
        return Visit2<T, Proc, typename Successor<Index>::type, Arity>()(x, y, p);
    }
};

template<typename T, typename Proc>
inline Proc visit_impl(T& x, Proc p)
{
    return Visit1<T, Proc, Integer<0>, typename IntrospectionArity<T>::type>()(x, p);
}

template<typename T, typename Proc>
inline Proc visit_impl(T& x, T& y, Proc p)
{
    return Visit2<T, Proc, Integer<0>, typename IntrospectionArity<T>::type>()(x, y, p);
}

template<typename GetComparator>
struct Equal_Visitor
{
    bool value; // Should be initialised to true, but want to keep POD-ness of the type

    typedef Equal_Visitor type;
    typedef true_type IntrospectionEnabled;
    typedef bool IntrospectionItem0;

    template<typename T, typename Index>
    inline void
    operator() (T const& x, T const& y, Index)
    {
      value = value ? typename Apply<GetComparator, T>::type()(x, y) : false ;
    }
};

template<typename GetComparator>
struct Less_Visitor
{
    bool value; // Should be initialised to false, but want to keep POD-ness of the type

    typedef Less_Visitor type;
    typedef true_type IntrospectionEnabled;
    typedef bool IntrospectionItem0;

    template<typename T, typename Index>
    inline void
    operator() (T const& x, T const& y, Index)
    {
      value = value ? true : typename Apply<GetComparator, T>::type()(x, y);
    }
};

template<typename GetComparator, typename T>
inline bool equal_impl(T const& x, T const& y)
{
    Equal_Visitor<GetComparator> tmp = {true};
    return visit_impl(x, y, tmp).value;
}

template<typename GetComparator, typename T>
inline bool less_impl(T const& x, T const& y)
{
    Less_Visitor<GetComparator> tmp = {false};
    return visit_impl(x, y, tmp).value;
}

} // namespace impl

template<typename T, typename enable=void>
struct generate_introspected_comparisons : IntrospectionEnabled<T> {};

template<typename T>
struct less<T, typename enable_if<generate_introspected_comparisons<T>, void>::type>
{
    typedef less type;
    typedef true_type IntrospectionEnabled;
    typedef T input_type_0;
    typedef T input_type_1;
    typedef bool codomain_type;

    inline codomain_type operator()(typename parameter_type<T>::type x, typename parameter_type<T>::type y) const
    {
        return impl::less_impl<less<placeholders::_0> >(impl::get_storage(x), impl::get_storage(y));
    }
};

template<typename T>
struct equal<T, typename enable_if<generate_introspected_comparisons<T>, void>::type>
{
    typedef equal type;
    typedef true_type IntrospectionEnabled;
    typedef T input_type_0;
    typedef T input_type_1;
    typedef bool codomain_type;

    inline codomain_type operator()(typename parameter_type<T>::type x, typename parameter_type<T>::type y) const
    {
      return impl::equal_impl<equal<placeholders::_0> >(impl::get_storage(x), impl::get_storage(y));
    }
};

template<typename T>
inline typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator==(T const& x, T const& y)
{
    return impl::equal_impl<OperatorEquals<placeholders::_0> >(impl::get_storage(x), impl::get_storage(y));
}

template<typename T>
inline typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator!=(T const& x, T const& y)
{
    return !(x == y);
}

template<typename T>
inline typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator<(T const& x, T const& y)
{
    return impl::less_impl<OperatorLessThan<placeholders::_0> >(impl::get_storage(x), impl::get_storage(y));
}

template<typename T>
inline typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator<=(T const& x, T const& y)
{
    return !(y < x);
}

template<typename T>
inline typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator>(T const& x, T const& y)
{
    return y < x;
}

template<typename T>
inline typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator>=(T const& x, T const& y)
{
    return !(x < y);
}


template<typename T, typename enable=void>
struct generate_introspected_underlying_type : IntrospectionEnabled<T> {};

template<typename Tag>
struct generate_introspected_underlying_type<empty_type<Tag> > : false_type {};

template<typename T, typename Tag>
struct generate_introspected_underlying_type<singleton<T, Tag> > : false_type {};

template<typename T>
struct underlying_type<T,
    typename enable_if<generate_introspected_underlying_type<T>, void>::type>
{
    typedef typename ArrayTransform<typename GenerateIntrospectionItems<T>::type, get_underlying_type<placeholders::_0> >::type TransformedTypes;

    typedef typename impl::GenerateStorageNS::GenerateStorageFromArray<TransformedTypes,
        typename IntrospectionStorageTag<T>::type>::type type;
};

// ArrayNoArg type and singleton can be reduced to simpler cases, unwrapping the struct in singelton's case
template<typename Tag>
struct underlying_type<empty_type<Tag> > : ArrayNoArg {};

template<typename T, typename Tag>
struct underlying_type<singleton<T, Tag> > : get_underlying_type<T> {};


template<typename Arr, typename Tag>
struct deduce_type
{
    typedef typename ArrayTransform<Arr, decay_ref<placeholders::_0> >::type TransformedTypes;

    typedef typename impl::GenerateStorageNS::GenerateStorageFromArray<TransformedTypes,
        Tag>::type type;
};

// The make_storage functions deduce a storage type based on the parameters passed in,
// taking into account "decaying" Ref objects.
template<typename Tag>
inline typename deduce_type<Array<>, Tag>::type make_storage()
{
    typedef typename deduce_type<Array<>, Tag>::type T;
    return T::make();
}

template<typename Tag, typename T0>
inline typename deduce_type<Array<T0>, Tag>::type make_storage(T0 const& m0)
{
    typedef typename deduce_type<Array<T0>, Tag>::type T;
    return T::make(m0);
}

template<typename Tag, typename T0, typename T1>
inline typename deduce_type<Array<T0, T1>, Tag>::type make_storage(T0 const& m0, T1 const& m1)
{
    typedef typename deduce_type<Array<T0, T1>, Tag>::type T;
    return T::make(m0, m1);
}

template<typename Tag, typename T0, typename T1, typename T2>
inline typename deduce_type<Array<T0, T1, T2>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2)
{
    typedef typename deduce_type<Array<T0, T1, T2>, Tag>::type T;
    return T::make(m0, m1, m2);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3>
inline typename deduce_type<Array<T0, T1, T2, T3>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3>, Tag>::type T;
    return T::make(m0, m1, m2, m3);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4>
inline typename deduce_type<Array<T0, T1, T2, T3, T4>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3, T4 const& m4)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3, T4>, Tag>::type T;
    return T::make(m0, m1, m2, m3, m4);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
inline typename deduce_type<Array<T0, T1, T2, T3, T4, T5>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3, T4 const& m4, T5 const& m5)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3, T4, T5>, Tag>::type T;
    return T::make(m0, m1, m2, m3, m4, m5);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3, T4 const& m4, T5 const& m5, T6 const& m6)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6>, Tag>::type T;
    return T::make(m0, m1, m2, m3, m4, m5, m6);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3, T4 const& m4, T5 const& m5, T6 const& m6, T7 const& m7)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Tag>::type T;
    return T::make(m0, m1, m2, m3, m4, m5, m6, m7);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
inline typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3, T4 const& m4, T5 const& m5, T6 const& m6, T7 const& m7, T8 const& m8)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Tag>::type T;
    return T::make(m0, m1, m2, m3, m4, m5, m6, m7, m8);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
inline typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3, T4 const& m4, T5 const& m5, T6 const& m6, T7 const& m7, T8 const& m8, T9 const& m9)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Tag>::type T;
    return T::make(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9);
}

template<typename T, typename Proc>
Proc visit(T& x, Proc p)
{
    return impl::visit_impl(impl::get_storage(x), p);
}

template<typename T, typename U, typename Proc>
Proc visit(T& x, U& y, Proc p)
{
    return impl::visit_impl(impl::get_storage(x), impl::get_storage(y), p);
}

} // namespace intro

#endif
