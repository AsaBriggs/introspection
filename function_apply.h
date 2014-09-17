#ifndef INCLUDED_FUNCTION_APPLY
#define INCLUDED_FUNCTION_APPLY

#ifndef INCLUDED_FUNCTION_SIGNATURES
#include "function_signatures.h"
#endif

#ifndef INCLUDED_INTROSPECTION_ASSERT
#include "introspection_assert.h"
#endif

#ifndef INCLUDED_METAPROGRAMMING
#include "metaprogramming.h"
#endif

#ifndef INCLUDED_COMPILER_SPECIFICS
#include "compiler_specifics.h"
#endif

namespace intro {

namespace function_apply {

template<typename Func, typename Index>
struct TYPE_HIDDEN_VISIBILITY GetParam :
    parameter_type<typename ArrayIndex<typename GetInputTypeArray<Func>::type, Index>::type>
{
    METAPROGRAMMING_ONLY(GetParam)
};

template<typename Func, typename Enable=void>
struct TYPE_HIDDEN_VISIBILITY ApplyObj;

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY ApplyObj<Func,
                typename disable_if<or_<is_same<void, typename GetCodomainType<Func>::type>,
                                        function_pointer_specialisations::is_a_function_wrapper<Func> >,
                                    void>::type>
{
    typedef ApplyObj type;
    typedef true_type IntrospectionEnabled;
    typedef typename GetCodomainType<Func>::type codomain_type;
    typedef typename GetInputTypeArray<Func>::type FuncInputs;
    typedef typename ArrayConcat<Array<Func>, FuncInputs>::type input_types;

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : GetParam<Func, Integer<N> > {METAPROGRAMMING_ONLY(lookup)};

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<1>, typename ArraySize<input_types>::type> ));
        return func();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<2>, typename ArraySize<input_types>::type> ));
        return func(p0);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<3>, typename ArraySize<input_types>::type> ));
        return func(p0, p1);
    }

// Could not use a macro for 2 parameter function call as the , would not work out
// on member function pointers.
#define FUNCTION_CALL_3_9(FuncType, FunctionCall, ReturnStatement) \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(FuncType func, \
               typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2) const \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<4>, typename ArraySize<input_types>::type> )); \
        ReturnStatement() FunctionCall() p1, p2); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(FuncType func, \
               typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3) const \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<5>, typename ArraySize<input_types>::type> )); \
        ReturnStatement() FunctionCall() p1, p2, p3); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(FuncType func, \
               typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3, \
               typename lookup<4>::type p4) const \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<6>, typename ArraySize<input_types>::type> )); \
        ReturnStatement() FunctionCall() p1, p2, p3, p4); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(FuncType func, \
               typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3, \
               typename lookup<4>::type p4, \
               typename lookup<5>::type p5) const \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<7>, typename ArraySize<input_types>::type> )); \
        ReturnStatement() FunctionCall() p1, p2, p3, p4, p5); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(FuncType func, \
               typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3, \
               typename lookup<4>::type p4, \
               typename lookup<5>::type p5, \
               typename lookup<6>::type p6) const \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<8>, typename ArraySize<input_types>::type> )); \
        ReturnStatement() FunctionCall() p1, p2, p3, p4, p5, p6); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(FuncType func, \
               typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3, \
               typename lookup<4>::type p4, \
               typename lookup<5>::type p5, \
               typename lookup<6>::type p6, \
               typename lookup<7>::type p7) const \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename ArraySize<input_types>::type> )); \
        ReturnStatement() FunctionCall() p1, p2, p3, p4, p5, p6, p7); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(FuncType func, \
               typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3, \
               typename lookup<4>::type p4, \
               typename lookup<5>::type p5, \
               typename lookup<6>::type p6, \
               typename lookup<7>::type p7, \
               typename lookup<8>::type p8) const \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<input_types>::type> )); \
        ReturnStatement() FunctionCall() p1, p2, p3, p4, p5, p6, p7, p8); \
    }

