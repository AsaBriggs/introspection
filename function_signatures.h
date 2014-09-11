#ifndef INCLUDED_FUNCTION_SIGNATURES
#define INCLUDED_FUNCTION_SIGNATURES

#ifndef INCLUDED_DETECT_TRAITS
#include "detect_traits.h"
#endif

#ifndef INCLUDED_METAPROGRAMMING
#include "metaprogramming.h"
#endif

namespace intro {

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

struct no_template_argument { typedef no_template_argument type; };
struct template_param { typedef template_param type; };

template<typename T>
struct CodomainDeduction { typedef CodomainDeduction type; };

// Generates the non-impl functions to forward onto the impl, via the ResolveFunctionSignatureType metafunction.
#define GENERATE_FUNCTION_SIGNATURE_GETTERS(x)\
namespace impl{\
GENERATE_HAS_AND_GET_MEMBER_TYPE3(x)\
}\
template<typename T> struct Get_##x : impl::GetMemberType_##x<typename ResolveFunctionSignatureType<T>::type> {}; \
template<typename T> struct Has_##x : impl::HasMemberType_##x<typename ResolveFunctionSignatureType<T>::type> {};\

GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_0)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_1)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_2)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_3)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_4)
GENERATE_FUNCTION_SIGNATURE_GETTERS(codomain_type)

// add typedef input_types to return all the types in a single Array.
// Used in preference to input_type_N typedefs.
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_types)

#undef GENERATE_FUNCTION_SIGNATURE_GETTERS

template<typename T>
struct GetCodomainType : Get_codomain_type<T> {};

template<typename T>
struct FunctionSignatureEnabled : Has_codomain_type<T> {};

namespace impl {

template<typename T, typename Index>
struct HasNumberedInputType;

template<typename T>
struct HasNumberedInputType<T, Integer<0> > : Has_input_type_0<T> {};

template<typename T>
struct HasNumberedInputType<T, Integer<1> > : Has_input_type_1<T> {};

template<typename T>
struct HasNumberedInputType<T, Integer<2> > : Has_input_type_2<T> {};

template<typename T>
struct HasNumberedInputType<T, Integer<3> > : Has_input_type_3<T> {};

template<typename T>
struct HasNumberedInputType<T, Integer<4> > : Has_input_type_4<T> {};

template<typename T>
struct HasNumberedInputType<T, Integer<5> > : false_type {};


template<typename T, typename Index>
struct HasArrayInputItem :
    not_<is_same<ArrayNoArg, typename ArrayIndex<typename GetMemberType_input_types<T>::type, Index>::type > >
{};

template<typename T, typename Index>
struct HasInputType_Impl :
     eval_if<HasMemberType_input_types<T>,
             HasArrayInputItem<T, Index>,
             HasNumberedInputType<T, Index> >
{};

} // namespace impl

template<typename T, typename Index>
struct HasInputType : impl::HasInputType_Impl<typename ResolveFunctionSignatureType<T>::type, Index>
{};


namespace impl {

template<typename T, typename Index>
struct GetNumberedInputType_Impl;

template<typename T>
struct GetNumberedInputType_Impl<T, Integer<0> > : Get_input_type_0<T> {};

template<typename T>
struct GetNumberedInputType_Impl<T, Integer<1> > : Get_input_type_1<T> {};

template<typename T>
struct GetNumberedInputType_Impl<T, Integer<2> > : Get_input_type_2<T> {};

template<typename T>
struct GetNumberedInputType_Impl<T, Integer<3> > : Get_input_type_3<T> {};

template<typename T>
struct GetNumberedInputType_Impl<T, Integer<4> > : Get_input_type_4<T> {};

template<typename T, typename Index>
struct GetArrayInputType_Impl : ArrayIndex<typename GetMemberType_input_types<T>::type, Index>
{};

template<typename T, typename Index>
struct GetInputType_Impl : eval_if<HasMemberType_input_types<T>,
    GetArrayInputType_Impl<T, Index>,
    GetNumberedInputType_Impl<T, Index> >
{};

} // namespace impl

template<typename T, typename Index>
struct GetInputType : impl::GetInputType_Impl<typename ResolveFunctionSignatureType<T>::type, Index>
{};

