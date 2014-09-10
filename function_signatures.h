#ifndef INCLUDED_FUNCTION_SIGNATURES
#define INCLUDED_FUNCTION_SIGNATURES

#ifndef INCLUDED_DETECT_TRAITS
#include "detect_traits.h"
#endif

#ifndef INCLUDED_METAPROGRAMMING
#include "metaprogramming.h"
#endif

namespace intro {

// It is essential to box at the very least reference (const and non-const) types
// as otherwise the detect traits mechanism will not work; you can't form a pointer to a reference
// and any attempt to do so just results in the function being SFINAE (silently) removed from the
// overload set. Sad but true.
template<typename T>
struct box_ref
{
    typedef T type;
};

template<typename T>
struct box_ref<Ref<T> >
{
    typedef T& type;
};

namespace impl {

// This is the metafunction by which function pointers become associated with a metafunction
// describing it. For standard functors it is trivial to add typedefs with the appropriate information
// but nesting typedefs is impossible in pointers.
// It is assumed that all types using within namespace impl have been passed through this metafunction first
// to get the appropriate information.
template<typename T>
struct ResolveFunctionSignatureType
{
    typedef T type;
};

template<typename T>
struct unbox_ref
{
    typedef T type;
};

template<typename T>
struct unbox_ref<box_ref<T> >
{
    typedef T type;
};

template<typename T>
struct unbox_ref<Ref<T> >
{

    typedef T& type;
};

}

struct no_template_argument { typedef no_template_argument type; };
struct template_param { typedef template_param type; };

template<typename T>
struct CodomainDeduction { typedef CodomainDeduction type; };

// Generates the non-impl functions to forward onto the impl, via the ResolveFunctionSignatureType metafunction.
#define GENERATE_FUNCTION_SIGNATURE_GETTERS(x)\
namespace impl{\
GENERATE_HAS_AND_GET_MEMBER_TYPE(x)\
}\
template<typename T> struct Get_##x : impl::unbox_ref< typename impl::GetMemberType_##x<typename impl::ResolveFunctionSignatureType<T>::type>::type > {}; \
template<typename T> struct Has_##x : impl::HasMemberType_##x<typename impl::ResolveFunctionSignatureType<T>::type> {};\

GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_0)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_1)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_2)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_3)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_4)
GENERATE_FUNCTION_SIGNATURE_GETTERS(codomain_type)

#undef GENERATE_FUNCTION_SIGNATURE_GETTERS

template<typename T>
struct GetCodomainType : Get_codomain_type<T> {};

template<typename T>
struct FunctionSignatureEnabled : Has_codomain_type<T> {};

namespace impl {

template<typename T, typename Index>
struct HasInputType_Impl;

template<typename T>
struct HasInputType_Impl<T, Integer<0> > : Has_input_type_0<T> {};

template<typename T>
struct HasInputType_Impl<T, Integer<1> > : Has_input_type_1<T> {};

template<typename T>
struct HasInputType_Impl<T, Integer<2> > : Has_input_type_2<T> {};

template<typename T>
struct HasInputType_Impl<T, Integer<3> > : Has_input_type_3<T> {};

template<typename T>
struct HasInputType_Impl<T, Integer<4> > : Has_input_type_4<T> {};

template<typename T>
struct HasInputType_Impl<T, Integer<5> > : false_type {};


template<typename T, typename Index>
struct GetInputType_Impl;

template<typename T>
struct GetInputType_Impl<T, Integer<0> > : Get_input_type_0<T> {};

template<typename T>
struct GetInputType_Impl<T, Integer<1> > : Get_input_type_1<T> {};

template<typename T>
struct GetInputType_Impl<T, Integer<2> > : Get_input_type_2<T> {};

template<typename T>
struct GetInputType_Impl<T, Integer<3> > : Get_input_type_3<T> {};

template<typename T>
struct GetInputType_Impl<T, Integer<4> > : Get_input_type_4<T> {};

} // namespace impl

template<typename T, typename Index>
struct HasInputType : impl::HasInputType_Impl<typename impl::ResolveFunctionSignatureType<T>::type, Index> {};

template<typename T, typename Index>
struct GetInputType : impl::GetInputType_Impl<typename impl::ResolveFunctionSignatureType<T>::type, Index> {};

namespace impl {

// Count upwards; higher Arity is less likely.
// Note that Indexing is zero based, and that CurrentArity suggests 0..CurrentArity-1(inclusive) are available
template<typename T, typename CurrentArity>
struct GetFunctionArityLoop : eval_if<HasInputType<T, CurrentArity>,
                                      GetFunctionArityLoop<T, typename Successor<CurrentArity>::type>,
                                      CurrentArity>
{};

} // namespace impl

template<typename T>
struct GetFunctionArity : impl::GetFunctionArityLoop<typename impl::ResolveFunctionSignatureType<T>::type, Integer<0> > {};