#define FUNCTION_CALL_MACRO() func(p0,
#define RETURN_MACRO() return
FUNCTION_CALL_3_9(Func, FUNCTION_CALL_MACRO, RETURN_MACRO)
#undef FUNCTION_CALL_MACRO
#undef RETURN_MACRO
};

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY ApplyObj<Func,
                typename enable_if<and_<is_same<void, typename GetCodomainType<Func>::type>,
                                        not_<function_pointer_specialisations::is_a_function_wrapper<Func> > >,
                                   void>::type>
{
    typedef ApplyObj type;
    typedef true_type IntrospectionEnabled;
    typedef void codomain_type;
    typedef typename GetInputTypeArray<Func>::type FuncInputs;
    typedef typename ArrayConcat<Array<Func>, FuncInputs>::type input_types;

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : GetParam<Func, Integer<N> > {METAPROGRAMMING_ONLY(lookup)};

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<1>, typename ArraySize<input_types>::type> ));
        func();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<2>, typename ArraySize<input_types>::type> ));
        func(p0);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<3>, typename ArraySize<input_types>::type> ));
        func(p0, p1);
    }

#define FUNCTION_CALL_MACRO() func(p0,
#define RETURN_MACRO()
FUNCTION_CALL_3_9(Func, FUNCTION_CALL_MACRO, RETURN_MACRO)
#undef FUNCTION_CALL_MACRO
#undef RETURN_MACRO

};

template<typename CodomainType, typename InputTypes>
struct TYPE_HIDDEN_VISIBILITY ApplyObj<function_pointer_specialisations::function_wrapper<CodomainType, InputTypes, false_type> >
{
    typedef function_pointer_specialisations::function_wrapper<CodomainType, InputTypes, false_type> Spec;
    typedef ApplyObj type;
    typedef true_type IntrospectionEnabled;
    typedef CodomainType codomain_type;
    typedef typename ArrayConcat<Array<typename Spec::Func>, InputTypes>::type input_types;

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : GetParam<Spec, Integer<N> > {METAPROGRAMMING_ONLY(lookup)};

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<1>, typename ArraySize<input_types>::type> ));
        return (*func)();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<2>, typename ArraySize<input_types>::type> ));
        return (*func)(p0);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<3>, typename ArraySize<input_types>::type> ));
        return (*func)(p0, p1);
    }

#define FUNCTION_CALL_MACRO() (*func)(p0, 
#define RETURN_MACRO() return
FUNCTION_CALL_3_9(typename Spec::Func, FUNCTION_CALL_MACRO, RETURN_MACRO)
#undef FUNCTION_CALL_MACRO
#undef RETURN_MACRO

};

template<typename InputTypes>
struct TYPE_HIDDEN_VISIBILITY ApplyObj<function_pointer_specialisations::function_wrapper<void, InputTypes, false_type> >
{
    typedef function_pointer_specialisations::function_wrapper<void, InputTypes, false_type> Spec;
    typedef ApplyObj type;
    typedef true_type IntrospectionEnabled;
    typedef void codomain_type;
    typedef typename ArrayConcat<Array<typename Spec::Func>, InputTypes>::type input_types;

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : GetParam<Spec, Integer<N> > {METAPROGRAMMING_ONLY(lookup)};

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<1>, typename ArraySize<input_types>::type> ));
        (*func)();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<2>, typename ArraySize<input_types>::type> ));
        (*func)(p0);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<3>, typename ArraySize<input_types>::type> ));
        (*func)(p0, p1);
    }

#define FUNCTION_CALL_MACRO() (*func)(p0, 
#define RETURN_MACRO()
FUNCTION_CALL_3_9(typename Spec::Func, FUNCTION_CALL_MACRO, RETURN_MACRO)
#undef FUNCTION_CALL_MACRO
#undef RETURN_MACRO

};

