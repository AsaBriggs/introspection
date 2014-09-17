#ifndef INCLUDED_METAPROGRAMMING_ARRAY
#define INCLUDED_METAPROGRAMMING_ARRAY

#ifndef INCLUDED_CSTDDEF
#include <cstddef>
#define INCLUDED_CSTDDEF
#endif

#ifndef INCLUDED_COMPILER_SPECIFICS
#include "compiler_specifics.h"
#endif

#ifndef INCLUDED_METAPROGRAMMING_INTEGER
#include "metaprogramming_integer.h"
#endif

namespace intro {

struct TYPE_DEFAULT_VISIBILITY ArrayNoArg
{
    typedef ArrayNoArg type;
    // Construction allowed to make binding/function application easier.
};

// Note that Array has as many types as Apply can handle with placeholder expressions.
// Attempting to expand the interface would destroy the ability of Apply to handle all Arrays passed to it.
template<typename T0=ArrayNoArg, typename T1=ArrayNoArg, typename T2=ArrayNoArg, typename T3=ArrayNoArg, typename T4=ArrayNoArg, typename T5=ArrayNoArg, typename T6=ArrayNoArg, typename T7=ArrayNoArg, typename T8=ArrayNoArg, typename T9=ArrayNoArg>
struct TYPE_HIDDEN_VISIBILITY Array
{
    typedef Array type;
    METAPROGRAMMING_ONLY(Array)
};


template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<0> >
{
    typedef T0 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<1> >
{
    typedef T1 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<2> >
{
    typedef T2 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<3> >
{
    typedef T3 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<4> >
{
    typedef T4 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<5> >
{
    typedef T5 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<6> >
{
    typedef T6 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<7> >
{
    typedef T7 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<8> >
{
    typedef T8 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<9> >
{
    typedef T9 type;
    METAPROGRAMMING_ONLY(ArrayIndex)
};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY ArraySize;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > : Integer<10> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8> > : Integer<9> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4, T5, T6, T7> > : Integer<8> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4, T5, T6> > : Integer<7> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4, T5> > : Integer<6> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3, T4> > : Integer<5> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2, typename T3>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2, T3> > : Integer<4> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1, typename T2>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1, T2> > : Integer<3> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0, T1> > : Integer<2> {METAPROGRAMMING_ONLY(ArraySize)};

template<typename T0>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<T0> > : Integer<1> {METAPROGRAMMING_ONLY(ArraySize)};

template<>
struct TYPE_HIDDEN_VISIBILITY ArraySize<Array<> > : Integer<0> {METAPROGRAMMING_ONLY(ArraySize)};


template<typename T, typename U>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat ;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, U0> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, T7, U0, U1> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, U0, U1, U2> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4, T5>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, U0, U1, U2, U3> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3, T4>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, U0, U1, U2, U3, U4> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename T3, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2, T3>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, U0, U1, U2, U3, U4, U5> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename T2, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1, T2>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, U0, U1, U2, U3, U4, U5, U6> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename T1, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0, T1>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, U0, U1, U2, U3, U4, U5, U6, U7> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename T0, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<T0>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, U0, U1, U2, U3, U4, U5, U6, U7, U8> {METAPROGRAMMING_ONLY(ArrayConcat)};

template<typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct TYPE_HIDDEN_VISIBILITY ArrayConcat<Array<>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> {METAPROGRAMMING_ONLY(ArrayConcat)};


template<typename T, typename At>
struct TYPE_HIDDEN_VISIBILITY ArraySplit;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<0> > : Array<Array<>, Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<1> > : Array<Array<T0>, Array<T1, T2, T3, T4, T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<2> > : Array<Array<T0, T1>, Array<T2, T3, T4, T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<3> > : Array<Array<T0, T1, T2>, Array<T3, T4, T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<4> > : Array<Array<T0, T1, T2, T3>, Array<T4, T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<5> > : Array<Array<T0, T1, T2, T3, T4>, Array<T5, T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<6> > : Array<Array<T0, T1, T2, T3, T4, T5>, Array<T6, T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<7> > : Array<Array<T0, T1, T2, T3, T4, T5, T6>, Array<T7, T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<8> > : Array<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Array<T8, T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<9> > : Array<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Array<T9> > {METAPROGRAMMING_ONLY(ArraySplit)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<10> > : Array<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Array<> > {METAPROGRAMMING_ONLY(ArraySplit)};


template<typename T>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > : Array<T9, T8, T7, T6, T5, T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8> > : Array<T8, T7, T6, T5, T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6, T7> > : Array<T7, T6, T5, T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6> > : Array<T6, T5, T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4, T5> > : Array<T5, T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3, T4> > : Array<T4, T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2, typename T3>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2, T3> > : Array<T3, T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1, typename T2>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1, T2> > : Array<T2, T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0, typename T1>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0, T1> > : Array<T1, T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<typename T0>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<T0> > : Array<T0> {METAPROGRAMMING_ONLY(ArrayReverse)};

template<>
struct TYPE_HIDDEN_VISIBILITY ArrayReverse<Array<> > : Array<> {METAPROGRAMMING_ONLY(ArrayReverse)};

namespace ArrayRotate_impl {

template<typename T, typename F, typename M, typename L>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate;

template<typename T, IntegerValueType F, IntegerValueType M, IntegerValueType L>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate<T, Integer<F>, Integer<M>, Integer<L> >
{
    // Assert F <= M
    // Assert M <= L
    // Assert L <= ArraySize<T>
    // Split into
    // 0..F, F..M, M..L, L..End
    //
    typedef typename ArraySplit<T, Integer<F> >::type SplitAtFirst; // T0 = 0..F
    typedef typename ArraySplit<typename ArrayIndex<SplitAtFirst, Integer<1> >::type, Integer<M - F> >::type SplitAtM; // T0 = F..M
    typedef typename ArraySplit<typename ArrayIndex<SplitAtM, Integer<1> >::type, Integer<L - M> >::type SplitAtL; // T0 = M..L, T1 = L..end

    typedef typename ArrayConcat<typename ArrayIndex<SplitAtFirst, Integer<0> >::type, typename ArrayIndex<SplitAtL, Integer<0> >::type>::type A; // 0..F & M..L
    typedef typename ArrayConcat<A, typename ArrayIndex<SplitAtM, Integer<0> >::type>::type B; // 0..F & M..L & F..M
    typedef typename ArrayConcat<B, typename ArrayIndex<SplitAtL, Integer<1> >::type>::type type; // 0..F & M..L & F..M & L..End
    METAPROGRAMMING_ONLY(ArrayRotate)
};


} // namespace ArrayRotate_impl

template<typename T, typename F, typename M, typename L>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate;
// Needs L <= ArraySize<T>

template<typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate<T, F, F, F> : T {METAPROGRAMMING_ONLY(ArrayRotate)};

template<typename T, typename F, typename L>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate<T, F, F, L> : T {METAPROGRAMMING_ONLY(ArrayRotate)};

template<typename T, typename F, typename L>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate<T, F, L, L> : T {METAPROGRAMMING_ONLY(ArrayRotate)};

template<typename T, typename F, typename M, typename L>
struct TYPE_HIDDEN_VISIBILITY ArrayRotate : ArrayRotate_impl::ArrayRotate<T, F, M, L> {METAPROGRAMMING_ONLY(ArrayRotate)};


template<typename T, typename M>
struct TYPE_HIDDEN_VISIBILITY ArrayRotateDefault : ArrayRotate<T, Integer<0>, M, typename ArraySize<T>::type> {METAPROGRAMMING_ONLY(ArrayRotateDefault)};


template<typename T, typename Index>
struct TYPE_HIDDEN_VISIBILITY ArrayEraseIndex;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayEraseIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<0> > : Array<T1, T2, T3, T4, T5, T6, T7, T8, T9> {METAPROGRAMMING_ONLY(ArrayEraseIndex)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayEraseIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<1> > : Array<T0, T2, T3, T4, T5, T6, T7, T8, T9> {METAPROGRAMMING_ONLY(ArrayEraseIndex)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayEraseIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<2> > : Array<T0, T1, T3, T4, T5, T6, T7, T8, T9> {METAPROGRAMMING_ONLY(ArrayEraseIndex)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayEraseIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<3> > : Array<T0, T1, T2, T4, T5, T6, T7, T8, T9> {METAPROGRAMMING_ONLY(ArrayEraseIndex)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayEraseIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<4> > : Array<T0, T1, T2, T3, T5, T6, T7, T8, T9> {METAPROGRAMMING_ONLY(ArrayEraseIndex)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayEraseIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<5> > : Array<T0, T1, T2, T3, T4, T6, T7, T8, T9> {METAPROGRAMMING_ONLY(ArrayEraseIndex)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayEraseIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<6> > : Array<T0, T1, T2, T3, T4, T5, T7, T8, T9> {METAPROGRAMMING_ONLY(ArrayEraseIndex)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayEraseIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<7> > : Array<T0, T1, T2, T3, T4, T5, T6, T8, T9> {METAPROGRAMMING_ONLY(ArrayEraseIndex)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayEraseIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<8> > : Array<T0, T1, T2, T3, T4, T5, T6, T7, T9> {METAPROGRAMMING_ONLY(ArrayEraseIndex)};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TYPE_HIDDEN_VISIBILITY ArrayEraseIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<9> > : Array<T0, T1, T2, T3, T4, T5, T6, T7, T8> {METAPROGRAMMING_ONLY(ArrayEraseIndex)};

} // namespace intro

#endif