namespace impl {

template<typename T, typename AccumulatedArray, typename CurrentIndex, typename Arity>
struct GetInputTypeArrayLoop;

template<typename T, typename AccumulatedArray, typename Arity>
struct GetInputTypeArrayLoop<T, AccumulatedArray, Arity, Arity> : AccumulatedArray
{};

template<typename T, typename AccumulatedArray, typename CurrentIndex, typename Arity>
struct GetInputTypeArrayLoop :
    GetInputTypeArrayLoop<T, typename ArrayConcat<AccumulatedArray, Array<typename GetInputType<T, CurrentIndex>::type> >::type, typename Successor<CurrentIndex>::type, Arity>
{};


template<typename T>
struct GetInputTypeArray_Impl :
    GetInputTypeArrayLoop<T, Array<>, Integer<0>, typename GetFunctionArity<T>::type > {};

}

template<typename T>
struct GetInputTypeArray : impl::GetInputTypeArray_Impl<T> {};

namespace impl {

template<typename InputType, typename ParamArrayItem>
struct UseTemplateParamWhereNeeded;

template<>
struct UseTemplateParamWhereNeeded<template_param, no_template_argument>
{}; // typedef type not defined as this situation is unexpected; a parameter was expected

template<typename ParamArrayItem>
struct UseTemplateParamWhereNeeded<template_param, ParamArrayItem>
{
    typedef ParamArrayItem type;
};

template<typename InputType>
struct UseTemplateParamWhereNeeded<InputType, no_template_argument>
{
    typedef InputType type;
};

template<>
struct UseTemplateParamWhereNeeded<ArrayNoArg, no_template_argument> : ArrayNoArg {};

template<>
struct UseTemplateParamWhereNeeded<ArrayNoArg, ArrayNoArg> : ArrayNoArg {};

template<typename T, typename CodomainMFC, typename ParamArray, typename Arity>
struct ApplyCodomainDeduction
{
    typedef typename ArrayZip<typename GetInputTypeArray<T>::type, ParamArray, UseTemplateParamWhereNeeded<placeholders::_0, placeholders::_1> >::type TypesToApply;
    // Must use RationaliseApplyArray to convert the ArrayNoArg into apply_ignore within the first 5 elements of the array.
    // If we did not do this then very bad things would happen.
    typedef typename Apply_Impl<CodomainMFC, typename RationaliseApplyArray<TypesToApply, ArrayNoArg>::type>::type type;
};

template<typename T, typename CodomainType, typename ParamArray>
struct GetCodomainType_Impl : identity_type<CodomainType> {};

template<typename T, typename U, typename ParamArray>
struct GetCodomainType_Impl<T, CodomainDeduction<U>, ParamArray> : ApplyCodomainDeduction<T, U, ParamArray, typename GetFunctionArity<T>::type>
{};

} // namespace impl

template<typename T, typename I0=no_template_argument, typename I1=no_template_argument, typename I2=no_template_argument, typename I3=no_template_argument, typename I4=no_template_argument>
struct DeduceCodomainType : impl::GetCodomainType_Impl<typename impl::ResolveFunctionSignatureType<T>::type,
  typename GetCodomainType<typename impl::ResolveFunctionSignatureType<T>::type>::type, Array<I0, I1, I2, I3, I4> > {};





//Specialisations for function pointers