namespace impl {

// Count upwards; higher Arity is less likely.
// Note that Indexing is zero based, and that CurrentArity suggests 0..CurrentArity-1(inclusive) are available
template<typename T, typename CurrentArity>
struct GetFunctionArityLoop : eval_if<HasNumberedInputType<T, CurrentArity>,
                                      GetFunctionArityLoop<T, typename Successor<CurrentArity>::type>,
                                      CurrentArity>
{};

template<typename T>
struct GetFunctionArityArray : ArraySize<typename GetMemberType_input_types<T>::type>
{};

template<typename T>
struct GetFunctionArity_Impl : eval_if<HasMemberType_input_types<T>,
  GetFunctionArityArray<T>,
  GetFunctionArityLoop<T, Integer<0> > >
{};

} // namespace impl

template<typename T>
struct GetFunctionArity : impl::GetFunctionArity_Impl<typename ResolveFunctionSignatureType<T>::type>
{};

namespace impl {

template<typename T, typename AccumulatedArray, typename CurrentIndex, typename Arity>
struct GetInputTypeArrayNumbered;

template<typename T, typename AccumulatedArray, typename Arity>
struct GetInputTypeArrayNumbered<T, AccumulatedArray, Arity, Arity> : AccumulatedArray
{};

template<typename T, typename AccumulatedArray, typename CurrentIndex, typename Arity>
struct GetInputTypeArrayNumbered :
    GetInputTypeArrayNumbered<T, typename ArrayConcat<AccumulatedArray, Array<typename GetInputType<T, CurrentIndex>::type> >::type, typename Successor<CurrentIndex>::type, Arity>
{};


template<typename T>
struct GetInputTypeArray_Impl : eval_if<HasMemberType_input_types<T>,
    GetMemberType_input_types<T>,
    GetInputTypeArrayNumbered<T, Array<>, Integer<0>, typename GetFunctionArity<T>::type> >
{};

}

template<typename T>
struct GetInputTypeArray : impl::GetInputTypeArray_Impl<typename ResolveFunctionSignatureType<T>::type> {};

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
struct DeduceCodomainType : impl::GetCodomainType_Impl<typename ResolveFunctionSignatureType<T>::type,
  typename GetCodomainType<typename ResolveFunctionSignatureType<T>::type>::type, Array<I0, I1, I2, I3, I4> > {};


//Specialisations for function pointers

namespace impl {

template<typename R>
struct nullary_function
{
    typedef nullary_function type;
    typedef true_type introspection_enabled;
    typedef R codomain_type;
    typedef codomain_type (*Func)();

    inline codomain_type
    operator()(Func func) const
    {
        return (*func)();
    }
};

template<>
struct nullary_function<void>
{
    typedef nullary_function type;
    typedef true_type introspection_enabled;
    typedef void codomain_type;
    typedef codomain_type (*Func)();

    inline codomain_type
    operator()(Func func) const
    {
        (*func)();
    }
};

template<typename R, typename U>
struct unary_function
{
    typedef unary_function type;
    typedef true_type introspection_enabled;
    typedef Array<U> input_types;
    typedef R codomain_type;
    typedef codomain_type(*Func)(U);

    inline codomain_type
    operator()(Func func, U a) const
    {
        return (*func)(a);
    }
};

template<typename U>
struct unary_function<void, U>
{
    typedef unary_function type;
    typedef true_type introspection_enabled;
    typedef Array<U> input_types;
    typedef void codomain_type;
    typedef codomain_type (*Func)(U);

    inline codomain_type
    operator()(Func func, U a) const
    {
        (*func)(a);
    }
};

template<typename R, typename U, typename V>
struct binary_function
{
    typedef binary_function type;
    typedef true_type introspection_enabled;
    typedef Array<U, V> input_types;
    typedef R codomain_type;
    typedef codomain_type (*Func)(U, V);

    inline codomain_type
    operator()(Func func, U a, V b) const
    {
        return (*func)(a, b);
    }
};

template<typename U, typename V>
struct binary_function<void, U, V>
{
    typedef binary_function type;
    typedef true_type introspection_enabled;
    typedef Array<U, V> input_types;
    typedef void codomain_type;
    typedef codomain_type (*Func)(U, V);

    inline codomain_type
    operator()(Func func, U a, V b) const
    {
        (*func)(a, b);
    }
};


template<typename R, typename U, typename V, typename W>
struct trinary_function
{
    typedef trinary_function type;
    typedef true_type introspection_enabled;
    typedef Array<U, V, W> input_types;
    typedef R codomain_type;
    typedef codomain_type (*Func)(U, V, W);

    inline codomain_type
    operator()(Func func, U a, V b, W c) const
    {
        return (*func)(a, b, c);
    }
};

template<typename U, typename V, typename W>
struct trinary_function<void, U, V, W>
{
    typedef trinary_function type;
    typedef true_type introspection_enabled;
    typedef Array<U, V, W> input_types;
    typedef void codomain_type;
    typedef codomain_type (*Func)(U, V, W);

