#ifndef INCLUDED_FUNCTION_SIGNATURES
#define INCLUDED_FUNCTION_SIGNATURES

#ifndef INCLUDED_DETECT_TRAITS
#include "detect_traits.h"
#endif

#ifndef INCLUDED_METAPROGRAMMING
#include "metaprogramming.h"
#endif

#ifndef INCLUDED_COMPILER_SPECIFICS
#include "compiler_specifics.h"
#endif

namespace intro {

// This is the metafunction by which function pointers become associated with a metafunction
// describing it. For standard functors it is trivial to add typedefs with the appropriate information
// but nesting typedefs is impossible in pointers.
// It is assumed that all types using within namespace impl have been passed through this metafunction first
// to get the appropriate information.
template<typename T, typename Enable=void>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType
{
    typedef T type;
    INTROSPECTION_STATIC_ASSERT(( is_struct_class_or_union<T> )); // Assert here = function arity too high
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY CodomainDeduction { typedef CodomainDeduction type; METAPROGRAMMING_ONLY(CodomainDeduction)};

// Generates the non-impl functions to forward onto the impl, via the ResolveFunctionSignatureType metafunction.
#define GENERATE_FUNCTION_SIGNATURE_GETTERS(x)\
namespace function_signature_getters {\
GENERATE_HAS_AND_GET_MEMBER_TYPE(x)\
}\
template<typename T> struct TYPE_HIDDEN_VISIBILITY Has_##x : function_signature_getters::HasMemberType_##x<typename ResolveFunctionSignatureType<T>::type> {METAPROGRAMMING_ONLY(Has_##x)};\
template<typename T> struct TYPE_HIDDEN_VISIBILITY Get_##x : function_signature_getters::GetMemberType_##x<typename ResolveFunctionSignatureType<T>::type> {METAPROGRAMMING_ONLY(Get_##x)};

GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_0)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_1)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_2)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_3)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_4)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_5)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_6)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_7)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_8)
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_type_9)
GENERATE_FUNCTION_SIGNATURE_GETTERS(codomain_type)

// add typedef input_types to return all the types in a single Array.
// Used in preference to input_type_N typedefs.
GENERATE_FUNCTION_SIGNATURE_GETTERS(input_types)