template<typename CodomainType, typename InputTypes>
struct TYPE_HIDDEN_VISIBILITY ApplyObj<function_pointer_specialisations::function_wrapper<CodomainType, InputTypes, true_type> >
{
    typedef function_pointer_specialisations::function_wrapper<CodomainType, InputTypes, true_type> Spec;
    typedef ApplyObj type;
    typedef true_type IntrospectionEnabled;
    typedef CodomainType codomain_type;
    typedef typename ArrayConcat<Array<typename Spec::Func>, InputTypes>::type input_types;

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : GetParam<Spec, Integer<N> > {METAPROGRAMMING_ONLY(lookup)};

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<2>, typename ArraySize<input_types>::type> ));
        return (p0->*func)();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<3>, typename ArraySize<input_types>::type> ));
        return (p0->*func)(p1);
    }

#define FUNCTION_CALL_MACRO() (p0->*func)(
#define RETURN_MACRO() return
FUNCTION_CALL_3_9(typename Spec::Func, FUNCTION_CALL_MACRO, RETURN_MACRO)
#undef FUNCTION_CALL_MACRO
#undef RETURN_MACRO

};


template<typename InputTypes>
struct TYPE_HIDDEN_VISIBILITY ApplyObj<function_pointer_specialisations::function_wrapper<void, InputTypes, true_type> >
{
    typedef function_pointer_specialisations::function_wrapper<void, InputTypes, true_type> Spec;
    typedef ApplyObj type;
    typedef true_type IntrospectionEnabled;
    typedef void codomain_type;
    typedef typename ArrayConcat<Array<typename Spec::Func>, InputTypes>::type input_types;

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : GetParam<Spec, Integer<N> > {METAPROGRAMMING_ONLY(lookup)};

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<2>, typename ArraySize<input_types>::type> ));
        (p0->*func)();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<3>, typename ArraySize<input_types>::type> ));
        (p0->*func)(p1);
    }

#define FUNCTION_CALL_MACRO() (p0->*func)(
#define RETURN_MACRO() 
FUNCTION_CALL_3_9(typename Spec::Func, FUNCTION_CALL_MACRO, RETURN_MACRO)
#undef FUNCTION_CALL_MACRO
#undef RETURN_MACRO

};

#undef FUNCTION_CALL_3_9

// Helper metafunction
template<typename Func>
struct TYPE_HIDDEN_VISIBILITY GetApplyObj : ApplyObj<typename ResolveFunctionSignatureType<Func>::type>
{
    METAPROGRAMMING_ONLY(GetApplyObj)
};

// General pattern is to enable on a given arity and void/non-void return
template<typename Func, typename Arity>
struct TYPE_HIDDEN_VISIBILITY EnableApplyIfVoid :
    enable_if<and_<is_same<Arity, typename GetFunctionArity<Func>::type>,
                   is_same<void, typename GetCodomainType<Func>::type> >,
              void>
{
    METAPROGRAMMING_ONLY(EnableApplyIfVoid)
};

template<typename Func, typename Arity>
struct TYPE_HIDDEN_VISIBILITY EnableApplyIfNotVoid :
    enable_if<and_<is_same<Arity, typename GetFunctionArity<Func>::type>,
                   not_<is_same<void, typename GetCodomainType<Func>::type> > >,
             typename GetCodomainType<Func>::type>
{
    METAPROGRAMMING_ONLY(EnableApplyIfNotVoid)
};

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY IsFunctionPointer_impl : false_type {METAPROGRAMMING_ONLY(IsFunctionPointer_impl)};

template<typename CodomainType, typename InputType>
struct TYPE_HIDDEN_VISIBILITY IsFunctionPointer_impl<function_pointer_specialisations::function_wrapper<CodomainType, InputType, false_type> > : true_type {METAPROGRAMMING_ONLY(IsFunctionPointer_impl)};

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY IsFunctionPointer : IsFunctionPointer_impl<typename ResolveFunctionSignatureType<Func>::type> {METAPROGRAMMING_ONLY(IsFunctionPointer)};


template<typename Func>
struct TYPE_HIDDEN_VISIBILITY IsMemberFunctionPointer_impl : false_type {METAPROGRAMMING_ONLY(IsMemberFunctionPointer_impl)};

