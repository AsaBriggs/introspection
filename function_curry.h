#ifndef INCLUDED_FUNCTION_CURRY
#define INCLUDED_FUNCTION_CURRY

#ifndef INCLUDED_FUNCTION_APPLY
#include "function_apply.h"
#endif

#ifndef INCLUDED_INTROSPECTION_ASSERT
#include "introspection_assert.h"
#endif

namespace intro {

// Takes a function object of arity N and turns is into a function object of arity N-1
// May want to bind the function or one of the parameters...
//

namespace Curry_impl {

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY enable_if_void_codomain : enable_if<is_same<void, typename GetCodomainType<Func>::type>, void> {METAPROGRAMMING_ONLY(enable_if_void_codomain)};

template<typename Func>
struct TYPE_HIDDEN_VISIBILITY enable_if_not_void_codomain : enable_if<not_<is_same<void, typename GetCodomainType<Func>::type> >, void> {METAPROGRAMMING_ONLY(enable_if_not_void_codomain)};

template<typename T, typename Index>
struct GetParamFromArray : parameter_type<typename ArrayIndex<T, Index>::type>{METAPROGRAMMING_ONLY(GetParamFromArray)};

} // namespace Curry_impl

template<typename Func, typename P, typename Index, typename Enable=void>
struct Curry;

#define RETURN_STATEMENT() return
#define ENABLE_NOT_VOID_MF() Curry_impl::enable_if_not_void_codomain

#define NO_RETURN_STATEMENT()
#define ENABLE_VOID_MF() Curry_impl::enable_if_void_codomain

#define GENERATE_BIND_0(ReturnStatement, EnableMetafunction) \
template<typename Func, typename P> \
struct Curry<Func, P, Integer<0>, typename EnableMetafunction() <Func>::type> \
{ \
    typedef Curry type; \
    typedef true_type IntrospectionEnabled; \
    typedef Array<Func, P> IntrospectionItems;   \
 \
    typedef typename GetCodomainType<Func>::type codomain_type; \
    typedef typename ArrayEraseIndex<typename GetInputTypeArray<Func>::type, Integer<0> >::type input_types; \
    Func m0; \
    P m1; \
 \
    template<IntegerValueType N> struct TYPE_HIDDEN_VISIBILITY lookup : Curry_impl::GetParamFromArray<input_types, Integer<N> > {METAPROGRAMMING_ONLY(lookup)}; \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()() \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<1>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(m1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<2>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(m1, p0); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<3>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(m1, p0, p1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<4>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(m1, p0, p1, p2); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<5>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(m1, p0, p1, p2, p3); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<6>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(m1, p0, p1, p2, p3, p4); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<7>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(m1, p0, p1, p2, p3, p4, p5); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<8>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(m1, p0, p1, p2, p3, p4, p5, p6); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(m1, p0, p1, p2, p3, p4, p5, p6, p7); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7, \
	       typename lookup<8>::type p8) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(m1, p0, p1, p2, p3, p4, p5, p6, p7, p8); \
    } \
};

GENERATE_BIND_0(RETURN_STATEMENT, ENABLE_NOT_VOID_MF)
GENERATE_BIND_0(NO_RETURN_STATEMENT, ENABLE_VOID_MF)
#undef GENERATE_BIND_0


#define GENERATE_BIND_1(ReturnStatement, EnableMetafunction) \
template<typename Func, typename P> \
struct Curry<Func, P, Integer<1>, typename EnableMetafunction() <Func>::type> \
{ \
    typedef Curry type; \
    typedef true_type IntrospectionEnabled; \
    typedef Array<Func, P> IntrospectionItems; \
 \
    typedef typename GetCodomainType<Func>::type codomain_type; \
    typedef typename ArrayEraseIndex<typename GetInputTypeArray<Func>::type, Integer<1> >::type input_types; \
    Func m0; \
    P m1; \
 \
    template<IntegerValueType N> struct TYPE_HIDDEN_VISIBILITY lookup : Curry_impl::GetParamFromArray<input_types, Integer<N> > {METAPROGRAMMING_ONLY(lookup)}; \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<2>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, m1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<3>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, m1, p1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<4>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, m1, p1, p2); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<5>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, m1, p1, p2, p3); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<6>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, m1, p1, p2, p3, p4); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<7>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, m1, p1, p2, p3, p4, p5); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<8>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, m1, p1, p2, p3, p4, p5, p6); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, m1, p1, p2, p3, p4, p5, p6, p7); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7, \
	       typename lookup<8>::type p8) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, m1, p1, p2, p3, p4, p5, p6, p7, p8); \
    } \
};

