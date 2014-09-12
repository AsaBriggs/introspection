#include <cassert>
#include "storage.h"
#include "function_signatures.h"

namespace intro {
namespace {

// Done a copy-paste job of the essence of the Boost static assert scheme.
// Note design of the static assert mechanism copied from BOOST MPL which carries the
// following copyright
//
// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

struct failed {};

// The trick of the assert scheme is to use this type to extract the Predicate type.
template<typename Pred>
struct extract_assert_pred;

template<typename Pred>
struct extract_assert_pred<void(Pred)> { typedef Pred type; };

template<bool C> struct assert { typedef assert type; };

template<typename Pred>
struct eval_assert {
    typedef typename extract_assert_pred<Pred>::type P;
    typedef typename if_<typename P::type,
        assert<false>,
        failed ************ not_<P>::************
    >::type type;
};

template<typename Pred>
struct eval_assert_not {
    typedef typename extract_assert_pred<Pred>::type P;
    typedef typename if_<typename not_<typename P::type>::type,
        assert<false>,
        failed ************ not_<P>::************
    >::type type;
};

template<typename T>
T make_T();

template< bool C >
int assertion_failed( typename assert<C>::type );

#define CAT(x, y) CAT_(x, y)
#define CAT_(x, y) x ## y

// Note that this mechanism is limited to just one assert per line, for simplicity.
#define STATIC_ASSERT(Pred) enum { CAT(TEST,__LINE__) = sizeof(assertion_failed<false>(make_T<typename eval_assert<void Pred>::type>())) }
#define STATIC_ASSERT2(Pred) enum { CAT(TEST, __LINE__) = sizeof(assertion_failed<false>(make_T<eval_assert<void Pred>::type>())) }

#define STATIC_ASSERT_NOT(Pred) enum { CAT(TEST,__LINE__) = sizeof(assertion_failed<false>(make_T<typename eval_assert_not<void Pred>::type>())) }
#define STATIC_ASSERT_NOT2(Pred) enum { CAT(TEST, __LINE__) = sizeof(assertion_failed<false>(make_T<eval_assert_not<void Pred>::type>())) }

// End of Boost MPL code.

STATIC_ASSERT2((true_type));

#ifdef INTROSPECTION_COMPILATION_FAILURE_TESTS
STATIC_ASSERT2((false_type));
STATIC_ASSERT_NOT2((true_type));
#endif

#define TEST(x) assert((x))

const char EXPECTED_VALUE = 'a';
const char UNEXPECTED_VALUE = 'b';

// All distinct types
typedef Array<bool, unsigned char, signed char, char, short, unsigned short, int, unsigned int, long, unsigned long> TestArray;
typedef Array<unsigned long, long, unsigned int, int, unsigned short, short, char, signed char, unsigned char, bool> ReversedTestArray;

typedef Array<> Bool0;
typedef Array<bool> Bool1;
typedef Array<bool, bool> Bool2;
typedef Array<bool, bool, bool> Bool3;
typedef Array<bool, bool, bool, bool> Bool4;
typedef Array<bool, bool, bool, bool, bool> Bool5;
typedef Array<bool, bool, bool, bool, bool, bool> Bool6;
typedef Array<bool, bool, bool, bool, bool, bool, bool> Bool7;
typedef Array<bool, bool, bool, bool, bool, bool, bool, bool> Bool8;
typedef Array<bool, bool, bool, bool, bool, bool, bool, bool, bool> Bool9;
typedef Array<bool, bool, bool, bool, bool, bool, bool, bool, bool, bool> Bool10;
typedef Array<Bool0, Bool1, Bool2, Bool3, Bool4, Bool5, Bool6, Bool7, Bool8, Bool9> BoolArray;

template<typename LHSIndex, typename RHSIndex>
void test_array_concat2()
{
  // Awkward as we need 1 more array than an array can contain
  typedef typename Min<Integer<10>, typename Add<LHSIndex, RHSIndex>::type>::type ConcatArrayLength;
  typedef typename eval_if<is_same<Integer<10>, ConcatArrayLength>, Bool10, ArrayIndex<BoolArray, ConcatArrayLength> >::type ExpectedArray;

  STATIC_ASSERT(( is_same<ExpectedArray,
                         typename ArrayConcat<typename ArrayIndex<BoolArray, LHSIndex>::type,
	                 typename ArrayIndex<BoolArray, RHSIndex>::type>::type> ));
}

template<typename LHSIndex>
void test_array_concat()
{
  test_array_concat2<LHSIndex, Integer<0> >();
  test_array_concat2<LHSIndex, Integer<1> >();
  test_array_concat2<LHSIndex, Integer<2> >();
  test_array_concat2<LHSIndex, Integer<3> >();
  test_array_concat2<LHSIndex, Integer<4> >();
  test_array_concat2<LHSIndex, Integer<5> >();
  test_array_concat2<LHSIndex, Integer<6> >();
  test_array_concat2<LHSIndex, Integer<7> >();
  test_array_concat2<LHSIndex, Integer<8> >();
  test_array_concat2<LHSIndex, Integer<9> >();
}

void test_array_split()
{
  // Use TestArray as at all indices have different types
  STATIC_ASSERT2(( is_same<Array<Array<>,
                      TestArray>,
			     ArraySplit<TestArray, Integer<0> >::type> ));

  STATIC_ASSERT2(( is_same<Array<Array<bool>,
                      Array<unsigned char, signed char, char, short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<1> >::type> ));

  STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char>,
                Array<signed char, char, short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<2> >::type> ));

  STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char>,
                      Array<char, short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<3> >::type> ));

  STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char>,
                      Array<short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<4> >::type> ));

  STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char,short>,
                      Array<unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<5> >::type> ));

  STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short>,
                      Array<int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<6> >::type> ));

  STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short, int>,
                      Array<unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<7> >::type> ));

  STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short, int, unsigned int>,
                      Array<long, unsigned long> >,
        ArraySplit<TestArray, Integer<8> >::type> ));

  STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short, int, unsigned int, long>,
                      Array<unsigned long> >,
        ArraySplit<TestArray, Integer<9> >::type> ));

  STATIC_ASSERT2(( is_same<Array<TestArray,
                      Array<> >,
        ArraySplit<TestArray, Integer<10> >::type> ));
}

template<typename Length>
void test_array_reverse2()
{
  typedef typename ArraySplit<TestArray, Length>::type SplitArray;
  typedef typename ArrayReverse<typename ArrayIndex<SplitArray, Integer<0> >::type>::type ReversedFirst;
  typedef typename ArrayReverse<typename ArrayIndex<SplitArray, Integer<1> >::type>::type ReversedSecond;
  typedef typename ArrayConcat<ReversedSecond, ReversedFirst>::type Result;
  STATIC_ASSERT(( is_same<ReversedTestArray, Result> ));
}

void test_array_reverse()
{
  test_array_reverse2<Integer<0> >();
  test_array_reverse2<Integer<1> >();
  test_array_reverse2<Integer<2> >();
  test_array_reverse2<Integer<3> >();
  test_array_reverse2<Integer<4> >();
  test_array_reverse2<Integer<5> >();
  test_array_reverse2<Integer<6> >();
  test_array_reverse2<Integer<7> >();
  test_array_reverse2<Integer<8> >();
  test_array_reverse2<Integer<9> >();
  test_array_reverse2<Integer<10> >();
}

void test_array_rotate()
{
  typedef Array<bool, char, short, unsigned short, unsigned char, signed char, int, unsigned int, long, unsigned long> Expected;
  // F = 1
  // M = 3
  // L = 6
  STATIC_ASSERT2(( is_same<Expected, ArrayRotate<TestArray, Integer<1>, Integer<3>, Integer<6> >::type> ));

  typedef Array<unsigned short, int, unsigned int, long, unsigned long, bool, unsigned char, signed char, char, short> Expected2;
  // rotate test array about index 5, i.e. from bool up to but not including unsigned short is rotated
  STATIC_ASSERT2(( is_same<Expected2, ArrayRotateDefault<TestArray, Integer<5> >::type > ));
}

