#include <cassert>
#include "storage.h"
#include "storage_io.h"
#include "function_signatures.h"
#include "introspection_assert.h"

#include <iostream>
#include <sstream>

namespace intro {
namespace {

INTROSPECTION_STATIC_ASSERT2((true_type));

#ifdef INTROSPECTION_COMPILATION_FAILURE_TESTS
INTROSPECTION_STATIC_ASSERT2((false_type));
INTROSPECTION_STATIC_ASSERT_NOT2((true_type));

struct Test_METAPROGRAMMING_ONLY
{
  METAPROGRAMMING_ONLY(Test_METAPROGRAMMING_ONLY)
};

Test_METAPROGRAMMING_ONLY no_viable_constructor_destructor;
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

  INTROSPECTION_STATIC_ASSERT(( is_same<ExpectedArray,
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
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<Array<>,
                      TestArray>,
			     ArraySplit<TestArray, Integer<0> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<Array<bool>,
                      Array<unsigned char, signed char, char, short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<1> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char>,
                Array<signed char, char, short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<2> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char>,
                      Array<char, short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<3> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char>,
                      Array<short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<4> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char,short>,
                      Array<unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<5> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short>,
                      Array<int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<6> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short, int>,
                      Array<unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<7> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short, int, unsigned int>,
                      Array<long, unsigned long> >,
        ArraySplit<TestArray, Integer<8> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short, int, unsigned int, long>,
                      Array<unsigned long> >,
        ArraySplit<TestArray, Integer<9> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<TestArray,
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
  INTROSPECTION_STATIC_ASSERT(( is_same<ReversedTestArray, Result> ));
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
  INTROSPECTION_STATIC_ASSERT2(( is_same<Expected, ArrayRotate<TestArray, Integer<1>, Integer<3>, Integer<6> >::type> ));

  typedef Array<unsigned short, int, unsigned int, long, unsigned long, bool, unsigned char, signed char, char, short> Expected2;
  // rotate test array about index 5, i.e. from bool up to but not including unsigned short is rotated
  INTROSPECTION_STATIC_ASSERT2(( is_same<Expected2, ArrayRotateDefault<TestArray, Integer<5> >::type > ));
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

  INTROSPECTION_STATIC_ASSERT2(( is_same<ArrayTransform<Integers, AddOne>::type, Expected> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<ArrayTransform<Integers, Add<placeholders::_0, Integer<1> > >::type, Expected> ));
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

  INTROSPECTION_STATIC_ASSERT2(( is_same<ArrayZip<Integers, MoreIntegers, AddTogether>::type, Expected> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<ArrayZip<Integers, MoreIntegers, Add<placeholders::_0, placeholders::_1> >::type, Expected> ));
}

typedef Array<placeholders::_9, placeholders::_8, placeholders::_7, placeholders::_6, placeholders::_5, placeholders::_4, placeholders::_3, placeholders::_2, placeholders::_1, placeholders::_0> ReversingArray;

struct ArrayReverser
{
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
  struct apply : Array<T9, T8, T7, T6, T5, T4, T3, T2, T1, T0> {};
};

void test_Apply()
{
  INTROSPECTION_STATIC_ASSERT2(( is_same<int, Apply<placeholders::_0, int>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<float, Apply<placeholders::_2,int, bool, float>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<empty_type<int>, Apply<empty_type<int> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<empty_type<int>, Apply<empty_type<int>, short, double, char, float, void >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<empty_type<bool>, Apply<empty_type<placeholders::_0>, bool, int, long, float, short>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<empty_type<int>, Apply<empty_type<placeholders::_1>, bool, int, long, float, short>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<empty_type<long>, Apply<empty_type<placeholders::_2>, bool, int, long, float, short>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<empty_type<float>, Apply<empty_type<placeholders::_3>, bool, int, long, float, short>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<empty_type<short>, Apply<empty_type<placeholders::_4>, bool, int, long, float, short>::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<3>, Apply<AddTogether, Integer<1>, Integer<2> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, Apply<Array<> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int, int>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int, int, int>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int, int, int, int>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int, int, int, int, int>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, Apply<Array<>, int, int, int, int, int, int, int, int, int, int>::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<ReversedTestArray, Apply_Environment<ReversingArray, TestArray>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<ReversedTestArray, Apply_Environment<ArrayReverser, TestArray>::type> ));

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
  INTROSPECTION_STATIC_ASSERT2(( is_convertible<int, long> ));
  INTROSPECTION_STATIC_ASSERT2(( is_convertible<int&, int const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_convertible<float, double> ));
  INTROSPECTION_STATIC_ASSERT_NOT2((is_convertible<float, double&> ));

  INTROSPECTION_STATIC_ASSERT2(( is_convertible<float (&)[10], float*> ));
  INTROSPECTION_STATIC_ASSERT2(( is_convertible<float (&)[], float*> ));
  INTROSPECTION_STATIC_ASSERT2(( is_convertible<float (&)[], float const*> ));

  INTROSPECTION_STATIC_ASSERT_NOT2(( is_convertible<Parent*, Child*> ));
  INTROSPECTION_STATIC_ASSERT2(( is_convertible<Child*, Parent*> ));
  INTROSPECTION_STATIC_ASSERT2(( is_convertible<Child*, Parent const*> ));

  INTROSPECTION_STATIC_ASSERT2(( is_convertible<FromType, ToType> ));
  INTROSPECTION_STATIC_ASSERT2(( is_convertible<FromType, ToType const&> ));

  INTROSPECTION_STATIC_ASSERT2(( is_convertible<FromType2, ToType> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_convertible<FromType2, ToType&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_convertible<FromType2, ToType const&> ));

  INTROSPECTION_STATIC_ASSERT2(( is_convertible<int, ImplicitConvertingConstructor> ));
  INTROSPECTION_STATIC_ASSERT2(( is_convertible<int const&, ImplicitConvertingConstructor> ));
  INTROSPECTION_STATIC_ASSERT2(( is_convertible<int const volatile&, ImplicitConvertingConstructor> ));

  INTROSPECTION_STATIC_ASSERT_NOT2(( is_convertible<int, ExplicitConvertingConstructor> ));
}

struct AStruct {};
class AClass {};
union AUnion { int a; };

void test_is_struct_class_or_union()
{
  INTROSPECTION_STATIC_ASSERT2(( is_struct_class_or_union<AStruct> ));
  INTROSPECTION_STATIC_ASSERT2(( is_struct_class_or_union<AClass> ));
  INTROSPECTION_STATIC_ASSERT2(( is_struct_class_or_union<AUnion> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_struct_class_or_union<void> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_struct_class_or_union<bool> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_struct_class_or_union<double> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_struct_class_or_union<double&> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_struct_class_or_union<double&> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_struct_class_or_union<double*> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_struct_class_or_union<int AUnion::*> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_struct_class_or_union<void(*)()> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_struct_class_or_union<void(AUnion::*)()> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_struct_class_or_union<void(AUnion::*)(int)const> ));
}

void test_boolean_types()
{
  INTROSPECTION_STATIC_ASSERT2(( true_type ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( false_type ));
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

  INTROSPECTION_STATIC_ASSERT2(( ValueToTrueFalse<true> ));
  INTROSPECTION_STATIC_ASSERT2(( ValueToTrueFalse<1> ));

  INTROSPECTION_STATIC_ASSERT_NOT2(( ValueToTrueFalse<false> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( ValueToTrueFalse<0> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<1>, Successor<Integer<0> >::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<4>, Successor<Integer<3> >::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<-2>, Successor<Integer<-3> >::type > ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<-1>, Predecessor<Integer<0> >::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<2>, Predecessor<Integer<3> >::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<-4>, Predecessor<Integer<-3> >::type > ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<0>, Min<Integer<0>, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<3>, Min<Integer<4>, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<-5>, Min<Integer<-5>, Integer<-3> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<0>, Max<Integer<0>, Integer<-1> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<3>, Max<Integer<2>, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<-5>, Max<Integer<-5>, Integer<-7> >::type> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<-5>, Subtract<Integer<0>, Integer<5> >::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<42>, Subtract<Integer<47>, Integer<5> >::type > ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<-5>, Add<Integer<0>, Integer<-5> >::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<42>, Add<Integer<37>, Integer<5> >::type > ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<10>, Multiply<Integer<2>, Integer<5> >::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<0>, Multiply<Integer<37>, Integer<0> >::type > ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<7>, Divide<Integer<42>, Integer<6> >::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<0>, Divide<Integer<0>, Integer<1> >::type > ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<-10>, Negate<Integer<10> >::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<0>, Negate<Integer<0> >::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<42>, Negate<Integer<-42> >::type > ));
}

void test_boolean_operations()
{
  INTROSPECTION_STATIC_ASSERT_NOT2(( not_<true_type> ));
  INTROSPECTION_STATIC_ASSERT2(( not_<false_type> ));

  INTROSPECTION_STATIC_ASSERT_NOT2(( or_<false_type, false_type> ));
  INTROSPECTION_STATIC_ASSERT2(( or_<false_type, true_type> ));
  INTROSPECTION_STATIC_ASSERT2(( or_<true_type, false_type> ));
  INTROSPECTION_STATIC_ASSERT2(( or_<true_type, true_type> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( or_<false_type, false_type, false_type> ));
  INTROSPECTION_STATIC_ASSERT2(( or_<false_type, true_type, true_type> ));
  INTROSPECTION_STATIC_ASSERT2(( or_<true_type, false_type, true_type> ));
  INTROSPECTION_STATIC_ASSERT2(( or_<true_type, true_type, false_type> ));
  INTROSPECTION_STATIC_ASSERT2(( or_<true_type, true_type, true_type> ));

  INTROSPECTION_STATIC_ASSERT_NOT2(( and_<false_type, false_type> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( and_<false_type, true_type> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( and_<true_type, false_type> ));
  INTROSPECTION_STATIC_ASSERT2(( and_<true_type, true_type> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( and_<false_type, false_type, false_type> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( and_<false_type, false_type, true_type> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( and_<false_type, true_type, false_type> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( and_<true_type, false_type, false_type> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( and_<false_type, true_type, true_type> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( and_<true_type, false_type, true_type> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( and_<true_type, true_type, false_type> ));
  INTROSPECTION_STATIC_ASSERT2(( and_<true_type, true_type, true_type> ));
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
  INTROSPECTION_STATIC_ASSERT_NOT2(( is_reference<int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_reference<int&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_reference<int(&)[2]> ));
  INTROSPECTION_STATIC_ASSERT2(( is_reference<int(&)[]> ));
}

void test_is_same()
{
  INTROSPECTION_STATIC_ASSERT2(( is_same<int, identity_type<identity_type<int> >::type > ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<if_<true_type, int, void>::type, int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<if_<false_type, void, int>::type, int> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<eval_if<true_type, identity_type<int>, void>::type, int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<eval_if<false_type, void, identity_type<int> >::type, int> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<make_const_ref<int>::type, int const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_const_ref<int const>::type, int const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_const_ref<int const&>::type, int const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_const_ref<int &>::type, int const&> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<make_const_ref<int volatile>::type, int volatile const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_const_ref<int volatile const>::type, int volatile const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_const_ref<int volatile const&>::type, int volatile const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_const_ref<int volatile &>::type, int volatile const&> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<make_ref_type<int>::type, int&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_ref_type<int const>::type, int const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_ref_type<int const&>::type, int const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_ref_type<int &>::type, int&> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<make_ref_type<int volatile>::type, int volatile&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_ref_type<int volatile const>::type, int volatile const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_ref_type<int volatile const&>::type, int volatile const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<make_ref_type<int volatile &>::type, int volatile&> ));
}

void test_deduce_input_type()
{
  INTROSPECTION_STATIC_ASSERT2(( is_same<int&, deduce_input_type<int&>::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int, deduce_input_type<int const&>::type > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int, deduce_input_type<int>::type > ));
}


struct test_param {};

void test_parameter_type()
{
  INTROSPECTION_STATIC_ASSERT2(( is_same<parameter_type<test_param>::type, test_param const&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<parameter_type<int>::type, int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<parameter_type<int*>::type, int*> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<parameter_type<int&>::type, int&> ));
}

void test_underlying_ref_swap()
{
  INTROSPECTION_STATIC_ASSERT2(( is_same<underlying_type<int>::type, int> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<get_underlying_type<int>::type, int> ));
  {
    int a = 0;
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
  INTROSPECTION_STATIC_ASSERT2(( is_same<decay_ref<int>::type, int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<decay_ref<int&>::type, int&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<decay_ref<int const&>::type, int const&> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<decay_ref<int(&)[10] >::type, int*> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<decay_ref<int const(&)[10] >::type, int const*> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<decay_ref<int(&)[] >::type, int*> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<decay_ref<int const(&)[] >::type, int const*> ));

  INTROSPECTION_STATIC_ASSERT2(( is_same<decay_ref<Ref<int> >::type, int&> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<decay_ref<Ref<int const> >::type, int const&> ));
}

void test_Array()
{
  // Tests the array is self-evaluating
  INTROSPECTION_STATIC_ASSERT2(( is_same<TestArray, TestArray::type> ));

#define ARRAY_INDEX_TEST(n, X) INTROSPECTION_STATIC_ASSERT2(( is_same<ArrayIndex<TestArray, Integer<n> >::type, X> ))
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

  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<0>, ArraySize<Bool0>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<1>, ArraySize<Bool1>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<2>, ArraySize<Bool2>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<3>, ArraySize<Bool3>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<4>, ArraySize<Bool4>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<5>, ArraySize<Bool5>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<6>, ArraySize<Bool6>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<7>, ArraySize<Bool7>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<8>, ArraySize<Bool8>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<9>, ArraySize<Bool9>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<10>, ArraySize<Bool10>::type> ));

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
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasMemberType_TestTypedef<TestFalse> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasMemberType_TestTypedef<void> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasMemberType_TestTypedef<void*> ));

  INTROSPECTION_STATIC_ASSERT2(( HasMemberType_TestTypedef<TestTrue> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int, GetMemberType_TestTypedef<TestTrue>::type> ));

  INTROSPECTION_STATIC_ASSERT2(( HasMemberType_TestTypedef<TestTrue2> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int volatile const&, GetMemberType_TestTypedef<TestTrue2>::type> ));
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

std::ostream& getOutput()
{
#ifdef PRINT_TEST_OUPTUT_TO_COUT
    return std::cout;
#else
    static std::ostringstream os;
    return os;
#endif
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
  swap(a, b);
}

void test_singleton()
{
    typedef singleton<int, DefaultTag> type;
    type x = {1};
    type y = {2};
    TEST(1 == x.m0);

    test_generated_operations(x, y);

    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<1> > ));

    INTROSPECTION_STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));

    getOutput() << x << '\n';
    getOutput() << y << '\n';

    std::istringstream stream("22");
    type k;
    stream >> k;
    TEST(22 == k.m0);
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

    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<2> > ));

    INTROSPECTION_STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));

    getOutput() << x << '\n';
    getOutput() << y << '\n';
    getOutput() << z << '\n';

    std::istringstream stream("22 3.0");
    type k;
    stream >> k;
    TEST(22 == k.m0);
    TEST(3.0f == k.m1);
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

    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<3> > ));

    INTROSPECTION_STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));

