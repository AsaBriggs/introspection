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

#ifndef INCLUDED_METAPROGRAMMING_INTEGER
#include "metaprogramming_integer.h"
#endif

#ifndef INCLUDED_METAPROGRAMMING_ARRAY
#include "metaprogramming_array.h"
#endif

#ifndef INCLUDED_METAPROGRAMMING_APPLY
#include "metaprogramming_apply.h"
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

template<IntegerValueType num>
struct TYPE_HIDDEN_VISIBILITY Successor<Integer<num> > : Integer<num+1> {METAPROGRAMMING_ONLY(Successor)};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY Predecessor;

template<IntegerValueType num>
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

template<typename T, typename U>
struct TYPE_HIDDEN_VISIBILITY Less;

template<IntegerValueType t, IntegerValueType u>
struct TYPE_HIDDEN_VISIBILITY Less<Integer<t>, Integer<u> > : Integer<(u<t)? u : t> {METAPROGRAMMING_ONLY(Less)};

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

template<typename T0>
struct TYPE_HIDDEN_VISIBILITY Increment;

template<IntegerValueType num0>
struct TYPE_HIDDEN_VISIBILITY Increment<Integer<num0> > : Integer<num0 + 1> {METAPROGRAMMING_ONLY(Increment)};

template<typename T0>
struct TYPE_HIDDEN_VISIBILITY Decrement;

template<IntegerValueType num0>
struct TYPE_HIDDEN_VISIBILITY Decrement<Integer<num0> > : Integer<num0 - 1> {METAPROGRAMMING_ONLY(Decrement)};


template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY Subtract;

template<IntegerValueType num0, IntegerValueType num1>
struct TYPE_HIDDEN_VISIBILITY Subtract<Integer<num0>, Integer<num1> > : Integer<num0 - num1> {METAPROGRAMMING_ONLY(Subtract)};


template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY Add;

template<IntegerValueType num0, IntegerValueType num1>
struct TYPE_HIDDEN_VISIBILITY Add<Integer<num0>, Integer<num1> > : Integer<num0 + num1> {METAPROGRAMMING_ONLY(Add)};


template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY Multiply;

template<IntegerValueType num0, IntegerValueType num1>
struct TYPE_HIDDEN_VISIBILITY Multiply<Integer<num0>, Integer<num1> > : Integer<num0 * num1> {METAPROGRAMMING_ONLY(Multiply)};


template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY Divide;

template<IntegerValueType num0, IntegerValueType num1>
struct TYPE_HIDDEN_VISIBILITY Divide<Integer<num0>, Integer<num1> > : Integer<num0 / num1> {METAPROGRAMMING_ONLY(Divide)};


template<typename T0>
struct TYPE_HIDDEN_VISIBILITY Negate;

template<IntegerValueType num>
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


template<typename T, typename Enable=void>
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