struct AddOne
{
  template<typename T>
  struct apply : Add<T, Integer<1> > {};
};

void test_array_transform()
{
  typedef Array<Integer<0>, Integer<1>, Integer<2>, Integer<3>, Integer<4>, Integer<5>, Integer<6>, Integer<7>, Integer<8>, Integer<9> > Integers;

  typedef Array<Integer<1>, Integer<2>, Integer<3>, Integer<4>, Integer<5>, Integer<6>, Integer<7>, Integer<8>, Integer<9>, Integer<10> > Expected;

  STATIC_ASSERT2(( is_same<ArrayTransform<Integers, AddOne>::type, Expected> ));
  STATIC_ASSERT2(( is_same<ArrayTransform<Integers, Add<placeholders::_0, Integer<1> > >::type, Expected> ));
}

struct AddTogether
{
  template<typename T, typename U>
  struct apply : Add<T, U> {};
};

void test_array_zip()
{
  typedef Array<Integer<0>, Integer<1>, Integer<2>, Integer<3>, Integer<4>, Integer<5>, Integer<6>, Integer<7>, Integer<8>, Integer<9> > Integers;
  typedef Array<Integer<1>, Integer<2>, Integer<3>, Integer<4>, Integer<5>, Integer<6>, Integer<7>, Integer<8>, Integer<9>, Integer<10> > MoreIntegers;
  typedef Array<Integer<1>, Integer<3>, Integer<5>, Integer<7>, Integer<9>, Integer<11>, Integer<13>, Integer<15>, Integer<17>, Integer<19> > Expected;

  STATIC_ASSERT2(( is_same<ArrayZip<Integers, MoreIntegers, AddTogether>::type, Expected> ));
  STATIC_ASSERT2(( is_same<ArrayZip<Integers, MoreIntegers, Add<placeholders::_0, placeholders::_1> >::type, Expected> ));
}

typedef Array<placeholders::_9, placeholders::_8, placeholders::_7, placeholders::_6, placeholders::_5, placeholders::_4, placeholders::_3, placeholders::_2, placeholders::_1, placeholders::_0> ReversingArray;

struct ArrayReverser
{
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
  struct apply : Array<T9, T8, T7, T6, T5, T4, T3, T2, T1, T0> {};
};

void test_Apply()
{
  STATIC_ASSERT2(( is_same<empty_type<int>, Apply<empty_type<int> >::type> ));
  STATIC_ASSERT2(( is_same<empty_type<int>, Apply<empty_type<int>, short, double, char, float, void >::type> ));

  STATIC_ASSERT2(( is_same<empty_type<bool>, Apply<empty_type<placeholders::_0>, bool, int, long, float, short>::type> ));
  STATIC_ASSERT2(( is_same<empty_type<int>, Apply<empty_type<placeholders::_1>, bool, int, long, float, short>::type> ));
  STATIC_ASSERT2(( is_same<empty_type<long>, Apply<empty_type<placeholders::_2>, bool, int, long, float, short>::type> ));
  STATIC_ASSERT2(( is_same<empty_type<float>, Apply<empty_type<placeholders::_3>, bool, int, long, float, short>::type> ));
  STATIC_ASSERT2(( is_same<empty_type<short>, Apply<empty_type<placeholders::_4>, bool, int, long, float, short>::type> ));

  STATIC_ASSERT2(( is_same<Integer<3>, Apply<AddTogether, Integer<1>, Integer<2> >::type> ));

  STATIC_ASSERT2(( is_same<Array<>, Apply<Array<> >::type> ));
  STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int>::type> ));
  STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int>::type> ));
  STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int>::type> ));
  STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int>::type> ));
  STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int>::type> ));
  STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int, int>::type> ));
  STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int, int, int>::type> ));
  STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int, int, int, int>::type> ));
  STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int, int, int, int, int>::type> ));
  STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int, int, int, int, int, int>::type> ));

  STATIC_ASSERT2(( is_same<ReversedTestArray, Apply_Environment<ReversingArray, TestArray>::type> ));
  STATIC_ASSERT2(( is_same<ReversedTestArray, Apply_Environment<ArrayReverser, TestArray>::type> ));

#ifdef INTROSPECTION_COMPILATION_FAILURE_TESTS
  typedef Apply<empty_type<placeholders::_0> >::type insufficientArguments0;
  typedef Apply<empty_type<placeholders::_1> >::type insufficientArguments1;
  typedef Apply<empty_type<placeholders::_2> >::type insufficientArguments2;
  typedef Apply<empty_type<placeholders::_3> >::type insufficientArguments3;
  typedef Apply<empty_type<placeholders::_4> >::type insufficientArguments4;

  typedef Apply<empty_type<placeholders::_1>, int>::type insufficientArguments5;
  typedef Apply<empty_type<placeholders::_2>, int>::type insufficientArguments6;
  typedef Apply<empty_type<placeholders::_3>, int>::type insufficientArguments7;
  typedef Apply<empty_type<placeholders::_4>, int>::type insufficientArguments8;

  typedef Apply<empty_type<placeholders::_2>, int, int>::type insufficientArguments9;
  typedef Apply<empty_type<placeholders::_3>, int, int>::type insufficientArguments10;
  typedef Apply<empty_type<placeholders::_4>, int, int>::type insufficientArguments11;

  typedef Apply<empty_type<placeholders::_3>, int, int, int>::type insufficientArguments12;
  typedef Apply<empty_type<placeholders::_4>, int, int, int>::type insufficientArguments13;

  typedef Apply<empty_type<placeholders::_4>, int, int, int, int>::type insufficientArguments14;
#endif
}

struct Parent {};
struct Child : Parent {};

struct ToType {};

struct FromType
{
  operator ToType() const;
};

struct FromType2
{
  operator ToType const&() const;
};

struct ImplicitConvertingConstructor
{
  ImplicitConvertingConstructor(int) {}
};

struct ExplicitConvertingConstructor
{
  explicit ExplicitConvertingConstructor(int) {}
};

void test_is_convertible()
{
  STATIC_ASSERT2(( is_convertible<int, long> ));
  STATIC_ASSERT2(( is_convertible<int&, int const&> ));
  STATIC_ASSERT2(( is_convertible<float, double> ));
  STATIC_ASSERT_NOT2((is_convertible<float, double&> ));

  STATIC_ASSERT2(( is_convertible<float (&)[10], float*> ));
  STATIC_ASSERT2(( is_convertible<float (&)[], float*> ));
  STATIC_ASSERT2(( is_convertible<float (&)[], float const*> ));

  STATIC_ASSERT_NOT2(( is_convertible<Parent*, Child*> ));
  STATIC_ASSERT2(( is_convertible<Child*, Parent*> ));
  STATIC_ASSERT2(( is_convertible<Child*, Parent const*> ));

  STATIC_ASSERT2(( is_convertible<FromType, ToType> ));
  STATIC_ASSERT2(( is_convertible<FromType, ToType const&> ));

  STATIC_ASSERT2(( is_convertible<FromType2, ToType> ));
  STATIC_ASSERT_NOT2(( is_convertible<FromType2, ToType&> ));
  STATIC_ASSERT2(( is_convertible<FromType2, ToType const&> ));

  STATIC_ASSERT2(( is_convertible<int, ImplicitConvertingConstructor> ));
  STATIC_ASSERT2(( is_convertible<int const&, ImplicitConvertingConstructor> ));
  STATIC_ASSERT2(( is_convertible<int const volatile&, ImplicitConvertingConstructor> ));

  STATIC_ASSERT_NOT2(( is_convertible<int, ExplicitConvertingConstructor> ));
}

