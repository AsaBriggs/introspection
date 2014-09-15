#ifndef INCLUDED_METAPROGRAMMING
#define INCLUDED_METAPROGRAMMING

#ifndef INCLUDED_CSTDDEF
#include <cstddef>
#define INCLUDED_CSTDDEF
#endif

#ifndef INCLUDED_COMPILER_SPECIFICS
#include "compiler_specifics.h"
#endif

#ifndef INCLUDED_INTROSPECTION_NUMERICS
#include "introspection_numerics.h"
#endif

#ifndef INCLUDED_INTROSPECTION_ASSERT
#include "introspection_assert.h"
#endif

namespace intro {

struct TYPE_DEFAULT_VISIBILITY true_type
{
    typedef true_type type;
    static const bool value = true;
    ALWAYS_INLINE_HIDDEN operator bool() const { return value ; }
};

struct TYPE_DEFAULT_VISIBILITY false_type
{
    typedef false_type type;
    static const bool value = false;
    ALWAYS_INLINE_HIDDEN operator bool() const { return value ; }
};

template<int num>
struct TYPE_DEFAULT_VISIBILITY Integer
{
    typedef Integer type;
    static const int value = num;
    ALWAYS_INLINE_HIDDEN operator int() const { return value ; }
};

struct TYPE_HIDDEN_VISIBILITY DefaultTag
{
    typedef DefaultTag type;
    typedef true_type IntrospectionEnabled;
    METAPROGRAMMING_ONLY(DefaultTag)
};

template<typename T>
struct TYPE_DEFAULT_VISIBILITY Ref
{
    typedef Ref type;
    typedef true_type IntrospectionEnabled;
    typedef T* IntrospectionItem0;
    T* m0; // hold by pointer to make the type regular (assignment is enabled).

    // Need implict conversion operator to allow
    // storage conversion to happen without another function call
    ALWAYS_INLINE_HIDDEN operator T&() const { return *m0; }