GENERATE_BIND_1(RETURN_STATEMENT, ENABLE_NOT_VOID_MF)
GENERATE_BIND_1(NO_RETURN_STATEMENT, ENABLE_VOID_MF)
#undef GENERATE_BIND_1


#define GENERATE_BIND_2(ReturnStatement, EnableMetafunction) \
template<typename Func, typename P> \
struct Curry<Func, P, Integer<2>, typename EnableMetafunction() <Func>::type> \
{ \
    typedef Curry type; \
    typedef true_type IntrospectionEnabled; \
    typedef Array<Func, P> IntrospectionItems; \
 \
    typedef typename GetCodomainType<Func>::type codomain_type; \
    typedef typename ArrayEraseIndex<typename GetInputTypeArray<Func>::type, Integer<2> >::type input_types; \
    Func m0; \
    P m1; \
 \
    template<IntegerValueType N> struct TYPE_HIDDEN_VISIBILITY lookup : Curry_impl::GetParamFromArray<input_types, Integer<N> > {METAPROGRAMMING_ONLY(lookup)}; \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<3>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, m1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<4>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, m1, p2); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<5>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, m1, p2, p3); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<6>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, m1, p2, p3, p4); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<7>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, m1, p2, p3, p4, p5); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<8>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, m1, p2, p3, p4, p5, p6); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, m1, p2, p3, p4, p5, p6, p7); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7, \
	       typename lookup<8>::type p8) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, m1, p2, p3, p4, p5, p6, p7, p8); \
    } \
};

GENERATE_BIND_2(RETURN_STATEMENT, ENABLE_NOT_VOID_MF)
GENERATE_BIND_2(NO_RETURN_STATEMENT, ENABLE_VOID_MF)
#undef GENERATE_BIND_2


#define GENERATE_BIND_3(ReturnStatement, EnableMetafunction) \
template<typename Func, typename P> \
struct Curry<Func, P, Integer<3>, typename EnableMetafunction() <Func>::type> \
{ \
    typedef Curry type; \
    typedef true_type IntrospectionEnabled; \
    typedef Array<Func, P> IntrospectionItems; \
 \
    typedef typename GetCodomainType<Func>::type codomain_type; \
    typedef typename ArrayEraseIndex<typename GetInputTypeArray<Func>::type, Integer<3> >::type input_types; \
    Func m0; \
    P m1; \
 \
    template<IntegerValueType N> struct TYPE_HIDDEN_VISIBILITY lookup : Curry_impl::GetParamFromArray<input_types, Integer<N> > {METAPROGRAMMING_ONLY(lookup)}; \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<4>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, m1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<5>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, m1, p3); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<6>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, m1, p3, p4); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<7>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, m1, p3, p4, p5); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<8>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, m1, p3, p4, p5, p6); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, m1, p3, p4, p5, p6, p7); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7, \
	       typename lookup<8>::type p8) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, m1, p3, p4, p5, p6, p7, p8); \
    } \
};

GENERATE_BIND_3(RETURN_STATEMENT, ENABLE_NOT_VOID_MF)
GENERATE_BIND_3(NO_RETURN_STATEMENT, ENABLE_VOID_MF)
#undef GENERATE_BIND_3