struct AStruct {};
class AClass {};
union AUnion { int a; };

void test_is_struct_class_or_union()
{
  STATIC_ASSERT2(( IsStructClassOrUnion<AStruct> ));
  STATIC_ASSERT2(( IsStructClassOrUnion<AClass> ));
  STATIC_ASSERT2(( IsStructClassOrUnion<AUnion> ));
  STATIC_ASSERT_NOT2(( IsStructClassOrUnion<void> ));
  STATIC_ASSERT_NOT2(( IsStructClassOrUnion<bool> ));
  STATIC_ASSERT_NOT2(( IsStructClassOrUnion<double> ));
  STATIC_ASSERT_NOT2(( IsStructClassOrUnion<double&> ));
  STATIC_ASSERT_NOT2(( IsStructClassOrUnion<double&> ));
  STATIC_ASSERT_NOT2(( IsStructClassOrUnion<double*> ));
  STATIC_ASSERT_NOT2(( IsStructClassOrUnion<int AUnion::*> ));
  STATIC_ASSERT_NOT2(( IsStructClassOrUnion<void(*)()> ));
  STATIC_ASSERT_NOT2(( IsStructClassOrUnion<void(AUnion::*)()> ));
  STATIC_ASSERT_NOT2(( IsStructClassOrUnion<void(AUnion::*)(int)const> ));
}

void test_boolean_types()
{
  STATIC_ASSERT2(( true_type ));
  STATIC_ASSERT_NOT2(( false_type ));
  // Tst runtime value
  TEST(true_type());
  TEST(!false_type());
}

void test_make_ref()
{
  int x = 0;
  Ref<int> y = make_ref(x);
  TEST(y.m0 == &x);
}

void test_integer_operations()
{
  TEST( Integer<123>() == 123 );

  STATIC_ASSERT2(( is_same<Integer<1>, Successor<Integer<0> >::type > ));
  STATIC_ASSERT2(( is_same<Integer<4>, Successor<Integer<3> >::type > ));
  STATIC_ASSERT2(( is_same<Integer<-2>, Successor<Integer<-3> >::type > ));

  STATIC_ASSERT2(( is_same<Integer<-1>, Predecessor<Integer<0> >::type > ));
  STATIC_ASSERT2(( is_same<Integer<2>, Predecessor<Integer<3> >::type > ));
  STATIC_ASSERT2(( is_same<Integer<-4>, Predecessor<Integer<-3> >::type > ));

  STATIC_ASSERT2(( is_same<Integer<0>, Min<Integer<0>, Integer<2> >::type> ));
  STATIC_ASSERT2(( is_same<Integer<3>, Min<Integer<4>, Integer<3> >::type> ));
  STATIC_ASSERT2(( is_same<Integer<-5>, Min<Integer<-5>, Integer<-3> >::type> ));

  STATIC_ASSERT2(( is_same<Integer<-5>, Subtract<Integer<0>, Integer<5> >::type > ));
  STATIC_ASSERT2(( is_same<Integer<42>, Subtract<Integer<47>, Integer<5> >::type > ));

  STATIC_ASSERT2(( is_same<Integer<-5>, Add<Integer<0>, Integer<-5> >::type > ));
  STATIC_ASSERT2(( is_same<Integer<42>, Add<Integer<37>, Integer<5> >::type > ));
}

void test_boolean_operations()
{
  STATIC_ASSERT_NOT2(( not_<true_type> ));
  STATIC_ASSERT2(( not_<false_type> ));

  STATIC_ASSERT_NOT2(( or_<false_type, false_type> ));
  STATIC_ASSERT2(( or_<false_type, true_type> ));
  STATIC_ASSERT2(( or_<true_type, false_type> ));
  STATIC_ASSERT2(( or_<true_type, true_type> ));
  STATIC_ASSERT_NOT2(( or_<false_type, false_type, false_type> ));
  STATIC_ASSERT2(( or_<false_type, true_type, true_type> ));
  STATIC_ASSERT2(( or_<true_type, false_type, true_type> ));
  STATIC_ASSERT2(( or_<true_type, true_type, false_type> ));
  STATIC_ASSERT2(( or_<true_type, true_type, true_type> ));

  STATIC_ASSERT_NOT2(( and_<false_type, false_type> ));
  STATIC_ASSERT_NOT2(( and_<false_type, true_type> ));
  STATIC_ASSERT_NOT2(( and_<true_type, false_type> ));
  STATIC_ASSERT2(( and_<true_type, true_type> ));
  STATIC_ASSERT_NOT2(( and_<false_type, false_type, false_type> ));
  STATIC_ASSERT_NOT2(( and_<false_type, false_type, true_type> ));
  STATIC_ASSERT_NOT2(( and_<false_type, true_type, false_type> ));
  STATIC_ASSERT_NOT2(( and_<true_type, false_type, false_type> ));
  STATIC_ASSERT_NOT2(( and_<false_type, true_type, true_type> ));
  STATIC_ASSERT_NOT2(( and_<true_type, false_type, true_type> ));
  STATIC_ASSERT_NOT2(( and_<true_type, true_type, false_type> ));
  STATIC_ASSERT2(( and_<true_type, true_type, true_type> ));
}

template<typename T>
typename enable_if<is_same<T, int>, char>::type enable_if_test() { return EXPECTED_VALUE; }

template<typename T>
typename enable_if<not_<is_same<T, int> >, char>::type enable_if_test() { return UNEXPECTED_VALUE; }

template<typename T>
typename disable_if<is_same<T, int>, char>::type disable_if_test() { return UNEXPECTED_VALUE; }

template<typename T>
typename disable_if<not_<is_same<T, int> >, char>::type disable_if_test() { return EXPECTED_VALUE; }

void test_enable_disable_if()
{
  char test = enable_if_test<int>();
  TEST(EXPECTED_VALUE == test);

  char test2 = disable_if_test<int>();
  TEST(EXPECTED_VALUE == test2);
}
void test_is_reference()
{
  STATIC_ASSERT_NOT2(( is_reference<int> ));
  STATIC_ASSERT2(( is_reference<int&> ));
  STATIC_ASSERT2(( is_reference<int(&)[2]> ));
  STATIC_ASSERT2(( is_reference<int(&)[]> ));
}

void test_is_same()
{
  STATIC_ASSERT2(( is_same<int, identity_type<identity_type<int> >::type > ));

  STATIC_ASSERT2(( is_same<if_<true_type, int, void>::type, int> ));
  STATIC_ASSERT2(( is_same<if_<false_type, void, int>::type, int> ));

  STATIC_ASSERT2(( is_same<eval_if<true_type, identity_type<int>, void>::type, int> ));
  STATIC_ASSERT2(( is_same<eval_if<false_type, void, identity_type<int> >::type, int> ));

  STATIC_ASSERT2(( is_same<make_const_ref<int>::type, int const&> ));
  STATIC_ASSERT2(( is_same<make_const_ref<int const>::type, int const&> ));
  STATIC_ASSERT2(( is_same<make_const_ref<int const&>::type, int const&> ));
  STATIC_ASSERT2(( is_same<make_const_ref<int &>::type, int const&> ));

  STATIC_ASSERT2(( is_same<make_const_ref<int volatile >::type, int volatile const&> ));
  STATIC_ASSERT2(( is_same<make_const_ref<int volatile const>::type, int volatile const&> ));
  STATIC_ASSERT2(( is_same<make_const_ref<int volatile const&>::type, int volatile const&> ));
  STATIC_ASSERT2(( is_same<make_const_ref<int volatile &>::type, int volatile const&> ));
}

void test_deduce_input_type()
{
  STATIC_ASSERT2(( is_same<int&, deduce_input_type<int&>::type > ));
  STATIC_ASSERT2(( is_same<int, deduce_input_type<int const&>::type > ));
  STATIC_ASSERT2(( is_same<int, deduce_input_type<int>::type > ));
}