    getOutput() << x << '\n';
    getOutput() << y << '\n';
    getOutput() << z << '\n';
    getOutput() << a << '\n';

    std::istringstream stream("22 3.0 3");
    type k;
    stream >> k;
    TEST(22 == k.m0);
    TEST(3.0f == k.m1);
    TEST('3' == k.m2);
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

    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<4> > ));

    INTROSPECTION_STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));

    getOutput() << x << '\n';
    getOutput() << y << '\n';
    getOutput() << z << '\n';
    getOutput() << a << '\n';
    getOutput() << b << '\n';

    std::istringstream stream("22 3.0 3 1");
    type k;
    stream >> k;
    TEST(22 == k.m0);
    TEST(3.0f == k.m1);
    TEST('3' == k.m2);
    TEST(true == k.m3);
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

    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<5> > ));

    INTROSPECTION_STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<unsigned, GetIntrospectionItem<type, Integer<4> >::type> ));

    getOutput() << x << '\n';
    getOutput() << y << '\n';
    getOutput() << z << '\n';
    getOutput() << a << '\n';
    getOutput() << b << '\n';
    getOutput() << c << '\n';

    std::istringstream stream("22 3.0 3 1 12345");
    type k;
    stream >> k;
    TEST(22 == k.m0);
    TEST(3.0f == k.m1);
    TEST('3' == k.m2);
    TEST(true == k.m3);
    TEST(12345U == k.m4);
}