template<typename CodomainType, typename InputType>
struct TYPE_HIDDEN_VISIBILITY IsMemberFunctionPointer_impl<function_pointer_specialisations::function_wrapper<CodomainType, InputType, true_type> > : true_type {METAPROGRAMMING_ONLY(IsMemberFunctionPointer_impl)};

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY IsMemberFunctionPointer : IsMemberFunctionPointer_impl<typename ResolveFunctionSignatureType<Func>::type> {METAPROGRAMMING_ONLY(IsMemberFunctionPointer)};


template<typename Func>
struct TYPE_HIDDEN_VISIBILITY EnableApplyIfArity10VoidFunctionPointer :
    enable_if<and_<is_same<Integer<10>, typename GetFunctionArity<Func>::type>,
                   is_same<void, typename GetCodomainType<Func>::type>,
                   IsFunctionPointer<Func> >,
              void>
{
    METAPROGRAMMING_ONLY(EnableApplyIfArity10VoidFunctionPointer)
};

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY EnableApplyIfArity10NonVoidFunctionPointer :
    enable_if<and_<is_same<Integer<10>, typename GetFunctionArity<Func>::type>,
                   not_<is_same<void, typename GetCodomainType<Func>::type> >,
                   IsFunctionPointer<Func> >,
              typename GetCodomainType<Func>::type>
{
    METAPROGRAMMING_ONLY(EnableApplyIfArity10NonVoidFunctionPointer)
};

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY EnableApplyIfArity10VoidMemberFunctionPointer :
    enable_if<and_<is_same<Integer<10>, typename GetFunctionArity<Func>::type>,
                   is_same<void, typename GetCodomainType<Func>::type>,
                   IsMemberFunctionPointer<Func> >,
              void>
{
    METAPROGRAMMING_ONLY(EnableApplyIfArity10VoidMemberFunctionPointer)
};

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY EnableApplyIfArity10NonVoidMemberFunctionPointer :
    enable_if<and_<is_same<Integer<10>, typename GetFunctionArity<Func>::type>,
                   not_<is_same<void, typename GetCodomainType<Func>::type> >,
                   IsMemberFunctionPointer<Func> >,
              typename GetCodomainType<Func>::type>
{
    METAPROGRAMMING_ONLY(EnableApplyIfArity10NonVoidMemberFunctionPointer)
};

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY EnableApplyIfArity10VoidFunctor :
    enable_if<and_<is_same<Integer<10>, typename GetFunctionArity<Func>::type>,
                   is_same<void, typename GetCodomainType<Func>::type>,
                   and_<not_<IsFunctionPointer<Func> >,
                        not_<IsMemberFunctionPointer<Func> > > >,
              void>
{
    METAPROGRAMMING_ONLY(EnableApplyIfArity10VoidFunctor)
};

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY EnableApplyIfArity10NonVoidFunctor :
    enable_if<and_<is_same<Integer<10>, typename GetFunctionArity<Func>::type>,
                   not_<is_same<void, typename GetCodomainType<Func>::type> >,
                   and_<not_<IsFunctionPointer<Func> >,
                        not_<IsMemberFunctionPointer<Func> > > >,
              typename GetCodomainType<Func>::type>
{
    METAPROGRAMMING_ONLY(EnableApplyIfArity10NonVoidFunctor)
};


} // namespace function_apply


template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfNotVoid<Func, Integer<0> >::type
apply(Func func)
{
    return typename function_apply::GetApplyObj<Func>::type()(func);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfVoid<Func, Integer<0> >::type
apply(Func func)
{
    typename function_apply::GetApplyObj<Func>::type()(func);
}


template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfNotVoid<Func, Integer<1> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0)
{
    return typename function_apply::GetApplyObj<Func>::type()(func, p0);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfVoid<Func, Integer<1> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0)
{
    typename function_apply::GetApplyObj<Func>::type()(func, p0);
}


template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfNotVoid<Func, Integer<2> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1)
{
    return typename function_apply::GetApplyObj<Func>::type()(func, p0, p1);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfVoid<Func, Integer<2> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1)
{
    typename function_apply::GetApplyObj<Func>::type()(func, p0, p1);
}


