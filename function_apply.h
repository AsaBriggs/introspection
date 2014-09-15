#ifndef INCLUDED_FUNCTION_APPLY
#define INCLUDED_FUNCTION_APPLY

#ifndef INCLUDED_FUNCTION_SIGNATURES
#include "function_signatures.h"
#endif

namespace intro {

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

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : ArrayIndex<FuncInputs, Integer<N> > {METAPROGRAMMING_ONLY(lookup)};

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

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : ArrayIndex<FuncInputs, Integer<N> > {METAPROGRAMMING_ONLY(lookup)};

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

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : ArrayIndex<InputTypes, Integer<N> > {METAPROGRAMMING_ONLY(lookup)};

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

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : ArrayIndex<InputTypes, Integer<N> > {};

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

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : ArrayIndex<InputTypes, Integer<N> > {};

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

    template<int N> struct TYPE_HIDDEN_VISIBILITY lookup : ArrayIndex<InputTypes, Integer<N> > {};

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
template<typename Fun>
struct TYPE_HIDDEN_VISIBILITY GetApplyObj : ApplyObj<typename ResolveFunctionSignatureType<Fun>::type>
{
    METAPROGRAMMING_ONLY(GetApplyObj)
};


template<typename Func>
ALWAYS_INLINE_HIDDEN
typename disable_if<is_same<void ,typename GetCodomainType<typename GetApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename GetApplyObj<Func>::type>::type >::type
apply(Func func)
{
    return typename GetApplyObj<Func>::type()(func);
}

template<typename Func>
ALWAYS_INLINE_HIDDEN
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func)
{
    typename GetApplyObj<Func>::type()(func);
}


template<typename Func, typename P0>
ALWAYS_INLINE_HIDDEN
typename disable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename ApplyObj<Func>::type>::type >::type
apply(Func func, P0 p0)
{
    return typename GetApplyObj<Func>::type()(func, p0);
}

template<typename Func, typename P0>
ALWAYS_INLINE_HIDDEN
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func, P0 p0)
{
    typename GetApplyObj<Func>::type()(func, p0);
}


template<typename Func, typename P0, typename P1>
ALWAYS_INLINE_HIDDEN
typename disable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename ApplyObj<Func>::type>::type >::type
apply(Func func, P0 p0, P1 p1)
{
    return typename GetApplyObj<Func>::type()(func, p0, p1);
}

template<typename Func, typename P0, typename P1>
ALWAYS_INLINE_HIDDEN
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func, P0 p0, P1 p1)
{
    typename GetApplyObj<Func>::type()(func, p0, p1);
}


template<typename Func, typename P0, typename P1, typename P2>
ALWAYS_INLINE_HIDDEN
typename disable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename ApplyObj<Func>::type>::type >::type
apply(Func func, P0 p0, P1 p1, P2 p2)
{
  return typename GetApplyObj<Func>::type()(func, p0, p1, p2);
}

template<typename Func, typename P0, typename P1, typename P2>
ALWAYS_INLINE_HIDDEN
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func, P0 p0, P1 p1, P2 p2)
{
    typename GetApplyObj<Func>::type()(func, p0, p1, p2);
}


template<typename Func, typename P0, typename P1, typename P2, typename P3>
ALWAYS_INLINE_HIDDEN
typename disable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename ApplyObj<Func>::type>::type >::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3)
{
    return typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3);
}

template<typename Func, typename P0, typename P1, typename P2, typename P3>
ALWAYS_INLINE_HIDDEN
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3)
{
    typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3);
}


template<typename Func, typename P0, typename P1, typename P2, typename P3, typename P4>
ALWAYS_INLINE_HIDDEN
typename disable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename ApplyObj<Func>::type>::type >::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4)
{
    return typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4);
}

template<typename Func, typename P0, typename P1, typename P2, typename P3, typename P4>
ALWAYS_INLINE_HIDDEN
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4)
{
    typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4);
}


template<typename Func, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
ALWAYS_INLINE_HIDDEN
typename disable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename ApplyObj<Func>::type>::type >::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
{
    return typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5);
}

template<typename Func, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
ALWAYS_INLINE_HIDDEN
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
{
    typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5);
}


template<typename Func, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
ALWAYS_INLINE_HIDDEN
typename disable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename ApplyObj<Func>::type>::type >::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
{
    return typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6);
}

template<typename Func, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
ALWAYS_INLINE_HIDDEN
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
{
    typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6);
}


template<typename Func, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
ALWAYS_INLINE_HIDDEN
typename disable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename ApplyObj<Func>::type>::type >::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
{
    return typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6, p7);
}

template<typename Func, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
ALWAYS_INLINE_HIDDEN
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7)
{
    typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6, p7);
}


template<typename Func, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
ALWAYS_INLINE_HIDDEN
typename disable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename ApplyObj<Func>::type>::type >::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
{
    return typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

template<typename Func, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
ALWAYS_INLINE_HIDDEN
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func, P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8)
{
    typename GetApplyObj<Func>::type()(func, p0, p1, p2, p3, p4, p5, p6, p7, p8);
}


} // namespace intro

#endif