namespace impl {

template<typename R>
struct nullary_function
{
    typedef nullary_function type;
    typedef true_type introspection_enabled;
    typedef R codomain_type;
};

template<typename R>
struct ResolveFunctionSignatureType<R(*)()> :
    nullary_function<box_ref<R> >
{};

template<typename R, typename U>
struct unary_function
{
    typedef unary_function type;
    typedef true_type introspection_enabled;
    typedef U input_type_0;
    typedef R codomain_type;
};

template<typename R, typename U>
struct ResolveFunctionSignatureType<R(*)(U)> :
    unary_function<box_ref<R>,
                   box_ref<U> >
{};

template<typename R, typename U, typename V>
struct binary_function
{
    typedef binary_function type;
    typedef true_type introspection_enabled;
    typedef U input_type_0;
    typedef V input_type_1;
    typedef R codomain_type;
};

template<typename R, typename U, typename V>
struct ResolveFunctionSignatureType<R(*)(U, V)> :
    binary_function<box_ref<R>,
                    box_ref<U>,
                    box_ref<V> >
{};


template<typename R, typename U, typename V, typename W>
struct trinary_function
{
    typedef trinary_function type;
    typedef true_type introspection_enabled;
    typedef U input_type_0;
    typedef V input_type_1;
    typedef W input_type_2;
    typedef R codomain_type;
};

template<typename R, typename U, typename V, typename W>
struct ResolveFunctionSignatureType<R(*)(U, V, W)> :
    trinary_function<box_ref<R>,
                     box_ref<U>,
                     box_ref<V> ,
                     box_ref<W> >
{};


template<typename R, typename U, typename V, typename W, typename X>
struct quaternary_function
{
    typedef quaternary_function type;
    typedef true_type introspection_enabled;
    typedef U input_type_0;
    typedef V input_type_1;
    typedef W input_type_2;
    typedef X input_type_3;
    typedef R codomain_type;
};

template<typename R, typename U, typename V, typename W, typename X>
struct ResolveFunctionSignatureType<R(*)(U, V, W, X)> :
    quaternary_function<box_ref<R>,
                        box_ref<U>,
                        box_ref<V>,
                        box_ref<W>,
                        box_ref<X> >
{};


template<typename R, typename U, typename V, typename W, typename X, typename Y>
struct quinternary_function
{
    typedef quinternary_function type;
    typedef true_type introspection_enabled;
    typedef U input_type_0;
    typedef V input_type_1;
    typedef W input_type_2;
    typedef X input_type_3;
    typedef Y input_type_4;
    typedef R codomain_type;
};

template<typename R, typename U, typename V, typename W, typename X, typename Y>
  struct ResolveFunctionSignatureType<R(*)(U, V, W, X, Y)> :
    quinternary_function<box_ref<R>,
                         box_ref<U>,
                         box_ref<V>,
                         box_ref<W>,
                         box_ref<X>,
                         box_ref<Y> >
{};


template<typename R, typename C>
struct nullary_member_function
{
    typedef nullary_member_function type;
    typedef true_type introspection_enabled;
    typedef C input_type_0;
    typedef R codomain_type;
};

template<typename R, typename C>
struct ResolveFunctionSignatureType<R(C::*)()> :
    nullary_member_function<box_ref<R>, box_ref<C> >
{};

template<typename R, typename C>
struct ResolveFunctionSignatureType<R(C::*)() const> :
    nullary_member_function<box_ref<R>, box_ref<C const> >
{};


template<typename R, typename C, typename U>
struct unary_member_function
{
    typedef unary_member_function type;
    typedef true_type introspection_enabled;
    typedef C input_type_0;
    typedef U input_type_1;
    typedef R codomain_type;
};

template<typename R, typename C, typename U>
struct ResolveFunctionSignatureType<R(C::*)(U)> :
   unary_member_function<box_ref<R>, box_ref<C>, box_ref<U> >
{};

template<typename R, typename C, typename U>
struct ResolveFunctionSignatureType<R(C::*)(U) const> :
   unary_member_function<box_ref<R>, box_ref<C const>, box_ref<U> >
{};


template<typename R, typename C, typename U, typename V>
struct binary_member_function
{
    typedef binary_member_function type;
    typedef true_type introspection_enabled;
    typedef C input_type_0;
    typedef U input_type_1;
    typedef V input_type_2;
    typedef R codomain_type;
};

template<typename R, typename C, typename U, typename V>
struct ResolveFunctionSignatureType<R(C::*)(U, V)> :
    binary_member_function<box_ref<R>, box_ref<C>, box_ref<U>, box_ref<V> >
{};

template<typename R, typename C, typename U, typename V>
struct ResolveFunctionSignatureType<R(C::*)(U, V) const> :
    binary_member_function<box_ref<R>, box_ref<C const>, box_ref<U>, box_ref<V> >
{};


template<typename R, typename C, typename U, typename V, typename W>
struct ternary_member_function
{
    typedef ternary_member_function type;
    typedef true_type introspection_enabled;
    typedef C input_type_0;
    typedef U input_type_1;
    typedef V input_type_2;
    typedef W input_type_3;
    typedef R codomain_type;
};

template<typename R, typename C, typename U, typename V, typename W>
struct ResolveFunctionSignatureType<R(C::*)(U, V, W)> :
    ternary_member_function<box_ref<R>, box_ref<C>, box_ref<U>, box_ref<V>, box_ref<W> >
{};

template<typename R, typename C, typename U, typename V, typename W>
struct ResolveFunctionSignatureType<R(C::*)(U, V, W) const> :
    ternary_member_function<box_ref<R>, box_ref<C const>, box_ref<U>, box_ref<V>, box_ref<W> >
{};


template<typename R, typename C, typename U, typename V, typename W, typename X>
struct quaternary_member_function
{
    typedef quaternary_member_function type;
    typedef true_type introspection_enabled;
    typedef C input_type_0;
    typedef U input_type_1;
    typedef V input_type_2;
    typedef W input_type_3;
    typedef X input_type_4;
    typedef R codomain_type;
};

template<typename R, typename C, typename U, typename V, typename W, typename X>
struct ResolveFunctionSignatureType<R(C::*)(U, V, W, X)> :
    quaternary_member_function<box_ref<R>, box_ref<C>, box_ref<U>, box_ref<V>, box_ref<W>, box_ref<X> >
{};

template<typename R, typename C, typename U, typename V, typename W, typename X>
struct ResolveFunctionSignatureType<R(C::*)(U, V, W, X) const> :
    quaternary_member_function<box_ref<R>, box_ref<C const>, box_ref<U>, box_ref<V>, box_ref<W>, box_ref<X> >
{};

}

} // namespace intro

#endif