void test_parameter_type()
{
  STATIC_ASSERT2(( is_same<parameter_type<int>::type, int const&> ));
  STATIC_ASSERT2(( is_same<parameter_type<int&>::type, int&> ));
}

void test_underlying_ref_swap()
{
  STATIC_ASSERT2(( is_same<underlying_type<int>::type, int> ));

  STATIC_ASSERT2(( is_same<get_underlying_type<int>::type, int> ));
  {
    int a = 0 ;
    TEST(&a == &get_underlying_ref(a));
  }

  {
    int a = 1;
    int b = 2;

    swap_basic(a, b);
    TEST(1 == b);
    TEST(2 == a);

    swap(a, b);
    TEST(1 == a);
    TEST(2 == b);
  }
}

void test_logical_operations()
{
  TEST((OperatorEquals<int>()(1, 1)));
  TEST(!(OperatorEquals<int>()(1, 2)));

  TEST(!(OperatorLessThan<int>()(1, 1)));
  TEST((OperatorLessThan<int>()(1, 2)));
  TEST(!(OperatorLessThan<int>()(2, 1)));

  TEST((equal<int>()(1, 1)));
  TEST(!(equal<int>()(1, 2)));

  TEST(!(less<int>()(1, 1)));
  TEST((less<int>()(1, 2)));
  TEST(!(less<int>()(2, 1)));
}

void test_decay_ref()
{
  STATIC_ASSERT2(( is_same<decay_ref<int>::type, int> ));
  STATIC_ASSERT2(( is_same<decay_ref<int&>::type, int&> ));
  STATIC_ASSERT2(( is_same<decay_ref<int const&>::type, int const&> ));
  STATIC_ASSERT2(( is_same<decay_ref<Ref<int> >::type, int&> ));
  STATIC_ASSERT2(( is_same<decay_ref<Ref<int const> >::type, int const&> ));
}
void test_Array()
{
  // Tests the array is self-evaluating
  STATIC_ASSERT2(( is_same<TestArray, TestArray::type> ));

#define ARRAY_INDEX_TEST(n, X) STATIC_ASSERT2(( is_same<ArrayIndex<TestArray, Integer<n> >::type, X> ))
  ARRAY_INDEX_TEST(0, bool);
  ARRAY_INDEX_TEST(1, unsigned char);
  ARRAY_INDEX_TEST(2, signed char);
  ARRAY_INDEX_TEST(3, char);
  ARRAY_INDEX_TEST(4, short);
  ARRAY_INDEX_TEST(5, unsigned short);
  ARRAY_INDEX_TEST(6, int);
  ARRAY_INDEX_TEST(7, unsigned int);
  ARRAY_INDEX_TEST(8, long);
  ARRAY_INDEX_TEST(9, unsigned long);
#undef ARRAY_INDEX_TEST

  STATIC_ASSERT2(( is_same<Integer<0>, ArraySize<Bool0>::type> ));
  STATIC_ASSERT2(( is_same<Integer<1>, ArraySize<Bool1>::type> ));
  STATIC_ASSERT2(( is_same<Integer<2>, ArraySize<Bool2>::type> ));
  STATIC_ASSERT2(( is_same<Integer<3>, ArraySize<Bool3>::type> ));
  STATIC_ASSERT2(( is_same<Integer<4>, ArraySize<Bool4>::type> ));
  STATIC_ASSERT2(( is_same<Integer<5>, ArraySize<Bool5>::type> ));
  STATIC_ASSERT2(( is_same<Integer<6>, ArraySize<Bool6>::type> ));
  STATIC_ASSERT2(( is_same<Integer<7>, ArraySize<Bool7>::type> ));
  STATIC_ASSERT2(( is_same<Integer<8>, ArraySize<Bool8>::type> ));
  STATIC_ASSERT2(( is_same<Integer<9>, ArraySize<Bool9>::type> ));
  STATIC_ASSERT2(( is_same<Integer<10>, ArraySize<Bool10>::type> ));

  test_array_concat<Integer<0> >();
  test_array_concat<Integer<1> >();
  test_array_concat<Integer<2> >();
  test_array_concat<Integer<3> >();
  test_array_concat<Integer<4> >();
  test_array_concat<Integer<5> >();
  test_array_concat<Integer<6> >();
  test_array_concat<Integer<7> >();
  test_array_concat<Integer<8> >();
  test_array_concat<Integer<9> >();

  test_array_split();
  test_array_reverse();
  test_array_rotate();
  test_array_transform();
  test_array_zip();
}


void test_metaprogramming()
{
  test_boolean_types();
  test_make_ref();
  test_integer_operations();
  test_boolean_operations();
  test_enable_disable_if();
  test_is_reference();
  test_is_same();
  test_deduce_input_type();
  test_parameter_type();
  test_underlying_ref_swap();
  test_logical_operations();
  test_decay_ref();
  test_is_convertible();
  test_is_struct_class_or_union();
  test_Array();
  test_Apply();
}

GENERATE_HAS_AND_GET_MEMBER_TYPE(TestTypedef)

struct TestFalse {};

struct TestTrue
{
  typedef int TestTypedef;
};

struct TestTrue2
{
  typedef int const volatile& TestTypedef;
};

void test_detect_traits()
{
  STATIC_ASSERT_NOT2(( HasMemberType_TestTypedef<TestFalse> ));
  STATIC_ASSERT_NOT2(( HasMemberType_TestTypedef<void> ));
  STATIC_ASSERT_NOT2(( HasMemberType_TestTypedef<void*> ));

  STATIC_ASSERT2(( HasMemberType_TestTypedef<TestTrue> ));
  STATIC_ASSERT2(( is_same<int, GetMemberType_TestTypedef<TestTrue>::type> ));

  STATIC_ASSERT2(( HasMemberType_TestTypedef<TestTrue2> ));
  STATIC_ASSERT2(( is_same<int volatile const&, GetMemberType_TestTypedef<TestTrue2>::type> ));
}

void test_empty()
{
  empty_type<DefaultTag> a;
  empty_type<DefaultTag> b;
  TEST(a == b);
  TEST(!(a != b));
  TEST(!(a < b ));
  TEST(a <= b);
  TEST(a >= b);
  TEST(!(a > b));
}

template<typename T>
void test_equality(T const& x, T const& y)
{
  TEST(x == x);
  TEST(y == y);
  TEST(!(x == y));
  TEST(!(y == x));
  TEST(x != y);
  TEST(y != x);
}

template<typename T>
void test_equals(T const& x, T const& y)
{
  TEST(equal<T>()(x, x));
  TEST(equal<T>()(y, y));
  TEST(!equal<T>()(x, y));
  TEST(!equal<T>()(y, x));
}

// Needs x to be less than y to work out
template<typename T>
void test_total_ordering(T const& x, T const& y)
{
  TEST(x < y);
  TEST(!(y < x));

  TEST(x <= y);
  TEST(!(y <= x));

  TEST(!(x > y));
  TEST(y > x);

  TEST(!(x >= y));
  TEST(y >= x);
}

// Needs x to be less than y to work out
template<typename T>
void test_less(T const& x, T const& y)
{
  TEST(less<T>()(x, y));
  TEST(!less<T>()(y, x));
}

template<typename T>
void test_swap(T const& x, T const& y)
{
  TEST(!(x == y));
  T x2 = x;
  T y2 = y;
  swap(x2, y2);
  TEST(x == y2);
  TEST(y == x2);
}

template<typename T>
void test_generated_operations(T const& x, T const& y)
{
  test_equality(x, y);
  test_equals(x, y);
  test_total_ordering(x, y);
  test_less(x, y);

  test_swap(x, y);
}

void test_singleton()
{
    typedef singleton<int, DefaultTag> type;
    type x = {1};
    type y = {2};
    TEST(1 == x.m0);

    test_generated_operations(x, y);

    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<1> > ));

    STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
}

