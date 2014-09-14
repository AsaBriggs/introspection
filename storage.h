#ifndef INCLUDED_STORAGE
#define INCLUDED_STORAGE

#ifndef INCLUDED_METAPROGRAMMING
#include "metaprogramming.h"
#endif

#ifndef INCLUDED_DETECT_TRAITS
#include "detect_traits.h"
#endif

#ifndef INCLUDED_COMPILER_SPECIFICS
#include "compiler_specifics.h"
#endif

namespace intro {

// Each storage struct is an aggregate, with a nested typedef type to itself
// as well as having introspection enabled and a static function make that
// allows uniform construction of an instance. Note that make takes parameters
// that must be convertible to the underlying values, thus allowing the Ref to decay to
// the correct value
// Note the make functions have not been parked as always inline as the constructor might
// start gettingexpensive for non-POD payload types.
template<typename Tag=DefaultTag>
struct TYPE_DEFAULT_VISIBILITY empty_type
{
    typedef empty_type type;
    typedef true_type IntrospectionEnabled;

    static INLINE type make()
    {
        type tmp = {};
        return tmp;
    }
};

template<typename T0, typename Tag=DefaultTag>
struct TYPE_DEFAULT_VISIBILITY singleton
{
    typedef singleton type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0> IntrospectionItems;

    T0 m0;

    template<typename P0>
    static INLINE type make(P0 const& p0)
    {
        type tmp = {p0};
        return tmp;
    }
};

template<typename T0, typename T1, typename Tag=DefaultTag>
struct TYPE_DEFAULT_VISIBILITY pair
{
    typedef pair type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1> IntrospectionItems;

    T0 m0;
    T1 m1;