#undef GENERATE_FUNCTION_SIGNATURE_GETTERS

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetCodomainType : Get_codomain_type<T> {METAPROGRAMMING_ONLY(GetCodomainType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY FunctionSignatureEnabled : Has_codomain_type<T> {METAPROGRAMMING_ONLY(FunctionSignatureEnabled)};

namespace HasInputType_impl {

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType;

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<0> > : Has_input_type_0<T> {METAPROGRAMMING_ONLY(HasNumberedInputType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<1> > : Has_input_type_1<T> {METAPROGRAMMING_ONLY(HasNumberedInputType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<2> > : Has_input_type_2<T> {METAPROGRAMMING_ONLY(HasNumberedInputType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<3> > : Has_input_type_3<T> {METAPROGRAMMING_ONLY(HasNumberedInputType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<4> > : Has_input_type_4<T> {METAPROGRAMMING_ONLY(HasNumberedInputType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<5> > : Has_input_type_5<T> {METAPROGRAMMING_ONLY(HasNumberedInputType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<6> > : Has_input_type_6<T> {METAPROGRAMMING_ONLY(HasNumberedInputType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<7> > : Has_input_type_7<T> {METAPROGRAMMING_ONLY(HasNumberedInputType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<8> > : Has_input_type_8<T> {METAPROGRAMMING_ONLY(HasNumberedInputType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<9> > : Has_input_type_9<T> {METAPROGRAMMING_ONLY(HasNumberedInputType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<10> > : false_type {METAPROGRAMMING_ONLY(HasNumberedInputType)};

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY HasArrayInputItem :
    not_<is_same<ArrayNoArg, typename ArrayIndex<typename Get_input_types<T>::type, Index>::type > >
{
    METAPROGRAMMING_ONLY(HasArrayInputItem)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY HasArrayInputItem<T, Integer<10> > : false_type {METAPROGRAMMING_ONLY(HasArrayInputItem)};

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY HasInputType :
    eval_if<Has_input_types<T>,
            HasInputType_impl::HasArrayInputItem<T, Index>,
            HasInputType_impl::HasNumberedInputType<T, Index> >
{
    METAPROGRAMMING_ONLY(HasInputType)
};

} // namespace HasInputType_impl

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY HasInputType :
    HasInputType_impl::HasInputType<typename ResolveFunctionSignatureType<T>::type, Index>
{
    METAPROGRAMMING_ONLY(HasInputType)
};


namespace GetInputType_impl {

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_impl;

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_impl<T, Integer<0> > : Get_input_type_0<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_impl<T, Integer<1> > : Get_input_type_1<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_impl<T, Integer<2> > : Get_input_type_2<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_impl<T, Integer<3> > : Get_input_type_3<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_impl<T, Integer<4> > : Get_input_type_4<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_impl<T, Integer<5> > : Get_input_type_5<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_impl<T, Integer<6> > : Get_input_type_6<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_impl<T, Integer<7> > : Get_input_type_7<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_impl<T, Integer<8> > : Get_input_type_8<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_impl<T, Integer<9> > : Get_input_type_9<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_impl)};

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetArrayInputType_impl :
    ArrayIndex<typename Get_input_types<T>::type, Index>
{
    METAPROGRAMMING_ONLY(GetArrayInputType_impl)
};

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetInputType :
    eval_if<Has_input_types<T>,
            GetInputType_impl::GetArrayInputType_impl<T, Index>,
            GetInputType_impl::GetNumberedInputType_impl<T, Index> >
{
    METAPROGRAMMING_ONLY(GetInputType)
};

} // namespace GetInputType_impl

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetInputType :
    GetInputType_impl::GetInputType<typename ResolveFunctionSignatureType<T>::type, Index>
{
    METAPROGRAMMING_ONLY(GetInputType)
};


namespace GetFunctionArity_impl {

// Count upwards; higher Arity is less likely.
// Note that Indexing is zero based, and that CurrentArity suggests 0..CurrentArity-1(inclusive) are available
template<typename T, typename CurrentArity>
struct TYPE_HIDDEN_VISIBILITY GetFunctionArityLoop : eval_if<HasInputType<T, CurrentArity>,
                                      GetFunctionArityLoop<T, typename Successor<CurrentArity>::type>,
                                      CurrentArity>
{
    METAPROGRAMMING_ONLY(GetFunctionArityLoop)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetFunctionArityArray : ArraySize<typename Get_input_types<T>::type>
{
    METAPROGRAMMING_ONLY(GetFunctionArityArray)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetFunctionArity :
    eval_if<Has_input_types<T>,
            GetFunctionArity_impl::GetFunctionArityArray<T>,
            GetFunctionArity_impl::GetFunctionArityLoop<T, Integer<0> > >
{
    METAPROGRAMMING_ONLY(GetFunctionArity)
};

} // namespace GetFunctionArity_impl

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetFunctionArity :
    GetFunctionArity_impl::GetFunctionArity<typename ResolveFunctionSignatureType<T>::type>
{
    METAPROGRAMMING_ONLY(GetFunctionArity)
};


namespace GetInputTypeArray_impl {

template<typename T, typename AccumulatedArray, typename CurrentIndex, typename Arity>
struct TYPE_HIDDEN_VISIBILITY GetInputTypeArrayNumbered;

template<typename T, typename AccumulatedArray, typename Arity>
struct TYPE_HIDDEN_VISIBILITY GetInputTypeArrayNumbered<T, AccumulatedArray, Arity, Arity> : AccumulatedArray
{
    METAPROGRAMMING_ONLY(GetInputTypeArrayNumbered)
};

template<typename T, typename AccumulatedArray, typename CurrentIndex, typename Arity>
struct TYPE_HIDDEN_VISIBILITY GetInputTypeArrayNumbered :
    GetInputTypeArrayNumbered<T, typename ArrayConcat<AccumulatedArray, Array<typename GetInputType<T, CurrentIndex>::type> >::type, typename Successor<CurrentIndex>::type, Arity>
{
    METAPROGRAMMING_ONLY(GetInputTypeArrayNumbered)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetInputTypeArray :
    eval_if<Has_input_types<T>,
            Get_input_types<T>,
            GetInputTypeArray_impl::GetInputTypeArrayNumbered<T, Array<>, Integer<0>, typename GetFunctionArity<T>::type> >
{
    METAPROGRAMMING_ONLY(GetInputTypeArray)
};

} // namespace GetInputTypeArray_impl

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetInputTypeArray :
    GetInputTypeArray_impl::GetInputTypeArray<typename ResolveFunctionSignatureType<T>::type>
{
    METAPROGRAMMING_ONLY(GetInputTypeArray)
};


struct TYPE_HIDDEN_VISIBILITY no_template_argument { typedef no_template_argument type; METAPROGRAMMING_ONLY(no_template_argument) };
struct TYPE_HIDDEN_VISIBILITY template_param { typedef template_param type; METAPROGRAMMING_ONLY(template_param) };

namespace GetCodomainType_impl {

template<typename InputType, typename ParamArrayItem>
struct TYPE_HIDDEN_VISIBILITY UseTemplateParamWhereNeeded;

template<>
struct TYPE_HIDDEN_VISIBILITY UseTemplateParamWhereNeeded<template_param, no_template_argument>
{
    METAPROGRAMMING_ONLY(UseTemplateParamWhereNeeded)
}; // typedef type not defined as this situation is unexpected; a parameter was expected

template<typename ParamArrayItem>
struct TYPE_HIDDEN_VISIBILITY UseTemplateParamWhereNeeded<template_param, ParamArrayItem>
{
    typedef ParamArrayItem type;
    METAPROGRAMMING_ONLY(UseTemplateParamWhereNeeded)
};

template<typename InputType>
struct TYPE_HIDDEN_VISIBILITY UseTemplateParamWhereNeeded<InputType, no_template_argument>
{
    typedef InputType type;
    METAPROGRAMMING_ONLY(UseTemplateParamWhereNeeded)
};

template<>
struct TYPE_HIDDEN_VISIBILITY UseTemplateParamWhereNeeded<ArrayNoArg, no_template_argument> : ArrayNoArg {METAPROGRAMMING_ONLY(UseTemplateParamWhereNeeded)};

template<>
struct TYPE_HIDDEN_VISIBILITY UseTemplateParamWhereNeeded<ArrayNoArg, ArrayNoArg> : ArrayNoArg {METAPROGRAMMING_ONLY(UseTemplateParamWhereNeeded)};

template<typename T, typename CodomainMFC, typename ParamArray, typename Arity>
struct TYPE_HIDDEN_VISIBILITY ApplyCodomainDeduction
{
    typedef typename ArrayZip<typename GetInputTypeArray<T>::type, ParamArray, UseTemplateParamWhereNeeded<placeholders::_0, placeholders::_1> >::type TypesToApply;
    // Must use RationaliseApplyArray to convert the ArrayNoArg into apply_ignore within the first 5 elements of the array.
    // If we did not do this then very bad things would happen.
    typedef typename Apply_Environment<CodomainMFC, typename RationaliseApplyArray<TypesToApply, ArrayNoArg>::type>::type type;
    METAPROGRAMMING_ONLY(ApplyCodomainDeduction)
};

template<typename T, typename CodomainType, typename ParamArray>
struct TYPE_HIDDEN_VISIBILITY GetCodomainType : identity_type<CodomainType> {METAPROGRAMMING_ONLY(GetCodomainType)};

template<typename T, typename U, typename ParamArray>
struct TYPE_HIDDEN_VISIBILITY GetCodomainType<T, CodomainDeduction<U>, ParamArray> : ApplyCodomainDeduction<T, U, ParamArray, typename GetFunctionArity<T>::type>
{
    METAPROGRAMMING_ONLY(GetCodomainType)
};

} // namespace GetCodomainType_impl

template<typename T, typename I0=no_template_argument, typename I1=no_template_argument, typename I2=no_template_argument, typename I3=no_template_argument, typename I4=no_template_argument, typename I5=no_template_argument, typename I6=no_template_argument, typename I7=no_template_argument, typename I8=no_template_argument, typename I9=no_template_argument>
struct TYPE_HIDDEN_VISIBILITY DeduceCodomainType : GetCodomainType_impl::GetCodomainType<typename ResolveFunctionSignatureType<T>::type,
typename GetCodomainType<typename ResolveFunctionSignatureType<T>::type>::type, Array<I0, I1, I2, I3, I4, I5, I6, I7, I8, I9> >
{
    METAPROGRAMMING_ONLY(DeduceCodomainType)
};


namespace function_pointer_specialisations {

template<typename CodomainType, typename InputTypes>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature;

template<typename CodomainType>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature<CodomainType, Array<ArrayNoArg> >
{
    typedef CodomainType(*type)();
    METAPROGRAMMING_ONLY(function_pointer_signature)
};

template<typename CodomainType, typename A>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature<CodomainType, Array<A, ArrayNoArg> >
{
    typedef CodomainType(*type)(A);
    METAPROGRAMMING_ONLY(function_pointer_signature)
};

template<typename CodomainType, typename A, typename B>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature<CodomainType, Array<A, B, ArrayNoArg> >
{
    typedef CodomainType(*type)(A, B);
    METAPROGRAMMING_ONLY(function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature<CodomainType, Array<A, B, C, ArrayNoArg> >
{
    typedef CodomainType(*type)(A, B, C);
    METAPROGRAMMING_ONLY(function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C, typename D>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature<CodomainType, Array<A, B, C, D, ArrayNoArg> >
{
    typedef CodomainType(*type)(A, B, C, D);
    METAPROGRAMMING_ONLY(function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature<CodomainType, Array<A, B, C, D, E, ArrayNoArg> >
{
    typedef CodomainType(*type)(A, B, C, D, E);
    METAPROGRAMMING_ONLY(function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature<CodomainType, Array<A, B, C, D, E, F, ArrayNoArg> >
{
    typedef CodomainType(*type)(A, B, C, D, E, F);
    METAPROGRAMMING_ONLY(function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature<CodomainType, Array<A, B, C, D, E, F, G, ArrayNoArg> >
{
    typedef CodomainType(*type)(A, B, C, D, E, F, G);
    METAPROGRAMMING_ONLY(function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature<CodomainType, Array<A, B, C, D, E, F, G, H, ArrayNoArg> >
{
    typedef CodomainType(*type)(A, B, C, D, E, F, G, H);
    METAPROGRAMMING_ONLY(function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature<CodomainType, Array<A, B, C, D, E, F, G, H, I, ArrayNoArg> >
{
    typedef CodomainType(*type)(A, B, C, D, E, F, G, H, I);
    METAPROGRAMMING_ONLY(function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J>
struct TYPE_HIDDEN_VISIBILITY function_pointer_signature<CodomainType, Array<A, B, C, D, E, F, G, H, I, J> >
{
    typedef CodomainType(*type)(A, B, C, D, E, F, G, H, I, J);
    METAPROGRAMMING_ONLY(function_pointer_signature)
};


template<typename CodomainType, typename InputTypes>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature;


#define MEMBER_FUNCTION_POINTER_SIGNATURES(CV)\
template<typename CodomainType, typename A> \
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A CV*, ArrayNoArg> > \
{ \
    typedef CodomainType(A::*type)() CV; \
    METAPROGRAMMING_ONLY(member_function_pointer_signature) \
}; \
 \
template<typename CodomainType, typename A, typename B> \
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A CV*, B, ArrayNoArg> > \
{ \
    typedef CodomainType(A::*type)(B) CV; \
    METAPROGRAMMING_ONLY(member_function_pointer_signature) \
}; \
 \
template<typename CodomainType, typename A, typename B, typename C> \
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A CV*, B, C, ArrayNoArg> > \
{ \
    typedef CodomainType(A::*type)(B, C) CV; \
    METAPROGRAMMING_ONLY(member_function_pointer_signature) \
}; \
 \
template<typename CodomainType, typename A, typename B, typename C, typename D> \
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A CV*, B, C, D, ArrayNoArg> > \
{ \
    typedef CodomainType(A::*type)(B, C, D) CV; \
    METAPROGRAMMING_ONLY(member_function_pointer_signature) \
}; \
 \
template<typename CodomainType, typename A, typename B, typename C, typename D, typename E> \
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A CV*, B, C, D, E, ArrayNoArg> > \
{ \
    typedef CodomainType(A::*type)(B, C, D, E) CV; \
    METAPROGRAMMING_ONLY(member_function_pointer_signature) \
}; \
 \
template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F> \
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A CV*, B, C, D, E, F, ArrayNoArg> > \
{ \
    typedef CodomainType(A::*type)(B, C, D, E, F) CV; \
    METAPROGRAMMING_ONLY(member_function_pointer_signature) \
}; \
 \
template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G> \
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A CV*, B, C, D, E, F, G, ArrayNoArg> > \
{ \
    typedef CodomainType(A::*type)(B, C, D, E, F, G) CV; \
    METAPROGRAMMING_ONLY(member_function_pointer_signature) \
}; \
 \
template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H> \
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A CV*, B, C, D, E, F, G, H, ArrayNoArg> > \
{ \
    typedef CodomainType(A::*type)(B, C, D, E, F, G, H) CV; \
    METAPROGRAMMING_ONLY(member_function_pointer_signature) \
}; \
 \
template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I> \
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A CV*, B, C, D, E, F, G, H, I, ArrayNoArg> > \
{ \
    typedef CodomainType(A::*type)(B, C, D, E, F, G, H, I) CV; \
    METAPROGRAMMING_ONLY(member_function_pointer_signature) \
}; \
 \
template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J> \
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A CV*, B, C, D, E, F, G, H, I, J> > \
{ \
    typedef CodomainType(A::*type)(B, C, D, E, F, G, H, I, J) CV; \
    METAPROGRAMMING_ONLY(member_function_pointer_signature) \
};

MEMBER_FUNCTION_POINTER_SIGNATURES()
MEMBER_FUNCTION_POINTER_SIGNATURES(const)
MEMBER_FUNCTION_POINTER_SIGNATURES(volatile)
MEMBER_FUNCTION_POINTER_SIGNATURES(const volatile)
#undef MEMBER_FUNCTION_POINTER_SIGNATURES


template<typename CodomainType, typename InputTypes, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY get_function_pointer_signature :
    eval_if<MemberFunction,
            member_function_pointer_signature<CodomainType, InputTypes>,
            function_pointer_signature<CodomainType, InputTypes> >
{
    METAPROGRAMMING_ONLY(get_function_pointer_signature)
};

template<typename CodomainType, typename InputTypes, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper;

// Note ArrayNoArg explicitly mentioned in the specialisations
// to remove ambiguity between partial specialsations
template<typename CodomainType, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<ArrayNoArg>, MemberFunction>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<> input_types;
    typedef typename get_function_pointer_signature<codomain_type, input_types, MemberFunction>::type Func;
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, ArrayNoArg>, MemberFunction>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A> input_types;
    typedef typename get_function_pointer_signature<codomain_type, input_types, MemberFunction>::type Func;
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, ArrayNoArg>, MemberFunction>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B> input_types;
    typedef typename get_function_pointer_signature<codomain_type, input_types, MemberFunction>::type Func;
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B, typename C, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, C, ArrayNoArg>, MemberFunction>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B, C> input_types;
    typedef typename get_function_pointer_signature<codomain_type, input_types, MemberFunction>::type Func;
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, C, D, ArrayNoArg>, MemberFunction>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B, C, D> input_types;
    typedef typename get_function_pointer_signature<codomain_type, input_types, MemberFunction>::type Func;
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, C, D, E, ArrayNoArg>, MemberFunction>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B, C, D, E> input_types;
    typedef typename get_function_pointer_signature<codomain_type, input_types, MemberFunction>::type Func;
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, C, D, E, F, ArrayNoArg>, MemberFunction>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B, C, D, E, F> input_types;
    typedef typename get_function_pointer_signature<codomain_type, input_types, MemberFunction>::type Func;
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, C, D, E, F, G, ArrayNoArg>, MemberFunction>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B, C, D, E, F, G> input_types;
    typedef typename get_function_pointer_signature<codomain_type, input_types, MemberFunction>::type Func;
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, C, D, E, F, G, H, ArrayNoArg>, MemberFunction>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B, C, D, E, F, G, H> input_types;
    typedef typename get_function_pointer_signature<codomain_type, input_types, MemberFunction>::type Func;
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, C, D, E, F, G, H, I, ArrayNoArg>, MemberFunction>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B, C, D, E, F, G, H, I> input_types;
    typedef typename get_function_pointer_signature<codomain_type, input_types, MemberFunction>::type Func;
    METAPROGRAMMING_ONLY(function_wrapper)
};
template<typename CodomainType, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, C, D, E, F, G, H, I, J>, MemberFunction>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B, C, D, E, F, G, H, I, J> input_types;
    typedef typename get_function_pointer_signature<codomain_type, input_types, MemberFunction>::type Func;
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY is_a_function_wrapper : false_type
{
    METAPROGRAMMING_ONLY(is_a_function_wrapper)
};

template<typename CodomainType, typename InputType, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY is_a_function_wrapper<function_pointer_specialisations::function_wrapper<CodomainType, InputType, MemberFunction> > : true_type
{
    METAPROGRAMMING_ONLY(is_a_function_wrapper)
};

} // namespace function_pointer_specialisations
 
template<typename R>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)()> :
    function_pointer_specialisations::function_wrapper<R, Array<>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename A>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(A)> :
    function_pointer_specialisations::function_wrapper<R, Array<A>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename A, typename B>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(A, B)> :
    function_pointer_specialisations::function_wrapper<R, Array<A, B>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename A, typename B, typename C>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(A, B, C)> :
    function_pointer_specialisations::function_wrapper<R, Array<A, B, C>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename A, typename B, typename C, typename D>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(A, B, C, D)> :
    function_pointer_specialisations::function_wrapper<R, Array<A, B, C, D>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename A, typename B, typename C, typename D, typename E>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(A, B, C, D, E)> :
    function_pointer_specialisations::function_wrapper<R, Array<A, B, C, D, E>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename A, typename B, typename C, typename D, typename E, typename F>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(A, B, C, D, E, F)> :
    function_pointer_specialisations::function_wrapper<R, Array<A, B, C, D, E, F>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename A, typename B, typename C, typename D, typename E, typename F, typename G>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(A, B, C, D, E, F, G)> :
    function_pointer_specialisations::function_wrapper<R, Array<A, B, C, D, E, F, G>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(A, B, C, D, E, F, G, H)> :
    function_pointer_specialisations::function_wrapper<R, Array<A, B, C, D, E, F, G, H>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(A, B, C, D, E, F, G, H, I)> :
    function_pointer_specialisations::function_wrapper<R, Array<A, B, C, D, E, F, G, H, I>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(A, B, C, D, E, F, G, H, I, J)> :
    function_pointer_specialisations::function_wrapper<R, Array<A, B, C, D, E, F, G, H, I, J>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};


#define MEMBER_FUNCTION_POINTER_WRAPPERS(CV)\
template<typename R, typename A> \
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(A::*)() CV> : \
    function_pointer_specialisations::function_wrapper<R, Array<A CV*>, true_type> \
{ \
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType) \
}; \
 \
template<typename R, typename A, typename B> \
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(A::*)(B) CV> : \
    function_pointer_specialisations::function_wrapper<R, Array<A CV*, B>, true_type> \
{ \
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType) \
}; \
 \
template<typename R, typename A, typename B, typename C> \
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(A::*)(B, C) CV> : \
    function_pointer_specialisations::function_wrapper<R, Array<A CV*, B, C>, true_type> \
{ \
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType) \
}; \
 \
template<typename R, typename A, typename B, typename C, typename D> \
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(A::*)(B, C, D) CV> : \
    function_pointer_specialisations::function_wrapper<R, Array<A CV*, B, C, D>, true_type> \
{ \
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType) \
}; \
 \
template<typename R, typename A, typename B, typename C, typename D, typename E> \
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(A::*)(B, C, D, E) CV> : \
    function_pointer_specialisations::function_wrapper<R, Array<A CV*, B, C, D, E>, true_type> \
{ \
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType) \
}; \
 \
template<typename R, typename A, typename B, typename C, typename D, typename E, typename F> \
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(A::*)(B, C, D, E, F) CV> : \
    function_pointer_specialisations::function_wrapper<R, Array<A CV*, B, C, D, E, F>, true_type> \
{ \
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType) \
}; \
 \
template<typename R, typename A, typename B, typename C, typename D, typename E, typename F, typename G> \
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(A::*)(B, C, D, E, F, G) CV> : \
    function_pointer_specialisations::function_wrapper<R, Array<A CV*, B, C, D, E, F, G>, true_type> \
{ \
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType) \
}; \
 \
template<typename R, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H> \
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(A::*)(B, C, D, E, F, G, H) CV> : \
    function_pointer_specialisations::function_wrapper<R, Array<A CV*, B, C, D, E, F, G, H>, true_type> \
{ \
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType) \
}; \
 \
template<typename R, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I> \
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(A::*)(B, C, D, E, F, G, H, I) CV> : \
    function_pointer_specialisations::function_wrapper<R, Array<A CV*, B, C, D, E, F, G, H, I>, true_type> \
{ \
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType) \
}; \
 \
template<typename R, typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J> \
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(A::*)(B, C, D, E, F, G, H, I, J) CV> : \
    function_pointer_specialisations::function_wrapper<R, Array<A CV*, B, C, D, E, F, G, H, I, J>, true_type> \
{ \
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType) \
};

MEMBER_FUNCTION_POINTER_WRAPPERS()
MEMBER_FUNCTION_POINTER_WRAPPERS(const)
MEMBER_FUNCTION_POINTER_WRAPPERS(volatile)
MEMBER_FUNCTION_POINTER_WRAPPERS(const volatile)

#undef MEMBER_FUNCTION_POINTER_WRAPPERS

namespace GetFunctionValueType_impl {

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetFunctionValueType
{
    typedef T type;
    METAPROGRAMMING_ONLY(GetFunctionValueType)
};

template<typename CodomainType, typename InputType, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY GetFunctionValueType<function_pointer_specialisations::function_wrapper<CodomainType, InputType, MemberFunction> >
{
    typedef typename function_pointer_specialisations::function_wrapper<CodomainType, InputType, MemberFunction>::Func type;
    METAPROGRAMMING_ONLY(GetFunctionValueType)
};

} // namespac GetFunctionValueType_impl

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetFunctionValueType : GetFunctionValueType_impl::GetFunctionValueType<typename ResolveFunctionSignatureType<T>::type>{METAPROGRAMMING_ONLY(GetFunctionValueType)};

} // namespace intro

#endif