void test_sextuple()
{
    typedef sextuple<int, float, char, bool, unsigned, long, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a', false, 3U, 99L};
    type y = {2, 3.5f, 'a', false, 3U, 99L};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    TEST(false == x.m3);
    TEST(3U == x.m4);
    TEST(99L == x.m5);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a', false, 3U, 99L};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b', false, 3U, 99L};
    test_generated_operations(x, a);

    // Differ in the m3 value
    type b = {1, 3.5f, 'a', true, 3U, 99L};
    test_generated_operations(x, b);

    // Differ in the m4 value
    type c = {1, 3.5f, 'a', true, 4U, 99L};
    test_generated_operations(x, c);

    // Differ in the m5 value
    type d = {1, 3.5f, 'a', true, 4U, 100L};
    test_generated_operations(x, d);

    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<5> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<6> > ));

    INTROSPECTION_STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<unsigned, GetIntrospectionItem<type, Integer<4> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetIntrospectionItem<type, Integer<5> >::type> ));

    getOutput() << x << '\n';
    getOutput() << y << '\n';
    getOutput() << z << '\n';
    getOutput() << a << '\n';
    getOutput() << b << '\n';
    getOutput() << c << '\n';
    getOutput() << d << '\n';

    std::istringstream stream("22 3.0 3 1 12345 112132");
    type k;
    stream >> k;
    TEST(22 == k.m0);
    TEST(3.0f == k.m1);
    TEST('3' == k.m2);
    TEST(true == k.m3);
    TEST(12345U == k.m4);
    TEST(112132L == k.m5);
}

