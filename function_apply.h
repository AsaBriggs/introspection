#ifndef INCLUDED_FUNCTION_APPLY
#define INCLUDED_FUNCTION_APPLY

#ifndef INCLUDED_FUNCTION_SIGNATURES
#include "function_signatures.h"
#endif

namespace intro {

// Objective is to be able to call a given function object in a uniform manner
// template<typename Func ...>
// typename codomain_type<Func ...>::type apply(Func f ...) { return f(...); }
// where ... are 0..n arguments
// Use an intermediate layer of function applicators to commonise functors, function pointers and member function pointer
// apply function

// functor
// function_wrapper

template<typename T>
struct is_a_function_wrapper : false_type
{};

template<typename CodomainType, typename InputType, typename MemberFunction>
struct is_a_function_wrapper<function_pointer_specialisations::function_wrapper<CodomainType, InputType, MemberFunction> > : true_type
{};

template<typename Func, typename Enable=void>
struct ApplyObj;

template<typename Func>
struct ApplyObj<Func, typename disable_if<or_<is_same<void, typename GetCodomainType<Func>::type>, is_a_function_wrapper<Func> >, void>::type>
{
  typedef ApplyObj type;
  typedef true_type IntrospectionEnabled;
  typedef typename GetCodomainType<Func>::type codomain_type;
  typedef typename GetInputTypeArray<Func>::type FuncInputs;
  typedef typename ArrayConcat<Array<Func>, FuncInputs>::type input_types;

  template<int N> struct lookup : ArrayIndex<FuncInputs, Integer<N> > {};

  INLINE codomain_type
  operator()(Func fun) const
  {
      return fun();
  }

  INLINE codomain_type
  operator()(Func func,
             typename lookup<0>::type p0) const
  {
      return func(p0);
  }

  INLINE codomain_type
  operator()(Func func,
             typename lookup<0>::type p0,
             typename lookup<1>::type p1) const
  {
      return func(p0, p1);
  }

};

template<typename Func>
  struct ApplyObj<Func, typename enable_if<and_<is_same<void, typename GetCodomainType<Func>::type>, not_<is_a_function_wrapper<Func> > >, void>::type>
{
  typedef ApplyObj type;
  typedef true_type IntrospectionEnabled;
  typedef void codomain_type;
  typedef typename GetInputTypeArray<Func>::type FuncInputs;
  typedef typename ArrayConcat<Array<Func>, FuncInputs>::type input_types;

  template<int N> struct lookup : ArrayIndex<FuncInputs, Integer<N> > {};

  INLINE codomain_type
  operator()(Func fun) const
  {
      fun();
  }

  INLINE codomain_type
  operator()(Func func,
             typename lookup<0>::type p0) const
  {
      func(p0);
  }

  INLINE codomain_type
  operator()(Func func,
             typename lookup<0>::type p0,
             typename lookup<1>::type p1) const
  {
      func(p0, p1);
  }
};

template<typename CodomainType, typename InputTypes>
struct ApplyObj<function_pointer_specialisations::function_wrapper<CodomainType, InputTypes, false_type> >
{
  typedef function_pointer_specialisations::function_wrapper<CodomainType, InputTypes, false_type> Spec;
  typedef ApplyObj type;
  typedef true_type IntrospectionEnabled;
  typedef CodomainType codomain_type;
  typedef typename ArrayConcat<Array<typename Spec::Func>, InputTypes>::type input_types;

  template<int N> struct lookup : ArrayIndex<InputTypes, Integer<N> > {};

  codomain_type operator()(typename Spec::Func func) const
  {
      return (*func)();
  }

  codomain_type operator()(typename Spec::Func func,
                           typename lookup<0>::type p0) const
  {
      return func(p0);
  }

  codomain_type operator()(typename Spec::Func func,
                           typename lookup<0>::type p0,
                           typename lookup<1>::type p1) const
  {
    return func(p0, p1);
  }
};

template<typename InputTypes>
struct ApplyObj<function_pointer_specialisations::function_wrapper<void, InputTypes, false_type> >
{
  typedef function_pointer_specialisations::function_wrapper<void, InputTypes, false_type> Spec;
  typedef ApplyObj type;
  typedef true_type IntrospectionEnabled;
  typedef void codomain_type;
  typedef typename ArrayConcat<Array<typename Spec::Func>, InputTypes>::type input_types;