    inline codomain_type
    operator()(Func func, U a, V b, W c) const
    {
        (*func)(a, b, c);
    }
};

template<typename R, typename U, typename V, typename W, typename X>
struct quaternary_function
{
    typedef quaternary_function type;
    typedef true_type introspection_enabled;
    typedef Array<U, V, W, X> input_types;
    typedef R codomain_type;
    typedef codomain_type (*Func)(U, V, W, X);

    inline codomain_type
    operator()(Func func, U a, V b, W c, X d) const
    {
        return (*func)(a, b, c, d);
    }
};

template<typename U, typename V, typename W, typename X>
struct quaternary_function<void, U, V, W, X>
{
    typedef quaternary_function type;
    typedef true_type introspection_enabled;
    typedef Array<U, V, W, X> input_types;
    typedef void codomain_type;
    typedef codomain_type (*Func)(U, V, W, X);

    inline codomain_type
    operator()(Func func, U a, V b, W c, X d) const
    {
        (*func)(a, b, c, d);
    }
};


template<typename R, typename U, typename V, typename W, typename X, typename Y>
struct quinternary_function
{
    typedef quinternary_function type;
    typedef true_type introspection_enabled;
    typedef Array<U, V, W, X, Y> input_types;
    typedef R codomain_type;
    typedef codomain_type (*Func)(U, V, W, X, Y);

    inline codomain_type
    operator()(Func func, U a, V b, W c, X d, Y e) const
    {
        return (*func)(a, b, c, d, e);
    }
};

template<typename U, typename V, typename W, typename X, typename Y>
struct quinternary_function<void, U, V, W, X, Y>
{
    typedef quinternary_function type;
    typedef true_type introspection_enabled;
    typedef Array<U, V, W, X, Y> input_types;
    typedef void codomain_type;
    typedef codomain_type (*Func)(U, V, W, X, Y);

    inline codomain_type
    operator()(Func func, U a, V b, W c, X d, Y e) const
    {
        (*func)(a, b, c, d, e);
    }
};


template<typename R, typename C, typename Signature>
struct nullary_member_function
{
    typedef nullary_member_function type;
    typedef true_type introspection_enabled;
    typedef Array<C> input_types;
    typedef R codomain_type;
    typedef Signature Func;

    inline codomain_type
    operator()(Func func, C c) const
    {
        return (c.*func)();
    }
};

template<typename C, typename Signature>
struct nullary_member_function<void, C, Signature>
{
    typedef nullary_member_function type;
    typedef true_type introspection_enabled;
    typedef Array<C> input_types;
    typedef void codomain_type;
    typedef Signature Func;

    inline codomain_type
    operator()(Func func, C c) const
    {
        (c.*func)();
    }
};


template<typename R, typename C, typename U, typename Signature>
struct unary_member_function
{
    typedef unary_member_function type;
    typedef true_type introspection_enabled;
    typedef Array<C, U> input_types;
    typedef R codomain_type;
    typedef Signature Func;

    inline codomain_type
    operator()(Func func, C c, U u) const
    {
        return (c.*func)(u);
    }
};

template<typename C, typename U, typename Signature>
struct unary_member_function<void, C, U, Signature>
{
    typedef unary_member_function type;
    typedef true_type introspection_enabled;
    typedef Array<C, U> input_types;
    typedef void codomain_type;
    typedef Signature Func;

    inline codomain_type
    operator()(Func func, C c, U u) const
    {
        (c.*func)(u);
    }
};


template<typename R, typename C, typename U, typename V, typename Signature>
struct binary_member_function
{
    typedef binary_member_function type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V> input_types;
    typedef R codomain_type;
    typedef Signature Func;

    inline codomain_type
    operator()(Func func, C c, U u, V v) const
    {
        return (c.*func)(u, v);
    }
};

template<typename C, typename U, typename V, typename Signature>
struct binary_member_function<void, C, U, V, Signature>
{
    typedef binary_member_function type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V> input_types;
    typedef void codomain_type;
    typedef Signature Func;

    inline codomain_type
    operator()(Func func, C c, U u, V v) const
    {
        (c.*func)(u, v);
    }
};


template<typename R, typename C, typename U, typename V, typename W, typename Signature>
struct ternary_member_function
{
    typedef ternary_member_function type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V, W> input_types;
    typedef R codomain_type;
    typedef Signature Func;