void test_septuple()
{
    typedef septuple<int, float, char, bool, unsigned, long, double, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a', false, 3U, 99L, 1.0};
    type y = {2, 3.5f, 'a', false, 3U, 99L, 1.0};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    TEST(false == x.m3);
    TEST(3U == x.m4);
    TEST(99L == x.m5);
    TEST(1.0 == x.m6);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a', false, 3U, 99L, 1.0};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b', false, 3U, 99L, 1.0};
    test_generated_operations(x, a);

    // Differ in the m3 value
    type b = {1, 3.5f, 'a', true, 3U, 99L, 1.0};
    test_generated_operations(x, b);

    // Differ in the m4 value
    type c = {1, 3.5f, 'a', true, 4U, 99L, 1.0};
    test_generated_operations(x, c);

    // Differ in the m5 value
    type d = {1, 3.5f, 'a', true, 4U, 100L, 1.0};
    test_generated_operations(x, d);

    // Differ in the m6 value
    type e = {1, 3.5f, 'a', true, 4U, 100L, 2.0};
    test_generated_operations(x, e);

    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<5> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<6> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<7> > ));

    INTROSPECTION_STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<unsigned, GetIntrospectionItem<type, Integer<4> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetIntrospectionItem<type, Integer<5> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<double, GetIntrospectionItem<type, Integer<6> >::type> ));

    getOutput() << x << '\n';
    getOutput() << y << '\n';
    getOutput() << z << '\n';
    getOutput() << a << '\n';
    getOutput() << b << '\n';
    getOutput() << c << '\n';
    getOutput() << d << '\n';
    getOutput() << e << '\n';

    std::istringstream stream("22 3.0 3 1 12345 112132 3.3e7");
    type k;
    stream >> k;
    TEST(22 == k.m0);
    TEST(3.0f == k.m1);
    TEST('3' == k.m2);
    TEST(true == k.m3);
    TEST(12345U == k.m4);
    TEST(112132L == k.m5);
    TEST(3.3e7 == k.m6);
}

void test_octuple()
{
    typedef octuple<int, float, char, bool, unsigned, long, double, unsigned long, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a', false, 3U, 99L, 1.0, 3UL};
    type y = {2, 3.5f, 'a', false, 3U, 99L, 1.0, 3UL};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    TEST(false == x.m3);
    TEST(3U == x.m4);
    TEST(99L == x.m5);
    TEST(1.0 == x.m6);
    TEST(3UL == x.m7);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a', false, 3U, 99L, 1.0, 3UL};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b', false, 3U, 99L, 1.0, 3UL};
    test_generated_operations(x, a);

    // Differ in the m3 value
    type b = {1, 3.5f, 'a', true, 3U, 99L, 1.0, 3UL};
    test_generated_operations(x, b);

    // Differ in the m4 value
    type c = {1, 3.5f, 'a', true, 4U, 99L, 1.0, 3UL};
    test_generated_operations(x, c);

    // Differ in the m5 value
    type d = {1, 3.5f, 'a', true, 4U, 100L, 1.0, 3UL};
    test_generated_operations(x, d);

    // Differ in the m6 value
    type e = {1, 3.5f, 'a', true, 4U, 100L, 2.0, 3UL};
    test_generated_operations(x, e);

    // Differ in the m7 value
    type f = {1, 3.5f, 'a', true, 4U, 100L, 2.0, 4UL};
    test_generated_operations(x, f);

    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<5> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<6> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<7> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<8> > ));

    INTROSPECTION_STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<unsigned, GetIntrospectionItem<type, Integer<4> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetIntrospectionItem<type, Integer<5> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<double, GetIntrospectionItem<type, Integer<6> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<unsigned long, GetIntrospectionItem<type, Integer<7> >::type> ));

    getOutput() << x << '\n';
    getOutput() << y << '\n';
    getOutput() << z << '\n';
    getOutput() << a << '\n';
    getOutput() << b << '\n';
    getOutput() << c << '\n';
    getOutput() << d << '\n';
    getOutput() << e << '\n';
    getOutput() << f << '\n';

    std::istringstream stream("22 3.0 3 1 12345 112132 3.3e7 22");
    type k;
    stream >> k;
    TEST(22 == k.m0);
    TEST(3.0f == k.m1);
    TEST('3' == k.m2);
    TEST(true == k.m3);
    TEST(12345U == k.m4);
    TEST(112132L == k.m5);
    TEST(3.3e7 == k.m6);
    TEST(22UL == k.m7);
}

void test_nonuple()
{
    typedef nonuple<int, float, char, bool, unsigned, long, double, unsigned long, bool, DefaultTag> type;
    // Differed in the m0 value
    type x = {1, 3.5f, 'a', false, 3U, 99L, 1.0, 3UL, false};
    type y = {2, 3.5f, 'a', false, 3U, 99L, 1.0, 3UL, false};
    TEST(1 == x.m0);
    TEST(3.5f == x.m1);
    TEST('a' == x.m2);
    TEST(false == x.m3);
    TEST(3U == x.m4);
    TEST(99L == x.m5);
    TEST(1.0 == x.m6);
    TEST(3UL == x.m7);
    TEST(false == x.m8);
    test_generated_operations(x, y);

    // Differ in the m1 value
    type z = {1, 4.0f, 'a', false, 3U, 99L, 1.0, 3UL, false};
    test_generated_operations(x, z);

    // Differ in the m2 value
    type a = {1, 3.5f, 'b', false, 3U, 99L, 1.0, 3UL, false};
    test_generated_operations(x, a);

    // Differ in the m3 value
    type b = {1, 3.5f, 'a', true, 3U, 99L, 1.0, 3UL, false};
    test_generated_operations(x, b);

    // Differ in the m4 value
    type c = {1, 3.5f, 'a', true, 4U, 99L, 1.0, 3UL, false};
    test_generated_operations(x, c);

    // Differ in the m5 value
    type d = {1, 3.5f, 'a', true, 4U, 100L, 1.0, 3UL, false};
    test_generated_operations(x, d);

    // Differ in the m6 value
    type e = {1, 3.5f, 'a', true, 4U, 100L, 2.0, 3UL, false};
    test_generated_operations(x, e);

    // Differ in the m7 value
    type f = {1, 3.5f, 'a', true, 4U, 100L, 2.0, 4UL, false};
    test_generated_operations(x, f);

    // Differ in the m8 value
    type g = {1, 3.5f, 'a', true, 4U, 100L, 2.0, 4UL, true};
    test_generated_operations(x, g);

    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<5> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<6> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<7> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<8> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<9> > ));

    INTROSPECTION_STATIC_ASSERT2(( is_same<int, GetIntrospectionItem<type, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetIntrospectionItem<type, Integer<1> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<char, GetIntrospectionItem<type, Integer<2> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<3> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<unsigned, GetIntrospectionItem<type, Integer<4> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetIntrospectionItem<type, Integer<5> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<double, GetIntrospectionItem<type, Integer<6> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<unsigned long, GetIntrospectionItem<type, Integer<7> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetIntrospectionItem<type, Integer<8> >::type> ));

    getOutput() << x << '\n';
    getOutput() << y << '\n';
    getOutput() << z << '\n';
    getOutput() << a << '\n';
    getOutput() << b << '\n';
    getOutput() << c << '\n';
    getOutput() << d << '\n';
    getOutput() << e << '\n';
    getOutput() << f << '\n';
    getOutput() << g << '\n';

    std::istringstream stream("22 3.0 3 1 12345 112132 3.3e7 22 0");
    type k;
    stream >> k;
    TEST(22 == k.m0);
    TEST(3.0f == k.m1);
    TEST('3' == k.m2);
    TEST(true == k.m3);
    TEST(12345U == k.m4);
    TEST(112132L == k.m5);
    TEST(3.3e7 == k.m6);
    TEST(22UL == k.m7);
    TEST(false == k.m8);
}

