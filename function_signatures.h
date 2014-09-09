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

// T const & versus T, convertible to T versus T?

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


// Count upwards; higher Arity is less likely.
// Note that Indexing is zero based, and that CurrentArity suggests 0..CurrentArity are available
template<typename T, typename CurrentArity>
struct GetFunctionArityLoop : eval_if<HasInputType_Impl<T, CurrentArity>,
                                      GetFunctionArityLoop<T, typename Successor<CurrentArity>::type>,
                                      CurrentArity>
{};

template<typename T, typename AccumulatedArray, typename CurrentIndex, typename Arity>
struct GetInputTypeArrayLoop;

template<typename T, typename AccumulatedArray, typename Arity>
struct GetInputTypeArrayLoop<T, AccumulatedArray, Arity, Arity> : AccumulatedArray {};

template<typename T, typename AccumulatedArray, typename CurrentIndex, typename Arity>
struct GetInputTypeArrayLoop :
    GetInputTypeArrayLoop<T, typename ArrayConcat<AccumulatedArray, typename GetInputType_Impl<T, CurrentIndex>::type>::type, typename Successor<CurrentIndex>::type, Arity> {};


template<typename T>
struct GetInputTypeArray_Impl :
    GetInputTypeArrayLoop<T, Array<>, Integer<0>, typename GetFunctionArityLoop<T, Integer<0> >::type > {};




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
    typedef typename ArrayZip<typename GetInputTypeArray_Impl<T>::type, ParamArray, UseTemplateParam>::type TypesToApply;
    typedef typename ApplyCodomainDeduction_Impl<CodomainMFC, TypesToApply, Arity>::type type;
};

template<typename T, typename CodomainType, typename ParamArray>
struct GetCodomainType_Impl : identity_type<CodomainType> {};

template<typename T, typename U, typename ParamArray>
struct GetCodomainType_Impl<T, CodomainDeduction<U>, ParamArray> : ApplyCodomainDeduction<T, U, ParamArray, typename GetFunctionArityLoop<T, Integer<0> >::type>
{};

} // namespace impl

// Only need a codomain before the fun can start
template<typename T>
struct FunctionSignatureEnabled : HasMemberType_codomain_type<T> {};

template<typename T, typename Index>
struct HasInputType : impl::HasInputType_Impl<T, Index> {};

template<typename T, typename Index>
struct GetInputType : impl::GetInputType_Impl<T, Index> {};

template<typename T>
struct GetInputTypeArray : impl::GetInputTypeArray_Impl<T> {};

template<typename T>
struct GetFunctionArity : impl::GetFunctionArityLoop<T, Integer<0> > {};

template<typename T, typename I0=no_argument, typename I1=no_argument, typename I2=no_argument, typename I3=no_argument, typename I4=no_argument>
struct GetCodomainType : impl::GetCodomainType_Impl<T, typename GetMemberType_codomain_type<T>::type, Array<I0, I1, I2, I3, I4> > {};

/*
//Specialisations for function pointers
template<typename T>
struct GetCodomainType<T(*)>
{
  typedef T type;
};

template<typename T>
struct FunctionSignatureEnabled<T(*)> : true_type {};

template<typename T, typename Index>
struct HasInputType<T(*), Index> : false_type {};
*/
} // namespace intro

#endif
