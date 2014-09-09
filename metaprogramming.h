#ifndef INCLUDED_METAPROGRAMMING
#define INCLUDED_METAPROGRAMMING

namespace intro {

struct Empty { typedef Empty type; };

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

template<typename T, typename Tag>
struct Ref
{
    typedef Ref type;
    typedef true_type IntrospectionEnabled;
    typedef T* IntrospectionItem0;
    T* m0; // hold by pointer to make the type regular (assignment is enabled).

    // Need implict conversion operator to allow
    // storage conversion to happen without another function call
    operator T&() { return *m0; }
    operator T const&() const { return *m0; }

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
template<typename T, typename Tag>
inline Ref<T, Tag> make_ref(T& x)
{
    return Ref<T, Tag>::make(x);
}

template<typename T>
inline Ref<T, DefaultTag> make_ref(T& x)
{
    return Ref<T, DefaultTag>::make(x);
}

namespace impl {

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

template<typename T, typename Tag>
struct decay_ref_impl<Ref<T, Tag> >
{
    typedef T& type;
};

} // namespace impl


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

struct GetUnderlyingType
{
    template<typename T>
    struct apply : get_underlying_type<T>
    {};
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

struct DecayRef
{
    template<typename T>
    struct apply : decay_ref<T>
    {};
};

template<typename T0=Empty, typename T1=Empty, typename T2=Empty, typename T3=Empty, typename T4=Empty, typename T5=Empty, typename T6=Empty, typename T7=Empty, typename T8=Empty, typename T9=Empty>
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

template<typename T, typename Fun>
struct ArrayTransform
{
    typedef Array<typename Fun::template apply<typename ArrayIndex<T, Integer<0> >::type>::type,
                  typename Fun::template apply<typename ArrayIndex<T, Integer<1> >::type>::type,
                  typename Fun::template apply<typename ArrayIndex<T, Integer<2> >::type>::type,
                  typename Fun::template apply<typename ArrayIndex<T, Integer<3> >::type>::type,
                  typename Fun::template apply<typename ArrayIndex<T, Integer<4> >::type>::type,
                  typename Fun::template apply<typename ArrayIndex<T, Integer<5> >::type>::type,
                  typename Fun::template apply<typename ArrayIndex<T, Integer<6> >::type>::type,
                  typename Fun::template apply<typename ArrayIndex<T, Integer<7> >::type>::type,
                  typename Fun::template apply<typename ArrayIndex<T, Integer<8> >::type>::type,
                  typename Fun::template apply<typename ArrayIndex<T, Integer<9> >::type>::type> type;


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

// Note that applying Fun to Empty should return Empty
template<typename T, typename Fun>
struct ArrayTransform : impl::ArrayTransform<T, Fun> {};

} // namespace intro

#endif
