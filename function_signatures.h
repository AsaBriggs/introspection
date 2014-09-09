#ifndef INCLUDED_FUNCTION_SIGNATURES
#define INCLUDED_FUNCTION_SIGNATURES

#ifndef INCLUDED_DETECT_TRAITS
#include "detect_traits.h"
#endif

#ifndef INCLUDED_METAPROGRAMMING
#include "metaprogramming.h"
#endif

namespace intro {

struct template_param { typedef template_param type; };
struct no_argument { typedef no_argument type; };

template<typename T>
struct CodomainDeduction { typedef CodomainDeduction type; };

GENERATE_HAS_AND_GET_MEMBER_TYPE(input_type_0)
GENERATE_HAS_AND_GET_MEMBER_TYPE(input_type_1)
GENERATE_HAS_AND_GET_MEMBER_TYPE(input_type_2)
GENERATE_HAS_AND_GET_MEMBER_TYPE(input_type_3)
GENERATE_HAS_AND_GET_MEMBER_TYPE(input_type_4)
GENERATE_HAS_AND_GET_MEMBER_TYPE(codomain_type)


template<typename T>
struct GetCodomainType : GetMemberType_codomain_type<T> {};

template<typename T>
struct FunctionSignatureEnabled : HasMemberType_codomain_type<T> {};


namespace impl {

template<typename T, typename Index>
struct HasInputType_Impl;

template<typename T>
struct HasInputType_Impl<T, Integer<0> > : HasMemberType_input_type_0<T> {};

template<typename T>
struct HasInputType_Impl<T, Integer<1> > : HasMemberType_input_type_1<T> {};

template<typename T>
struct HasInputType_Impl<T, Integer<2> > : HasMemberType_input_type_2<T> {};

template<typename T>
struct HasInputType_Impl<T, Integer<3> > : HasMemberType_input_type_3<T> {};

template<typename T>
struct HasInputType_Impl<T, Integer<4> > : HasMemberType_input_type_4<T> {};

template<typename T>
struct HasInputType_Impl<T, Integer<5> > : false_type {};


template<typename T, typename Index>
struct GetInputType_Impl;

template<typename T>
struct GetInputType_Impl<T, Integer<0> > : GetMemberType_input_type_0<T> {};

template<typename T>
struct GetInputType_Impl<T, Integer<1> > : GetMemberType_input_type_1<T> {};

template<typename T>
struct GetInputType_Impl<T, Integer<2> > : GetMemberType_input_type_2<T> {};

template<typename T>
struct GetInputType_Impl<T, Integer<3> > : GetMemberType_input_type_3<T> {};

template<typename T>
struct GetInputType_Impl<T, Integer<4> > : GetMemberType_input_type_4<T> {};

} // namespace impl

template<typename T, typename Index>
struct HasInputType : impl::HasInputType_Impl<T, Index> {};

template<typename T, typename Index>
struct GetInputType : impl::GetInputType_Impl<T, Index> {};

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
struct GetFunctionArity : impl::GetFunctionArityLoop<T, Integer<0> > {};


namespace impl {

template<typename T, typename AccumulatedArray, typename CurrentIndex, typename Arity>
struct GetInputTypeArrayLoop;

template<typename T, typename AccumulatedArray, typename Arity>
struct GetInputTypeArrayLoop<T, AccumulatedArray, Arity, Arity> : AccumulatedArray {};

template<typename T, typename AccumulatedArray, typename CurrentIndex, typename Arity>
struct GetInputTypeArrayLoop :
    GetInputTypeArrayLoop<T, typename ArrayConcat<AccumulatedArray, Array<typename GetInputType<T, CurrentIndex>::type> >::type, typename Successor<CurrentIndex>::type, Arity> {};


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
struct UseTemplateParamWhereNeeded<template_param, no_argument>
{}; // typedef type not defined as this situation is unexpected; a parameter was expected

template<typename ParamArrayItem>
struct UseTemplateParamWhereNeeded<template_param, ParamArrayItem>
{
    typedef ParamArrayItem type;
};

template<typename InputType>
struct UseTemplateParamWhereNeeded<InputType, no_argument>
{
    typedef InputType type;
};

template<>
struct UseTemplateParamWhereNeeded<Empty, no_argument>
{
    typedef Empty type;
};

template<>
struct UseTemplateParamWhereNeeded<Empty, Empty>
{
    typedef Empty type;
};

struct UseTemplateParam
{
    template<typename InputType, typename ParamArrayItem>
    struct apply : UseTemplateParamWhereNeeded<InputType, ParamArrayItem> {};
};

template<typename MFC, typename TypesToApply, typename Arity>
struct ApplyCodomainDeduction_Impl;

template<typename MFC, typename TypesToApply>
struct ApplyCodomainDeduction_Impl<MFC, TypesToApply, Integer<1> > :
    MFC::template apply<typename ArrayIndex<TypesToApply, Integer<0> >::type>
{};

template<typename MFC, typename TypesToApply>
struct ApplyCodomainDeduction_Impl<MFC, TypesToApply, Integer<2> > :
    MFC::template apply<typename ArrayIndex<TypesToApply, Integer<0> >::type,
                        typename ArrayIndex<TypesToApply, Integer<1> >::type>
{};

template<typename MFC, typename TypesToApply>
struct ApplyCodomainDeduction_Impl<MFC, TypesToApply, Integer<3> > :
    MFC::template apply<typename ArrayIndex<TypesToApply, Integer<0> >::type,
                        typename ArrayIndex<TypesToApply, Integer<1> >::type,
                        typename ArrayIndex<TypesToApply, Integer<2> >::type>
{};

template<typename MFC, typename TypesToApply>
struct ApplyCodomainDeduction_Impl<MFC, TypesToApply, Integer<4> > :
    MFC::template apply<typename ArrayIndex<TypesToApply, Integer<0> >::type,
                        typename ArrayIndex<TypesToApply, Integer<1> >::type,
                        typename ArrayIndex<TypesToApply, Integer<2> >::type,
                        typename ArrayIndex<TypesToApply, Integer<3> >::type>
{};

template<typename MFC, typename TypesToApply>
struct ApplyCodomainDeduction_Impl<MFC, TypesToApply, Integer<5> > :
    MFC::template apply<typename ArrayIndex<TypesToApply, Integer<0> >::type,
                        typename ArrayIndex<TypesToApply, Integer<1> >::type,
                        typename ArrayIndex<TypesToApply, Integer<2> >::type,
                        typename ArrayIndex<TypesToApply, Integer<3> >::type,
                        typename ArrayIndex<TypesToApply, Integer<4> >::type>
{};

template<typename T, typename CodomainMFC, typename ParamArray, typename Arity>
struct ApplyCodomainDeduction
{
    typedef typename ArrayZip<typename GetInputTypeArray<T>::type, ParamArray, UseTemplateParam>::type TypesToApply;
    typedef typename ApplyCodomainDeduction_Impl<CodomainMFC, TypesToApply, Arity>::type type;
};

template<typename T, typename CodomainType, typename ParamArray>
struct GetCodomainType_Impl : identity_type<CodomainType> {};

template<typename T, typename U, typename ParamArray>
struct GetCodomainType_Impl<T, CodomainDeduction<U>, ParamArray> : ApplyCodomainDeduction<T, U, ParamArray, typename GetFunctionArity<T>::type>
{};

} // namespace impl

template<typename T, typename I0=no_argument, typename I1=no_argument, typename I2=no_argument, typename I3=no_argument, typename I4=no_argument>
struct DeduceCodomainType : impl::GetCodomainType_Impl<T, typename GetCodomainType<T>::type, Array<I0, I1, I2, I3, I4> > {};





//Specialisations for function pointers
template<typename T>
struct GetCodomainType<T(*)()>
{
    typedef T type;
};

template<typename T>
struct FunctionSignatureEnabled<T(*)()> : true_type {};

template<typename T, typename Index>
struct HasInputType<T(*)(), Index> : false_type {};

template<typename T, typename Index>
struct GetInputType<T(*)(), Index> ;

template<typename T>
struct GetFunctionArity<T(*)()> : Integer<0> {};



template<typename T, typename U>
struct GetCodomainType<T(*)(U)>
{
    typedef T type;
};

template<typename T, typename U>
struct FunctionSignatureEnabled<T(*)(U)> : true_type {};

template<typename T, typename U>
struct HasInputType<T(*)(U), Integer<0> > : true_type {};

template<typename T, typename U, typename Index>
struct HasInputType<T(*)(U), Index> : false_type {};

template<typename T, typename U>
struct GetInputType<T(*)(U), Integer<0> > : deduce_input_type<U> {};

template<typename T, typename U>
struct GetFunctionArity<T(*)(U)> : Integer<1> {};




template<typename T, typename U, typename V>
struct GetCodomainType<T(*)(U, V)>
{
    typedef T type;
};

template<typename T, typename U, typename V>
struct FunctionSignatureEnabled<T(*)(U, V)> : true_type {};

template<typename T, typename U, typename V>
struct HasInputType<T(*)(U, V), Integer<0> > : true_type {};

template<typename T, typename U, typename V>
struct HasInputType<T(*)(U, V), Integer<1> > : true_type {};

template<typename T, typename U, typename V, typename Index>
struct HasInputType<T(*)(U, V), Index> : false_type {};

template<typename T, typename U, typename V>
struct GetInputType<T(*)(U, V), Integer<0> > : deduce_input_type<U> {};

template<typename T, typename U, typename V>
struct GetInputType<T(*)(U, V), Integer<1> > : deduce_input_type<V> {};

template<typename T, typename U, typename V>
struct GetFunctionArity<T(*)(U, V)> : Integer<2> {};





template<typename T, typename U, typename V, typename W>
struct GetCodomainType<T(*)(U, V, W)>
{
    typedef T type;
};

template<typename T, typename U, typename V, typename W>
struct FunctionSignatureEnabled<T(*)(U, V, W)> : true_type {};

template<typename T, typename U, typename V, typename W>
struct HasInputType<T(*)(U, V, W), Integer<0> > : true_type {};

template<typename T, typename U, typename V, typename W>
struct HasInputType<T(*)(U, V, W), Integer<1> > : true_type {};

template<typename T, typename U, typename V, typename W>
struct HasInputType<T(*)(U, V, W), Integer<2> > : true_type {};

template<typename T, typename U, typename V, typename W, typename Index>
struct HasInputType<T(*)(U, V, W), Index> : false_type {};

template<typename T, typename U, typename V, typename W>
struct GetInputType<T(*)(U, V, W), Integer<0> > : deduce_input_type<U> {};

template<typename T, typename U, typename V, typename W>
struct GetInputType<T(*)(U, V, W), Integer<1> > : deduce_input_type<V> {};

template<typename T, typename U, typename V, typename W>
struct GetInputType<T(*)(U, V, W), Integer<2> > : deduce_input_type<W> {};

template<typename T, typename U, typename V, typename W>
struct GetFunctionArity<T(*)(U, V, W)> : Integer<3> {};





template<typename T, typename U, typename V, typename W, typename X>
struct GetCodomainType<T(*)(U, V, W, X)>
{
    typedef T type;
};

template<typename T, typename U, typename V, typename W, typename X>
struct FunctionSignatureEnabled<T(*)(U, V, W, X)> : true_type {};

template<typename T, typename U, typename V, typename W, typename X>
struct HasInputType<T(*)(U, V, W, X), Integer<0> > : true_type {};

template<typename T, typename U, typename V, typename W, typename X>
struct HasInputType<T(*)(U, V, W, X), Integer<1> > : true_type {};

template<typename T, typename U, typename V, typename W, typename X>
struct HasInputType<T(*)(U, V, W, X), Integer<2> > : true_type {};

template<typename T, typename U, typename V, typename W, typename X>
struct HasInputType<T(*)(U, V, W, X), Integer<3> > : true_type {};

template<typename T, typename U, typename V, typename W, typename X, typename Index>
struct HasInputType<T(*)(U, V, W, X), Index> : false_type {};

template<typename T, typename U, typename V, typename W, typename X>
struct GetInputType<T(*)(U, V, W, X), Integer<0> > : deduce_input_type<U> {};

template<typename T, typename U, typename V, typename W, typename X>
struct GetInputType<T(*)(U, V, W, X), Integer<1> > : deduce_input_type<V> {};

template<typename T, typename U, typename V, typename W, typename X>
struct GetInputType<T(*)(U, V, W, X), Integer<2> > : deduce_input_type<W> {};

template<typename T, typename U, typename V, typename W, typename X>
struct GetInputType<T(*)(U, V, W, X), Integer<3> > : deduce_input_type<X> {};

template<typename T, typename U, typename V, typename W, typename X>
struct GetFunctionArity<T(*)(U, V, W, X)> : Integer<4> {};




template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct GetCodomainType<T(*)(U, V, W, X, Y)>
{
    typedef T type;
};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct FunctionSignatureEnabled<T(*)(U, V, W, X, Y)> : true_type {};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct HasInputType<T(*)(U, V, W, X, Y), Integer<0> > : true_type {};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct HasInputType<T(*)(U, V, W, X, Y), Integer<1> > : true_type {};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct HasInputType<T(*)(U, V, W, X, Y), Integer<2> > : true_type {};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct HasInputType<T(*)(U, V, W, X, Y), Integer<3> > : true_type {};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct HasInputType<T(*)(U, V, W, X, Y), Integer<4> > : true_type {};

template<typename T, typename U, typename V, typename W, typename X, typename Y, typename Index>
struct HasInputType<T(*)(U, V, W, X, Y), Index> : false_type {};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct GetInputType<T(*)(U, V, W, X, Y), Integer<0> > : deduce_input_type<U> {};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct GetInputType<T(*)(U, V, W, X, Y), Integer<1> > : deduce_input_type<V> {};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct GetInputType<T(*)(U, V, W, X, Y), Integer<2> > : deduce_input_type<W> {};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct GetInputType<T(*)(U, V, W, X, Y), Integer<3> > : deduce_input_type<X> {};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct GetInputType<T(*)(U, V, W, X, Y), Integer<4> > : deduce_input_type<Y> {};

template<typename T, typename U, typename V, typename W, typename X, typename Y>
struct GetFunctionArity<T(*)(U, V, W, X, Y)> : Integer<5> {};

} // namespace intro

#endif