void test_pair()
{
    typedef pair<int, float, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f};
    type y = {2, 3.5f};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f};
    test_generated_operations(x, z);

    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<2> > ));

    STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
}

void test_triple()
{
    typedef triple<int, float, char, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a'};
    type y = {2, 3.5f, 'a'};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a'};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b'};
    test_generated_operations(x, a);

    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<3> > ));

    STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
}

void test_quadruple()
{
    typedef quadruple<int, float, char, bool, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a', false};
    type y = {2, 3.5f, 'a', false};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    TEST(false == x.m3);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a', false};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b', false};
    test_generated_operations(x, a);

    // Differ in the m3 value
    type b = {1, 3.5f, 'a', true};
    test_generated_operations(x, b);

    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<4> > ));

    STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
}

void test_quintuple()
{
    typedef quintuple<int, float, char, bool, unsigned, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a', false, 3U};
    type y = {2, 3.5f, 'a', false, 3U};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    TEST(false == x.m3);
    TEST(3U == x.m4);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a', false, 3U};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b', false, 3U};
    test_generated_operations(x, a);

    // Differ in the m3 value
    type b = {1, 3.5f, 'a', true, 3U};
    test_generated_operations(x, b);

    // Differ in the m4 value
    type c = {1, 3.5f, 'a', true, 4U};
    test_generated_operations(x, c);

    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<5> > ));

    STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
    STATIC_ASSERT2(( is_same<unsigned, GetIntrospectionItem<type, Integer<4> >::type> ));
}

void test_sextuple()
{
    typedef sextuple<int, float, char, bool, unsigned, long long, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a', false, 3U, 99LL};
    type y = {2, 3.5f, 'a', false, 3U, 99LL};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    TEST(false == x.m3);
    TEST(3U == x.m4);
    TEST(99LL == x.m5);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a', false, 3U, 99LL};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b', false, 3U, 99LL};
    test_generated_operations(x, a);

    // Differ in the m3 value
    type b = {1, 3.5f, 'a', true, 3U, 99LL};
    test_generated_operations(x, b);

    // Differ in the m4 value
    type c = {1, 3.5f, 'a', true, 4U, 99LL};
    test_generated_operations(x, c);

    // Differ in the m5 value
    type d = {1, 3.5f, 'a', true, 4U, 100LL};
    test_generated_operations(x, d);

    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<5> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<6> > ));

    STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
    STATIC_ASSERT2(( is_same<unsigned, GetIntrospectionItem<type, Integer<4> >::type> ));
    STATIC_ASSERT2(( is_same<long long, GetIntrospectionItem<type, Integer<5> >::type> ));
}

void test_septuple()
{
    typedef septuple<int, float, char, bool, unsigned, long long, double, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a', false, 3U, 99LL, 1.0};
    type y = {2, 3.5f, 'a', false, 3U, 99LL, 1.0};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    TEST(false == x.m3);
    TEST(3U == x.m4);
    TEST(99LL == x.m5);
    TEST(1.0 == x.m6);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a', false, 3U, 99LL, 1.0};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b', false, 3U, 99LL, 1.0};
    test_generated_operations(x, a);

    // Differ in the m3 value
    type b = {1, 3.5f, 'a', true, 3U, 99LL, 1.0};
    test_generated_operations(x, b);

    // Differ in the m4 value
    type c = {1, 3.5f, 'a', true, 4U, 99LL, 1.0};
    test_generated_operations(x, c);

    // Differ in the m5 value
    type d = {1, 3.5f, 'a', true, 4U, 100LL, 1.0};
    test_generated_operations(x, d);

    // Differ in the m6 value
    type e = {1, 3.5f, 'a', true, 4U, 100LL, 2.0};
    test_generated_operations(x, e);

    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<5> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<6> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<7> > ));

    STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
    STATIC_ASSERT2(( is_same<unsigned, GetIntrospectionItem<type, Integer<4> >::type> ));
    STATIC_ASSERT2(( is_same<long long, GetIntrospectionItem<type, Integer<5> >::type> ));
    STATIC_ASSERT2(( is_same<double, GetIntrospectionItem<type, Integer<6> >::type> ));
}

void test_octuple()
{
    typedef octuple<int, float, char, bool, unsigned, long long, double, unsigned long, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a', false, 3U, 99LL, 1.0, 3UL};
    type y = {2, 3.5f, 'a', false, 3U, 99LL, 1.0, 3UL};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    TEST(false == x.m3);
    TEST(3U == x.m4);
    TEST(99LL == x.m5);
    TEST(1.0 == x.m6);
    TEST(3UL == x.m7);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a', false, 3U, 99LL, 1.0, 3UL};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b', false, 3U, 99LL, 1.0, 3UL};
    test_generated_operations(x, a);

    // Differ in the m3 value
    type b = {1, 3.5f, 'a', true, 3U, 99LL, 1.0, 3UL};
    test_generated_operations(x, b);

    // Differ in the m4 value
    type c = {1, 3.5f, 'a', true, 4U, 99LL, 1.0, 3UL};
    test_generated_operations(x, c);

    // Differ in the m5 value
    type d = {1, 3.5f, 'a', true, 4U, 100LL, 1.0, 3UL};
    test_generated_operations(x, d);

    // Differ in the m6 value
    type e = {1, 3.5f, 'a', true, 4U, 100LL, 2.0, 3UL};
    test_generated_operations(x, e);

    // Differ in the m7 value
    type f = {1, 3.5f, 'a', true, 4U, 100LL, 2.0, 4UL};
    test_generated_operations(x, f);

    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<5> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<6> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<7> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<8> > ));

    STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
    STATIC_ASSERT2(( is_same<unsigned, GetIntrospectionItem<type, Integer<4> >::type> ));
    STATIC_ASSERT2(( is_same<long long, GetIntrospectionItem<type, Integer<5> >::type> ));
    STATIC_ASSERT2(( is_same<double, GetIntrospectionItem<type, Integer<6> >::type> ));
    STATIC_ASSERT2(( is_same<unsigned long, GetIntrospectionItem<type, Integer<7> >::type> ));
}

void test_nonuple()
{
    typedef nonuple<int, float, char, bool, unsigned, long long, double, unsigned long, bool, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a', false, 3U, 99LL, 1.0, 3UL, false};
    type y = {2, 3.5f, 'a', false, 3U, 99LL, 1.0, 3UL, false};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    TEST(false == x.m3);
    TEST(3U == x.m4);
    TEST(99LL == x.m5);
    TEST(1.0 == x.m6);
    TEST(3UL == x.m7);
    TEST(false == x.m8);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a', false, 3U, 99LL, 1.0, 3UL, false};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b', false, 3U, 99LL, 1.0, 3UL, false};
    test_generated_operations(x, a);

    // Differ in the m3 value
    type b = {1, 3.5f, 'a', true, 3U, 99LL, 1.0, 3UL, false};
    test_generated_operations(x, b);

    // Differ in the m4 value
    type c = {1, 3.5f, 'a', true, 4U, 99LL, 1.0, 3UL, false};
    test_generated_operations(x, c);

    // Differ in the m5 value
    type d = {1, 3.5f, 'a', true, 4U, 100LL, 1.0, 3UL, false};
    test_generated_operations(x, d);

    // Differ in the m6 value
    type e = {1, 3.5f, 'a', true, 4U, 100LL, 2.0, 3UL, false};
    test_generated_operations(x, e);

    // Differ in the m7 value
    type f = {1, 3.5f, 'a', true, 4U, 100LL, 2.0, 4UL, false};
    test_generated_operations(x, f);

    // Differ in the m8 value
    type g = {1, 3.5f, 'a', true, 4U, 100LL, 2.0, 4UL, true};
    test_generated_operations(x, g);

    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<5> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<6> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<7> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<8> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<9> > ));

    STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
    STATIC_ASSERT2(( is_same<unsigned, GetIntrospectionItem<type, Integer<4> >::type> ));
    STATIC_ASSERT2(( is_same<long long, GetIntrospectionItem<type, Integer<5> >::type> ));
    STATIC_ASSERT2(( is_same<double, GetIntrospectionItem<type, Integer<6> >::type> ));
    STATIC_ASSERT2(( is_same<unsigned long, GetIntrospectionItem<type, Integer<7> >::type> ));
    STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<8> >::type> ));
}