template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfNotVoid<Func, Integer<3> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2)
{
    return typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfVoid<Func, Integer<3> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2)
{
    typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfNotVoid<Func, Integer<4> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3)
{
    return typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfVoid<Func, Integer<4> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3)
{
    typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfNotVoid<Func, Integer<5> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4)
{
    return typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfVoid<Func, Integer<5> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4)
{
    typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4);
}


template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfNotVoid<Func, Integer<6> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5)
{
    return typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfVoid<Func, Integer<6> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5)
{
    typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5);
}


template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfNotVoid<Func, Integer<7> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6)
{
    return typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfVoid<Func, Integer<7> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6)
{
    typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6);
}


template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfNotVoid<Func, Integer<8> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6,
      typename function_apply::GetParam<Func, Integer<7> >::type p7)
{
    return typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6, p7);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfVoid<Func, Integer<8> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6,
      typename function_apply::GetParam<Func, Integer<7> >::type p7)
{
    typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6, p7);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfNotVoid<Func, Integer<9> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6,
      typename function_apply::GetParam<Func, Integer<7> >::type p7,
      typename function_apply::GetParam<Func, Integer<8> >::type p8)
{
    return typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfVoid<Func, Integer<9> >::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6,
      typename function_apply::GetParam<Func, Integer<7> >::type p7,
      typename function_apply::GetParam<Func, Integer<8> >::type p8)
{
    typename function_apply::GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

// Warning :- the following apply were added as a hack and a bodge to increase the range of function_curry
// Using the Apply object scheme limits the Arity of functions to be 10 - #objects to create the function call
// = 8 for member function pointers, 9 for function pointers and for functors.
template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfArity10NonVoidFunctionPointer<Func>::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6,
      typename function_apply::GetParam<Func, Integer<7> >::type p7,
      typename function_apply::GetParam<Func, Integer<8> >::type p8,
      typename function_apply::GetParam<Func, Integer<9> >::type p9)
{
    return (*func)(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfArity10VoidFunctionPointer<Func>::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6,
      typename function_apply::GetParam<Func, Integer<7> >::type p7,
      typename function_apply::GetParam<Func, Integer<8> >::type p8,
      typename function_apply::GetParam<Func, Integer<9> >::type p9)
{
    (*func)(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfArity10NonVoidMemberFunctionPointer<Func>::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6,
      typename function_apply::GetParam<Func, Integer<7> >::type p7,
      typename function_apply::GetParam<Func, Integer<8> >::type p8,
      typename function_apply::GetParam<Func, Integer<9> >::type p9)
{
    return (p0->*func)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfArity10VoidMemberFunctionPointer<Func>::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6,
      typename function_apply::GetParam<Func, Integer<7> >::type p7,
      typename function_apply::GetParam<Func, Integer<8> >::type p8,
      typename function_apply::GetParam<Func, Integer<9> >::type p9)
{
    (p0->*func)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfArity10NonVoidFunctor<Func>::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6,
      typename function_apply::GetParam<Func, Integer<7> >::type p7,
      typename function_apply::GetParam<Func, Integer<8> >::type p8,
      typename function_apply::GetParam<Func, Integer<9> >::type p9)
{
    return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename function_apply::EnableApplyIfArity10VoidFunctor<Func>::type
apply(Func func,
      typename function_apply::GetParam<Func, Integer<0> >::type p0,
      typename function_apply::GetParam<Func, Integer<1> >::type p1,
      typename function_apply::GetParam<Func, Integer<2> >::type p2,
      typename function_apply::GetParam<Func, Integer<3> >::type p3,
      typename function_apply::GetParam<Func, Integer<4> >::type p4,
      typename function_apply::GetParam<Func, Integer<5> >::type p5,
      typename function_apply::GetParam<Func, Integer<6> >::type p6,
      typename function_apply::GetParam<Func, Integer<7> >::type p7,
      typename function_apply::GetParam<Func, Integer<8> >::type p8,
      typename function_apply::GetParam<Func, Integer<9> >::type p9)
{
    func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

} // namespace intro

#endif