void test_storage_reference_types()
{
    typedef singleton<int&, DefaultTag> type;
    int tmp = 0;
    type x = {tmp};
    type y = type::make(make_ref(tmp));
    (void) x;
    (void) y;

    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<1> > ));

    INTROSPECTION_STATIC_ASSERT2(( is_same<int&, GetIntrospectionItem<type, Integer<0> >::type> ));
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
};

void test_numbered_introspection()
{
    typedef NumberedStorageType type;
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<9>, IntrospectionArity<type>::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Array<Integer<0>, Integer<1>, Integer<2>, Integer<3>, Integer<4>, Integer<5>, Integer<6>, Integer<7>, Integer<8> >, GenerateIntrospectionItems<type>::type> ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<2> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<3> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<4> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<5> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<6> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<7> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasIntrospectionItem<type, Integer<8> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasIntrospectionItem<type, Integer<9> > ));

    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<0>, GetIntrospectionItem<type, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<1>, GetIntrospectionItem<type, Integer<1> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<2>, GetIntrospectionItem<type, Integer<2> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<3>, GetIntrospectionItem<type, Integer<3> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<4>, GetIntrospectionItem<type, Integer<4> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<5>, GetIntrospectionItem<type, Integer<5> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<6>, GetIntrospectionItem<type, Integer<6> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<7>, GetIntrospectionItem<type, Integer<7> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<8>, GetIntrospectionItem<type, Integer<8> >::type> ));
}

typedef triple<int, long, char> VisitorTestType;

struct TestVisitor
{
  bool visit0;
  bool visit1;
  bool visit2;
  bool visitStart;
  bool visitEnd;
  void operator()(int const&, Integer<0>) { visit0 = true; }
  void operator()(long const&, Integer<1>) { visit1 = true; }
  void operator()(char const&, Integer<2>) { visit2 = true; }
  void operator()(VisitStart) { visitStart = true; }
  void operator()(VisitEnd) { visitEnd = true; }
};

struct TestVisitor2
{
  bool visit0;
  bool visit1;
  bool visit2;
  bool visitStart;
  bool visitEnd;
  void operator()(int const&, int const&, Integer<0>) { visit0 = true; }
  void operator()(long const&, long const&, Integer<1>) { visit1 = true; }
  void operator()(char const&, char const&, Integer<2>) { visit2 = true; }
  void operator()(VisitStart) { visitStart = true; }
  void operator()(VisitEnd) { visitEnd = true; }
};

void test_visit()
{
  // Visitor mechanism uses looping so testing a short
  // container exercises no different (meta)code to a
  // longer container.
  {
    TestVisitor v = {false, false, false, false, false};
    VisitorTestType t = {3, 9L, 'a'};
    v = visit(t, v);
    TEST(v.visit0);
    TEST(v.visit1);
    TEST(v.visit2);
    TEST(!v.visitStart);
    TEST(!v.visitEnd);
  }

  {
    TestVisitor v = {false, false, false, false, false};
    VisitorTestType t = {3, 9L, 'a'};
    v = visit_with_start_end(t, v);
    TEST(v.visit0);
    TEST(v.visit1);
    TEST(v.visit2);
    TEST(v.visitStart);
    TEST(v.visitEnd);
  }

  {
    TestVisitor2 v = {false, false, false, false, false};
    VisitorTestType t = {3, 9L, 'a'};
    v = visit(t, t, v);
    TEST(v.visit0);
    TEST(v.visit1);
    TEST(v.visit2);
    TEST(!v.visitStart);
    TEST(!v.visitEnd);
  }

  {
    TestVisitor2 v = {false, false, false, false, false};
    VisitorTestType t = {3, 9L, 'a'};
    v = visit_with_start_end(t, t, v);
    TEST(v.visit0);
    TEST(v.visit1);
    TEST(v.visit2);
    TEST(v.visitStart);
    TEST(v.visitEnd);
  }
}

void testfun0()
{
  typedef int(*type)();
  INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<type, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<0>, GetFunctionArity<type>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<>, GetInputTypeArray<type>::type> ));
}

void testfun1()
{
  typedef int(*type)(long);
  INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<type, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<1>, GetFunctionArity<type>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long>, GetInputTypeArray<type>::type> ));
}

void testfun2()
{
  typedef int(*type)(long, float);
  INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<type, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<2>, GetFunctionArity<type>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long, float>, GetInputTypeArray<type>::type> ));
}

void testfun3()
{
  typedef int(*type)(long, float, short&);
  INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<type, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<short&, GetInputType<type, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<3>, GetFunctionArity<type>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long, float, short&>, GetInputTypeArray<type>::type> ));
}

void testfun4()
{
  typedef int(*type)(long, float, short&, int const&);
  INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<type, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<short&, GetInputType<type, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int const&, GetInputType<type, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<4>, GetFunctionArity<type>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long, float, short&, int const&>, GetInputTypeArray<type>::type> ));
}

void testfun5()
{
  typedef int(*type)(long, float, short&, int const&, bool);
  INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<type, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<short&, GetInputType<type, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int const&, GetInputType<type, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetInputType<type, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<5>, GetFunctionArity<type>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long, float, short&, int const&, bool>, GetInputTypeArray<type>::type> ));
}