void test_decuple()
{
    typedef decuple<int, float, char, bool, unsigned, long long, double, unsigned long, bool, int, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a', false, 3U, 99LL, 1.0, 3UL, false, 88};
    type y = {2, 3.5f, 'a', false, 3U, 99LL, 1.0, 3UL, false, 88};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    TEST(false == x.m3);
    TEST(3U == x.m4);
    TEST(99LL == x.m5);
    TEST(1.0 == x.m6);
    TEST(3UL == x.m7);
    TEST(false == x.m8);
    TEST(88 == x.m9);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a', false, 3U, 99LL, 1.0, 3UL, false, 88};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b', false, 3U, 99LL, 1.0, 3UL, false, 88};
    test_generated_operations(x, a);

    // Differ in the m3 value
    type b = {1, 3.5f, 'a', true, 3U, 99LL, 1.0, 3UL, false, 88};
    test_generated_operations(x, b);

    // Differ in the m4 value
    type c = {1, 3.5f, 'a', true, 4U, 99LL, 1.0, 3UL, false, 88};
    test_generated_operations(x, c);

    // Differ in the m5 value
    type d = {1, 3.5f, 'a', true, 4U, 100LL, 1.0, 3UL, false, 88};
    test_generated_operations(x, d);

    // Differ in the m6 value
    type e = {1, 3.5f, 'a', true, 4U, 100LL, 2.0, 3UL, false, 88};
    test_generated_operations(x, e);

    // Differ in the m7 value
    type f = {1, 3.5f, 'a', true, 4U, 100LL, 2.0, 4UL, false, 88};
    test_generated_operations(x, f);

    // Differ in the m8 value
    type g = {1, 3.5f, 'a', true, 4U, 100LL, 2.0, 4UL, true, 88};
    test_generated_operations(x, g);

    // Differ in the m9 value
    type h = {1, 3.5f, 'a', true, 4U, 100LL, 2.0, 4UL, true, 89};
    test_generated_operations(x, h);

    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<5> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<6> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<7> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<8> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<9> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<10> > ));

    STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
    STATIC_ASSERT2(( is_same<unsigned, GetIntrospectionItem<type, Integer<4> >::type> ));
    STATIC_ASSERT2(( is_same<long long, GetIntrospectionItem<type, Integer<5> >::type> ));
    STATIC_ASSERT2(( is_same<double, GetIntrospectionItem<type, Integer<6> >::type> ));
    STATIC_ASSERT2(( is_same<unsigned long, GetIntrospectionItem<type, Integer<7> >::type> ));
    STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<8> >::type> ));
    STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<9> >::type> ));
}

void test_storage_reference_types()
{
    typedef singleton<int&, DefaultTag> type;
    int tmp = 0;
    type x = {tmp};
    type y = type::make(make_ref(tmp));
    (void) x;
    (void) y;

    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<1> > ));

    STATIC_ASSERT2(( is_same<int&, GetIntrospectionItem<type, Integer<0> >::type> ));
}

struct NumberedStorageType
{
    typedef NumberedStorageType type;
    typedef true_type IntrospectionEnabled;
    typedef Integer<0> IntrospectionItem0;
    typedef Integer<1> IntrospectionItem1;
    typedef Integer<2> IntrospectionItem2;
    typedef Integer<3> IntrospectionItem3;
    typedef Integer<4> IntrospectionItem4;
    typedef Integer<5> IntrospectionItem5;
    typedef Integer<6> IntrospectionItem6;
    typedef Integer<7> IntrospectionItem7;
    typedef Integer<8> IntrospectionItem8;
    typedef Integer<9> IntrospectionItem9;
};

void test_numbered_introspection()
{
    typedef NumberedStorageType type;
    STATIC_ASSERT2(( is_same<Integer<10>, IntrospectionArity<type>::type> ));
    STATIC_ASSERT2(( is_same<Array<Integer<0>, Integer<1>, Integer<2>, Integer<3>, Integer<4>, Integer<5>, Integer<6>, Integer<7>, Integer<8>, Integer<9> >, GenerateIntrospectionItems<type>::type> ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<5> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<6> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<7> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<8> > ));
    STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<9> > ));
    STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<10> > ));

    STATIC_ASSERT2(( is_same<Integer<0>, GetIntrospectionItem<type, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<1>, GetIntrospectionItem<type, Integer<1> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<2>, GetIntrospectionItem<type, Integer<2> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<3>, GetIntrospectionItem<type, Integer<3> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<4>, GetIntrospectionItem<type, Integer<4> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<5>, GetIntrospectionItem<type, Integer<5> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<6>, GetIntrospectionItem<type, Integer<6> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<7>, GetIntrospectionItem<type, Integer<7> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<8>, GetIntrospectionItem<type, Integer<8> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<9>, GetIntrospectionItem<type, Integer<9> >::type> ));

}

typedef triple<int, long, char> VisitorTestType;

struct TestVisitor
{
  bool visit0;
  bool visit1;
  bool visit2;
  void operator()(int const&, Integer<0>) { visit0 = true; }
  void operator()(long const&, Integer<1>) { visit1 = true; }
  void operator()(char const&, Integer<2>) { visit2 = true; }

};

void test_visit()
{
  // Visitor mechanism uses looping so testing a short
  // container exercises no different (meta)code to a
  // longer container.
  TestVisitor v = {false, false, false};
  VisitorTestType t = {3, 9L, 'a'};
  v = visit(t, v);
  TEST(v.visit0);
  TEST(v.visit1);
  TEST(v.visit2);
}

int fun0() { return 0; }
void voidfun0() {}

void testfun0()
{
  typedef int(*type)();
  STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  STATIC_ASSERT_NOT2(( HasInputType<type, Integer<0> > ));
  STATIC_ASSERT2(( is_same<Integer<0>, GetFunctionArity<type>::type> ));
  STATIC_ASSERT2(( is_same<Array<>, GetInputTypeArray<type>::type> ));

  //TEST(( 0 == ResolveFunctionSignatureType<type>::type()(&fun0)));
  //ResolveFunctionSignatureType<void(*)()>::type()(&voidfun0);
}

int fun1(long) { return 0; }
void voidfun1(long) {}

void testfun1()
{
  typedef int(*type)(long);
  STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  STATIC_ASSERT_NOT2(( HasInputType<type, Integer<1> > ));
  STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  STATIC_ASSERT2(( is_same<Integer<1>, GetFunctionArity<type>::type> ));
  STATIC_ASSERT2(( is_same<Array<long>, GetInputTypeArray<type>::type> ));

  //TEST(( 0 == ResolveFunctionSignatureType<type>::type()(&fun1, 1)));
  //ResolveFunctionSignatureType<void(*)(long)>::type()(&voidfun1, 0);
}

int fun2(long, float) { return 0; }
void voidfun2(long, float) {}

void testfun2()
{
  typedef int(*type)(long, float);
  STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  STATIC_ASSERT_NOT2(( HasInputType<type, Integer<2> > ));
  STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  STATIC_ASSERT2(( is_same<Integer<2>, GetFunctionArity<type>::type> ));
  STATIC_ASSERT2(( is_same<Array<long, float>, GetInputTypeArray<type>::type> ));

  //TEST(( 0 == ResolveFunctionSignatureType<type>::type()(&fun2, 1, 2.0f)));
  //ResolveFunctionSignatureType<void(*)(long, float)>::type()(&voidfun2, 0, 2.0f);
}