#define GENERATE_BIND_4(ReturnStatement, EnableMetafunction) \
template<typename Func, typename P> \
struct Curry<Func, P, Integer<4>, typename EnableMetafunction() <Func>::type> \
{ \
    typedef Curry type; \
    typedef true_type IntrospectionEnabled; \
    typedef Array<Func, P> IntrospectionItems; \
 \
    typedef typename GetCodomainType<Func>::type codomain_type; \
    typedef typename ArrayEraseIndex<typename GetInputTypeArray<Func>::type, Integer<4> >::type input_types; \
    Func m0; \
    P m1; \
 \
    template<IntegerValueType N> struct TYPE_HIDDEN_VISIBILITY lookup : Curry_impl::GetParamFromArray<input_types, Integer<N> > {METAPROGRAMMING_ONLY(lookup)}; \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<5>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, m1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<6>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, m1, p4); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<7>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, m1, p4, p5); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<2>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<8>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, m1, p4, p5, p6); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, m1, p4, p5, p6, p7); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7, \
	       typename lookup<8>::type p8) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, m1, p4, p5, p6, p7, p8); \
    } \
};

GENERATE_BIND_4(RETURN_STATEMENT, ENABLE_NOT_VOID_MF)
GENERATE_BIND_4(NO_RETURN_STATEMENT, ENABLE_VOID_MF)
#undef GENERATE_BIND_4


#define GENERATE_BIND_5(ReturnStatement, EnableMetafunction) \
template<typename Func, typename P> \
struct Curry<Func, P, Integer<5>, typename EnableMetafunction() <Func>::type> \
{ \
    typedef Curry type; \
    typedef true_type IntrospectionEnabled; \
    typedef Array<Func, P> IntrospectionItems; \
 \
    typedef typename GetCodomainType<Func>::type codomain_type; \
    typedef typename ArrayEraseIndex<typename GetInputTypeArray<Func>::type, Integer<5> >::type input_types; \
    Func m0; \
    P m1; \
 \
    template<IntegerValueType N> struct TYPE_HIDDEN_VISIBILITY lookup : Curry_impl::GetParamFromArray<input_types, Integer<N> > {METAPROGRAMMING_ONLY(lookup)}; \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<6>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, m1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<7>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, m1, p5); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<8>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, m1, p5, p6); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, m1, p5, p6, p7); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7, \
	       typename lookup<8>::type p8) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, m1, p5, p6, p7, p8); \
    } \
};

GENERATE_BIND_5(RETURN_STATEMENT, ENABLE_NOT_VOID_MF)
GENERATE_BIND_5(NO_RETURN_STATEMENT, ENABLE_VOID_MF)
#undef GENERATE_BIND_5


#define GENERATE_BIND_6(ReturnStatement, EnableMetafunction) \
template<typename Func, typename P> \
struct Curry<Func, P, Integer<6>, typename EnableMetafunction() <Func>::type> \
{ \
    typedef Curry type; \
    typedef true_type IntrospectionEnabled; \
    typedef Array<Func, P> IntrospectionItems; \
 \
    typedef typename GetCodomainType<Func>::type codomain_type; \
    typedef typename ArrayEraseIndex<typename GetInputTypeArray<Func>::type, Integer<6> >::type input_types; \
    Func m0; \
    P m1; \
 \
    template<IntegerValueType N> struct TYPE_HIDDEN_VISIBILITY lookup : Curry_impl::GetParamFromArray<input_types, Integer<N> > {METAPROGRAMMING_ONLY(lookup)}; \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<7>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, p5, m1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<8>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, p5, m1, p6); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, p5, m1, p6, p7); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7, \
	       typename lookup<8>::type p8) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, p5, m1, p6, p7, p8); \
    } \
};

GENERATE_BIND_6(RETURN_STATEMENT, ENABLE_NOT_VOID_MF)
GENERATE_BIND_6(NO_RETURN_STATEMENT, ENABLE_VOID_MF)
#undef GENERATE_BIND_6