    inline codomain_type
    operator()(Func func, C c, U u, V v, W w) const
    {
        return (c.*func)(u, v, w);
    }
};

template<typename C, typename U, typename V, typename W, typename Signature>
struct ternary_member_function<void, C, U, V, W, Signature>
{
    typedef ternary_member_function type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V, W> input_types;
    typedef void codomain_type;
    typedef Signature Func;

    inline codomain_type
    operator()(Func func, C c, U u, V v, W w) const
    {
        (c.*func)(u, v, w);
    }
};


template<typename R, typename C, typename U, typename V, typename W, typename X, typename Signature>
struct quaternary_member_function
{
    typedef quaternary_member_function type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V, W, X> input_types;
    typedef R codomain_type;
    typedef Signature Func;

    inline codomain_type
    operator()(Func func, C c, U u, V v, W w, X x) const
    {
        return (c.*func)(u, v, w, x);
    }
};

template<typename C, typename U, typename V, typename W, typename X, typename Signature>
struct quaternary_member_function<void, C, U, V, W, X, Signature>
{
    typedef quaternary_member_function type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V, W, X> input_types;
    typedef void codomain_type;
    typedef Signature Func;

    inline codomain_type
    operator()(Func func, C c, U u, V v, W w, X x) const
    {
        (c.*func)(u, v, w, x);
    }
};

} // namespace impl
 
template<typename R>
struct ResolveFunctionSignatureType<R(*)()> :
    impl::nullary_function<R>
{};

template<typename R, typename U>
struct ResolveFunctionSignatureType<R(*)(U)> :
    impl::unary_function<R, U>
{};

template<typename R, typename U, typename V>
struct ResolveFunctionSignatureType<R(*)(U, V)> :
    impl::binary_function<R, U, V>
{};

template<typename R, typename U, typename V, typename W>
struct ResolveFunctionSignatureType<R(*)(U, V, W)> :
    impl::trinary_function<R, U, V, W>
{};

template<typename R, typename U, typename V, typename W, typename X>
struct ResolveFunctionSignatureType<R(*)(U, V, W, X)> :
    impl::quaternary_function<R, U, V, W, X>
{};

template<typename R, typename U, typename V, typename W, typename X, typename Y>
struct ResolveFunctionSignatureType<R(*)(U, V, W, X, Y)> :
    impl::quinternary_function<R, U, V, W, X, Y>
{};


template<typename R, typename C>
struct ResolveFunctionSignatureType<R(C::*)()> :
    impl::nullary_member_function<R, C&, R(C::*)()>
{};

template<typename R, typename C>
struct ResolveFunctionSignatureType<R(C::*)() const> :
    impl::nullary_member_function<R, C const&, R(C::*)() const>
{};


template<typename R, typename C, typename U>
struct ResolveFunctionSignatureType<R(C::*)(U)> :
    impl::unary_member_function<R, C&, U, R(C::*)(U)>
{};

template<typename R, typename C, typename U>
struct ResolveFunctionSignatureType<R(C::*)(U) const> :
    impl::unary_member_function<R, C const&, U, R(C::*)(U) const>
{};


template<typename R, typename C, typename U, typename V>
struct ResolveFunctionSignatureType<R(C::*)(U, V)> :
    impl::binary_member_function<R, C&, U, V,R(C::*)(U, V)>
{};

template<typename R, typename C, typename U, typename V>
struct ResolveFunctionSignatureType<R(C::*)(U, V) const> :
    impl::binary_member_function<R, C const&, U, V, R(C::*)(U, V) const>
{};


template<typename R, typename C, typename U, typename V, typename W>
struct ResolveFunctionSignatureType<R(C::*)(U, V, W)> :
    impl::ternary_member_function<R, C&, U, V, W, R(C::*)(U, V, W)>
{};

template<typename R, typename C, typename U, typename V, typename W>
struct ResolveFunctionSignatureType<R(C::*)(U, V, W) const> :
    impl::ternary_member_function<R, C const&, U, V, W, R(C::*)(U, V, W) const>
{};


template<typename R, typename C, typename U, typename V, typename W, typename X>
struct ResolveFunctionSignatureType<R(C::*)(U, V, W, X)> :
    impl::quaternary_member_function<R, C&, U, V, W, X, R(C::*)(U, V, W, X)>
{};

template<typename R, typename C, typename U, typename V, typename W, typename X>
struct ResolveFunctionSignatureType<R(C::*)(U, V, W, X) const> :
    impl::quaternary_member_function<R, C const&, U, V, W, X, R(C::*)(U, V, W, X) const>
{};

} // namespace intro

#endif