void testfun6()
{
  typedef int(*type)(long, float, short&, int const&, bool, int volatile*&);
  INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<type, Integer<6> > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<short&, GetInputType<type, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int const&, GetInputType<type, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetInputType<type, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int volatile*&, GetInputType<type, Integer<5> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<6>, GetFunctionArity<type>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long, float, short&, int const&, bool, int volatile*&>, GetInputTypeArray<type>::type> ));
}

void testfun7()
{
  typedef int(*type)(long, float, short&, int const&, bool, int volatile*&, true_type&);
  INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<6> > ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<type, Integer<7> > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<short&, GetInputType<type, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int const&, GetInputType<type, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetInputType<type, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int volatile*&, GetInputType<type, Integer<5> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<true_type&, GetInputType<type, Integer<6> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<7>, GetFunctionArity<type>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long, float, short&, int const&, bool, int volatile*&, true_type&>, GetInputTypeArray<type>::type> ));
}

void testfun8()
{
  typedef int(*type)(long, float, short&, int const&, bool, int volatile*&, true_type&, void*);
  INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<6> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<7> > ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<type, Integer<8> > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<short&, GetInputType<type, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int const&, GetInputType<type, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetInputType<type, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int volatile*&, GetInputType<type, Integer<5> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<true_type&, GetInputType<type, Integer<6> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<void*, GetInputType<type, Integer<7> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<8>, GetFunctionArity<type>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long, float, short&, int const&, bool, int volatile*&, true_type&, void*>, GetInputTypeArray<type>::type> ));
}

void testfun9()
{
  typedef int(*type)(long, float, short&, int const&, bool, int volatile*&, true_type&, void*, char(&)[10]);
  INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<6> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<7> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<8> > ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<type, Integer<9> > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<short&, GetInputType<type, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int const&, GetInputType<type, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetInputType<type, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int volatile*&, GetInputType<type, Integer<5> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<true_type&, GetInputType<type, Integer<6> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<void*, GetInputType<type, Integer<7> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<char(&)[10], GetInputType<type, Integer<8> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<9>, GetFunctionArity<type>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long, float, short&, int const&, bool, int volatile*&, true_type&, void*, char(&)[10]>, GetInputTypeArray<type>::type> ));
}

void testfun10()
{
  typedef int(*type)(long, float, short&, int const&, bool, int volatile*&, true_type&, void*, char(&)[10], void(*)());
  INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<type>::type,int> ));
  INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<type> ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<6> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<7> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<8> > ));
  INTROSPECTION_STATIC_ASSERT2(( HasInputType<type, Integer<9> > ));
  INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<type, Integer<10> > ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetInputType<type, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<float, GetInputType<type, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<short&, GetInputType<type, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int const&, GetInputType<type, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<bool, GetInputType<type, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<int volatile*&, GetInputType<type, Integer<5> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<true_type&, GetInputType<type, Integer<6> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<void*, GetInputType<type, Integer<7> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<char(&)[10], GetInputType<type, Integer<8> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<void(*)(), GetInputType<type, Integer<9> >::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<10>, GetFunctionArity<type>::type> ));
  INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long, float, short&, int const&, bool, int volatile*&, true_type&, void*, char(&)[10], void(*)()>, GetInputTypeArray<type>::type> ));
}

struct MyFunctionObject
{
    typedef long input_type_0;
    typedef int codomain_type;
    int operator()(long){ return 1; }

  static void test()
  {
    INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<MyFunctionObject>::type,int> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<MyFunctionObject>::type,int> ));
    INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<MyFunctionObject> ));
    INTROSPECTION_STATIC_ASSERT2(( HasInputType<MyFunctionObject, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<MyFunctionObject, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<long, GetInputType<MyFunctionObject, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<1>, GetFunctionArity<MyFunctionObject>::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long>, GetInputTypeArray<MyFunctionObject>::type> ));
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
    INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<MyRefFunctionObject>::type,int&> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<MyRefFunctionObject>::type,int&> ));
    INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<MyRefFunctionObject> ));
    INTROSPECTION_STATIC_ASSERT2(( HasInputType<MyRefFunctionObject, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<MyRefFunctionObject, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<long const&, GetInputType<MyRefFunctionObject, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<1>, GetFunctionArity<MyRefFunctionObject>::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Array<long const&>, GetInputTypeArray<MyRefFunctionObject>::type> ));
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
    INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<MyGenericFunctionObject>::type,CodomainDeduction<ReturnFirstValue<placeholders::_0> > > ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<MyGenericFunctionObject, int>::type,int> ));
    INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<MyGenericFunctionObject> ));
    INTROSPECTION_STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<MyGenericFunctionObject, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<1>, GetFunctionArity<MyGenericFunctionObject>::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Array<template_param>, GetInputTypeArray<MyGenericFunctionObject>::type> ));
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
    INTROSPECTION_STATIC_ASSERT2(( is_same<GetCodomainType<MyGenericFunctionObject2>::type,CodomainDeduction<ReturnThirdValue> > ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<DeduceCodomainType<MyGenericFunctionObject2, char, short, int, float, void*>::type,int> ));
    INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<MyGenericFunctionObject2> ));
    INTROSPECTION_STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject2, Integer<0> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject2, Integer<1> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject2, Integer<2> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject2, Integer<3> > ));
    INTROSPECTION_STATIC_ASSERT2(( HasInputType<MyGenericFunctionObject2, Integer<4> > ));
    INTROSPECTION_STATIC_ASSERT_NOT2(( HasInputType<MyGenericFunctionObject2, Integer<5> > ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<0> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<1> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<2> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<3> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<4> >::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Integer<5>, GetFunctionArity<MyGenericFunctionObject2>::type> ));
    INTROSPECTION_STATIC_ASSERT2(( is_same<Array<template_param, template_param, template_param, template_param, template_param>, GetInputTypeArray<MyGenericFunctionObject2>::type> ));
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

  void voidFun5(int, char&, double (&)[], int const volatile (&)[10], void(*)()) const {}
  int intFun5(int, char&, double (&)[], int const volatile (&)[10], void(*)()) { return 0; }

  void voidFun6(int, char&, double (&)[], int const volatile (&)[10], void(*)(), long) const {}
  int intFun6(int, char&, double (&)[], int const volatile (&)[10], void(*)(), long) { return 0; }

  void voidFun7(int, char&, double (&)[], int const volatile (&)[10], void(*)(), long, float) const {}
  int intFun7(int, char&, double (&)[], int const volatile (&)[10], void(*)(), long, float) { return 0; }

  void voidFun8(int, char&, double (&)[], int const volatile (&)[10], void(*)(), long, float, bool) const {}
  int intFun8(int, char&, double (&)[], int const volatile (&)[10], void(*)(), long, float, bool) { return 0; }

  void voidFun9(int, char&, double (&)[], int const volatile (&)[10], void(*)(), long, float, bool, int) const {}
  int intFun9(int, char&, double (&)[], int const volatile (&)[10], void(*)(), long, float, bool, int) { return 0; }

};