int fun3(long, float, short&) { return 0; }
void voidfun3(long, float, short&) {}

void testfun3()
{
  typedef int(*type)(long, float, short&);
  STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  STATIC_ASSERT2(( HasInputType<type, Integer<2> > ));
  STATIC_ASSERT_NOT2(( HasInputType<type, Integer<3> > ));
  STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  STATIC_ASSERT2(( is_same<short&, GetInputType<type, Integer<2> >::type> ));
  STATIC_ASSERT2(( is_same<Integer<3>, GetFunctionArity<type>::type> ));
  STATIC_ASSERT2(( is_same<Array<long, float, short&>, GetInputTypeArray<type>::type> ));

  //short tmp = 0;
  //TEST(( 0 == ResolveFunctionSignatureType<type>::type()(&fun3, 1, 2.0f, tmp)));
  //ResolveFunctionSignatureType<void(*)(long, float, short&)>::type()(&voidfun3, 0, 2.0f, tmp);
}

int fun4(long, float, short&, int const&) { return 0; }
void voidfun4(long, float, short&, int const&) {}

void testfun4()
{
  typedef int(*type)(long, float, short&, int const&);
  STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  STATIC_ASSERT2(( HasInputType<type, Integer<2> > ));
  STATIC_ASSERT2(( HasInputType<type, Integer<3> > ));
  STATIC_ASSERT_NOT2(( HasInputType<type, Integer<4> > ));
  STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  STATIC_ASSERT2(( is_same<short&, GetInputType<type, Integer<2> >::type> ));
  STATIC_ASSERT2(( is_same<int const&, GetInputType<type, Integer<3> >::type> ));
  STATIC_ASSERT2(( is_same<Integer<4>, GetFunctionArity<type>::type> ));
  STATIC_ASSERT2(( is_same<Array<long, float, short&, int const&>, GetInputTypeArray<type>::type> ));

  //short tmp = 0;
  //int tmp2 = 1;
  //TEST(( 0 == ResolveFunctionSignatureType<type>::type()(&fun4, 1, 2.0f, tmp, tmp2)));
  //ResolveFunctionSignatureType<void(*)(long, float, short&, int const&)>::type()(&voidfun4, 0, 2.0f, tmp, tmp2);
}

int fun5(long, float, short&, int const&, bool) { return 0; }
void voidfun5(long, float, short&, int const&, bool) {}

void testfun5()
{
  typedef int(*type)(long, float, short&, int const&, bool);
  STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  STATIC_ASSERT2(( HasInputType<type, Integer<2> > ));
  STATIC_ASSERT2(( HasInputType<type, Integer<3> > ));
  STATIC_ASSERT2(( HasInputType<type, Integer<4> > ));
  STATIC_ASSERT_NOT2(( HasInputType<type, Integer<5> > ));
  STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  STATIC_ASSERT2(( is_same<short&, GetInputType<type, Integer<2> >::type> ));
  STATIC_ASSERT2(( is_same<int const&, GetInputType<type, Integer<3> >::type> ));
  STATIC_ASSERT2(( is_same<bool, GetInputType<type, Integer<4> >::type> ));
  STATIC_ASSERT2(( is_same<Integer<5>, GetFunctionArity<type>::type> ));
  STATIC_ASSERT2(( is_same<Array<long, float, short&, int const&, bool>, GetInputTypeArray<type>::type> ));

  //short tmp = 0;
  //int tmp2 = 1;
  //TEST((0 == ResolveFunctionSignatureType<type>::type()(&fun5, 1, 2.0f, tmp, tmp2, true)));
  //ResolveFunctionSignatureType<void(*)(long, float, short&, int const&, bool)>::type()(&voidfun5, 0, 2.0f, tmp, tmp2, true);
}

struct MyFunctionObject
{
    typedef long input_type_0;
    typedef int codomain_type;
    int operator()(long){ return 1; }

  static void test()
  {
    STATIC_ASSERT2(( is_same<GetCodomainType<MyFunctionObject>::type,int> ));
    STATIC_ASSERT2(( is_same<DeduceCodomainType<MyFunctionObject>::type,int> ));
    STATIC_ASSERT2(( FunctionSignatureEnabled<MyFunctionObject> ));
    STATIC_ASSERT2(( HasInputType<MyFunctionObject, Integer<0> > ));
    STATIC_ASSERT_NOT2(( HasInputType<MyFunctionObject, Integer<1> > ));
    STATIC_ASSERT2(( is_same<long, GetInputType<MyFunctionObject, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<1>, GetFunctionArity<MyFunctionObject>::type> ));
    STATIC_ASSERT2(( is_same<Array<long>, GetInputTypeArray<MyFunctionObject>::type> ));
  }
};

struct MyRefFunctionObject
{
    static int aValue;
    typedef long const& input_type_0;
    typedef int& codomain_type;
    int& operator()(long const&){ return aValue; }

  static void test()
  {
    STATIC_ASSERT2(( is_same<GetCodomainType<MyRefFunctionObject>::type,int&> ));
    STATIC_ASSERT2(( is_same<DeduceCodomainType<MyRefFunctionObject>::type,int&> ));
    STATIC_ASSERT2(( FunctionSignatureEnabled<MyRefFunctionObject> ));
    STATIC_ASSERT2(( HasInputType<MyRefFunctionObject, Integer<0> > ));
    STATIC_ASSERT_NOT2(( HasInputType<MyRefFunctionObject, Integer<1> > ));
    STATIC_ASSERT2(( is_same<long const&, GetInputType<MyRefFunctionObject, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<1>, GetFunctionArity<MyRefFunctionObject>::type> ));
    STATIC_ASSERT2(( is_same<Array<long const&>, GetInputTypeArray<MyRefFunctionObject>::type> ));
  }
};
int MyRefFunctionObject::aValue = 0;

template<typename T>
struct ReturnFirstValue
{
    typedef T type;
};

struct ReturnThirdValue
{
    template<typename T, typename U, typename V, typename W, typename X>
    struct apply
    {
        typedef V type;
    };
};

struct MyGenericFunctionObject
{
    typedef MyGenericFunctionObject type;
    typedef template_param input_type_0;
    typedef CodomainDeduction<ReturnFirstValue<placeholders::_0> > codomain_type;

    template<typename T>
    typename DeduceCodomainType<type, T>::type
    operator()(T x){ return x; }

  static void test()
  {
    // OK, test out the generic codomain deduction mechanism
    STATIC_ASSERT2(( is_same<GetCodomainType<MyGenericFunctionObject>::type,CodomainDeduction<ReturnFirstValue<placeholders::_0> > > ));
    STATIC_ASSERT2(( is_same<DeduceCodomainType<MyGenericFunctionObject, int>::type,int> ));
    STATIC_ASSERT2(( FunctionSignatureEnabled<MyGenericFunctionObject> ));
    STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject, Integer<0> > ));
    STATIC_ASSERT_NOT2(( HasInputType<MyGenericFunctionObject, Integer<1> > ));
    STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<1>, GetFunctionArity<MyGenericFunctionObject>::type> ));
    STATIC_ASSERT2(( is_same<Array<template_param>, GetInputTypeArray<MyGenericFunctionObject>::type> ));
  }
};

struct MyGenericFunctionObject2
{
    typedef MyGenericFunctionObject2 type;
    typedef template_param input_type_0;
    typedef template_param input_type_1;
    typedef template_param input_type_2;
    typedef template_param input_type_3;
    typedef template_param input_type_4;
    typedef CodomainDeduction<ReturnThirdValue> codomain_type;

    template<typename T, typename U, typename V, typename W, typename X>
    typename DeduceCodomainType<type, T, U, V, W, X>::type
    operator()(T, U, V v, W, X){ return v; }

