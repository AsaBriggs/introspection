#ifndef INCLUDED_FUNCTION_APPLY
#define INCLUDED_FUNCTION_APPLY

#ifndef INCLUDED_FUNCTION_SIGNATURES
#include "function_signatures.h"
#endif

namespace intro {

namespace function_apply {

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
                                        is_a_function_wrapper<Func> >,
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
        return func();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0) const
    {
        return func(p0);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        return func(p0, p1);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2) const
    {
        return func(p0, p1, p2);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3) const
    {
        return func(p0, p1, p2, p3);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4) const
    {
        return func(p0, p1, p2, p3, p4);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5) const
    {
        return func(p0, p1, p2, p3, p4, p5);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6) const
    {
        return func(p0, p1, p2, p3, p4, p5, p6);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7) const
    {
        return func(p0, p1, p2, p3, p4, p5, p6, p7);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7,
               typename lookup<8>::type p8) const
    {
        return func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
    }
};

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY ApplyObj<Func,
                typename enable_if<and_<is_same<void, typename GetCodomainType<Func>::type>,
                                        not_<is_a_function_wrapper<Func> > >,
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
        func();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0) const
    {
        func(p0);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        func(p0, p1);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2) const
    {
        func(p0, p1, p2);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3) const
    {
        func(p0, p1, p2, p3);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4) const
    {
        func(p0, p1, p2, p3, p4);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5) const
    {
        func(p0, p1, p2, p3, p4, p5);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6) const
    {
        func(p0, p1, p2, p3, p4, p5, p6);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7) const
    {
        func(p0, p1, p2, p3, p4, p5, p6, p7);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7,
               typename lookup<8>::type p8) const
    {
        func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
    }
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
        return (*func)();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0) const
    {
        return (*func)(p0);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        return (*func)(p0, p1);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2) const
    {
        return (*func)(p0, p1, p2);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3) const
    {
        return (*func)(p0, p1, p2, p3);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4) const
    {
        return (*func)(p0, p1, p2, p3, p4);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5) const
    {
        return (*func)(p0, p1, p2, p3, p4, p5);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6) const
    {
        return (*func)(p0, p1, p2, p3, p4, p5, p6);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7) const
    {
        return (*func)(p0, p1, p2, p3, p4, p5, p6, p7);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7,
               typename lookup<8>::type p8) const
    {
        return (*func)(p0, p1, p2, p3, p4, p5, p6, p7, p8);
    }
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
        (*func)();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0) const
    {
        (*func)(p0);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        (*func)(p0, p1);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2) const
    {
        (*func)(p0, p1, p2);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3) const
    {
        (*func)(p0, p1, p2, p3);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4) const
    {
        (*func)(p0, p1, p2, p3, p4);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5) const
    {
        (*func)(p0, p1, p2, p3, p4, p5);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6) const
    {
        (*func)(p0, p1, p2, p3, p4, p5, p6);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7) const
    {
        (*func)(p0, p1, p2, p3, p4, p5, p6, p7);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7,
               typename lookup<8>::type p8) const
    {
        (*func)(p0, p1, p2, p3, p4, p5, p6, p7, p8);
    }
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
        return (p0->*func)();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        return (p0->*func)(p1);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2) const
    {
        return (p0->*func)(p1, p2);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3) const
    {
        return (p0->*func)(p1, p2, p3);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4) const
    {
        return (p0->*func)(p1, p2, p3, p4);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5) const
    {
        return (p0->*func)(p1, p2, p3, p4, p5);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6) const
    {
        return (p0->*func)(p1, p2, p3, p4, p5, p6);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7) const
    {
        return (p0->*func)(p1, p2, p3, p4, p5, p6, p7);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7,
               typename lookup<8>::type p8) const
    {
        return (p0->*func)(p1, p2, p3, p4, p5, p6, p7, p8);
    }
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
        (p0->*func)();
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1) const
    {
        (p0->*func)(p1);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2) const
    {
        (p0->*func)(p1, p2);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3) const
    {
        (p0->*func)(p1, p2, p3);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4) const
    {
        (p0->*func)(p1, p2, p3, p4);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5) const
    {
        (p0->*func)(p1, p2, p3, p4, p5);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6) const
    {
        (p0->*func)(p1, p2, p3, p4, p5, p6);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7) const
    {
        (p0->*func)(p1, p2, p3, p4, p5, p6, p7);
    }

    ALWAYS_INLINE_HIDDEN codomain_type
    operator()(typename Spec::Func func,
               typename lookup<0>::type p0,
               typename lookup<1>::type p1,
               typename lookup<2>::type p2,
               typename lookup<3>::type p3,
               typename lookup<4>::type p4,
               typename lookup<5>::type p5,
               typename lookup<6>::type p6,
               typename lookup<7>::type p7,
               typename lookup<8>::type p8) const
    {
        (p0->*func)(p1, p2, p3, p4, p5, p6, p7, p8);
    }
};

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
                   is_same<void, typename GetCodomainType<Func>::type > >,
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

} // namespace intro

#endif


