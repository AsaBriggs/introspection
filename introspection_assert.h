#ifndef INCLUDED_INTROSPECTION_ASSERT
#define INCLUDED_INTROSPECTION_ASSERT
//
// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// Note by Asa Briggs, 12 September 2014
// Done a copy-paste job of the essence of the Boost static assert scheme.
// Note design of the static assert mechanism copied from BOOST MPL which carried
// the preceeding copyright

#ifndef INCLUDED_COMPILER_SPECIFICS
#include "compiler_specifics.h"
#endif

namespace intro {

namespace assert {

template<bool Pred, typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY if_c;

template<typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY if_c<true, T, F>
{
    typedef T type;
    METAPROGRAMMING_ONLY(if_c)
};

template<typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY if_c<false, T, F>
{
    typedef F type;
    METAPROGRAMMING_ONLY(if_c)
};

template<typename Pred, typename T, typename F>
struct TYPE_HIDDEN_VISIBILITY if_ : if_c<Pred::type::value, T, F>
{
    METAPROGRAMMING_ONLY(if_)
};

struct TYPE_HIDDEN_VISIBILITY assertion_true
{
    typedef assertion_true type;
    static const bool value = true;
    METAPROGRAMMING_ONLY(assertion_true)
};

struct TYPE_HIDDEN_VISIBILITY assertion_false
{
    typedef assertion_false type;
    static const bool value = false;
    METAPROGRAMMING_ONLY(assertion_false)
};

template<bool c>
struct TYPE_HIDDEN_VISIBILITY not_;

template<>
struct TYPE_HIDDEN_VISIBILITY not_<true> : assertion_false
{
    METAPROGRAMMING_ONLY(not_)
};

template<>
struct TYPE_HIDDEN_VISIBILITY not_<false> : assertion_true
{
    METAPROGRAMMING_ONLY(not_)
};

struct TYPE_HIDDEN_VISIBILITY failed {};

// The trick of the assert scheme is to use this type to extract the Predicate type.
template<typename Pred>
struct TYPE_HIDDEN_VISIBILITY extract_assert_pred;

template<typename Pred>
struct TYPE_HIDDEN_VISIBILITY extract_assert_pred<void(Pred)>
{
    typedef Pred type;
    METAPROGRAMMING_ONLY(extract_assert_pred)
};

template<bool C> struct TYPE_HIDDEN_VISIBILITY assertion { typedef assertion type; };

template<typename Pred>
struct TYPE_HIDDEN_VISIBILITY eval_assert {
  typedef typename ::intro::assert::extract_assert_pred<Pred>::type P;
    typedef typename ::intro::assert::if_<typename P::type,
        ::intro::assert::assertion<false>,
        ::intro::assert::failed ************ P::************
    >::type type;
    METAPROGRAMMING_ONLY(eval_assert)
};

template<typename Pred>
struct TYPE_HIDDEN_VISIBILITY eval_assert_not {
    typedef typename ::intro::assert::extract_assert_pred<Pred>::type P;
    typedef typename ::intro::assert::if_<typename ::intro::assert::not_<P::type::value>::type,
        ::intro::assert::assertion<false>,
      ::intro::assert::failed ************ ::intro::assert::not_<P::type::value>::************
    >::type type;
    METAPROGRAMMING_ONLY(eval_assert_not)
};

template<typename T>
HIDDEN T make_T();

template<bool C>
HIDDEN int assertion_failed( typename assertion<C>::type );

#define INFO_ASSERT_CAT(x, y) INFO_ASSERT_CAT_(x, y)
#define INFO_ASSERT_CAT_(x, y) x ## y

// Note that this mechanism is limited to just one assert per line, for simplicity.
#define INTROSPECTION_STATIC_ASSERT(Pred) enum { INFO_ASSERT_CAT(TEST,__LINE__) = sizeof(::intro::assert::assertion_failed<false>(::intro::assert::make_T<typename ::intro::assert::eval_assert<void Pred>::type>())) }
#define INTROSPECTION_STATIC_ASSERT2(Pred) enum { INFO_ASSERT_CAT(TEST, __LINE__) = sizeof(::intro::assert::assertion_failed<false>(::intro::assert::make_T< ::intro::assert::eval_assert<void Pred>::type>())) }

#define INTROSPECTION_STATIC_ASSERT_NOT(Pred) enum { INFO_ASSERT_CAT(TEST,__LINE__) = sizeof(::intro::assert::assertion_failed<false>(::intro::assert::make_T<typename ::intro::assert::eval_assert_not<void Pred>::type>())) }
#define INTROSPECTION_STATIC_ASSERT_NOT2(Pred) enum { INFO_ASSERT_CAT(TEST, __LINE__) = sizeof(::intro::assert::assertion_failed<false>(::intro::assert::make_T<  ::intro::assert::eval_assert_not<void Pred>::type>())) }

// End of Boost MPL code.

} // namespace assert
} // namespace intro

#endif