  static void test()
  {
    // OK, test out the generic codomain deduction mechanism with 5 parameters
    STATIC_ASSERT2(( is_same<GetCodomainType<MyGenericFunctionObject2>::type,CodomainDeduction<ReturnThirdValue> > ));
    STATIC_ASSERT2(( is_same<DeduceCodomainType<MyGenericFunctionObject2, char, short, int, float, void*>::type,int> ));
    STATIC_ASSERT2(( FunctionSignatureEnabled<MyGenericFunctionObject2> ));
    STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject2, Integer<0> > ));
    STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject2, Integer<1> > ));
    STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject2, Integer<2> > ));
    STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject2, Integer<3> > ));
    STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject2, Integer<4> > ));
    STATIC_ASSERT_NOT2(( HasInputType<MyGenericFunctionObject2, Integer<5> > ));
    STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<0> >::type> ));
    STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<1> >::type> ));
    STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<2> >::type> ));
    STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<3> >::type> ));
    STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<4> >::type> ));
    STATIC_ASSERT2(( is_same<Integer<5>, GetFunctionArity<MyGenericFunctionObject2>::type> ));
    STATIC_ASSERT2(( is_same<Array<template_param, template_param, template_param, template_param, template_param>, GetInputTypeArray<MyGenericFunctionObject2>::type> ));
  }
};

struct MemberFunctionTest
{
  void voidFun0() const {}
  int intFun0() { return 0; }

  void voidFun1(int) const {}
  int intFun1(int) { return 0; }

  void voidFun2(int, char&) const {}
  int intFun2(int, char&) { return 0; }

  void voidFun3(int, char&, double (&)[]) const {}
  int intFun3(int, char&, double (&)[]) { return 0; }

  void voidFun4(int, char&, double (&)[], int const volatile (&)[10]) const {}
  int intFun4(int, char&, double (&)[], int const volatile (&)[10]) { return 0; }
};

template<typename ReturnType, typename Input0, typename T>
void testMemberFun0(T func)
{
  STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  STATIC_ASSERT_NOT(( HasInputType<T, Integer<1> > ));
  STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  STATIC_ASSERT(( is_same<Integer<1>, typename GetFunctionArity<T>::type > ));
  STATIC_ASSERT(( is_same<Array<Input0>, typename GetInputTypeArray<T>::type> ));

  //MemberFunctionTest a;
  //typename ResolveFunctionSignatureType<T>::type()(func, a);
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun1(T func)
{
  STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  STATIC_ASSERT_NOT(( HasInputType<T, Integer<2> > ));
  STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  STATIC_ASSERT(( is_same<Integer<2>, typename GetFunctionArity<T>::type > ));
  STATIC_ASSERT(( is_same<Array<Input0, int>, typename GetInputTypeArray<T>::type> ));

  //MemberFunctionTest a;
  //typename ResolveFunctionSignatureType<T>::type()(func, a, 1);
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun2(T func)
{
  STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  STATIC_ASSERT(( HasInputType<T, Integer<2> > ));
  STATIC_ASSERT_NOT(( HasInputType<T, Integer<3> > ));
  STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  STATIC_ASSERT(( is_same<char&, typename GetInputType<T, Integer<2> >::type> ));
  STATIC_ASSERT(( is_same<Integer<3>, typename GetFunctionArity<T>::type > ));
  STATIC_ASSERT(( is_same<Array<Input0, int, char&>, typename GetInputTypeArray<T>::type> ));

  //char tmp = 'a';
  //MemberFunctionTest a;
  //typename ResolveFunctionSignatureType<T>::type()(func, a, 1, tmp);
}

extern double TEST_DOUBLE_ARRAY[];

template<typename ReturnType, typename Input0, typename T>
void testMemberFun3(T func)
{
  STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  STATIC_ASSERT(( HasInputType<T, Integer<2> > ));
  STATIC_ASSERT(( HasInputType<T, Integer<3> > ));
  STATIC_ASSERT_NOT(( HasInputType<T, Integer<4> > ));
  STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  STATIC_ASSERT(( is_same<char&, typename GetInputType<T, Integer<2> >::type> ));
  STATIC_ASSERT(( is_same<double (&)[], typename GetInputType<T, Integer<3> >::type> ));
  STATIC_ASSERT(( is_same<Integer<4>, typename GetFunctionArity<T>::type > ));
  STATIC_ASSERT(( is_same<Array<Input0, int, char&, double (&)[]>, typename GetInputTypeArray<T>::type> ));

  //char tmp = 'a';
  //MemberFunctionTest a;
  //typename ResolveFunctionSignatureType<T>::type()(func, a, 1, tmp, TEST_DOUBLE_ARRAY);
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun4(T func)
{
  STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  STATIC_ASSERT(( HasInputType<T, Integer<2> > ));
  STATIC_ASSERT(( HasInputType<T, Integer<3> > ));
  STATIC_ASSERT(( HasInputType<T, Integer<4> > ));
  STATIC_ASSERT_NOT(( HasInputType<T, Integer<5> > ));
  STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  STATIC_ASSERT(( is_same<char&, typename GetInputType<T, Integer<2> >::type> ));
  STATIC_ASSERT(( is_same<double (&)[], typename GetInputType<T, Integer<3> >::type> ));
  STATIC_ASSERT(( is_same<int const volatile (&)[10], typename GetInputType<T, Integer<4> >::type> ));
  STATIC_ASSERT(( is_same<Integer<5>, typename GetFunctionArity<T>::type > ));
  STATIC_ASSERT(( is_same<Array<Input0, int, char&, double (&)[], int const volatile (&)[10]>, typename GetInputTypeArray<T>::type> ));

  //char tmp = 'a';
  //int volatile const tmp2[10] = {};
  //MemberFunctionTest a;
  //typename ResolveFunctionSignatureType<T>::type()(func, a, 1, tmp, TEST_DOUBLE_ARRAY, tmp2);
}

double TEST_DOUBLE_ARRAY[1] = {};

void test_function_signatures()
{
  testfun0();
  testfun1();
  testfun2();
  testfun3();
  testfun4();
  testfun5();

  MyFunctionObject::test();
  MyRefFunctionObject::test();
  MyGenericFunctionObject::test();
  MyGenericFunctionObject2::test();

  testMemberFun0<void, MemberFunctionTest const&>(&MemberFunctionTest::voidFun0);
  testMemberFun0<int, MemberFunctionTest&>(&MemberFunctionTest::intFun0);

  testMemberFun1<void, MemberFunctionTest const&>(&MemberFunctionTest::voidFun1);
  testMemberFun1<int, MemberFunctionTest&>(&MemberFunctionTest::intFun1);

  testMemberFun2<void, MemberFunctionTest const&>(&MemberFunctionTest::voidFun2);
  testMemberFun2<int, MemberFunctionTest&>(&MemberFunctionTest::intFun2);

  testMemberFun3<void, MemberFunctionTest const&>(&MemberFunctionTest::voidFun3);
  testMemberFun3<int, MemberFunctionTest&>(&MemberFunctionTest::intFun3);

  testMemberFun4<void, MemberFunctionTest const&>(&MemberFunctionTest::voidFun4);
  testMemberFun4<int, MemberFunctionTest&>(&MemberFunctionTest::intFun4);
}

} // unnamed namespace
} // namespace intro

using namespace intro;

int main()
{
    test_metaprogramming();
    test_detect_traits();
    test_empty();
    test_singleton();
    test_pair();
    test_triple();
    test_quadruple();
    test_quintuple();
    test_sextuple();
    test_septuple();
    test_octuple();
    test_nonuple();
    test_decuple();
    test_storage_reference_types();
    test_numbered_introspection();
    test_visit();

    test_function_signatures();
}