template<IntegerValueType num>
struct TYPE_HIDDEN_VISIBILITY parameter_type<Integer<num> >
{
    typedef Integer<num> type;
    METAPROGRAMMING_ONLY(parameter_type)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY parameter_type<Ref<T> >
{
    typedef Ref<T> type;
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

X(true_type)
X(false_type)
X(DefaultTag)
X(ArrayNoArg)

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



//
// x, y, cmp
// if cmp(y, x)
//   return y, x
// else
//   return x, y

template<typename T, typename U, typename Cmp>
struct TYPE_HIDDEN_VISIBILITY GetMin : if_<Apply<Cmp, U, T>, U, T> {METAPROGRAMMING_ONLY(GetMin)};

template<typename T, typename U, typename Cmp>
struct TYPE_HIDDEN_VISIBILITY GetMax : if_<Apply<Cmp, U, T>, T, U> {METAPROGRAMMING_ONLY(GetMax)};

template<typename T, typename Cmp>
struct TYPE_HIDDEN_VISIBILITY ArraySort01_23_45_67_89
{
    typedef Array<typename GetMin<typename ArrayIndex<T, Integer<0> >::type, typename ArrayIndex<T, Integer<1> >::type, Cmp>::type,
                  typename GetMax<typename ArrayIndex<T, Integer<0> >::type, typename ArrayIndex<T, Integer<1> >::type, Cmp>::type,
                  typename GetMin<typename ArrayIndex<T, Integer<2> >::type, typename ArrayIndex<T, Integer<3> >::type, Cmp>::type,
                  typename GetMax<typename ArrayIndex<T, Integer<2> >::type, typename ArrayIndex<T, Integer<3> >::type, Cmp>::type,
                  typename GetMin<typename ArrayIndex<T, Integer<4> >::type, typename ArrayIndex<T, Integer<5> >::type, Cmp>::type,
                  typename GetMax<typename ArrayIndex<T, Integer<4> >::type, typename ArrayIndex<T, Integer<5> >::type, Cmp>::type,
                  typename GetMin<typename ArrayIndex<T, Integer<6> >::type, typename ArrayIndex<T, Integer<7> >::type, Cmp>::type,
                  typename GetMax<typename ArrayIndex<T, Integer<6> >::type, typename ArrayIndex<T, Integer<7> >::type, Cmp>::type,
                  typename GetMin<typename ArrayIndex<T, Integer<8> >::type, typename ArrayIndex<T, Integer<9> >::type, Cmp>::type,
                  typename GetMax<typename ArrayIndex<T, Integer<8> >::type, typename ArrayIndex<T, Integer<9> >::type, Cmp>::type > type;

    METAPROGRAMMING_ONLY(ArraySort01_23_45_67_89)
};

template<typename T, typename Cmp>
struct TYPE_HIDDEN_VISIBILITY ArraySort12_34_56_78
{
    typedef Array<typename ArrayIndex<T, Integer<0> >::type,
                  typename GetMin<typename ArrayIndex<T, Integer<1> >::type, typename ArrayIndex<T, Integer<2> >::type, Cmp>::type,
                  typename GetMax<typename ArrayIndex<T, Integer<1> >::type, typename ArrayIndex<T, Integer<2> >::type, Cmp>::type,
                  typename GetMin<typename ArrayIndex<T, Integer<3> >::type, typename ArrayIndex<T, Integer<4> >::type, Cmp>::type,
                  typename GetMax<typename ArrayIndex<T, Integer<3> >::type, typename ArrayIndex<T, Integer<4> >::type, Cmp>::type,
                  typename GetMin<typename ArrayIndex<T, Integer<5> >::type, typename ArrayIndex<T, Integer<6> >::type, Cmp>::type,
                  typename GetMax<typename ArrayIndex<T, Integer<5> >::type, typename ArrayIndex<T, Integer<6> >::type, Cmp>::type,
                  typename GetMin<typename ArrayIndex<T, Integer<7> >::type, typename ArrayIndex<T, Integer<8> >::type, Cmp>::type,
                  typename GetMax<typename ArrayIndex<T, Integer<8> >::type, typename ArrayIndex<T, Integer<8> >::type, Cmp>::type,
                  typename ArrayIndex<T, Integer<9> >::type > type;

    METAPROGRAMMING_ONLY(ArraySort12_34_56_78)
};

template<typename Arr, typename Cmp>
struct ArraySort_Both : ArraySort12_34_56_78<typename ArraySort01_23_45_67_89<Arr, Cmp>::type, Cmp>
{
    METAPROGRAMMING_ONLY(ArraySort_Both)
};

template<typename T, typename Cmp>
struct ArraySort
{
    typedef ArraySort_Both<T, Cmp> S0;
    typedef ArraySort_Both<typename S0::type, Cmp> S1;
    typedef ArraySort_Both<typename S1::type, Cmp> S2;
    typedef ArraySort_Both<typename S2::type, Cmp> S3;
    typedef ArraySort_Both<typename S3::type, Cmp> S4;
    typedef typename S4::type type;

    METAPROGRAMMING_ONLY(ArraySort)
};

template<typename T, typename Cmp>
struct ArraySort2 : ArraySort<T, Less<placeholders::_0, placeholders::_1> >
{
    METAPROGRAMMING_ONLY(ArraySort2)
};


} // namespace intro

#endif
