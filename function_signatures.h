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
template<typename T>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType
{
    typedef T type;
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

struct TYPE_HIDDEN_VISIBILITY no_template_argument { typedef no_template_argument type; METAPROGRAMMING_ONLY(no_template_argument) };
struct TYPE_HIDDEN_VISIBILITY template_param { typedef template_param type; METAPROGRAMMING_ONLY(template_param)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY CodomainDeduction { typedef CodomainDeduction type; METAPROGRAMMING_ONLY(CodomainDeduction)};

// Generates the non-impl functions to forward onto the impl, via the ResolveFunctionSignatureType metafunction.
#define GENERATE_FUNCTION_SIGNATURE_GETTERS(x)\
namespace impl{\
GENERATE_HAS_AND_GET_MEMBER_TYPE(x)\
}\
template<typename T> struct TYPE_HIDDEN_VISIBILITY Has_##x : impl::HasMemberType_##x<typename ResolveFunctionSignatureType<T>::type> {METAPROGRAMMING_ONLY(Has_##x)};\
template<typename T> struct TYPE_HIDDEN_VISIBILITY Get_##x : impl::GetMemberType_##x<typename ResolveFunctionSignatureType<T>::type> {METAPROGRAMMING_ONLY(Get_##x)};

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
struct TYPE_HIDDEN_VISIBILITY GetCodomainType : Get_codomain_type<T> {METAPROGRAMMING_ONLY(GetCodomainType)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY FunctionSignatureEnabled : Has_codomain_type<T> {METAPROGRAMMING_ONLY(FunctionSignatureEnabled)};

namespace impl {

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
struct TYPE_HIDDEN_VISIBILITY HasNumberedInputType<T, Integer<5> > : false_type {METAPROGRAMMING_ONLY(HasNumberedInputType)};


template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY HasArrayInputItem :
    not_<is_same<ArrayNoArg, typename ArrayIndex<typename GetMemberType_input_types<T>::type, Index>::type > >
{
    METAPROGRAMMING_ONLY(HasArrayInputItem)
};

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY HasInputType_Impl :
     eval_if<HasMemberType_input_types<T>,
             HasArrayInputItem<T, Index>,
             HasNumberedInputType<T, Index> >
{
    METAPROGRAMMING_ONLY(HasInputType_Impl)
};

} // namespace impl

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY HasInputType : impl::HasInputType_Impl<typename ResolveFunctionSignatureType<T>::type, Index>
{
    METAPROGRAMMING_ONLY(HasInputType)
};


namespace impl {

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_Impl;

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_Impl<T, Integer<0> > : Get_input_type_0<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_Impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_Impl<T, Integer<1> > : Get_input_type_1<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_Impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_Impl<T, Integer<2> > : Get_input_type_2<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_Impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_Impl<T, Integer<3> > : Get_input_type_3<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_Impl)};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetNumberedInputType_Impl<T, Integer<4> > : Get_input_type_4<T> {METAPROGRAMMING_ONLY(GetNumberedInputType_Impl)};

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetArrayInputType_Impl : ArrayIndex<typename GetMemberType_input_types<T>::type, Index>
{
    METAPROGRAMMING_ONLY(GetArrayInputType_Impl)
};

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetInputType_Impl : eval_if<HasMemberType_input_types<T>,
    GetArrayInputType_Impl<T, Index>,
    GetNumberedInputType_Impl<T, Index> >
{
    METAPROGRAMMING_ONLY(GetInputType_Impl)
};

} // namespace impl

template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetInputType : impl::GetInputType_Impl<typename ResolveFunctionSignatureType<T>::type, Index>
{
    METAPROGRAMMING_ONLY(GetInputType)
};

namespace impl {

// Count upwards; higher Arity is less likely.
// Note that Indexing is zero based, and that CurrentArity suggests 0..CurrentArity-1(inclusive) are available
template<typename T, typename CurrentArity>
struct TYPE_HIDDEN_VISIBILITY GetFunctionArityLoop : eval_if<HasNumberedInputType<T, CurrentArity>,
                                      GetFunctionArityLoop<T, typename Successor<CurrentArity>::type>,
                                      CurrentArity>
{
    METAPROGRAMMING_ONLY(GetFunctionArityLoop)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetFunctionArityArray : ArraySize<typename GetMemberType_input_types<T>::type>
{
    METAPROGRAMMING_ONLY(GetFunctionArityArray)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetFunctionArity_Impl : eval_if<HasMemberType_input_types<T>,
  GetFunctionArityArray<T>,
  GetFunctionArityLoop<T, Integer<0> > >
{
    METAPROGRAMMING_ONLY(GetFunctionArity_Impl)
};

} // namespace impl

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetFunctionArity : impl::GetFunctionArity_Impl<typename ResolveFunctionSignatureType<T>::type>
{
    METAPROGRAMMING_ONLY(GetFunctionArity)
};

namespace impl {

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
struct TYPE_HIDDEN_VISIBILITY GetInputTypeArray_Impl : eval_if<HasMemberType_input_types<T>,
    GetMemberType_input_types<T>,
    GetInputTypeArrayNumbered<T, Array<>, Integer<0>, typename GetFunctionArity<T>::type> >
{
    METAPROGRAMMING_ONLY(GetInputTypeArray_Impl)
};

}

template<typename T>
struct TYPE_HIDDEN_VISIBILITY GetInputTypeArray : impl::GetInputTypeArray_Impl<typename ResolveFunctionSignatureType<T>::type> {METAPROGRAMMING_ONLY(GetInputTypeArray)};

namespace impl {

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
struct TYPE_HIDDEN_VISIBILITY GetCodomainType_Impl : identity_type<CodomainType> {METAPROGRAMMING_ONLY(GetCodomainType_Impl)};

template<typename T, typename U, typename ParamArray>
struct TYPE_HIDDEN_VISIBILITY GetCodomainType_Impl<T, CodomainDeduction<U>, ParamArray> : ApplyCodomainDeduction<T, U, ParamArray, typename GetFunctionArity<T>::type>
{
    METAPROGRAMMING_ONLY(GetCodomainType_Impl)
};

} // namespace impl

template<typename T, typename I0=no_template_argument, typename I1=no_template_argument, typename I2=no_template_argument, typename I3=no_template_argument, typename I4=no_template_argument>
struct TYPE_HIDDEN_VISIBILITY DeduceCodomainType : impl::GetCodomainType_Impl<typename ResolveFunctionSignatureType<T>::type,
  typename GetCodomainType<typename ResolveFunctionSignatureType<T>::type>::type, Array<I0, I1, I2, I3, I4> >
{
    METAPROGRAMMING_ONLY(DeduceCodomainType)
};


//Specialisations for function pointers

namespace impl {

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


template<typename CodomainType, typename InputTypes>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature;

template<typename CodomainType, typename A>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A const&, ArrayNoArg> >
{
    typedef CodomainType(A::*type)() const;
    METAPROGRAMMING_ONLY(member_function_pointer_signature)
};

template<typename CodomainType, typename A>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A&, ArrayNoArg> >
{
    typedef CodomainType(A::*type)();
    METAPROGRAMMING_ONLY(member_function_pointer_signature)
};

template<typename CodomainType, typename A, typename B>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A const&, B, ArrayNoArg> >
{
    typedef CodomainType(A::*type)(B) const;
    METAPROGRAMMING_ONLY(member_function_pointer_signature)
};

template<typename CodomainType, typename A, typename B>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A&, B, ArrayNoArg> >
{
    typedef CodomainType(A::*type)(B);
    METAPROGRAMMING_ONLY(member_function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A const&, B, C, ArrayNoArg> >
{
    typedef CodomainType(A::*type)(B, C) const;
    METAPROGRAMMING_ONLY(member_function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A&, B, C, ArrayNoArg> >
{
    typedef CodomainType(A::*type)(B, C);
    METAPROGRAMMING_ONLY(member_function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C, typename D>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A const&, B, C, D, ArrayNoArg> >
{
    typedef CodomainType(A::*type)(B, C, D) const;
    METAPROGRAMMING_ONLY(member_function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C, typename D>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A&, B, C, D, ArrayNoArg> >
{
    typedef CodomainType(A::*type)(B, C, D);
    METAPROGRAMMING_ONLY(member_function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A const&, B, C, D, E, ArrayNoArg> >
{
    typedef CodomainType(A::*type)(B, C, D, E) const;
    METAPROGRAMMING_ONLY(member_function_pointer_signature)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E>
struct TYPE_HIDDEN_VISIBILITY member_function_pointer_signature<CodomainType, Array<A&, B, C, D, E, ArrayNoArg> >
{
    typedef CodomainType(A::*type)(B, C, D, E);
    METAPROGRAMMING_ONLY(member_function_pointer_signature)
};


template<typename CodomainType, typename InputTypes, typename MemberFunction>
struct TYPE_HIDDEN_VISIBILITY function_wrapper;

// Note ArrayNoArg explicitly mentioned in the specialisations
// to remove ambiguity between partial specialsations
template<typename CodomainType>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;
    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func) const
    {
        return (*func)();
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<void, Array<ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef void codomain_type;
    typedef Array<> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func) const
    {
        (*func)();
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};


template<typename CodomainType, typename A>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, A a) const
    {
        return (*func)(a);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename A>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<void, Array<A, ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef void codomain_type;
    typedef Array<A> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, A a) const
    {
        (*func)(a);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, A a, B b) const
    {
        return (*func)(a, b);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename A, typename B>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<void, Array<A, B, ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef void codomain_type;
    typedef Array<A, B> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, A a, B b) const
    {
        (*func)(a, b);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B, typename C>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, C, ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B, C> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, A a, B b, C c) const
    {
        return (*func)(a, b, c);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename A, typename B, typename C>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<void, Array<A, B, C, ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef void codomain_type;
    typedef Array<A, B, C> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, A a, B b, C c) const
    {
        (*func)(a, b, c);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B, typename C, typename D>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, C, D, ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B, C, D> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, A a, B b, C c, D d) const
    {
        return (*func)(a, b, c, d);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename A, typename B, typename C, typename D>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<void, Array<A, B, C, D, ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef void codomain_type;
    typedef Array<A, B, C, D> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, A a, B b, C c, D d) const
    {
        (*func)(a, b, c, d);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename CodomainType, typename A, typename B, typename C, typename D, typename E>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<CodomainType, Array<A, B, C, D, E, ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef CodomainType codomain_type;
    typedef Array<A, B, C, D, E> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, A a, B b, C c, D d, E e) const
    {
      return (*func)(a, b, c, d, e);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename A, typename B, typename C, typename D, typename E>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<void, Array<A, B, C, D, E, ArrayNoArg>, false_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef void codomain_type;
    typedef Array<A, B, C, D, E> input_types;
    typedef typename function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, A a, B b, C c, D d, E e) const
    {
        (*func)(a, b, c, d, e);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename R, typename C>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<R, Array<C, ArrayNoArg>, true_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef Array<C> input_types;
    typedef R codomain_type;
    typedef typename member_function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, C c) const
    {
        return (c.*func)();
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename C>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<void, Array<C, ArrayNoArg>, true_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef Array<C> input_types;
    typedef void codomain_type;
    typedef typename member_function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, C c) const
    {
        (c.*func)();
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};


template<typename R, typename C, typename U>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<R, Array<C, U, ArrayNoArg>, true_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef Array<C, U> input_types;
    typedef R codomain_type;
    typedef typename member_function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, C c, U u) const
    {
        return (c.*func)(u);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename C, typename U>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<void, Array<C, U, ArrayNoArg>, true_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef Array<C, U> input_types;
    typedef void codomain_type;
    typedef typename member_function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, C c, U u) const
    {
        (c.*func)(u);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};


template<typename R, typename C, typename U, typename V>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<R, Array<C, U, V, ArrayNoArg>, true_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V> input_types;
    typedef R codomain_type;
    typedef typename member_function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, C c, U u, V v) const
    {
        return (c.*func)(u, v);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename C, typename U, typename V>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<void, Array<C, U, V, ArrayNoArg>, true_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V> input_types;
    typedef void codomain_type;
    typedef typename member_function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, C c, U u, V v) const
    {
        (c.*func)(u, v);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};


template<typename R, typename C, typename U, typename V, typename W>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<R, Array<C, U, V, W, ArrayNoArg>, true_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V, W> input_types;
    typedef R codomain_type;
    typedef typename member_function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, C c, U u, V v, W w) const
    {
        return (c.*func)(u, v, w);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename C, typename U, typename V, typename W>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<void, Array<C, U, V, W, ArrayNoArg>, true_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V, W> input_types;
    typedef void codomain_type;
    typedef typename member_function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, C c, U u, V v, W w) const
    {
        (c.*func)(u, v, w);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};


template<typename R, typename C, typename U, typename V, typename W, typename X>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<R, Array<C, U, V, W, X, ArrayNoArg>, true_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V, W, X> input_types;
    typedef R codomain_type;
    typedef typename member_function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, C c, U u, V v, W w, X x) const
    {
        return (c.*func)(u, v, w, x);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

template<typename C, typename U, typename V, typename W, typename X>
struct TYPE_HIDDEN_VISIBILITY function_wrapper<void, Array<C, U, V, W, X, ArrayNoArg>, true_type>
{
    typedef function_wrapper type;
    typedef true_type introspection_enabled;
    typedef Array<C, U, V, W, X> input_types;
    typedef void codomain_type;
    typedef typename member_function_pointer_signature<codomain_type, input_types>::type Func;

    /*
    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func, C c, U u, V v, W w, X x) const
    {
        (c.*func)(u, v, w, x);
    }
    */
    METAPROGRAMMING_ONLY(function_wrapper)
};

} // namespace impl
 
template<typename R>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)()> :
    impl::function_wrapper<R, Array<>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename U>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(U)> :
    impl::function_wrapper<R, Array<U>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename U, typename V>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(U, V)> :
    impl::function_wrapper<R, Array<U, V>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename U, typename V, typename W>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(U, V, W)> :
    impl::function_wrapper<R, Array<U, V, W>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename U, typename V, typename W, typename X>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(U, V, W, X)> :
    impl::function_wrapper<R, Array<U, V, W, X>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename U, typename V, typename W, typename X, typename Y>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(*)(U, V, W, X, Y)> :
    impl::function_wrapper<R, Array<U, V, W, X, Y>, false_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};


template<typename R, typename C>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(C::*)()> :
    impl::function_wrapper<R, Array<C&>, true_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename C>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(C::*)() const> :
    impl::function_wrapper<R, Array<C const&>, true_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};


template<typename R, typename C, typename U>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(C::*)(U)> :
    impl::function_wrapper<R, Array<C&, U>, true_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename C, typename U>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(C::*)(U) const> :
    impl::function_wrapper<R, Array<C const&, U>, true_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};


template<typename R, typename C, typename U, typename V>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(C::*)(U, V)> :
    impl::function_wrapper<R, Array<C&, U, V>, true_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename C, typename U, typename V>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(C::*)(U, V) const> :
    impl::function_wrapper<R, Array<C const&, U, V>, true_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};


template<typename R, typename C, typename U, typename V, typename W>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(C::*)(U, V, W)> :
    impl::function_wrapper<R, Array<C&, U, V, W>, true_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename C, typename U, typename V, typename W>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(C::*)(U, V, W) const> :
    impl::function_wrapper<R, Array<C const&, U, V, W>, true_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};


template<typename R, typename C, typename U, typename V, typename W, typename X>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(C::*)(U, V, W, X)> :
    impl::function_wrapper<R, Array<C&, U, V, W, X>, true_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

template<typename R, typename C, typename U, typename V, typename W, typename X>
struct TYPE_HIDDEN_VISIBILITY ResolveFunctionSignatureType<R(C::*)(U, V, W, X) const> :
    impl::function_wrapper<R, Array<C const&, U, V, W, X>, true_type>
{
    METAPROGRAMMING_ONLY(ResolveFunctionSignatureType)
};

} // namespace intro

#endif