    template<typename P0>
    static ALWAYS_INLINE_HIDDEN type make(P0& p0)
    {
        T& x = p0;
        type tmp = {&x};
        return tmp;
    }
};

// Caller of make_ref must ensure the lifetime of the referenced object is greater
// than the lifetime of the Ref.
template<typename T>
ALWAYS_INLINE_HIDDEN Ref<T> make_ref(T& x)
{
    return Ref<T>::make(x);
}


template<bool value>
struct TYPE_HIDDEN_VISIBILITY ValueToTrueFalse;

template<>
struct TYPE_HIDDEN_VISIBILITY ValueToTrueFalse<false> : false_type {METAPROGRAMMING_ONLY(ValueToTrueFalse)};

template<>
struct TYPE_HIDDEN_VISIBILITY ValueToTrueFalse<true> : true_type {METAPROGRAMMING_ONLY(ValueToTrueFalse)};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY Successor;

template<int num>
struct TYPE_HIDDEN_VISIBILITY Successor<Integer<num> > : Integer<num+1> {METAPROGRAMMING_ONLY(Successor)};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY Predecessor;

template<int num>
struct TYPE_HIDDEN_VISIBILITY Predecessor<Integer<num> > : Integer<num-1> {METAPROGRAMMING_ONLY(Predecessor)};


namespace Min_impl {

template<typename T, typename U, bool ULessThanT>
struct TYPE_HIDDEN_VISIBILITY Min;

template<typename T, typename U>
struct TYPE_HIDDEN_VISIBILITY Min<T, U, false> : T {METAPROGRAMMING_ONLY(Min)};

template<typename T, typename U>
struct TYPE_HIDDEN_VISIBILITY Min<T, U, true> : U {METAPROGRAMMING_ONLY(Min)};

} // namespace Min_impl

template<typename T, typename U>
struct TYPE_HIDDEN_VISIBILITY Min : Min_impl::Min<T, U, U::type::value < T::type::value> {METAPROGRAMMING_ONLY(Min)};


namespace Max_impl {

template<typename T, typename U, bool ULessThanT>
struct TYPE_HIDDEN_VISIBILITY Max;

template<typename T, typename U>
struct TYPE_HIDDEN_VISIBILITY Max<T, U, false> : U {METAPROGRAMMING_ONLY(Max)};

template<typename T, typename U>
struct TYPE_HIDDEN_VISIBILITY Max<T, U, true> : T {METAPROGRAMMING_ONLY(Max)};

} // namespace Max_impl

template<typename T, typename U>
struct TYPE_HIDDEN_VISIBILITY Max : Max_impl::Max<T, U, U::type::value < T::type::value> {METAPROGRAMMING_ONLY(Max)};


template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY Subtract;

template<int num0, int num1>
struct TYPE_HIDDEN_VISIBILITY Subtract<Integer<num0>, Integer<num1> > : Integer<num0 - num1> {METAPROGRAMMING_ONLY(Subtract)};


template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY Add;

template<int num0, int num1>
struct TYPE_HIDDEN_VISIBILITY Add<Integer<num0>, Integer<num1> > : Integer<num0 + num1> {METAPROGRAMMING_ONLY(Add)};


template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY Multiply;

template<int num0, int num1>
struct TYPE_HIDDEN_VISIBILITY Multiply<Integer<num0>, Integer<num1> > : Integer<num0 * num1> {METAPROGRAMMING_ONLY(Multiply)};


template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY Divide;

template<int num0, int num1>
struct TYPE_HIDDEN_VISIBILITY Divide<Integer<num0>, Integer<num1> > : Integer<num0 / num1> {METAPROGRAMMING_ONLY(Divide)};


template<typename T0>
struct TYPE_HIDDEN_VISIBILITY Negate;

template<int num>
struct TYPE_HIDDEN_VISIBILITY Negate<Integer<num> > : Integer<-num> {METAPROGRAMMING_ONLY(Negate)};


namespace not_impl {

template<typename V>
struct TYPE_HIDDEN_VISIBILITY not_;

template<>
struct TYPE_HIDDEN_VISIBILITY not_<false_type> : true_type {METAPROGRAMMING_ONLY(not_)};

template<>
struct TYPE_HIDDEN_VISIBILITY not_<true_type> : false_type {METAPROGRAMMING_ONLY(not_)};

} // namespace not_impl

template<typename V>
struct TYPE_HIDDEN_VISIBILITY not_ : not_impl::not_<typename V::type> {METAPROGRAMMING_ONLY(not_)};


namespace or_impl {

template<typename V0, typename V1, typename V2>
struct TYPE_HIDDEN_VISIBILITY or_;

template<>
struct TYPE_HIDDEN_VISIBILITY or_<false_type, false_type, false_type> : false_type {METAPROGRAMMING_ONLY(or_)};

template<typename V1, typename V2>
struct TYPE_HIDDEN_VISIBILITY or_<true_type, V1, V2> : true_type {METAPROGRAMMING_ONLY(or_)};

template<typename V1, typename V2>
struct TYPE_HIDDEN_VISIBILITY or_<false_type, V1, V2> : or_<typename V1::type, V2, false_type> {METAPROGRAMMING_ONLY(or_)};

} // namespace or_impl

template<typename V0, typename V1, typename V2=false_type>
struct TYPE_HIDDEN_VISIBILITY or_ : or_impl::or_<typename V0::type, V1, V2> {METAPROGRAMMING_ONLY(or_)};


namespace and_impl {

template<typename V0, typename V1, typename V2>
struct TYPE_HIDDEN_VISIBILITY and_;

template<>
struct TYPE_HIDDEN_VISIBILITY and_<true_type, true_type, true_type> : true_type {METAPROGRAMMING_ONLY(and_)};

template<typename V1, typename V2>
struct TYPE_HIDDEN_VISIBILITY and_<false_type, V1, V2> : false_type {METAPROGRAMMING_ONLY(and_)};

template<typename V1, typename V2>
struct TYPE_HIDDEN_VISIBILITY and_<true_type, V1, V2> : and_<typename V1::type, V2, true_type> {METAPROGRAMMING_ONLY(and_)};

} // namespace and_impl

template<typename V0, typename V1, typename V2=true_type>
struct TYPE_HIDDEN_VISIBILITY and_ : and_impl::and_<typename V0::type, V1, V2> {METAPROGRAMMING_ONLY(and_)};


namespace enable_if_impl {

template<typename enable, typename T>
struct TYPE_HIDDEN_VISIBILITY enable_if;

template<typename T>
struct TYPE_HIDDEN_VISIBILITY enable_if<true_type, T>
{
    typedef T type;
    METAPROGRAMMING_ONLY(enable_if)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY enable_if<false_type, T> {METAPROGRAMMING_ONLY(enable_if)};

} // namespace enable_if_impl

template<typename enable, typename T>
struct TYPE_HIDDEN_VISIBILITY enable_if : enable_if_impl::enable_if<typename enable::type, T> {METAPROGRAMMING_ONLY(enable_if)};


namespace disable_if_impl {

template<typename enable, typename T>
struct TYPE_HIDDEN_VISIBILITY disable_if;

template<typename T>
struct TYPE_HIDDEN_VISIBILITY disable_if<true_type, T> {METAPROGRAMMING_ONLY(disable_if)};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY disable_if<false_type, T>
{
    typedef T type;
    METAPROGRAMMING_ONLY(disable_if)
};

} // namespace disable_if_impl

template<typename enable, typename T>
struct TYPE_HIDDEN_VISIBILITY disable_if : disable_if_impl::disable_if<typename enable::type, T> {METAPROGRAMMING_ONLY(disable_if)};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY identity_type
{
    typedef T type;
    METAPROGRAMMING_ONLY(identity_type)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY identity_type<identity_type<T> > : identity_type<T> {METAPROGRAMMING_ONLY(identity_type)};


namespace if_impl {

template<typename Test, typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY if_;

template<typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY if_<true_type, T, F>
{
    typedef T type;
    METAPROGRAMMING_ONLY(if_)
};

template<typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY if_<false_type, T, F>
{
    typedef F type;
    METAPROGRAMMING_ONLY(if_)
};

} // namespace if_impl

template<typename Test, typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY if_ : if_impl::if_<typename Test::type, T, F> {METAPROGRAMMING_ONLY(if_)};


namespace eval_if_impl {

template<typename Test, typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY eval_if;

template<typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY eval_if<true_type, T, F>
{
    typedef typename T::type type;
    METAPROGRAMMING_ONLY(eval_if)
};

template<typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY eval_if<false_type, T, F>
{
    typedef typename F::type type;
    METAPROGRAMMING_ONLY(eval_if)
};

} // namespace eval_if_impl

template<typename Test, typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY eval_if : eval_if_impl::eval_if<typename Test::type, T, F> {METAPROGRAMMING_ONLY(eval_if)};


template<typename T, typename U>
struct TYPE_HIDDEN_VISIBILITY is_same : false_type {METAPROGRAMMING_ONLY(is_same)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY is_same<T, T> : true_type {METAPROGRAMMING_ONLY(is_same)};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY is_reference : false_type {METAPROGRAMMING_ONLY(is_reference)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY is_reference<T&> : true_type {METAPROGRAMMING_ONLY(is_reference)};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY make_const_ref
{
    typedef T const& type;
    METAPROGRAMMING_ONLY(make_const_ref)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY make_const_ref<T&>
{
    typedef T const& type;
    METAPROGRAMMING_ONLY(make_const_ref)
};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY make_ref_type
{
    typedef T& type;
    METAPROGRAMMING_ONLY(make_ref_type)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY make_ref_type<T&>
{
    typedef T& type;
    METAPROGRAMMING_ONLY(make_ref_type)
};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY deduce_input_type
{
    typedef T type;
    METAPROGRAMMING_ONLY(deduce_input_type)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY deduce_input_type<T const&>
{
    typedef T type;
    METAPROGRAMMING_ONLY(deduce_input_type)
};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY parameter_type
{
    typedef T const& type;
    METAPROGRAMMING_ONLY(parameter_type)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY parameter_type<T*>
{
    typedef T* type;
    METAPROGRAMMING_ONLY(parameter_type)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY parameter_type<T&>
{
    typedef T& type;
    METAPROGRAMMING_ONLY(parameter_type)
};

#define X(x)template<> \
struct TYPE_HIDDEN_VISIBILITY parameter_type<x> \
{ \
    typedef x type; \
    METAPROGRAMMING_ONLY(parameter_type) \
}; \

// Use the X-Macro
FUNDAMENTAL_TYPES

#undef X

template<typename T, typename enable=void>
struct TYPE_HIDDEN_VISIBILITY underlying_type
{
    typedef T type;
    METAPROGRAMMING_ONLY(underlying_type)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY get_underlying_type
{
    typedef typename underlying_type<T>::type type;
    INTROSPECTION_STATIC_ASSERT(( typename ValueToTrueFalse<sizeof(T) == sizeof(type)>::type ));
};

template<typename T>
ALWAYS_INLINE_HIDDEN typename get_underlying_type<T>::type& get_underlying_ref(T& x)
{
    return reinterpret_cast<typename get_underlying_type<T>::type&>(x);
}

template<typename T>
INLINE_HIDDEN void swap_basic(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template<typename T>
ALWAYS_INLINE_HIDDEN void swap(T& x, T& y)
{
    swap_basic(get_underlying_ref(x), get_underlying_ref(y));
}

template<typename T, typename enable=void>
struct TYPE_DEFAULT_VISIBILITY OperatorEquals
{
    typedef OperatorEquals type;
    typedef true_type IntrospectionEnabled;
    typedef typename parameter_type<T>::type input_type_0;
    typedef typename parameter_type<T>::type input_type_1;
    typedef bool codomain_type;

    INLINE codomain_type
    operator()(input_type_0 x, input_type_1 y) const
    {
        return x == y;
    }
};


template<typename T, typename enable=void>
struct TYPE_DEFAULT_VISIBILITY OperatorLessThan
{
    typedef OperatorLessThan type;
    typedef true_type IntrospectionEnabled;
    typedef typename parameter_type<T>::type input_type_0;
    typedef typename parameter_type<T>::type input_type_1;
    typedef bool codomain_type;

    INLINE codomain_type
    operator()(input_type_0 x, input_type_1 y) const
    {
        return x < y;
    }
};


template<typename T, typename enable=void>
struct TYPE_DEFAULT_VISIBILITY less : OperatorLessThan<T> {};

template<typename T, typename enable=void>
struct TYPE_DEFAULT_VISIBILITY equal : OperatorEquals<T> {};


namespace decay_ref_impl {

template<typename T>
struct TYPE_HIDDEN_VISIBILITY decay_ref
{
    typedef T type;
    METAPROGRAMMING_ONLY(decay_ref)
};

template<typename T, ptrdiff_t N>
  struct TYPE_HIDDEN_VISIBILITY decay_ref<T(&)[N]>
{
    typedef T* type;
    METAPROGRAMMING_ONLY(decay_ref)
};

template<typename T>
  struct TYPE_HIDDEN_VISIBILITY decay_ref<T(&)[]>
{
    typedef T* type;
    METAPROGRAMMING_ONLY(decay_ref)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY decay_ref<Ref<T> >
{
    typedef T& type;
    METAPROGRAMMING_ONLY(decay_ref)
};

} // namespace decay_ref_impl

template<typename T>
struct TYPE_HIDDEN_VISIBILITY decay_ref : decay_ref_impl::decay_ref<T> {METAPROGRAMMING_ONLY(decay_ref)};


template<typename From, typename To>
struct TYPE_HIDDEN_VISIBILITY is_convertible
{
private:
    typedef char Yes;
    struct TYPE_HIDDEN_VISIBILITY No { char a[2]; };
    static HIDDEN No test(...);
    static HIDDEN Yes test(To);
    static HIDDEN From get();
public:
    typedef typename ValueToTrueFalse<sizeof(test(get())) ==1>::type type;
    METAPROGRAMMING_ONLY(is_convertible)
};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY is_struct_class_or_union
{
private:
    typedef char Yes;
    struct TYPE_HIDDEN_VISIBILITY No { char x[2]; };
    template<typename U>
    static HIDDEN Yes test(char U::*);
    template<typename U>
    static HIDDEN No test(...);
public:
    typedef typename ValueToTrueFalse<sizeof(test<T>(0)) == 1>::type type;
    METAPROGRAMMING_ONLY(is_struct_class_or_union)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY is_struct_class_or_union<T*> : false_type
{
    METAPROGRAMMING_ONLY(is_struct_class_or_union)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY is_struct_class_or_union<T&> : false_type
{
    METAPROGRAMMING_ONLY(is_struct_class_or_union)
};

#define X(x)template<> \
struct TYPE_HIDDEN_VISIBILITY is_struct_class_or_union<x> : false_type \
{ \
    METAPROGRAMMING_ONLY(is_struct_class_or_union) \
}; \

// Use the X-Macro
INTEGRAL_TYPES
FLOATING_POINT_TYPES
// Note that NULL_POINTER_TYPE is implemented as a struct, hence FUNDAMENTAL_TYPES macro was not used.

#undef X


struct TYPE_DEFAULT_VISIBILITY ArrayNoArg
{
    typedef ArrayNoArg type;
};


// Note that Array has as many types as Apply can handle with placeholder expressions.
// Attempting to expand the interface would destroy the ability of Apply to handle all Arrays passed to it.
template<typename T0=ArrayNoArg, typename T1=ArrayNoArg, typename T2=ArrayNoArg, typename T3=ArrayNoArg, typename T4=ArrayNoArg, typename T5=ArrayNoArg, typename T6=ArrayNoArg, typename T7=ArrayNoArg, typename T8=ArrayNoArg, typename T9=ArrayNoArg>
struct TYPE_HIDDEN_VISIBILITY Array
{
    typedef Array type;
    METAPROGRAMMING_ONLY(Array)
};


template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<0> >
{
    typedef T0 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<1> >
{
    typedef T1 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<2> >
{
    typedef T2 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<3> >
{
    typedef T3 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<4> >
{
    typedef T4 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<5> >
{
    typedef T5 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<6> >
{
    typedef T6 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<7> >
{
    typedef T7 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<8> >
{
    typedef T8 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<9> >
{
    typedef T9 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY ArraySize;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > : Integer<10> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8> > : Integer<9> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4, T5, T6, T7> > : Integer<8> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4, T5, T6> > : Integer<7> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4, T5> > : Integer<6> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4> > : Integer<5> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3> > : Integer<4> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2> > : Integer<3> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1> > : Integer<2> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0> > : Integer<1> {METAPROGRAMMING_ONLY(ArraySize)};

template<>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<> > : Integer<0> {METAPROGRAMMING_ONLY(ArraySize)};


template<typename T, typename U>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat ;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, U0> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, T7, U0, U1> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, U0, U1, U2> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4, T5>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, U0, U1, U2, U3> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, U0, U1, U2, U3, U4> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, U0, U1, U2, U3, U4, U5> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, U0, U1, U2, U3, U4, U5, U6> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, U0, U1, U2, U3, U4, U5, U6, U7> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, U0, U1, U2, U3, U4, U5, U6, U7, U8> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> {METAPROGRAMMING_ONLY(ArrayConcat)};


template<typename T, typename At>
struct TYPE_HIDDEN_VISIBILITY ArraySplit;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<0> > : Array<Array<>, Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<1> > : Array<Array<T0>, Array<T1, T2, T3, T4, T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<2> > : Array<Array<T0, T1>, Array<T2, T3, T4, T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<3> > : Array<Array<T0, T1, T2>, Array<T3, T4, T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<4> > : Array<Array<T0, T1, T2, T3>, Array<T4, T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<5> > : Array<Array<T0, T1, T2, T3, T4>, Array<T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<6> > : Array<Array<T0, T1, T2, T3, T4, T5>, Array<T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<7> > : Array<Array<T0, T1, T2, T3, T4, T5, T6>, Array<T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<8> > : Array<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Array<T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<9> > : Array<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Array<T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<10> > : Array<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Array<> > {METAPROGRAMMING_ONLY(ArraySplit)};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > : Array<T9, T8, T7, T6, T5, T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8> > : Array<T8, T7, T6, T5, T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6, T7> > : Array<T7, T6, T5, T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6> > : Array<T6, T5, T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4, T5> > : Array<T5, T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4> > : Array<T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3> > : Array<T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2> > : Array<T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1> > : Array<T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0> > : Array<T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<> > : Array<> {METAPROGRAMMING_ONLY(ArrayReverse)};


template<typename T, typename F, typename M, typename L>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate;
// Needs L <= ArraySize<T>

template<typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate<T, F, F, F> : T {METAPROGRAMMING_ONLY(ArrayRotate)};

template<typename T, typename F, typename L>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate<T, F, F, L> : T {METAPROGRAMMING_ONLY(ArrayRotate)};

template<typename T, typename F, typename L>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate<T, F, L, L> : T {METAPROGRAMMING_ONLY(ArrayRotate)};

template<typename T, typename F, typename M, typename L>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate
{
  // Assert F <= M
  // Assert M <= L
  // Assert L <= ArraySize<T>
  // Split into
  // 0..F, F..M, M..L, L..End
  //
  typedef typename ArraySplit<T, F>::type SplitAtFirst; // T0 = 0..F
  typedef typename ArraySplit<typename ArrayIndex<SplitAtFirst, Integer<1> >::type, typename Subtract<M, F>::type>::type SplitAtM; // T0 = F..M
  typedef typename ArraySplit<typename ArrayIndex<SplitAtM, Integer<1> >::type, typename Subtract<L, M>::type>::type SplitAtL; // T0 = M..L, T1 = L..end

  typedef typename ArrayConcat<typename ArrayIndex<SplitAtFirst, Integer<0> >::type, typename ArrayIndex<SplitAtL, Integer<0> >::type>::type A; // 0..F & M..L
  typedef typename ArrayConcat<A, typename ArrayIndex<SplitAtM, Integer<0> >::type>::type B; // 0..F & M..L & F..M
  typedef typename ArrayConcat<B, typename ArrayIndex<SplitAtL, Integer<1> >::type>::type type; // 0..F & M..L & F..M & L..End
};


template<typename T, typename M>
struct TYPE_HIDDEN_VISIBILITY ArrayRotateDefault : ArrayRotate<T, Integer<0>, M, typename ArraySize<T>::type > {METAPROGRAMMING_ONLY(ArrayRotateDefault)};


namespace placeholders {

template<typename Index>
struct TYPE_HIDDEN_VISIBILITY Placeholder
{
    typedef Placeholder type;
    METAPROGRAMMING_ONLY(Placeholder)
};

typedef Placeholder<Integer<0> > _0;
typedef Placeholder<Integer<1> > _1;
typedef Placeholder<Integer<2> > _2;
typedef Placeholder<Integer<3> > _3;
typedef Placeholder<Integer<4> > _4;
typedef Placeholder<Integer<5> > _5;
typedef Placeholder<Integer<6> > _6;
typedef Placeholder<Integer<7> > _7;
typedef Placeholder<Integer<8> > _8;
typedef Placeholder<Integer<9> > _9;
// Thinking about the processing required to get placeholder _ to work
// I don't consider it worthwhile; either we need to loop over the placeholder expression
// replacing _ with numberered placeholders one-by-one or there has to be a big
// "match all possible placeholder combinations" which would be hideous to write.

} // namespace placeholders

namespace Apply_impl {

// Type deliberately distinct from ArrayNoArgs so that
// applying < 10 arguments is distinguishable from wanting to apply ArrayNoArgs at that position.
struct TYPE_HIDDEN_VISIBILITY ignore
{
    typedef ignore type;
    METAPROGRAMMING_ONLY(ignore)
};

// Check performed on looking up the value of a placeholder in the current
// Apply application parameters
template<typename T>
struct TYPE_HIDDEN_VISIBILITY CheckIsNotNoArgument
{
    typedef T type;
    METAPROGRAMMING_ONLY(CheckIsNotNoArgument)
};

template<>
struct TYPE_HIDDEN_VISIBILITY CheckIsNotNoArgument<ignore>; // leave undefined as binding ignore is an error.

template<typename T, typename Environment>
struct TYPE_HIDDEN_VISIBILITY LookupPlaceholder
{
    typedef T type;
    METAPROGRAMMING_ONLY(LookupPlaceholder)
};

template<typename Index, typename Environment>
struct TYPE_HIDDEN_VISIBILITY LookupPlaceholder<placeholders::Placeholder<Index>, Environment> :
    CheckIsNotNoArgument<typename ArrayIndex<Environment, Index>::type>
{
    METAPROGRAMMING_ONLY(LookupPlaceholder)
};

// Environment Arity is required when a metafunction class is passed into Apply
// (as opposed to passing in a placeholder expression which can be analysed
// using template class parameter syntax).
template<typename T>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity;

template<>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore> > : Integer<0> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore> > : Integer<1> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore> > : Integer<2> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, ignore, ignore, ignore, ignore, ignore, ignore, ignore> > : Integer<3> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, ignore, ignore, ignore, ignore, ignore, ignore> > : Integer<4> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, ignore, ignore, ignore, ignore, ignore> > : Integer<5> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, ignore, ignore, ignore, ignore> > : Integer<6> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, ignore, ignore, ignore> > : Integer<7> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, T7, ignore, ignore> > : Integer<8> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, ignore> > : Integer<9> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > : Integer<10> {METAPROGRAMMING_ONLY(EnvironmentArity)};


template<typename T, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments
{
    typedef T type;
    METAPROGRAMMING_ONLY(BindArguments)
};

template<typename Index, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<placeholders::Placeholder<Index>, Environment> :
    LookupPlaceholder<placeholders::Placeholder<Index>, Environment>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename> class T, typename P0, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename> class T, typename P0, typename P1, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename> class T, typename P0, typename P1, typename P2, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4, P5>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4, P5, P6>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type,
      typename LookupPlaceholder<P6, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type,
      typename LookupPlaceholder<P6, Environment>::type,
      typename LookupPlaceholder<P7, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type,
      typename LookupPlaceholder<P6, Environment>::type,
      typename LookupPlaceholder<P7, Environment>::type,
      typename LookupPlaceholder<P8, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type,
      typename LookupPlaceholder<P6, Environment>::type,
      typename LookupPlaceholder<P7, Environment>::type,
      typename LookupPlaceholder<P8, Environment>::type,
      typename LookupPlaceholder<P9, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

// This is the magic of the Apply mechanism. The assumption is that the Arity of the
// environment is the arity of the metafunction class passed into it. Through this
// binding we obtain a placeholder expression that can be passed to BindArguments.
template<typename T, typename EnvironmentArity>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders;

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<0> >
{
    typedef T type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<1> >
{
    typedef typename T::template apply<placeholders::_0> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<2> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<3> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<4> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<5> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<6> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<7> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<8> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6, placeholders::_7> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<9> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6, placeholders::_7, placeholders::_8> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<10> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6, placeholders::_7, placeholders::_8, placeholders::_9> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

// Metafunction Class passed in, so add placeholders to nested template class apply
// and bind the Environment. Note Apply and BindArguments are different metafunctions to prevent
// an infinte loop when the Environment is empty
template<typename T, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply :
    BindArguments<typename AddPlaceholders<T, typename EnvironmentArity<Environment>::type >::type, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<typename Index, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<placeholders::Placeholder<Index>, Environment> :
    BindArguments<placeholders::Placeholder<Index>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename> class T, typename P0, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0>, Environment> : BindArguments<T<P0>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename> class T, typename P0, typename P1, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1>, Environment> : BindArguments<T<P0, P1>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename> class T, typename P0, typename P1, typename P2, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2>, Environment> : BindArguments<T<P0, P1, P2>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3>, Environment> : BindArguments<T<P0, P1, P2, P3>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4>, Environment> : BindArguments<T<P0, P1, P2, P3, P4>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4, P5>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4, P5, P6>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4, P5, P6, P7>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4, P5, P6, P7, P8>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

} // namespace Apply_impl

template<typename T, typename P0=Apply_impl::ignore, typename P1=Apply_impl::ignore, typename P2=Apply_impl::ignore, typename P3=Apply_impl::ignore, typename P4=Apply_impl::ignore, typename P5=Apply_impl::ignore, typename P6=Apply_impl::ignore, typename P7=Apply_impl::ignore, typename P8=Apply_impl::ignore, typename P9=Apply_impl::ignore>
struct TYPE_HIDDEN_VISIBILITY Apply : Apply_impl::Apply<T, Array<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9> > {METAPROGRAMMING_ONLY(Apply)};

// Environment must be in the fom of an array where 0..N are parameters and the rest are ignore
// See RationaliseApplyArray for how to remove ArrayNoArg and the like.
template<typename T, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply_Environment : Apply_impl::Apply<T, Environment> {METAPROGRAMMING_ONLY(Apply_Environment)};


namespace ArrayTransform_impl {

template<typename T, typename Fun>
struct TYPE_HIDDEN_VISIBILITY ApplyIfNotArrayNoArg : Apply<Fun, T>
{
    METAPROGRAMMING_ONLY(ApplyIfNotArrayNoArg)
};

template<typename Fun>
struct TYPE_HIDDEN_VISIBILITY ApplyIfNotArrayNoArg<ArrayNoArg, Fun> : ArrayNoArg {METAPROGRAMMING_ONLY(ApplyIfNotArrayNoArg)};

} // ArrayTransform_impl

template<typename T, typename Fun>
struct TYPE_HIDDEN_VISIBILITY ArrayTransform
{
    typedef Array<typename ArrayTransform_impl::ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<0> >::type, Fun>::type,
                  typename ArrayTransform_impl::ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<1> >::type, Fun>::type,
                  typename ArrayTransform_impl::ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<2> >::type, Fun>::type,
                  typename ArrayTransform_impl::ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<3> >::type, Fun>::type,
                  typename ArrayTransform_impl::ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<4> >::type, Fun>::type,
                  typename ArrayTransform_impl::ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<5> >::type, Fun>::type,
                  typename ArrayTransform_impl::ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<6> >::type, Fun>::type,
                  typename ArrayTransform_impl::ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<7> >::type, Fun>::type,
                  typename ArrayTransform_impl::ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<8> >::type, Fun>::type,
                  typename ArrayTransform_impl::ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<9> >::type, Fun>::type> type;
    METAPROGRAMMING_ONLY(ArrayTransform)
};


namespace ArrayZip_impl {

template<typename T0, typename T1, typename Fun>
struct TYPE_HIDDEN_VISIBILITY ApplyIfNotArrayNoArg2 : Apply<Fun, T0, T1>
{
    METAPROGRAMMING_ONLY(ApplyIfNotArrayNoArg2)
};

template<typename Fun>
struct TYPE_HIDDEN_VISIBILITY ApplyIfNotArrayNoArg2<ArrayNoArg, ArrayNoArg, Fun> : ArrayNoArg {METAPROGRAMMING_ONLY(ApplyIfNotArrayNoArg2)};

} // namespace ArrayZip_impl

template<typename T, typename U, typename Fun>
struct TYPE_HIDDEN_VISIBILITY ArrayZip
{
    typedef Array<typename ArrayZip_impl::ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<0> >::type,
                                                                typename ArrayIndex<U, Integer<0> >::type, Fun>::type,
                  typename ArrayZip_impl::ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<1> >::type,
                                                                typename ArrayIndex<U, Integer<1> >::type, Fun>::type,
                  typename ArrayZip_impl::ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<2> >::type,
                                                                typename ArrayIndex<U, Integer<2> >::type, Fun>::type,
                  typename ArrayZip_impl::ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<3> >::type,
                                                                typename ArrayIndex<U, Integer<3> >::type, Fun>::type,
                  typename ArrayZip_impl::ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<4> >::type,
                                                                typename ArrayIndex<U, Integer<4> >::type, Fun>::type,
                  typename ArrayZip_impl::ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<5> >::type,
                                                                typename ArrayIndex<U, Integer<5> >::type, Fun>::type,
                  typename ArrayZip_impl::ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<6> >::type,
                                                                typename ArrayIndex<U, Integer<6> >::type, Fun>::type,
                  typename ArrayZip_impl::ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<7> >::type,
                                                                typename ArrayIndex<U, Integer<7> >::type, Fun>::type,
                  typename ArrayZip_impl::ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<8> >::type,
                                                                typename ArrayIndex<U, Integer<8> >::type, Fun>::type,
                  typename ArrayZip_impl::ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<9> >::type,
                                                                typename ArrayIndex<U, Integer<9> >::type, Fun>::type> type;
    METAPROGRAMMING_ONLY(ArrayZip)
};


namespace RationaliseApplyArray_impl {

template<typename T, typename From, typename To>
struct TYPE_HIDDEN_VISIBILITY RationaliseApplyArrayConvert
{
    typedef T type;
    METAPROGRAMMING_ONLY(RationaliseApplyArrayConvert)
};

template<typename From, typename To>
struct TYPE_HIDDEN_VISIBILITY RationaliseApplyArrayConvert<From, From, To>
{
    typedef To type;
    METAPROGRAMMING_ONLY(RationaliseApplyArrayConvert)
};

} // namespace RationaliseApplyArray_impl

template<typename T, typename ToRemove>
struct TYPE_HIDDEN_VISIBILITY RationaliseApplyArray
{
    // Did not use ArrayTransform as this skips over ArrayNoArg elements, which is not what this metafunction should do.
    typedef Array<typename RationaliseApplyArray_impl::RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<0> >::type, ToRemove, Apply_impl::ignore>::type,
                  typename RationaliseApplyArray_impl::RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<1> >::type, ToRemove, Apply_impl::ignore>::type,
                  typename RationaliseApplyArray_impl::RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<2> >::type, ToRemove, Apply_impl::ignore>::type,
                  typename RationaliseApplyArray_impl::RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<3> >::type, ToRemove, Apply_impl::ignore>::type,
                  typename RationaliseApplyArray_impl::RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<4> >::type, ToRemove, Apply_impl::ignore>::type,
                  typename RationaliseApplyArray_impl::RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<5> >::type, ToRemove, Apply_impl::ignore>::type,
                  typename RationaliseApplyArray_impl::RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<6> >::type, ToRemove, Apply_impl::ignore>::type,
                  typename RationaliseApplyArray_impl::RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<7> >::type, ToRemove, Apply_impl::ignore>::type,
                  typename RationaliseApplyArray_impl::RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<8> >::type, ToRemove, Apply_impl::ignore>::type,
                  typename RationaliseApplyArray_impl::RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<9> >::type, ToRemove, Apply_impl::ignore>::type> type;
    METAPROGRAMMING_ONLY(RationaliseApplyArray)
};


} // namespace intro

#endif