#define GENERATE_BIND_7(ReturnStatement, EnableMetafunction) \
template<typename Func, typename P> \
struct Curry<Func, P, Integer<7>, typename EnableMetafunction() <Func>::type> \
{ \
    typedef Curry type; \
    typedef true_type IntrospectionEnabled; \
    typedef Array<Func, P> IntrospectionItems; \
 \
    typedef typename GetCodomainType<Func>::type codomain_type; \
    typedef typename ArrayEraseIndex<typename GetInputTypeArray<Func>::type, Integer<7> >::type input_types; \
    Func m0; \
    P m1; \
 \
    template<IntegerValueType N> struct TYPE_HIDDEN_VISIBILITY lookup : Curry_impl::GetParamFromArray<input_types, Integer<N> > {METAPROGRAMMING_ONLY(lookup)}; \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<8>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, p5, p6, m1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, p5, p6, m1, p7); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7, \
	       typename lookup<8>::type p8) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
      ReturnStatement() m0(p0, p1, p2, p3, p4, p5, p6, m1, p7, p8); \
    } \
};

GENERATE_BIND_7(RETURN_STATEMENT, ENABLE_NOT_VOID_MF)
GENERATE_BIND_7(NO_RETURN_STATEMENT, ENABLE_VOID_MF)
#undef GENERATE_BIND_7


#define GENERATE_BIND_8(ReturnStatement, EnableMetafunction) \
template<typename Func, typename P> \
struct Curry<Func, P, Integer<8>, typename EnableMetafunction() <Func>::type> \
{ \
    typedef Curry type; \
    typedef true_type IntrospectionEnabled; \
    typedef Array<Func, P> IntrospectionItems; \
 \
    typedef typename GetCodomainType<Func>::type codomain_type; \
    typedef typename ArrayEraseIndex<typename GetInputTypeArray<Func>::type, Integer<8> >::type input_types; \
    Func m0; \
    P m1; \
 \
    template<IntegerValueType N> struct TYPE_HIDDEN_VISIBILITY lookup : Curry_impl::GetParamFromArray<input_types, Integer<N> > {METAPROGRAMMING_ONLY(lookup)}; \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, p5, p6, p7, m1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7, \
	       typename lookup<8>::type p8) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, p5, p6, p7, m1, p8); \
    } \
};

GENERATE_BIND_8(RETURN_STATEMENT, ENABLE_NOT_VOID_MF)
GENERATE_BIND_8(NO_RETURN_STATEMENT, ENABLE_VOID_MF)
#undef GENERATE_BIND_8


#define GENERATE_BIND_9(ReturnStatement, EnableMetafunction) \
template<typename Func, typename P> \
struct Curry<Func, P, Integer<9>, typename EnableMetafunction() <Func>::type> \
{ \
    typedef Curry type; \
    typedef true_type IntrospectionEnabled; \
    typedef Array<Func, P> IntrospectionItems; \
 \
    typedef typename GetCodomainType<Func>::type codomain_type; \
    typedef typename ArrayEraseIndex<typename GetInputTypeArray<Func>::type, Integer<9> >::type input_types; \
    Func m0; \
    P m1; \
 \
    template<IntegerValueType N> struct TYPE_HIDDEN_VISIBILITY lookup : Curry_impl::GetParamFromArray<input_types, Integer<N> > {METAPROGRAMMING_ONLY(lookup)}; \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
	       typename lookup<1>::type p1, \
	       typename lookup<2>::type p2, \
	       typename lookup<3>::type p3, \
	       typename lookup<4>::type p4, \
	       typename lookup<5>::type p5, \
	       typename lookup<6>::type p6, \
	       typename lookup<7>::type p7, \
	       typename lookup<8>::type p8) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() m0(p0, p1, p2, p3, p4, p5, p6, p7, p8, m1); \
    } \
};

GENERATE_BIND_9(RETURN_STATEMENT, ENABLE_NOT_VOID_MF)
GENERATE_BIND_9(NO_RETURN_STATEMENT, ENABLE_VOID_MF)
#undef GENERATE_BIND_9