    template<typename P0, typename P1>
    static INLINE type make(P0 const& p0, P1 const& p1)
    {
        type tmp = {p0, p1};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename Tag=DefaultTag>
struct TYPE_DEFAULT_VISIBILITY triple
{
    typedef triple type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1, T2> IntrospectionItems;

    T0 m0;
    T1 m1;
    T2 m2;

    template<typename P0, typename P1, typename P2>
    static INLINE type make(P0 const& p0, P1 const& p1, P2 const& p2)
    {
        type tmp = {p0, p1, p2};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename Tag=DefaultTag>
struct TYPE_DEFAULT_VISIBILITY quadruple
{
    typedef quadruple type;
    typedef true_type IntrospectionEnabled;
    typedef Array<T0, T1, T2, T3> IntrospectionItems;

    T0 m0;
    T1 m1;
    T2 m2;
    T3 m3;

    template<typename P0, typename P1, typename P2, typename P3>
    static INLINE type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3)
    {
        type tmp = {p0, p1, p2, p3};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename Tag=DefaultTag>
struct TYPE_DEFAULT_VISIBILITY quintuple
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
    static INLINE type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4)
    {
        type tmp = {p0, p1, p2, p3, p4};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename Tag=DefaultTag>
struct TYPE_DEFAULT_VISIBILITY sextuple
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
    static INLINE type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5)
    {
        type tmp = {p0, p1, p2, p3, p4, p5};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename Tag=DefaultTag>
struct TYPE_DEFAULT_VISIBILITY septuple
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
    static INLINE type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6)
    {
        type tmp = {p0, p1, p2, p3, p4, p5, p6};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename Tag=DefaultTag>
struct TYPE_DEFAULT_VISIBILITY octuple
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
    static INLINE type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7)
    {
        type tmp = {p0, p1, p2, p3, p4, p5, p6, p7};
        return tmp;
    }
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename Tag=DefaultTag>
struct TYPE_DEFAULT_VISIBILITY nonuple
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
    static INLINE type make(P0 const& p0, P1 const& p1, P2 const& p2, P3 const& p3, P4 const& p4, P5 const& p5, P6 const& p6, P7 const& p7, P8 const& p8)
    {
        type tmp = {p0, p1, p2, p3, p4, p5, p6, p7, p8};
        return tmp;
    }
};

// Note that to keep the requirements of storage within the Arity limits of Apply (N=10)
// It was decided that implementing storage containing N types would be troublesome and so was abandoned.
// If it is deemed necessary then the limits of Apply, Array and the number of placeholders should be
// increased.

GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionEnabled)

template<typename T>
struct TYPE_HIDDEN_VISIBILITY IntrospectionEnabled :
    and_<HasMemberType_IntrospectionEnabled<T>,
         GetMemberType_IntrospectionEnabled<T> >
{
    METAPROGRAMMING_ONLY(IntrospectionEnabled)
};

GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionStorageTag)

template<typename T>
struct TYPE_HIDDEN_VISIBILITY IntrospectionStorageTag :
    eval_if<HasMemberType_IntrospectionStorageTag<T>,
            GetMemberType_IntrospectionStorageTag<T>,
            DefaultTag>
{
    METAPROGRAMMING_ONLY(IntrospectionStorageTag)
};

// Add typedef IntrospectionIndirectStorage and hold the data
// in a visible member called m0.
GENERATE_HAS_AND_GET_MEMBER_TYPE(IntrospectionIndirectStorage)

template<typename T>
struct TYPE_HIDDEN_VISIBILITY IntrospectionIndirectStorage :
    eval_if<HasMemberType_IntrospectionIndirectStorage<T>,
            GetMemberType_IntrospectionIndirectStorage<T>,
            false_type>
{
    METAPROGRAMMING_ONLY(IntrospectionIndirectStorage)
};

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


namespace HasIntrospectionItem_impl {

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY HasNumberedIntrospectionItem;

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedIntrospectionItem<T, Integer<0> > : HasMemberType_IntrospectionItem0<T> {METAPROGRAMMING_ONLY(HasNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedIntrospectionItem<T, Integer<1> > : HasMemberType_IntrospectionItem1<T> {METAPROGRAMMING_ONLY(HasNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedIntrospectionItem<T, Integer<2> > : HasMemberType_IntrospectionItem2<T> {METAPROGRAMMING_ONLY(HasNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedIntrospectionItem<T, Integer<3> > : HasMemberType_IntrospectionItem3<T> {METAPROGRAMMING_ONLY(HasNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedIntrospectionItem<T, Integer<4> > : HasMemberType_IntrospectionItem4<T> {METAPROGRAMMING_ONLY(HasNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedIntrospectionItem<T, Integer<5> > : HasMemberType_IntrospectionItem5<T> {METAPROGRAMMING_ONLY(HasNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedIntrospectionItem<T, Integer<6> > : HasMemberType_IntrospectionItem6<T> {METAPROGRAMMING_ONLY(HasNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedIntrospectionItem<T, Integer<7> > : HasMemberType_IntrospectionItem7<T> {METAPROGRAMMING_ONLY(HasNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedIntrospectionItem<T, Integer<8> > : HasMemberType_IntrospectionItem8<T> {METAPROGRAMMING_ONLY(HasNumberedIntrospectionItem)};

// Alllows IntrospectionArityLoop to terminate
template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedIntrospectionItem<T, Integer<9> > : false_type {METAPROGRAMMING_ONLY(HasNumberedIntrospectionItem)};

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY HasArrayIntrospectionItem :
    not_<is_same<ArrayNoArg, typename ArrayIndex<typename GetMemberType_IntrospectionItems<T>::type, Index>::type > >
{
    METAPROGRAMMING_ONLY(HasArrayIntrospectionItem)
};

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY HasIntrospectionItem :
     eval_if<HasMemberType_IntrospectionItems<T>,
             HasArrayIntrospectionItem<T, Index>,
             HasNumberedIntrospectionItem<T, Index> >
{
    METAPROGRAMMING_ONLY(HasIntrospectionItem)
};

} // namespace HasIntrospectionItem_impl

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY HasIntrospectionItem :  HasIntrospectionItem_impl::HasIntrospectionItem<T, Index> {METAPROGRAMMING_ONLY(HasIntrospectionItem)};


namespace GetIntrospectionItem_impl {

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetNumberedIntrospectionItem;

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedIntrospectionItem<T, Integer<0> > : GetMemberType_IntrospectionItem0<T> {METAPROGRAMMING_ONLY(GetNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedIntrospectionItem<T, Integer<1> > : GetMemberType_IntrospectionItem1<T> {METAPROGRAMMING_ONLY(GetNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedIntrospectionItem<T, Integer<2> > : GetMemberType_IntrospectionItem2<T> {METAPROGRAMMING_ONLY(GetNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedIntrospectionItem<T, Integer<3> > : GetMemberType_IntrospectionItem3<T> {METAPROGRAMMING_ONLY(GetNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedIntrospectionItem<T, Integer<4> > : GetMemberType_IntrospectionItem4<T> {METAPROGRAMMING_ONLY(GetNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedIntrospectionItem<T, Integer<5> > : GetMemberType_IntrospectionItem5<T> {METAPROGRAMMING_ONLY(GetNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedIntrospectionItem<T, Integer<6> > : GetMemberType_IntrospectionItem6<T> {METAPROGRAMMING_ONLY(GetNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedIntrospectionItem<T, Integer<7> > : GetMemberType_IntrospectionItem7<T> {METAPROGRAMMING_ONLY(GetNumberedIntrospectionItem)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedIntrospectionItem<T, Integer<8> > : GetMemberType_IntrospectionItem8<T> {METAPROGRAMMING_ONLY(GetNumberedIntrospectionItem)};

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetArrayIntrospectionItem :
    ArrayIndex<typename GetMemberType_IntrospectionItems<T>::type, Index>
{
    METAPROGRAMMING_ONLY(GetArrayIntrospectionItem)
};

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetIntrospectionItem : eval_if<HasMemberType_IntrospectionItems<T>,
                                           GetArrayIntrospectionItem<T, Index>,
                                           GetNumberedIntrospectionItem<T, Index> >
{
    METAPROGRAMMING_ONLY(GetIntrospectionItem)
};

} // namespace GetIntrospectionItem_impl

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetIntrospectionItem : GetIntrospectionItem_impl::GetIntrospectionItem<T, Index> {METAPROGRAMMING_ONLY(GetIntrospectionItem)};


namespace IntrospectionArity_impl {

template<typename T, typename CurrentArity>
struct TYPE_HIDDEN_VISIBILITY IntrospectionArityLoop;

// Count upwards; higher Arity is less likely.
// Note that Indexing is zero based, and that CurrentArity suggests 0..CurrentArity-1 (inclusive) are available
template<typename T, typename CurrentArity>
struct TYPE_HIDDEN_VISIBILITY IntrospectionArityLoop : eval_if<HasIntrospectionItem<T, CurrentArity>,
                                        IntrospectionArityLoop<T, typename Successor<CurrentArity>::type>,
                                        CurrentArity>
{
    METAPROGRAMMING_ONLY(IntrospectionArityLoop)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY IntrospectionArityArray : ArraySize<typename GetMemberType_IntrospectionItems<T>::type>
{
    METAPROGRAMMING_ONLY(IntrospectionArityArray)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY IntrospectionArity : eval_if<IntrospectionEnabled<T>,
                                         eval_if<HasMemberType_IntrospectionItems<T>,
                                                 IntrospectionArityArray<T>,
                                                 IntrospectionArityLoop<T, Integer<0> > >,
                                         Integer<0> >
{
    METAPROGRAMMING_ONLY(IntrospectionArity)
};

} // namespace IntrospectionArity_impl

template<typename T>
struct TYPE_HIDDEN_VISIBILITY IntrospectionArity : IntrospectionArity_impl::IntrospectionArity<T> {METAPROGRAMMING_ONLY(IntrospectionArity)};


namespace GenerateIntrospectionItems_impl {

template<typename T, typename Arity, typename Index, typename CurrentArray>
struct TYPE_HIDDEN_VISIBILITY GenerateIntrospectionItems_Loop;

template<typename T, typename Arity, typename CurrentArray>
struct TYPE_HIDDEN_VISIBILITY GenerateIntrospectionItems_Loop<T, Arity, Arity, CurrentArray> : CurrentArray {METAPROGRAMMING_ONLY(GenerateIntrospectionItems_Loop)};

template<typename T, typename ArityMinusOne, typename Index, typename CurrentArray>
struct TYPE_HIDDEN_VISIBILITY GenerateIntrospectionItems_Loop : 
    GenerateIntrospectionItems_Loop<T, ArityMinusOne, typename Successor<Index>::type,
        typename ArrayConcat<CurrentArray, Array< typename GetIntrospectionItem_impl::GetNumberedIntrospectionItem<T, Index>::type> >::type>
{
    METAPROGRAMMING_ONLY(GenerateIntrospectionItems_Loop)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GenerateIntrospectionItems_DeduceArity :
    GenerateIntrospectionItems_Loop<T, typename IntrospectionArity<T>::type, Integer<0>, Array<> > {METAPROGRAMMING_ONLY(GenerateIntrospectionItems_DeduceArity)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GenerateIntrospectionItems : eval_if<HasMemberType_IntrospectionItems<T>,
                                                 GetMemberType_IntrospectionItems<T>,
                                                 GenerateIntrospectionItems_DeduceArity<T> >
{
    METAPROGRAMMING_ONLY(GenerateIntrospectionItems)
};

} // namespace GenerateIntrospectionItems_impl

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GenerateIntrospectionItems : GenerateIntrospectionItems_impl::GenerateIntrospectionItems<T> {METAPROGRAMMING_ONLY(GenerateIntrospectionItems)};


namespace GenerateStorage_impl {

template<typename Array, typename Tag>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray;

template<typename Tag>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray<Array<>, Tag>
{
    typedef empty_type<Tag> type;
    METAPROGRAMMING_ONLY(GenerateStorageFromArray)
};

template<typename Tag, typename T0>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray<Array<T0>, Tag>
{
    typedef singleton<T0, Tag> type;
    METAPROGRAMMING_ONLY(GenerateStorageFromArray)
};

template<typename Tag, typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray<Array<T0, T1>, Tag>
{
    typedef pair<T0, T1, Tag> type;
    METAPROGRAMMING_ONLY(GenerateStorageFromArray)
};

template<typename Tag, typename T0, typename T1, typename T2>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray<Array<T0, T1, T2>, Tag>
{
    typedef triple<T0, T1, T2, Tag> type;
    METAPROGRAMMING_ONLY(GenerateStorageFromArray)
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray<Array<T0, T1, T2, T3>, Tag>
{
    typedef quadruple<T0, T1, T2, T3, Tag> type;
    METAPROGRAMMING_ONLY(GenerateStorageFromArray)
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray<Array<T0, T1, T2, T3, T4>, Tag>
{
    typedef quintuple<T0, T1, T2, T3, T4, Tag> type;
    METAPROGRAMMING_ONLY(GenerateStorageFromArray)
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray<Array<T0, T1, T2, T3, T4, T5>, Tag>
{
    typedef sextuple<T0, T1, T2, T3, T4, T5, Tag> type;
    METAPROGRAMMING_ONLY(GenerateStorageFromArray)
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray<Array<T0, T1, T2, T3, T4, T5, T6>, Tag>
{
    typedef septuple<T0, T1, T2, T3, T4, T5, T6, Tag> type;
    METAPROGRAMMING_ONLY(GenerateStorageFromArray)
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Tag>
{
    typedef octuple<T0, T1, T2, T3, T4, T5, T6, T7, Tag> type;
    METAPROGRAMMING_ONLY(GenerateStorageFromArray)
};

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Tag>
{
    typedef nonuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, Tag> type;
    METAPROGRAMMING_ONLY(GenerateStorageFromArray)
};

template<typename T, typename Enabled>
struct TYPE_HIDDEN_VISIBILITY GenerateStorage;

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GenerateStorage<T, false_type> {METAPROGRAMMING_ONLY(GenerateStorage)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GenerateStorage<T, true_type> :
    GenerateStorageFromArray<typename GenerateIntrospectionItems<T>::type,
                                              typename IntrospectionStorageTag<T>::type>
{
    METAPROGRAMMING_ONLY(GenerateStorage)
};

} // namespace GenerateStorage_impl

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GenerateStorage : GenerateStorage_impl::GenerateStorage<T, typename IntrospectionEnabled<T>::type > {METAPROGRAMMING_ONLY(GenerateStorage)};

template<typename Array, typename Tag>
struct TYPE_HIDDEN_VISIBILITY GenerateStorageFromArray : GenerateStorage_impl::GenerateStorageFromArray<Array, Tag>{METAPROGRAMMING_ONLY(GenerateStorageFromArray)};


namespace DefaultGet_impl {

template<typename T, typename Index>
struct TYPE_DEFAULT_VISIBILITY DefaultGet;

#define MAKE_DEFAULT_GET_N(Idx)\
template<typename T>\
struct TYPE_DEFAULT_VISIBILITY DefaultGet<T const, Integer< Idx > >\
{\
    typedef DefaultGet type;\
    typedef Integer< Idx > Index;\
    typedef true_type IntrospectionEnabled;\
    typedef T const& input_type_0;\
    typedef typename make_const_ref<typename GetIntrospectionItem<T, Index>::type>::type codomain_type; \
\
    ALWAYS_INLINE_HIDDEN codomain_type\
    operator()(input_type_0 x) const\
    {\
        return x.m##Idx;\
    }\
};\
template<typename T>\
struct TYPE_DEFAULT_VISIBILITY DefaultGet<T, Integer< Idx > >\
{\
    typedef DefaultGet type;\
    typedef Integer< Idx > Index;\
    typedef true_type IntrospectionEnabled;\
    typedef T& input_type_0;\
    typedef typename make_ref_type<typename GetIntrospectionItem<T, Index>::type>::type codomain_type; \
\
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(input_type_0 x) const\
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

#undef MAKE_DEFAULT_GET_N

} // namespace DefaultGet_impl

template<typename T, typename Index>
struct TYPE_DEFAULT_VISIBILITY Get : DefaultGet_impl::DefaultGet<T, Index> {};

template<typename T>
ALWAYS_INLINE_HIDDEN
typename enable_if<IntrospectionIndirectStorage<T>, typename GenerateStorage<T>::type>::type const& get_storage(T const& x)
{
    return x.m0;
}

template<typename T>
ALWAYS_INLINE_HIDDEN
typename enable_if<IntrospectionIndirectStorage<T>, typename GenerateStorage<T>::type>::type& get_storage(T& x)
{
    return x.m0;
}

template<typename T>
ALWAYS_INLINE_HIDDEN
typename disable_if<IntrospectionIndirectStorage<T>, T>::type& get_storage(T& x)
{
    return x;
}

template<typename T>
ALWAYS_INLINE_HIDDEN
typename disable_if<IntrospectionIndirectStorage<T>, T>::type const& get_storage(T const& x)
{
    return x;
}

struct TYPE_DEFAULT_VISIBILITY VisitStart { typedef VisitStart type; };
struct TYPE_DEFAULT_VISIBILITY VisitEnd { typedef VisitEnd type; };

namespace Visit_impl {

// Note that T may be const-qualified
template<typename T, typename Proc, typename Index, typename Arity>
struct TYPE_DEFAULT_VISIBILITY Visit1;

template<typename T, typename Proc, typename Arity>
struct TYPE_DEFAULT_VISIBILITY Visit1<T, Proc, Arity, Arity>
{
    typedef Visit1 type;
    typedef true_type IntrospectionEnabled;
    typedef typename deduce_input_type<T&>::type input_type_0;
    typedef Proc input_type_1;
    typedef Proc codomain_type;

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(input_type_0 x, input_type_1 p)
    {
        return p;
    }
};

template<typename T, typename Proc, typename Index, typename Arity>
struct TYPE_DEFAULT_VISIBILITY Visit1
{
    typedef Visit1 type;
    typedef true_type IntrospectionEnabled;
    typedef typename deduce_input_type<T&>::type input_type_0;
    typedef Proc input_type_1;
    typedef Proc codomain_type;

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(input_type_0 x, input_type_1 p)
    {
        typedef typename Get<T, Index>::type Getter;
        p(Getter()(x), Index());
        return Visit1<T, Proc, typename Successor<Index>::type, Arity>()(x, p);
    }
};

// Note that T may be const-qualified
template<typename T, typename Proc, typename Index, typename Arity>
struct TYPE_DEFAULT_VISIBILITY Visit2;

template<typename T, typename Proc, typename Arity>
struct TYPE_DEFAULT_VISIBILITY Visit2<T, Proc, Arity, Arity>
{
    typedef Visit2 type;
    typedef true_type IntrospectionEnabled;
    typedef typename deduce_input_type<T&>::type input_type_0;
    typedef typename deduce_input_type<T&>::type input_type_1;
    typedef Proc input_type_2;
    typedef Proc codomain_type;

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(input_type_0 x, input_type_1 y, input_type_2 p)
    {
        return p;
    }
};

template<typename T, typename Proc, typename Index, typename Arity>
struct TYPE_DEFAULT_VISIBILITY Visit2
{
    typedef Visit2 type;
    typedef true_type IntrospectionEnabled;
    typedef typename deduce_input_type<T&>::type input_type_0;
    typedef typename deduce_input_type<T&>::type input_type_1;
    typedef Proc input_type_2;
    typedef Proc codomain_type;

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(input_type_0 x, input_type_1 y, input_type_2 p)
    {
        typedef typename Get<T, Index>::type Getter;
        p(Getter()(x), Getter()(y), Index());
        return Visit2<T, Proc, typename Successor<Index>::type, Arity>()(x, y, p);
    }
};

template<typename T, typename Proc>
ALWAYS_INLINE_HIDDEN Proc visit(T& x, Proc p)
{
    return Visit1<T, Proc, Integer<0>, typename IntrospectionArity<T>::type>()(x, p);
}

template<typename T, typename Proc>
ALWAYS_INLINE_HIDDEN Proc visit(T& x, T& y, Proc p)
{
    return Visit2<T, Proc, Integer<0>, typename IntrospectionArity<T>::type>()(x, y, p);
}


template<typename T, typename Proc>
ALWAYS_INLINE_HIDDEN Proc visit2(T& x, Proc p)
{
    p(VisitStart());
    p =  Visit1<T, Proc, Integer<0>, typename IntrospectionArity<T>::type>()(x, p);
    p(VisitEnd());
    return p;
}

template<typename T, typename Proc>
ALWAYS_INLINE_HIDDEN Proc visit2(T& x, T& y, Proc p)
{
    p(VisitStart());
    p = Visit2<T, Proc, Integer<0>, typename IntrospectionArity<T>::type>()(x, y, p);
    p(VisitEnd());
    return p;
}

} // namespace Visit_impl

template<typename T, typename Proc>
ALWAYS_INLINE_HIDDEN Proc visit(T& x, Proc p)
{
    return Visit_impl::visit(get_storage(x), p);
}

template<typename T, typename U, typename Proc>
ALWAYS_INLINE_HIDDEN Proc visit(T& x, U& y, Proc p)
{
    return Visit_impl::visit(get_storage(x), get_storage(y), p);
}

template<typename T, typename Proc>
ALWAYS_INLINE_HIDDEN Proc visit_with_start_end(T& x, Proc p)
{
    return Visit_impl::visit2(get_storage(x), p);
}

template<typename T, typename U, typename Proc>
ALWAYS_INLINE_HIDDEN Proc visit_with_start_end(T& x, U& y, Proc p)
{
    return Visit_impl::visit2(get_storage(x), get_storage(y), p);
}

namespace introspected_comparisons_impl {

template<typename GetComparator>
struct TYPE_DEFAULT_VISIBILITY Equal_Visitor
{
    bool value; // Should be initialised to true, but want to keep POD-ness of the type

    typedef Equal_Visitor type;
    typedef true_type IntrospectionEnabled;
    typedef bool IntrospectionItem0;

    template<typename T, typename Index>
    ALWAYS_INLINE_HIDDEN void
    operator() (T const& x, T const& y, Index)
    {
        value = value ? typename Apply<GetComparator, T>::type()(x, y) : false ;
    }
};

template<typename GetComparator>
struct TYPE_DEFAULT_VISIBILITY Less_Visitor
{
    bool value; // Should be initialised to false, but want to keep POD-ness of the type

    typedef Less_Visitor type;
    typedef true_type IntrospectionEnabled;
    typedef bool IntrospectionItem0;

    template<typename T, typename Index>
    ALWAYS_INLINE_HIDDEN void
    operator() (T const& x, T const& y, Index)
    {
        value = value ? true : typename Apply<GetComparator, T>::type()(x, y);
    }
};

template<typename GetComparator, typename T>
ALWAYS_INLINE_HIDDEN bool equal_impl(T const& x, T const& y)
{
    Equal_Visitor<GetComparator> tmp = {true};
    return visit(x, y, tmp).value;
}

template<typename GetComparator, typename T>
ALWAYS_INLINE_HIDDEN bool less_impl(T const& x, T const& y)
{
    Less_Visitor<GetComparator> tmp = {false};
    return visit(x, y, tmp).value;
}

} // namespace introspected_comparisons_impl

template<typename T, typename enable=void>
struct TYPE_HIDDEN_VISIBILITY generate_introspected_comparisons : IntrospectionEnabled<T> {METAPROGRAMMING_ONLY(generate_introspected_comparisons)};

template<typename T>
struct TYPE_DEFAULT_VISIBILITY less<T, typename enable_if<generate_introspected_comparisons<T>, void>::type>
{
    typedef less type;
    typedef true_type IntrospectionEnabled;
    typedef typename parameter_type<T>::type input_type_0;
    typedef typename parameter_type<T>::type input_type_1;
    typedef bool codomain_type;

    // Note function not forced to be always inline; wrapper operators are simple functions but
    // this may not be.
    INLINE codomain_type
    operator()(input_type_0 x, input_type_1 y) const
    {
        return introspected_comparisons_impl::less_impl<less<placeholders::_0> >(get_storage(x), get_storage(y));
    }
};

template<typename T>
struct TYPE_DEFAULT_VISIBILITY equal<T, typename enable_if<generate_introspected_comparisons<T>, void>::type>
{
    typedef equal type;
    typedef true_type IntrospectionEnabled;
    typedef typename parameter_type<T>::type input_type_0;
    typedef typename parameter_type<T>::type input_type_1;
    typedef bool codomain_type;

    // Note function not forced to be always inline; wrapper operators are simple functions but
    // this may not be.
    INLINE codomain_type
    operator()(input_type_0 x, input_type_1 y) const
    {
        return introspected_comparisons_impl::equal_impl<equal<placeholders::_0> >(get_storage(x), get_storage(y));
    }
};

// Note function not forced to be always inline; wrapper operators are simple functions but
// this may not be.
template<typename T>
INLINE typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator==(T const& x, T const& y)
{
    return introspected_comparisons_impl::equal_impl<OperatorEquals<placeholders::_0> >(get_storage(x), get_storage(y));
}

template<typename T>
ALWAYS_INLINE_HIDDEN typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator!=(T const& x, T const& y)
{
    return !(x == y);
}

// Note function not forced to be always inline; wrapper operators are simple functions but
// this may not be.
template<typename T>
INLINE typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator<(T const& x, T const& y)
{
    return introspected_comparisons_impl::less_impl<OperatorLessThan<placeholders::_0> >(get_storage(x), get_storage(y));
}

template<typename T>
ALWAYS_INLINE_HIDDEN
typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator<=(T const& x, T const& y)
{
    return !(y < x);
}

template<typename T>
ALWAYS_INLINE_HIDDEN typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator>(T const& x, T const& y)
{
    return y < x;
}

template<typename T>
ALWAYS_INLINE_HIDDEN typename enable_if<generate_introspected_comparisons<T>, bool>::type
operator>=(T const& x, T const& y)
{
    return !(x < y);
}


template<typename T, typename enable=void>
struct TYPE_HIDDEN_VISIBILITY generate_introspected_underlying_type : IntrospectionEnabled<T> {METAPROGRAMMING_ONLY(generate_introspected_underlying_type)};

template<typename Tag>
struct TYPE_HIDDEN_VISIBILITY generate_introspected_underlying_type<empty_type<Tag> > : false_type {METAPROGRAMMING_ONLY(generate_introspected_underlying_type)};

template<typename T, typename Tag>
struct TYPE_HIDDEN_VISIBILITY generate_introspected_underlying_type<singleton<T, Tag> > : false_type {METAPROGRAMMING_ONLY(generate_introspected_underlying_type)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY underlying_type<T,
    typename enable_if<generate_introspected_underlying_type<T>, void>::type>
{
    typedef typename ArrayTransform<typename GenerateIntrospectionItems<T>::type, get_underlying_type<placeholders::_0> >::type TransformedTypes;

    typedef typename GenerateStorageFromArray<TransformedTypes,
        typename IntrospectionStorageTag<T>::type>::type type;
    METAPROGRAMMING_ONLY(underlying_type)
};

// ArrayNoArg type and singleton can be reduced to simpler cases, unwrapping the struct in singelton's case
template<typename Tag>
struct TYPE_HIDDEN_VISIBILITY underlying_type<empty_type<Tag> > : empty_type<Tag> {METAPROGRAMMING_ONLY(underlying_type)};

template<typename T, typename Tag>
struct TYPE_HIDDEN_VISIBILITY underlying_type<singleton<T, Tag> > : get_underlying_type<T> {METAPROGRAMMING_ONLY(underlying_type)};


template<typename Arr, typename Tag>
struct TYPE_HIDDEN_VISIBILITY deduce_type
{
    typedef typename ArrayTransform<Arr, decay_ref<placeholders::_0> >::type TransformedTypes;

    typedef typename GenerateStorageFromArray<TransformedTypes,
        Tag>::type type;
    METAPROGRAMMING_ONLY(deduce_type)
};

// The make_storage functions deduce a storage type based on the parameters passed in,
// taking into account "decaying" Ref objects.
template<typename Tag>
ALWAYS_INLINE_HIDDEN typename deduce_type<Array<>, Tag>::type make_storage()
{
    typedef typename deduce_type<Array<>, Tag>::type T;
    return T::make();
}

template<typename Tag, typename T0>
ALWAYS_INLINE_HIDDEN typename deduce_type<Array<T0>, Tag>::type make_storage(T0 const& m0)
{
    typedef typename deduce_type<Array<T0>, Tag>::type T;
    return T::make(m0);
}

template<typename Tag, typename T0, typename T1>
ALWAYS_INLINE_HIDDEN typename deduce_type<Array<T0, T1>, Tag>::type make_storage(T0 const& m0, T1 const& m1)
{
    typedef typename deduce_type<Array<T0, T1>, Tag>::type T;
    return T::make(m0, m1);
}

template<typename Tag, typename T0, typename T1, typename T2>
ALWAYS_INLINE_HIDDEN typename deduce_type<Array<T0, T1, T2>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2)
{
    typedef typename deduce_type<Array<T0, T1, T2>, Tag>::type T;
    return T::make(m0, m1, m2);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3>
ALWAYS_INLINE_HIDDEN typename deduce_type<Array<T0, T1, T2, T3>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3>, Tag>::type T;
    return T::make(m0, m1, m2, m3);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4>
ALWAYS_INLINE_HIDDEN typename deduce_type<Array<T0, T1, T2, T3, T4>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3, T4 const& m4)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3, T4>, Tag>::type T;
    return T::make(m0, m1, m2, m3, m4);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
ALWAYS_INLINE_HIDDEN typename deduce_type<Array<T0, T1, T2, T3, T4, T5>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3, T4 const& m4, T5 const& m5)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3, T4, T5>, Tag>::type T;
    return T::make(m0, m1, m2, m3, m4, m5);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
ALWAYS_INLINE_HIDDEN typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3, T4 const& m4, T5 const& m5, T6 const& m6)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6>, Tag>::type T;
    return T::make(m0, m1, m2, m3, m4, m5, m6);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
ALWAYS_INLINE_HIDDEN typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3, T4 const& m4, T5 const& m5, T6 const& m6, T7 const& m7)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Tag>::type T;
    return T::make(m0, m1, m2, m3, m4, m5, m6, m7);
}

template<typename Tag, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
ALWAYS_INLINE_HIDDEN typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Tag>::type make_storage(T0 const& m0, T1 const& m1, T2 const& m2, T3 const& m3, T4 const& m4, T5 const& m5, T6 const& m6, T7 const& m7, T8 const& m8)
{
    typedef typename deduce_type<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Tag>::type T;
    return T::make(m0, m1, m2, m3, m4, m5, m6, m7, m8);
}


} // namespace intro

#endif