template<typename ReturnType, typename Input0, typename T>
void testMemberFun0(T func)
{
  INTROSPECTION_STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT_NOT(( HasInputType<T, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Integer<1>, typename GetFunctionArity<T>::type > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Array<Input0>, typename GetInputTypeArray<T>::type> ));
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun1(T func)
{
  INTROSPECTION_STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT_NOT(( HasInputType<T, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Integer<2>, typename GetFunctionArity<T>::type > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Array<Input0, int>, typename GetInputTypeArray<T>::type> ));
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun2(T func)
{
  INTROSPECTION_STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT_NOT(( HasInputType<T, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<char&, typename GetInputType<T, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Integer<3>, typename GetFunctionArity<T>::type > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Array<Input0, int, char&>, typename GetInputTypeArray<T>::type> ));
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun3(T func)
{
  INTROSPECTION_STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT_NOT(( HasInputType<T, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<char&, typename GetInputType<T, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<double (&)[], typename GetInputType<T, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Integer<4>, typename GetFunctionArity<T>::type > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Array<Input0, int, char&, double (&)[]>, typename GetInputTypeArray<T>::type> ));
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun4(T func)
{
  INTROSPECTION_STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT_NOT(( HasInputType<T, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<char&, typename GetInputType<T, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<double (&)[], typename GetInputType<T, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int const volatile (&)[10], typename GetInputType<T, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Integer<5>, typename GetFunctionArity<T>::type > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Array<Input0, int, char&, double (&)[], int const volatile (&)[10]>, typename GetInputTypeArray<T>::type> ));
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun5(T func)
{
  INTROSPECTION_STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT_NOT(( HasInputType<T, Integer<6> > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<char&, typename GetInputType<T, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<double (&)[], typename GetInputType<T, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int const volatile (&)[10], typename GetInputType<T, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<void(*)(), typename GetInputType<T, Integer<5> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Integer<6>, typename GetFunctionArity<T>::type > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Array<Input0, int, char&, double (&)[], int const volatile (&)[10], void(*)()>, typename GetInputTypeArray<T>::type> ));
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun6(T func)
{
  INTROSPECTION_STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<6> > ));
  INTROSPECTION_STATIC_ASSERT_NOT(( HasInputType<T, Integer<7> > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<char&, typename GetInputType<T, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<double (&)[], typename GetInputType<T, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int const volatile (&)[10], typename GetInputType<T, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<void(*)(), typename GetInputType<T, Integer<5> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<long, typename GetInputType<T, Integer<6> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Integer<7>, typename GetFunctionArity<T>::type > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Array<Input0, int, char&, double (&)[], int const volatile (&)[10], void(*)(), long>, typename GetInputTypeArray<T>::type> ));
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun7(T func)
{
  INTROSPECTION_STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<6> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<7> > ));
  INTROSPECTION_STATIC_ASSERT_NOT(( HasInputType<T, Integer<8> > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<char&, typename GetInputType<T, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<double (&)[], typename GetInputType<T, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int const volatile (&)[10], typename GetInputType<T, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<void(*)(), typename GetInputType<T, Integer<5> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<long, typename GetInputType<T, Integer<6> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<float, typename GetInputType<T, Integer<7> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Integer<8>, typename GetFunctionArity<T>::type > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Array<Input0, int, char&, double (&)[], int const volatile (&)[10], void(*)(), long, float>, typename GetInputTypeArray<T>::type> ));
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun8(T func)
{
  INTROSPECTION_STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<6> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<7> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<8> > ));
  INTROSPECTION_STATIC_ASSERT_NOT(( HasInputType<T, Integer<9> > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<char&, typename GetInputType<T, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<double (&)[], typename GetInputType<T, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int const volatile (&)[10], typename GetInputType<T, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<void(*)(), typename GetInputType<T, Integer<5> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<long, typename GetInputType<T, Integer<6> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<float, typename GetInputType<T, Integer<7> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<bool, typename GetInputType<T, Integer<8> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Integer<9>, typename GetFunctionArity<T>::type > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Array<Input0, int, char&, double (&)[], int const volatile (&)[10], void(*)(), long, float, bool>, typename GetInputTypeArray<T>::type> ));
}

template<typename ReturnType, typename Input0, typename T>
void testMemberFun9(T func)
{
  INTROSPECTION_STATIC_ASSERT(( is_same<typename GetCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<typename DeduceCodomainType<T>::type,ReturnType> ));
  INTROSPECTION_STATIC_ASSERT(( FunctionSignatureEnabled<T> ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<0> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<1> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<2> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<3> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<4> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<5> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<6> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<7> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<8> > ));
  INTROSPECTION_STATIC_ASSERT(( HasInputType<T, Integer<9> > ));
  INTROSPECTION_STATIC_ASSERT_NOT(( HasInputType<T, Integer<10> > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Input0, typename GetInputType<T, Integer<0> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<1> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<char&, typename GetInputType<T, Integer<2> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<double (&)[], typename GetInputType<T, Integer<3> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int const volatile (&)[10], typename GetInputType<T, Integer<4> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<void(*)(), typename GetInputType<T, Integer<5> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<long, typename GetInputType<T, Integer<6> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<float, typename GetInputType<T, Integer<7> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<bool, typename GetInputType<T, Integer<8> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<int, typename GetInputType<T, Integer<9> >::type> ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Integer<10>, typename GetFunctionArity<T>::type > ));
  INTROSPECTION_STATIC_ASSERT(( is_same<Array<Input0, int, char&, double (&)[], int const volatile (&)[10], void(*)(), long, float, bool, int>, typename GetInputTypeArray<T>::type> ));
}

void test_function_signatures()
{
  testfun0();
  testfun1();
  testfun2();
  testfun3();
  testfun4();
  testfun5();
  testfun6();
  testfun7();
  testfun8();
  testfun9();
  testfun10();

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

  testMemberFun5<void, MemberFunctionTest const&>(&MemberFunctionTest::voidFun5);
  testMemberFun5<int, MemberFunctionTest&>(&MemberFunctionTest::intFun5);

  testMemberFun6<void, MemberFunctionTest const&>(&MemberFunctionTest::voidFun6);
  testMemberFun6<int, MemberFunctionTest&>(&MemberFunctionTest::intFun6);

  testMemberFun7<void, MemberFunctionTest const&>(&MemberFunctionTest::voidFun7);
  testMemberFun7<int, MemberFunctionTest&>(&MemberFunctionTest::intFun7);

  testMemberFun8<void, MemberFunctionTest const&>(&MemberFunctionTest::voidFun8);
  testMemberFun8<int, MemberFunctionTest&>(&MemberFunctionTest::intFun8);

  testMemberFun9<void, MemberFunctionTest const&>(&MemberFunctionTest::voidFun9);
  testMemberFun9<int, MemberFunctionTest&>(&MemberFunctionTest::intFun9);
}

#ifdef INTROSPECTION_COMPILATION_FAILURE_TESTS
INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<void(*)(int, int, int, int, int, int, int, int, int, int, int)> ));
INTROSPECTION_STATIC_ASSERT2(( FunctionSignatureEnabled<void(MemberFunctionTest::*)(int, int, int, int, int, int, int, int, int, int)> ));
#endif