#define GENERATE_BIND_FUNC(ReturnStatement, EnableMetafunction) \
template<typename Func, typename Func2>						\
struct Curry<Func, Func2, Integer<-1>, typename EnableMetafunction() <Func>::type> \
{ \
    typedef Curry type; \
    typedef true_type IntrospectionEnabled; \
    typedef typename GetFunctionValueType<Func>::type FuncType;\
    typedef Array<FuncType> IntrospectionItems;	\
 \
    typedef typename GetCodomainType<Func>::type codomain_type; \
    typedef typename GetInputTypeArray<Func>::type input_types; \
    FuncType m0;							\
 \
    template<IntegerValueType N> struct TYPE_HIDDEN_VISIBILITY lookup : Curry_impl::GetParamFromArray<input_types, Integer<N> > {METAPROGRAMMING_ONLY(lookup)}; \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()() \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<0>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() apply(m0); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<1>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() apply(m0, p0); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
               typename lookup<1>::type p1) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<2>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() apply(m0, p0, p1); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<3>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() apply(m0, p0, p1, p2); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<4>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() apply(m0, p0, p1, p2, p3); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3, \
               typename lookup<4>::type p4) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<5>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() apply(m0, p0, p1, p2, p3, p4); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3, \
               typename lookup<4>::type p4, \
               typename lookup<5>::type p5) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<6>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() apply(m0, p0, p1, p2, p3, p4, p5); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3, \
               typename lookup<4>::type p4, \
               typename lookup<5>::type p5, \
               typename lookup<6>::type p6) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<7>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() apply(m0, p0, p1, p2, p3, p4, p5, p6); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3, \
               typename lookup<4>::type p4, \
               typename lookup<5>::type p5, \
               typename lookup<6>::type p6, \
               typename lookup<7>::type p7) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<8>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() apply(m0, p0, p1, p2, p3, p4, p5, p6, p7); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3, \
               typename lookup<4>::type p4, \
               typename lookup<5>::type p5, \
               typename lookup<6>::type p6, \
               typename lookup<7>::type p7, \
               typename lookup<8>::type p8) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() apply(m0, p0, p1, p2, p3, p4, p5, p6, p7, p8); \
    } \
 \
    ALWAYS_INLINE_HIDDEN codomain_type \
    operator()(typename lookup<0>::type p0, \
               typename lookup<1>::type p1, \
               typename lookup<2>::type p2, \
               typename lookup<3>::type p3, \
               typename lookup<4>::type p4, \
               typename lookup<5>::type p5, \
               typename lookup<6>::type p6, \
               typename lookup<7>::type p7, \
               typename lookup<8>::type p8, \
               typename lookup<9>::type p9) \
    { \
        INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename ArraySize<typename GetInputTypeArray<Func>::type>::type> )); \
        ReturnStatement() apply(m0, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); \
    } \
};

GENERATE_BIND_FUNC(RETURN_STATEMENT, ENABLE_NOT_VOID_MF)
GENERATE_BIND_FUNC(NO_RETURN_STATEMENT, ENABLE_VOID_MF)
#undef GENERATE_BIND_FUNC


#undef RETURN_STATEMENT
#undef NO_RETURN_STATEMENT
#undef ENABLE_NOT_VOID_MF
#undef ENABLE_VOID_MF

template<typename Func, typename Obj, typename Index>
ALWAYS_INLINE_HIDDEN Curry<typename ResolveFunctionSignatureType<Func>::type, Obj, Index>
perform_curry(Func func, Obj obj, Index)
{
    Curry<typename ResolveFunctionSignatureType<Func>::type, Obj, Index> tmp = {func, obj};
    return tmp;
}

template<typename Func>
ALWAYS_INLINE_HIDDEN Curry<typename ResolveFunctionSignatureType<Func>::type, typename ResolveFunctionSignatureType<Func>::type, Integer<-1> >
perform_curry(Func func, Integer<-1>)
{
    Curry<typename ResolveFunctionSignatureType<Func>::type, typename ResolveFunctionSignatureType<Func>::type, Integer<-1> > tmp = {func};
    return tmp;
}

template<typename Func>
ALWAYS_INLINE_HIDDEN Curry<typename ResolveFunctionSignatureType<Func>::type, typename ResolveFunctionSignatureType<Func>::type, Integer<-1> >
curry_function(Func func)
{
    return perform_curry(func, Integer<-1>());
}

} // namespace intro

#endif