  template<int N> struct lookup : ArrayIndex<InputTypes, Integer<N> > {};

  codomain_type operator()(typename Spec::Func func) const
  {
      (*func)();
  }

  codomain_type operator()(typename Spec::Func func,
                           typename lookup<0>::type p0) const
  {
      func(p0);
  }

  codomain_type operator()(typename Spec::Func func,
                           typename lookup<0>::type p0,
                           typename lookup<1>::type p1) const
  {
      func(p0, p1);
  }
};

template<typename CodomainType, typename InputTypes>
struct ApplyObj<function_pointer_specialisations::function_wrapper<CodomainType, InputTypes, true_type> >
{
  typedef function_pointer_specialisations::function_wrapper<CodomainType, InputTypes, true_type> Spec;
  typedef ApplyObj type;
  typedef true_type IntrospectionEnabled;
  typedef CodomainType codomain_type;
  typedef typename ArrayConcat<Array<typename Spec::Func>, InputTypes>::type input_types;

  template<int N> struct lookup : ArrayIndex<InputTypes, Integer<N> > {};

  codomain_type operator()(typename Spec::Func func,
                           typename lookup<0>::type p0) const
  {
      return (p0->*func)();
  }

  codomain_type operator()(typename Spec::Func func,
                           typename lookup<0>::type p0,
                           typename lookup<1>::type p1) const
  {
      return (p0->*func)(p1);
  }
};


template<typename InputTypes>
struct ApplyObj<function_pointer_specialisations::function_wrapper<void, InputTypes, true_type> >
{
  typedef function_pointer_specialisations::function_wrapper<void, InputTypes, true_type> Spec;
  typedef ApplyObj type;
  typedef true_type IntrospectionEnabled;
  typedef void codomain_type;
  typedef typename ArrayConcat<Array<typename Spec::Func>, InputTypes>::type input_types;

  template<int N> struct lookup : ArrayIndex<InputTypes, Integer<N> > {};

  codomain_type operator()(typename Spec::Func func,
                           typename lookup<0>::type p0) const
  {
      (p0->*func)();
  }

  codomain_type operator()(typename Spec::Func func,
                           typename lookup<0>::type p0,
                           typename lookup<1>::type p1) const
  {
      (p0->*func)(p1);
  }
};

template<typename Fun>
struct GetApplyObj : ApplyObj<typename ResolveFunctionSignatureType<Fun>::type>
{
    METAPROGRAMMING_ONLY(GetApplyObj)
};

template<typename Func>
typename disable_if<is_same<void ,typename GetCodomainType<typename GetApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename GetApplyObj<Func>::type>::type >::type
apply(Func func)
{
    return typename GetApplyObj<Func>::type()(func);
}

template<typename Func>
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func)
{
    typename GetApplyObj<Func>::type()(func);
}


template<typename Func, typename P0>
typename disable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename ApplyObj<Func>::type>::type >::type
apply(Func func, P0 p0)
{
    return typename GetApplyObj<Func>::type()(func, p0);
}

template<typename Func, typename P0>
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func, P0 p0)
{
    typename GetApplyObj<Func>::type()(func, p0);
}


template<typename Func, typename P0, typename P1>
typename disable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                    typename GetCodomainType<typename ApplyObj<Func>::type>::type >::type
apply(Func func, P0 p0, P1 p1)
{
    return typename GetApplyObj<Func>::type()(func, p0, p1);
}

template<typename Func, typename P0, typename P1>
typename enable_if<is_same<void ,typename GetCodomainType<typename ApplyObj<Func>::type>::type>,
                   void>::type
apply(Func func, P0 p0, P1 p1)
{
    typename GetApplyObj<Func>::type()(func, p0, p1);
}

} // namespace intro

#endif


