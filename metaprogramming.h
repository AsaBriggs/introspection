#ifndef INCLUDED_METAPROGRAMMING
#define INCLUDED_METAPROGRAMMING

namespace intro {

struct true_type
{
    typedef true_type type;
    static const bool value = true;
    operator bool() const { return value ; }
};

struct false_type
{
    typedef false_type type;
    static const bool value = false;
    operator bool() const { return value ; }
};

template<int num>
struct Integer
{
    typedef Integer type;
    static const int value = num;
    operator int() const { return value ; }
};

struct DefaultTag
{
    typedef DefaultTag type;
    typedef true_type IntrospectionEnabled;
};

template<typename T>
struct Ref
{
    typedef Ref type;
    typedef true_type IntrospectionEnabled;
    typedef T* IntrospectionItem0;
    T* m0; // hold by pointer to make the type regular (assignment is enabled).

    // Need implict conversion operator to allow
    // storage conversion to happen without another function call
    operator T&() const { return *m0; }

    template<typename P0>
    static inline type make(P0& p0)
    {
        T& x = p0;
        type tmp = {&x};
        return tmp;
    }
};

// Caller of make_ref must ensure the lifetime of the referenced object is greater
// than the lifetime of the Ref.
template<typename T>
inline Ref<T> make_ref(T& x)
{
    return Ref<T>::make(x);
}

namespace impl {

template<bool value>
struct ValueToTrueFalse_Impl;

template<>
struct ValueToTrueFalse_Impl<false> : false_type {};

template<>
struct ValueToTrueFalse_Impl<true> : true_type {};


template<typename T>
struct Successor_impl;

template<int num>
struct Successor_impl<Integer<num> > : Integer<num+1> {};


template<typename T>
struct Predecessor_impl;

template<int num>
struct Predecessor_impl<Integer<num> > : Integer<num-1> {};

template<int num0, int num1, bool num0LessEq>
struct Min_Impl2;

template<int num0, int num1>
struct Min_Impl2<num0, num1, false> : Integer<num1> {};

template<int num0, int num1>
struct Min_Impl2<num0, num1, true> : Integer<num0> {};

template<typename T, typename U>
struct Min_Impl;

template<int num0, int num1>
struct Min_Impl<Integer<num0>, Integer<num1> > : Min_Impl2<num0, num1, !(num1 < num0)> {};

template<typename T0, typename T1>
struct Subtract_impl;

template<int num0, int num1>
struct Subtract_impl<Integer<num0>, Integer<num1> > : Integer<num0 - num1> {};


template<typename T0, typename T1>
struct Add_impl;

template<int num0, int num1>
struct Add_impl<Integer<num0>, Integer<num1> > : Integer<num0 + num1> {};


template<typename V>
struct not_impl;

template<>
struct not_impl<false_type> : true_type {};

template<>
struct not_impl<true_type> : false_type {};


template<typename V0, typename V1, typename V2>
struct or_impl;

template<>
struct or_impl<false_type, false_type, false_type> : false_type {};

template<typename V1, typename V2>
struct or_impl<true_type, V1, V2> : true_type {};

template<typename V1, typename V2>
struct or_impl<false_type, V1, V2> : or_impl<typename V1::type, V2, false_type> {};


template<typename V0, typename V1, typename V2>
struct and_impl;

template<>
struct and_impl<true_type, true_type, true_type> : true_type {};

template<typename V1, typename V2>
struct and_impl<false_type, V1, V2> : false_type {};

template<typename V1, typename V2>
struct and_impl<true_type, V1, V2> : and_impl<typename V1::type, V2, true_type> {};


template<typename enable, typename T>
struct enable_if_impl;

template<typename T>
struct enable_if_impl<true_type, T>
{
    typedef T type;
};

template<typename T>
struct enable_if_impl<false_type, T> {};


template<typename enable, typename T>
struct disable_if_impl;

template<typename T>
struct disable_if_impl<true_type, T> {};


template<typename T>
struct disable_if_impl<false_type, T>
{
    typedef T type;
};


template<typename Test, typename T, typename F>
struct if_impl;

template<typename T, typename F>
struct if_impl<true_type, T, F> { typedef T type; };

template<typename T, typename F>
struct if_impl<false_type, T, F> { typedef F type; };


template<typename Test, typename T, typename F>
struct eval_if_impl;

template<typename T, typename F>
struct eval_if_impl<true_type, T, F> { typedef typename T::type type; };

template<typename T, typename F>
struct eval_if_impl<false_type, T, F> { typedef typename F::type type; };


template<typename T, typename U>
struct is_same_impl : false_type {};

template<typename T>
struct is_same_impl<T, T> : true_type {};


template<typename T>
struct is_reference_impl : false_type {};

template<typename T>
struct is_reference_impl<T&> : true_type {};

template<typename T>
struct make_const_ref_impl
{
    typedef T const& type;
};

template<typename T>
struct make_const_ref_impl<T&>
{
    typedef T const& type;
};

template<typename T>
struct parameter_type_impl
{
    typedef T const& type;
};

template<typename T>
struct parameter_type_impl<T&>
{
    typedef T& type;
};


template<typename T>
struct deduce_input_type_impl
{
    typedef T type;
};

template<typename T>
struct deduce_input_type_impl<T const&>
{
    typedef T type;
};


template<typename T>
struct decay_ref_impl
{
    typedef T type;
};

template<typename T, size_t N>
struct decay_ref_impl<T[N]>
{
    typedef T const* type;
};

template<typename T>
struct decay_ref_impl<Ref<T> >
{
    typedef T& type;
};

template<typename From, typename To>
struct is_convertible_impl
{
private:
  typedef char Yes;
  struct No { char a[2]; };
  static No test(...);
  static Yes test(To);
  static From get();
public:
  typedef typename ValueToTrueFalse_Impl<sizeof(test(get())) ==1>::type type;
};

template<typename T>
struct IsStructClassOrUnion_Impl
{
private:
    typedef char Yes;
    struct No { char x[2]; };
    template<typename U>
    static Yes test(char U::*);
    template<typename U>
    static No test(...);
public:
    typedef typename ValueToTrueFalse_Impl<sizeof(test<T>(0)) == 1>::type type;
};


} // namespace impl

template<bool value>
struct ValueToTrueFalse : impl::ValueToTrueFalse_Impl<value> {};

template<typename T>
struct Successor : impl::Successor_impl<T> {};

template<typename T>
struct Predecessor : impl::Predecessor_impl<T> {};

template<typename T, typename U>
struct Min : impl::Min_Impl<T, U> {};

template<typename T0, typename T1>
struct Subtract : impl::Subtract_impl<T0, T1> {};

template<typename T0, typename T1>
struct Add : impl::Add_impl<T0, T1> {};

template<typename V>
struct not_ : impl::not_impl<typename V::type> {};

template<typename V0, typename V1, typename V2=false_type>
struct or_ : impl::or_impl<typename V0::type, V1, V2> {};

template<typename V0, typename V1, typename V2=true_type>
struct and_ : impl::and_impl<typename V0::type, V1, V2> {};

template<typename enable, typename T>
struct enable_if : impl::enable_if_impl<typename enable::type, T> {};

template<typename enable, typename T>
struct disable_if : impl::disable_if_impl<typename enable::type, T> {};

template<typename T>
struct identity_type
{
  typedef T type;
};

template<typename T>
struct identity_type<identity_type<T> > : identity_type<T> {};

template<typename Test, typename T, typename F>
struct if_ : impl::if_impl<typename Test::type, T, F> {};

template<typename Test, typename T, typename F>
struct eval_if : impl::eval_if_impl<typename Test::type, T, F> {};

template<typename T, typename U>
struct is_same : impl::is_same_impl<T, U> {};

template<typename T>
struct is_reference : impl::is_reference_impl<T> {};

template<typename T>
struct make_const_ref : impl::make_const_ref_impl<T> {};

template<typename T>
struct deduce_input_type : impl::deduce_input_type_impl<T> {};

template<typename T>
struct parameter_type : impl::parameter_type_impl<T> {};


template<typename T, typename enable=void>
struct underlying_type
{
    typedef T type;
};

template<typename T>
struct get_underlying_type
{
    typedef typename underlying_type<T>::type type;
    // Purpose of this metafunction is to check the types have the same size
    static char arr[sizeof(T) == sizeof(type) ? 1 : 0];
};

template<typename T>
inline typename get_underlying_type<T>::type& get_underlying_ref(T& x)
{
    return reinterpret_cast<typename get_underlying_type<T>::type&>(x);
}

template<typename T>
inline void swap_basic(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template<typename T>
inline void swap(T& x, T& y)
{
    swap_basic(get_underlying_ref(x), get_underlying_ref(y));
}

template<typename T, typename enable=void>
//requires(Regular(T))
struct OperatorEquals
{
    typedef OperatorEquals type;
    typedef true_type IntrospectionEnabled;
    typedef T input_type_0;
    typedef T input_type_1;
    typedef bool codomain_type;

    inline codomain_type operator()(typename parameter_type<T>::type x, typename parameter_type<T>::type y) const
    {
        return x == y;
    }
};


template<typename T, typename enable=void>
//requires(TotallyOrdered(T))
struct OperatorLessThan
{
    typedef OperatorLessThan type;
    typedef true_type IntrospectionEnabled;
    typedef T input_type_0;
    typedef T input_type_1;
    typedef bool codomain_type;

    inline codomain_type operator()(typename parameter_type<T>::type x, typename parameter_type<T>::type y) const
    {
        return x < y;
    }
};


template<typename T, typename enable=void>
struct less : OperatorLessThan<T> {};

template<typename T, typename enable=void>
struct equal : OperatorEquals<T> {};

template<typename T>
struct decay_ref : impl::decay_ref_impl<T> {};

template<typename From, typename To>
struct is_convertible : impl::is_convertible_impl<From, To> {};

template<typename T>
struct IsStructClassOrUnion : impl::IsStructClassOrUnion_Impl<T> {};


struct ArrayNoArg { typedef ArrayNoArg type; };

template<typename T0=ArrayNoArg, typename T1=ArrayNoArg, typename T2=ArrayNoArg, typename T3=ArrayNoArg, typename T4=ArrayNoArg, typename T5=ArrayNoArg, typename T6=ArrayNoArg, typename T7=ArrayNoArg, typename T8=ArrayNoArg, typename T9=ArrayNoArg>
struct Array
{
    typedef Array type;
};

namespace impl {

template<typename T, typename Index>
struct ArrayIndex;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<0> >
{
    typedef T0 type;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<1> >
{
    typedef T1 type;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<2> >
{
    typedef T2 type;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<3> >
{
    typedef T3 type;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<4> >
{
    typedef T4 type;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<5> >
{
    typedef T5 type;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<6> >
{
    typedef T6 type;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<7> >
{
    typedef T7 type;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<8> >
{
    typedef T8 type;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArrayIndex<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<9> >
{
    typedef T9 type;
};

template<typename T>
struct ArraySize;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySize<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > : Integer<10> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct ArraySize<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8> > : Integer<9> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct ArraySize<Array<T0, T1, T2, T3, T4, T5, T6, T7> > : Integer<8> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct ArraySize<Array<T0, T1, T2, T3, T4, T5, T6> > : Integer<7> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct ArraySize<Array<T0, T1, T2, T3, T4, T5> > : Integer<6> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
struct ArraySize<Array<T0, T1, T2, T3, T4> > : Integer<5> {};

template<typename T0, typename T1, typename T2, typename T3>
struct ArraySize<Array<T0, T1, T2, T3> > : Integer<4> {};

template<typename T0, typename T1, typename T2>
struct ArraySize<Array<T0, T1, T2> > : Integer<3> {};

template<typename T0, typename T1>
struct ArraySize<Array<T0, T1> > : Integer<2> {};

template<typename T0>
struct ArraySize<Array<T0> > : Integer<1> {};

template<>
struct ArraySize<Array<> > : Integer<0> {};


template<typename T, typename U>
struct ArrayConcat ;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, U0> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, T7, U0, U1> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct ArrayConcat<Array<T0, T1, T2, T3, T4, T5, T6>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, T6, U0, U1, U2> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct ArrayConcat<Array<T0, T1, T2, T3, T4, T5>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, T5, U0, U1, U2, U3> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct ArrayConcat<Array<T0, T1, T2, T3, T4>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, T4, U0, U1, U2, U3, U4> {};

template<typename T0, typename T1, typename T2, typename T3, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct ArrayConcat<Array<T0, T1, T2, T3>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, T3, U0, U1, U2, U3, U4, U5> {};

template<typename T0, typename T1, typename T2, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct ArrayConcat<Array<T0, T1, T2>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, T2, U0, U1, U2, U3, U4, U5, U6> {};

template<typename T0, typename T1, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct ArrayConcat<Array<T0, T1>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, T1, U0, U1, U2, U3, U4, U5, U6, U7> {};

template<typename T0, typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct ArrayConcat<Array<T0>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<T0, U0, U1, U2, U3, U4, U5, U6, U7, U8> {};

template<typename U0, typename U1, typename U2, typename U3, typename U4, typename U5, typename U6, typename U7, typename U8, typename U9>
struct ArrayConcat<Array<>, Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> > : Array<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9> {};


template<typename T, typename At>
struct ArraySplit;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<0> > : Array<Array<>, Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<1> > : Array<Array<T0>, Array<T1, T2, T3, T4, T5, T6, T7, T8, T9> > {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<2> > : Array<Array<T0, T1>, Array<T2, T3, T4, T5, T6, T7, T8, T9> > {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<3> > : Array<Array<T0, T1, T2>, Array<T3, T4, T5, T6, T7, T8, T9> > {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<4> > : Array<Array<T0, T1, T2, T3>, Array<T4, T5, T6, T7, T8, T9> > {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<5> > : Array<Array<T0, T1, T2, T3, T4>, Array<T5, T6, T7, T8, T9> > {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<6> > : Array<Array<T0, T1, T2, T3, T4, T5>, Array<T6, T7, T8, T9> > {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<7> > : Array<Array<T0, T1, T2, T3, T4, T5, T6>, Array<T7, T8, T9> > {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<8> > : Array<Array<T0, T1, T2, T3, T4, T5, T6, T7>, Array<T8, T9> > {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<9> > : Array<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8>, Array<T9> > {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArraySplit<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Integer<10> > : Array<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, Array<> > {};


template<typename T>
struct ArrayReverse;

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > : Array<T9, T8, T7, T6, T5, T4, T3, T2, T1, T0> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8> > : Array<T8, T7, T6, T5, T4, T3, T2, T1, T0> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6, T7> > : Array<T7, T6, T5, T4, T3, T2, T1, T0> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct ArrayReverse<Array<T0, T1, T2, T3, T4, T5, T6> > : Array<T6, T5, T4, T3, T2, T1, T0> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct ArrayReverse<Array<T0, T1, T2, T3, T4, T5> > : Array<T5, T4, T3, T2, T1, T0> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
struct ArrayReverse<Array<T0, T1, T2, T3, T4> > : Array<T4, T3, T2, T1, T0> {};

template<typename T0, typename T1, typename T2, typename T3>
struct ArrayReverse<Array<T0, T1, T2, T3> > : Array<T3, T2, T1, T0> {};

template<typename T0, typename T1, typename T2>
struct ArrayReverse<Array<T0, T1, T2> > : Array<T2, T1, T0> {};

template<typename T0, typename T1>
struct ArrayReverse<Array<T0, T1> > : Array<T1, T0> {};

template<typename T0>
struct ArrayReverse<Array<T0> > : Array<T0> {};

template<>
struct ArrayReverse<Array<> > : Array<> {};



template<typename T, typename F, typename M, typename L>
struct ArrayRotate;
// Needs L <= ArraySize<T>


template<typename T, typename F>
struct ArrayRotate<T, F, F, F> : T {};

template<typename T, typename F, typename L>
struct ArrayRotate<T, F, F, L> : T {};

template<typename T, typename F, typename L>
struct ArrayRotate<T, F, L, L> : T {};


template<typename T, typename F, typename M, typename L>
struct ArrayRotate
{
  // Assert F <= M
  // Assert M <= L
  // Assert L <= ArraySize<T>
  // Split into
  // 0..F, F..M, M..L, L..End
  //
  typedef typename ArraySplit<T, F>::type SplitAtFirst; // T0 = 0..F
  typedef typename ArraySplit<typename ArrayIndex<SplitAtFirst, Integer<1> >::type, typename Subtract<M, F>::type>::type SplitAtM; // T0 = F..M
  typedef typename ArraySplit<typename ArrayIndex<SplitAtM, Integer<1> >::type, typename Subtract<L, M>::type>::type SplitAtL; // T0 = M..L, T1 = L..end

  typedef typename ArrayConcat<typename ArrayIndex<SplitAtFirst, Integer<0> >::type, typename ArrayIndex<SplitAtL, Integer<0> >::type>::type A; // 0..F & M..L
  typedef typename ArrayConcat<A, typename ArrayIndex<SplitAtM, Integer<0> >::type>::type B; // 0..F & M..L & F..M
  typedef typename ArrayConcat<B, typename ArrayIndex<SplitAtL, Integer<1> >::type>::type type; // 0..F & M..L & F..M & L..End
};

} // namespace impl

template<typename T, typename Index>
struct ArrayIndex : impl::ArrayIndex<T, Index> {};

template<typename T>
struct ArraySize : impl::ArraySize<T> {};

template<typename T, typename U>
struct ArrayConcat : impl::ArrayConcat<T, U> {};

template<typename T, typename At>
struct ArraySplit : impl::ArraySplit<T, At> {};

template<typename T>
struct ArrayReverse : impl::ArrayReverse<T> {};

template<typename T, typename F, typename M, typename L>
struct ArrayRotate : impl::ArrayRotate<T, F, M, L> {};

template<typename T, typename M>
struct ArrayRotateDefault : impl::ArrayRotate<T, Integer<0>, M, typename ArraySize<T>::type > {};

namespace placeholders {

template<typename Index>
struct Placeholder
{
    typedef Placeholder type;
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
}

namespace impl {

// Type deliberately distinct from ArrayNoArgs so that
// applying < 10 arguments is distinguishable.
struct apply_ignore { typedef apply_ignore type; };

// Check performed on looking up the value of a placeholder in the current
// Apply application parameters
template<typename T>
struct CheckIsNotNoArgument
{
    typedef T type;
};

template<>
struct CheckIsNotNoArgument<apply_ignore>; // leave undefined as binding apply_ignore is an error.

template<typename T, typename Environment>
struct LookupPlaceholder
{
    typedef T type;
};

template<typename Index, typename Environment>
struct LookupPlaceholder<placeholders::Placeholder<Index>, Environment> :
    CheckIsNotNoArgument<typename ArrayIndex<Environment, Index>::type>
{};

// Environment Arity is required when a metafunction class is passed into Apply
// (as opposed to passing in a placeholder expression which can be analysed
// using template class parameter syntax).
template<typename T>
struct EnvironmentArity;

template<>
struct EnvironmentArity<Array<apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore> > : Integer<0> {};

template<typename T0>
struct EnvironmentArity<Array<T0, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore> > : Integer<1> {};

template<typename T0, typename T1>
struct EnvironmentArity<Array<T0, T1, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore> > : Integer<2> {};

template<typename T0, typename T1, typename T2>
struct EnvironmentArity<Array<T0, T1, T2, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore> > : Integer<3> {};

template<typename T0, typename T1, typename T2, typename T3>
struct EnvironmentArity<Array<T0, T1, T2, T3, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore> > : Integer<4> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
struct EnvironmentArity<Array<T0, T1, T2, T3, T4, apply_ignore, apply_ignore, apply_ignore, apply_ignore, apply_ignore> > : Integer<5> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, apply_ignore, apply_ignore, apply_ignore, apply_ignore> > : Integer<6> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, apply_ignore, apply_ignore, apply_ignore> > : Integer<7> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, T7, apply_ignore, apply_ignore> > : Integer<8> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, apply_ignore> > : Integer<9> {};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct EnvironmentArity<Array<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> > : Integer<10> {};


template<typename T, typename Environment>
struct BindArguments
{
    typedef T type;
};

template<template<typename> class T, typename P0, typename Environment>
struct BindArguments<T<P0>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type>
{};

template<template<typename, typename> class T, typename P0, typename P1, typename Environment>
struct BindArguments<T<P0, P1>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type>
{};

template<template<typename, typename, typename> class T, typename P0, typename P1, typename P2, typename Environment>
struct BindArguments<T<P0, P1, P2>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type>
{};

template<template<typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename Environment>
struct BindArguments<T<P0, P1, P2, P3>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type>
{};

template<template<typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename Environment>
struct BindArguments<T<P0, P1, P2, P3, P4>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type>
{};

template<template<typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename Environment>
struct BindArguments<T<P0, P1, P2, P3, P4, P5>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type>
{};

template<template<typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename Environment>
struct BindArguments<T<P0, P1, P2, P3, P4, P5, P6>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type,
      typename LookupPlaceholder<P6, Environment>::type>
{};

template<template<typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename Environment>
struct BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type,
      typename LookupPlaceholder<P6, Environment>::type,
      typename LookupPlaceholder<P7, Environment>::type>
{};

template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename Environment>
struct BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8>, Environment> :
    T<typename LookupPlaceholder<P0, Environment>::type,
      typename LookupPlaceholder<P1, Environment>::type,
      typename LookupPlaceholder<P2, Environment>::type,
      typename LookupPlaceholder<P3, Environment>::type,
      typename LookupPlaceholder<P4, Environment>::type,
      typename LookupPlaceholder<P5, Environment>::type,
      typename LookupPlaceholder<P6, Environment>::type,
      typename LookupPlaceholder<P7, Environment>::type,
      typename LookupPlaceholder<P8, Environment>::type>
{};

template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename Environment>
struct BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9>, Environment> :
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
{};

// This is the magic of the Apply mechanism. The assumption is that the Airty of the
// environment is the arity of the metafunction class passed into it. Through this
// binding we obtain a placeholder expression that can be passed to BindArguments.
template<typename T, typename EnvironmentAirty>
struct AddPlaceholders;

template<typename T>
struct AddPlaceholders<T, Integer<0> >
{
    typedef T type;
};

template<typename T>
struct AddPlaceholders<T, Integer<1> >
{
    typedef typename T::template apply<placeholders::_0> type;
};

template<typename T>
struct AddPlaceholders<T, Integer<2> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1> type;
};

template<typename T>
struct AddPlaceholders<T, Integer<3> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2> type;
};

template<typename T>
struct AddPlaceholders<T, Integer<4> >
{
  typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3> type;
};

template<typename T>
struct AddPlaceholders<T, Integer<5> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4> type;
};

template<typename T>
struct AddPlaceholders<T, Integer<6> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5> type;
};

template<typename T>
struct AddPlaceholders<T, Integer<7> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6> type;
};

template<typename T>
struct AddPlaceholders<T, Integer<8> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6, placeholders::_7> type;
};

template<typename T>
struct AddPlaceholders<T, Integer<9> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6, placeholders::_7, placeholders::_8> type;
};

template<typename T>
struct AddPlaceholders<T, Integer<10> >
{
    typedef typename T::template apply<placeholders::_0, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4,
      placeholders::_5, placeholders::_6, placeholders::_7, placeholders::_8, placeholders::_9> type;
};

// Metafunction Class passed in, so add placeholders to nested template class apply
// and bind the Environment. Note Apply_Impl and BindArguments are different metafunctions to prevent
// an infinte loop when the Environment is empty
template<typename T, typename Environment>
struct Apply_Impl :
    BindArguments<typename AddPlaceholders<T, typename EnvironmentArity<Environment>::type >::type, Environment>
{};

template<template<typename> class T, typename P0, typename Environment>
struct Apply_Impl<T<P0>, Environment> : BindArguments<T<P0>, Environment>
{};

template<template<typename, typename> class T, typename P0, typename P1, typename Environment>
struct Apply_Impl<T<P0, P1>, Environment> : BindArguments<T<P0, P1>, Environment>
{};

template<template<typename, typename, typename> class T, typename P0, typename P1, typename P2, typename Environment>
struct Apply_Impl<T<P0, P1, P2>, Environment> : BindArguments<T<P0, P1, P2>, Environment>
{};

template<template<typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename Environment>
struct Apply_Impl<T<P0, P1, P2, P3>, Environment> : BindArguments<T<P0, P1, P2, P3>, Environment>
{};

template<template<typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename Environment>
struct Apply_Impl<T<P0, P1, P2, P3, P4>, Environment> : BindArguments<T<P0, P1, P2, P3, P4>, Environment>
{};

template<template<typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename Environment>
struct Apply_Impl<T<P0, P1, P2, P3, P4, P5>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5>, Environment>
{};

template<template<typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename Environment>
struct Apply_Impl<T<P0, P1, P2, P3, P4, P5, P6>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6>, Environment>
{};

template<template<typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename Environment>
struct Apply_Impl<T<P0, P1, P2, P3, P4, P5, P6, P7>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7>, Environment>
{};


template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename Environment>
struct Apply_Impl<T<P0, P1, P2, P3, P4, P5, P6, P7, P8>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8>, Environment>
{};


template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename, typename> class T, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename Environment>
struct Apply_Impl<T<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9>, Environment> : BindArguments<T<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9>, Environment>
{};

} // namespace impl

template<typename T, typename P0=impl::apply_ignore, typename P1=impl::apply_ignore, typename P2=impl::apply_ignore, typename P3=impl::apply_ignore, typename P4=impl::apply_ignore, typename P5=impl::apply_ignore, typename P6=impl::apply_ignore, typename P7=impl::apply_ignore, typename P8=impl::apply_ignore, typename P9=impl::apply_ignore>
struct Apply : impl::Apply_Impl<T, Array<P0, P1, P2, P3, P4, P5, P6, P7, P8, P9> > {};

// Environment must be in the fom of an array where 0..N are parameters and the rest are apply_ignore
// See RationaliseApplyArray for how to remove ArrayNoArg and the like.
template<typename T, typename Environment>
struct Apply_Environment : impl::Apply_Impl<T, Environment> {};


namespace impl {

template<typename T, typename Fun>
struct ApplyIfNotArrayNoArg : Apply<Fun, T>
{};

template<typename Fun>
struct ApplyIfNotArrayNoArg<ArrayNoArg, Fun> : ArrayNoArg {};

template<typename T, typename Fun>
struct ArrayTransform_Impl
{
    typedef Array<typename ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<0> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<1> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<2> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<3> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<4> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<5> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<6> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<7> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<8> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg<typename ArrayIndex<T, Integer<9> >::type, Fun>::type> type;
};


template<typename T0, typename T1, typename Fun>
struct ApplyIfNotArrayNoArg2 : Apply<Fun, T0, T1>
{};

template<typename Fun>
struct ApplyIfNotArrayNoArg2<ArrayNoArg, ArrayNoArg, Fun> : ArrayNoArg {};


template<typename T, typename U, typename Fun>
struct ArrayZip_Impl
{
    typedef Array<typename ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<0> >::type,
                                                 typename ArrayIndex<U, Integer<0> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<1> >::type,
                                                 typename ArrayIndex<U, Integer<1> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<2> >::type,
                                                 typename ArrayIndex<U, Integer<2> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<3> >::type,
                                                 typename ArrayIndex<U, Integer<3> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<4> >::type,
                                                 typename ArrayIndex<U, Integer<4> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<5> >::type,
                                                 typename ArrayIndex<U, Integer<5> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<6> >::type,
                                                 typename ArrayIndex<U, Integer<6> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<7> >::type,
                                                 typename ArrayIndex<U, Integer<7> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<8> >::type,
                                                 typename ArrayIndex<U, Integer<8> >::type, Fun>::type,
                  typename ApplyIfNotArrayNoArg2<typename ArrayIndex<T, Integer<9> >::type,
                                                 typename ArrayIndex<U, Integer<9> >::type, Fun>::type> type;
};

} // namespace impl

template<typename T, typename Fun>
struct ArrayTransform : impl::ArrayTransform_Impl<T, Fun> {};

template<typename T, typename U, typename Fun>
struct ArrayZip : impl::ArrayZip_Impl<T, U, Fun> {};

namespace impl {

template<typename T, typename From, typename To>
struct RationaliseApplyArrayConvert
{
    typedef T type;
};

template<typename From, typename To>
struct RationaliseApplyArrayConvert<From, From, To>
{
    typedef To type;
};

template<typename T, typename ToRemove>
struct RationaliseApplyArray
{
    // Did not use ArrayTransform as this skips over ArrayNoArg elements, which is not what this metafunction should do.
    typedef Array<typename RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<0> >::type, ToRemove, impl::apply_ignore>::type,
                  typename RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<1> >::type, ToRemove, impl::apply_ignore>::type,
                  typename RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<2> >::type, ToRemove, impl::apply_ignore>::type,
                  typename RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<3> >::type, ToRemove, impl::apply_ignore>::type,
                  typename RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<4> >::type, ToRemove, impl::apply_ignore>::type,
                  typename RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<5> >::type, ToRemove, impl::apply_ignore>::type,
                  typename RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<6> >::type, ToRemove, impl::apply_ignore>::type,
                  typename RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<7> >::type, ToRemove, impl::apply_ignore>::type,
                  typename RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<8> >::type, ToRemove, impl::apply_ignore>::type,
                  typename RationaliseApplyArrayConvert<typename ArrayIndex<T, Integer<9> >::type, ToRemove, impl::apply_ignore>::type> type;
};

} // namespace impl

} // namespace intro

#endif