namespace Apply_stress_test {
using namespace placeholders;

template<int base>
struct ArrayFrom : Array<Integer<base>,Integer<base + 1>,Integer<base + 2>,Integer<base + 3>,Integer<base + 4>,Integer<base + 5>,Integer<base + 6>,Integer<base + 7>,Integer<base + 8>,Integer<base + 9> > {};

typedef ArrayTransform<ArrayFrom<0>::type, _0> Apply1;
INTROSPECTION_STATIC_ASSERT2(( is_same<ArrayFrom<0>::type, Apply1::type> ));

#ifdef INTROSPECTION_APPLY_STRESS_TEST
template<int base>
struct ArrayArrayFrom : Array<typename ArrayFrom<base>::type, typename ArrayFrom<base + 10>::type, typename ArrayFrom<base + 20>::type, typename ArrayFrom<base + 30>::type, typename ArrayFrom<base + 40>::type, typename ArrayFrom<base + 50>::type, typename ArrayFrom<base + 60>::type, typename ArrayFrom<base + 70>::type, typename ArrayFrom<base + 80>::type, typename ArrayFrom<base + 90>::type > {};

// Need to delay the evaluation of the right-hand _0 until later, using the identity_type
typedef ArrayTransform<ArrayArrayFrom<10>::type, ArrayTransform<_0, identity_type<_0> > > Apply2;
INTROSPECTION_STATIC_ASSERT2(( is_same<ArrayArrayFrom<10>::type, Apply2::type> ));



template<int base>
struct ArrayArrayArrayFrom : Array<typename ArrayArrayFrom<base>::type, typename ArrayArrayFrom<base + 100>::type, typename ArrayArrayFrom<base + 200>::type, typename ArrayArrayFrom<base + 300>::type, typename ArrayArrayFrom<base + 400>::type, typename ArrayArrayFrom<base + 500>::type, typename ArrayArrayFrom<base + 600>::type, typename ArrayArrayFrom<base + 700>::type, typename ArrayArrayFrom<base + 800>::type, typename ArrayArrayFrom<base + 900>::type > {};

typedef ArrayTransform<ArrayArrayArrayFrom<1000>::type, ArrayTransform<_0, ArrayTransform<_0, identity_type<_0> > > > Apply3;
INTROSPECTION_STATIC_ASSERT2(( is_same<ArrayArrayArrayFrom<1000>::type, Apply3::type> ));



template<int base>
struct ArrayArrayArrayArrayFrom : Array<typename ArrayArrayArrayFrom<base>::type, typename ArrayArrayArrayFrom<base + 1000>::type, typename ArrayArrayArrayFrom<base + 2000>::type, typename ArrayArrayArrayFrom<base + 3000>::type, typename ArrayArrayArrayFrom<base + 4000>::type, typename ArrayArrayArrayFrom<base + 5000>::type, typename ArrayArrayArrayFrom<base + 6000>::type, typename ArrayArrayArrayFrom<base + 7000>::type, typename ArrayArrayArrayFrom<base + 8000>::type, typename ArrayArrayArrayFrom<base + 9000>::type > {};

typedef ArrayTransform<ArrayArrayArrayArrayFrom<10000>::type, ArrayTransform<_0, ArrayTransform<_0, ArrayTransform<_0, identity_type<_0> > > > > Apply4;
INTROSPECTION_STATIC_ASSERT2(( is_same<ArrayArrayArrayArrayFrom<10000>::type, Apply4::type> ));



template<int base>
struct ArrayArrayArrayArrayArrayFrom : Array<typename ArrayArrayArrayArrayFrom<base>::type, typename ArrayArrayArrayArrayFrom<base + 10000>::type, typename ArrayArrayArrayArrayFrom<base + 20000>::type, typename ArrayArrayArrayArrayFrom<base + 30000>::type, typename ArrayArrayArrayArrayFrom<base + 40000>::type, typename ArrayArrayArrayArrayFrom<base + 50000>::type, typename ArrayArrayArrayArrayFrom<base + 60000>::type, typename ArrayArrayArrayArrayFrom<base + 70000>::type, typename ArrayArrayArrayArrayFrom<base + 80000>::type, typename ArrayArrayArrayArrayFrom<base + 90000>::type > {};

typedef ArrayTransform<ArrayArrayArrayArrayArrayFrom<100000>::type, ArrayTransform<_0, ArrayTransform<_0, ArrayTransform<_0, ArrayTransform<_0, identity_type<_0> > > > > > Apply5;
INTROSPECTION_STATIC_ASSERT2(( is_same<ArrayArrayArrayArrayArrayFrom<100000>::type, Apply5::type> ));
#endif //INTROSPECTION_APPLY_STRESS_TEST

} // namespace Apply_stress_test

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
    test_storage_reference_types();
    test_numbered_introspection();
    test_visit();

    test_function_signatures();
}
