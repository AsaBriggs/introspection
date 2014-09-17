#ifndef INCLUDED_METAPROGRAMMING_APPLY
#define INCLUDED_METAPROGRAMMING_APPLY

#ifndef INCLUDED_COMPILER_SPECIFICS
#include "compiler_specifics.h"
#endif

#ifndef INCLUDED_METAPROGRAMMING_INTEGER
#include "metaprogramming_integer.h"
#endif

#ifndef INCLUDED_METAPROGRAMMING_ARRAY
#include "metaprogramming_array.h"
#endif

namespace intro {

namespace placeholders {

template<typename Index>
struct TYPE_HIDDEN_VISIBILITY Placeholder
{
    typedef Placeholder type;
    METAPROGRAMMING_ONLY(Placeholder)
};

typedef Placeholder<Integer<0> > _0;
typedef Placeholder<Integer<1> > _1;
typedef Placeholder<Integer<2> > _2;
typedef Placeholder<Integer<3> > _3;
typedef Placeholder<Integer<4> > _4;
typedef Placeholder<Integer<5> > _5;
typedef Placeholder<Integer<6> > _6;
typedef Placeholder<Integer<7> > _7;
typedef Placeholder<Integer<8> > _8;
typedef Placeholder<Integer<9> > _9;
// Thinking about the processing required to get placeholder _ to work
// I don't consider it worthwhile; either we need to loop over the placeholder expression
// replacing _ with numberered placeholders one-by-one or there has to be a big
// "match all possible placeholder combinations" which would be hideous to write.

} // namespace placeholders

namespace Apply_impl {

// Type deliberately distinct from ArrayNoArgs so that
// applying < 10 arguments is distinguishable from wanting to apply ArrayNoArgs at that position.
struct TYPE_HIDDEN_VISIBILITY ignore
{
    typedef ignore type;
    METAPROGRAMMING_ONLY(ignore)
};

// Check performed on looking up the value of a placeholder in the current
// Apply application parameters
template<typename T>
struct TYPE_HIDDEN_VISIBILITY CheckIsNotNoArgument
{
    typedef T type;
    METAPROGRAMMING_ONLY(CheckIsNotNoArgument)
};

template<>
struct TYPE_HIDDEN_VISIBILITY CheckIsNotNoArgument<ignore>; // leave undefined as binding ignore is an error.

template<typename T, typename Environment>
struct TYPE_HIDDEN_VISIBILITY LookupPlaceholder
{
    typedef T type;
    METAPROGRAMMING_ONLY(LookupPlaceholder)
};

template<typename Index, typename Environment>
struct TYPE_HIDDEN_VISIBILITY LookupPlaceholder<placeholders::Placeholder<Index>, Environment> :
    CheckIsNotNoArgument<typename ArrayIndex<Environment, Index>::type>
{
    METAPROGRAMMING_ONLY(LookupPlaceholder)
};

// Environment Arity is required when a metafunction class is passed into Apply
// (as opposed to passing in a placeholder expression which can be analysed
// using template class parameter syntax).
template<typename T>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity;

template<>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore> > : Integer<0> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore> > : Integer<1> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, ignore, ignore, ignore, ignore, ignore, ignore, ignore, ignore> > : Integer<2> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, ignore, ignore, ignore, ignore, ignore, ignore, ignore> > : Integer<3> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, ignore, ignore, ignore, ignore, ignore, ignore> > : Integer<4> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, ignore, ignore, ignore, ignore, ignore> > : Integer<5> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, ignore, ignore, ignore, ignore> > : Integer<6> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, ignore, ignore, ignore> > : Integer<7> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, T7, ignore, ignore> > : Integer<8> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, ignore> > : Integer<9> {METAPROGRAMMING_ONLY(EnvironmentArity)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > : Integer<10> {METAPROGRAMMING_ONLY(EnvironmentArity)};


template<typename T, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments
{
    typedef T type;
    METAPROGRAMMING_ONLY(BindArguments)
};

template<typename Index, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<placeholders::Placeholder<Index>, Environment> :
    LookupPlaceholder<placeholders::Placeholder<Index>, Environment>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename> class T, typename P0, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename> class T, typename P0, typename P1, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename> class T, typename P0, typename P1, typename P2, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4, P5>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4, P5, P6>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type,
      typename LookupPlaceholder<P6, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type,
      typename LookupPlaceholder<P6, Environment>::type,
      typename LookupPlaceholder<P7, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type,
      typename LookupPlaceholder<P6, Environment>::type,
      typename LookupPlaceholder<P7, Environment>::type,
      typename LookupPlaceholder<P8, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename Environment>
struct TYPE_HIDDEN_VISIBILITY BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type,
      typename LookupPlaceholder<P6, Environment>::type,
      typename LookupPlaceholder<P7, Environment>::type,
      typename LookupPlaceholder<P8, Environment>::type,
      typename LookupPlaceholder<P9, Environment>::type>
{
    METAPROGRAMMING_ONLY(BindArguments)
};

// This is the magic of the Apply mechanism. The assumption is that the Arity of the
// environment is the arity of the metafunction class passed into it. Through this
// binding we obtain a placeholder expression that can be passed to BindArguments.
template<typename T, typename EnvironmentArity>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders;

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<0> >
{
    typedef T type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<1> >
{
    typedef typename T::template apply<placeholders::_0> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<2> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<3> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<4> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<5> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<6> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<7> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<8> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6, placeholders::_7> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<9> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6, placeholders::_7, placeholders::_8> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

template<typename T>
struct TYPE_HIDDEN_VISIBILITY AddPlaceholders<T, Integer<10> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6, placeholders::_7, placeholders::_8, placeholders::_9> type;
    METAPROGRAMMING_ONLY(AddPlaceholders)
};

// Metafunction Class passed in, so add placeholders to nested template class apply
// and bind the Environment. Note Apply and BindArguments are different metafunctions to prevent
// an infinte loop when the Environment is empty
template<typename T, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply :
    BindArguments<typename AddPlaceholders<T, typename EnvironmentArity<Environment>::type>::type, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<typename Index, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<placeholders::Placeholder<Index>, Environment> :
    BindArguments<placeholders::Placeholder<Index>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename> class T, typename P0, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0>, Environment> : BindArguments<T<P0>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename> class T, typename P0, typename P1, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1>, Environment> : BindArguments<T<P0, P1>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename> class T, typename P0, typename P1, typename P2, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2>, Environment> : BindArguments<T<P0, P1, P2>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3>, Environment> : BindArguments<T<P0, P1, P2, P3>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4>, Environment> : BindArguments<T<P0, P1, P2, P3, P4>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4, P5>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4, P5, P6>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4, P5, P6, P7>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4, P5, P6, P7, P8>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply<T<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9>, Environment>
{
    METAPROGRAMMING_ONLY(Apply)
};

} // namespace Apply_impl

template<typename T, typename P0=Apply_impl::ignore, typename P1=Apply_impl::ignore, typename P2=Apply_impl::ignore, typename P3=Apply_impl::ignore, typename P4=Apply_impl::ignore, typename P5=Apply_impl::ignore, typename P6=Apply_impl::ignore, typename P7=Apply_impl::ignore, typename P8=Apply_impl::ignore, typename P9=Apply_impl::ignore>
struct TYPE_HIDDEN_VISIBILITY Apply : Apply_impl::Apply<T, Array<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9> > {METAPROGRAMMING_ONLY(Apply)};

// Environment must be in the fom of an array where 0..N are parameters and the rest are ignore
// See RationaliseApplyArray for how to remove ArrayNoArg and the like.
template<typename T, typename Environment>
struct TYPE_HIDDEN_VISIBILITY Apply_Environment : Apply_impl::Apply<T, Environment> {METAPROGRAMMING_ONLY(Apply_Environment)};

} // namespace intro

#endif
