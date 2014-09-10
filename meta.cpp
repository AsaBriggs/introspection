#include <cassert>
#include "storage.h"
#include "function_signatures.h"

namespace intro {
namespace {

#define TEST(x) assert((x))

const char EXPECTED_VALUE = 'a';
const char UNEXPECTED_VALUE = 'b';

template<typename T>
typename enable_if<is_same<T, int>, char>::type enable_if_test() { return EXPECTED_VALUE; }

template<typename T>
typename enable_if<not_<is_same<T, int> >, char>::type enable_if_test() { return UNEXPECTED_VALUE; }

template<typename T>
typename disable_if<is_same<T, int>, char>::type disable_if_test() { return UNEXPECTED_VALUE; }

template<typename T>
typename disable_if<not_<is_same<T, int> >, char>::type disable_if_test() { return EXPECTED_VALUE; }

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

  TEST((typename is_same< ExpectedArray,
            typename ArrayConcat<typename ArrayIndex<BoolArray, LHSIndex>::type,
                                 typename ArrayIndex<BoolArray, RHSIndex>::type>::type>::type()));
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
  TEST((is_same<Array<Array<>,
                      TestArray>,
        ArraySplit<TestArray, Integer<0> >::type>()));

  TEST((is_same<Array<Array<bool>,
                      Array<unsigned char, signed char, char, short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<1> >::type>()));

  TEST((is_same<Array<Array<bool, unsigned char>,
                Array<signed char, char, short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<2> >::type>()));

  TEST((is_same<Array<Array<bool, unsigned char, signed char>,
                      Array<char, short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<3> >::type>()));

  TEST((is_same<Array<Array<bool, unsigned char, signed char, char>,
                      Array<short, unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<4> >::type>()));

  TEST((is_same<Array<Array<bool, unsigned char, signed char, char,short>,
                      Array<unsigned short, int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<5> >::type>()));

  TEST((is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short>,
                      Array<int, unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<6> >::type>()));

  TEST((is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short, int>,
                      Array<unsigned int, long, unsigned long> >,
        ArraySplit<TestArray, Integer<7> >::type>()));

  TEST((is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short, int, unsigned int>,
                      Array<long, unsigned long> >,
        ArraySplit<TestArray, Integer<8> >::type>()));

  TEST((is_same<Array<Array<bool, unsigned char, signed char, char, short, unsigned short, int, unsigned int, long>,
                      Array<unsigned long> >,
        ArraySplit<TestArray, Integer<9> >::type>()));

  TEST((is_same<Array<TestArray,
                      Array<> >,
        ArraySplit<TestArray, Integer<10> >::type>()));
}

template<typename Length>
void test_array_reverse2()
{
  typedef typename ArraySplit<TestArray, Length>::type SplitArray;
  typedef typename ArrayReverse<typename ArrayIndex<SplitArray, Integer<0> >::type>::type ReversedFirst;
  typedef typename ArrayReverse<typename ArrayIndex<SplitArray, Integer<1> >::type>::type ReversedSecond;
  typedef typename ArrayConcat<ReversedSecond, ReversedFirst>::type Result;
  TEST((is_same<ReversedTestArray, Result>()));
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
  TEST((is_same<Expected, ArrayRotate<TestArray, Integer<1>, Integer<3>, Integer<6> >::type >()));

  typedef Array<unsigned short, int, unsigned int, long, unsigned long, bool, unsigned char, signed char, char, short> Expected2;
  // rotate test array about index 5, i.e. from bool up to but not including unsigned short is rotated
  TEST((is_same<Expected2, ArrayRotateDefault<TestArray, Integer<5> >::type >()));
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

  TEST((is_same<ArrayTransform<Integers, AddOne>::type, Expected>()));
  TEST((is_same<ArrayTransform<Integers, Add<placeholders::_0, Integer<1> > >::type, Expected>()));
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

  TEST((is_same<ArrayZip<Integers, MoreIntegers, AddTogether>::type, Expected>()));
  TEST((is_same<ArrayZip<Integers, MoreIntegers, Add<placeholders::_0, placeholders::_1> >::type, Expected>()));
}

void test_apply()
{
  TEST((is_same<empty_type<int>, Apply<empty_type<int> >::type>::type()));
  TEST((is_same<empty_type<int>, Apply<empty_type<int>, short, double, char, float, void >::type>::type()));

  TEST((is_same<empty_type<bool>, Apply<empty_type<placeholders::_0>, bool, int, long, float, short>::type>::type()));
  TEST((is_same<empty_type<int>, Apply<empty_type<placeholders::_1>, bool, int, long, float, short>::type>::type()));
  TEST((is_same<empty_type<long>, Apply<empty_type<placeholders::_2>, bool, int, long, float, short>::type>::type()));
  TEST((is_same<empty_type<float>, Apply<empty_type<placeholders::_3>, bool, int, long, float, short>::type>::type()));
  TEST((is_same<empty_type<short>, Apply<empty_type<placeholders::_4>, bool, int, long, float, short>::type>::type()));

  TEST((is_same<Integer<3>, Apply<AddTogether, Integer<1>, Integer<2> >::type>::type()));
}

void test_metaprogramming()
{
  TEST(true_type());
  TEST(!false_type());

  int x = 0;
  Ref<int> y = make_ref(x);
  TEST(y.m0 == &x);

  TEST( Integer<1>() == Successor<Integer<0> >::type());
  TEST( Integer<3>() == Successor<Integer<2> >::type());

  TEST( Integer<0>() == Predecessor<Integer<1> >::type());
  TEST( Integer<-2>() == Predecessor<Integer<-1> >::type());

  TEST((Integer<0>() == Min<Integer<0>, Integer<1> >::type()));
  TEST((Integer<0>() == Min<Integer<1>, Integer<0> >::type()));

  TEST((Integer<-1>() == Subtract<Integer<0>, Integer<1> >::type()));
  TEST((Integer<6>() == Subtract<Integer<1>, Integer<-5> >::type()));

  TEST((Integer<5>() == Add<Integer<3>, Integer<2> >::type()));
  TEST((Integer<10>() == Add<Integer<3>, Integer<7> >::type()));

  TEST(!not_<true_type>::type());
  TEST(not_<false_type>::type());

  TEST(!(or_<false_type, false_type>::type()));
  TEST((or_<false_type, true_type>::type()));
  TEST((or_<true_type, false_type>::type()));
  TEST((or_<true_type, true_type>::type()));
  TEST(!(or_<false_type, false_type, false_type>::type()));
  TEST((or_<false_type, true_type, true_type>::type()));
  TEST((or_<true_type, false_type, true_type>::type()));
  TEST((or_<true_type, true_type, false_type>::type()));
  TEST((or_<true_type, true_type, true_type>::type()));

  TEST(!(and_<false_type, false_type>::type()));
  TEST(!(and_<false_type, true_type>::type()));
  TEST(!(and_<true_type, false_type>::type()));
  TEST((and_<true_type, true_type>::type()));
  TEST(!(and_<false_type, false_type, false_type>::type()));
  TEST(!(and_<false_type, false_type, true_type>::type()));
  TEST(!(and_<false_type, true_type, false_type>::type()));
  TEST(!(and_<true_type, false_type, false_type>::type()));
  TEST(!(and_<false_type, true_type, true_type>::type()));
  TEST(!(and_<true_type, false_type, true_type>::type()));
  TEST(!(and_<true_type, true_type, false_type>::type()));
  TEST((and_<true_type, true_type, true_type>::type()));

  char test = enable_if_test<int>();
  TEST(EXPECTED_VALUE == test);

  char test2 = disable_if_test<int>();
  TEST(EXPECTED_VALUE == test2);

  TEST((is_same<int, identity_type<identity_type<int> >::type >::type()));

  TEST((is_same<if_<true_type, int, void>::type, int>()));
  TEST((is_same<if_<false_type, void, int>::type, int>()));

  TEST((is_same<eval_if<true_type, identity_type<int>, void>::type, int>()));
  TEST((is_same<eval_if<false_type, void, identity_type<int> >::type, int>()));

  TEST((!is_reference<int>::type()));
  TEST((is_reference<int&>::type()));
  TEST((is_reference<int(&)[2]>::type()));

  TEST((is_same<make_const_ref<int>::type, int const&>::type()));
  TEST((is_same<make_const_ref<int const>::type, int const&>::type()));
  TEST((is_same<make_const_ref<int const&>::type, int const&>::type()));
  TEST((is_same<make_const_ref<int &>::type, int const&>::type()));

  TEST((is_same<make_const_ref<int volatile >::type, int volatile const&>::type()));
  TEST((is_same<make_const_ref<int volatile const>::type, int volatile const&>::type()));
  TEST((is_same<make_const_ref<int volatile const&>::type, int volatile const&>::type()));
  TEST((is_same<make_const_ref<int volatile &>::type, int volatile const&>::type()));

  TEST((is_same<int&, deduce_input_type<int&>::type >::type()));
  TEST((is_same<int, deduce_input_type<int const&>::type >::type()));
  TEST((is_same<int, deduce_input_type<int>::type >::type()));

  TEST((is_same<parameter_type<int>::type, int const&>::type()));
  TEST((is_same<parameter_type<int&>::type, int&>::type()));

  TEST((is_same<underlying_type<int>::type, int>::type()));

  TEST((is_same<get_underlying_type<int>::type, int>::type()));

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

  TEST((is_same<decay_ref<int>::type, int>::type()));
  TEST((is_same<decay_ref<int&>::type, int&>::type()));
  TEST((is_same<decay_ref<int const&>::type, int const&>::type()));
  TEST((is_same<decay_ref<Ref<int> >::type, int&>::type()));
  TEST((is_same<decay_ref<Ref<int const> >::type, int const&>::type()));

  TEST((is_same<TestArray, TestArray::type>::type()));

#define ARRAY_INDEX_TEST(n, X) TEST((is_same<ArrayIndex<TestArray, Integer<n> >::type, X>::type()))
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

  TEST((0 == ArraySize<Bool0>::type()));
  TEST((1 == ArraySize<Bool1>::type()));
  TEST((2 == ArraySize<Bool2>::type()));
  TEST((3 == ArraySize<Bool3>::type()));
  TEST((4 == ArraySize<Bool4>::type()));
  TEST((5 == ArraySize<Bool5>::type()));
  TEST((6 == ArraySize<Bool6>::type()));
  TEST((7 == ArraySize<Bool7>::type()));
  TEST((8 == ArraySize<Bool8>::type()));
  TEST((9 == ArraySize<Bool9>::type()));
  TEST((10 == ArraySize<Bool10>::type()));

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

  test_apply();

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

struct MyFunctionObject
{
    typedef long input_type_0;
    typedef int codomain_type;
    int operator()(long){ return 1; }
};

struct MyRefFunctionObject
{
    static int aValue;
    typedef box_ref<long const&> input_type_0;
    typedef box_ref<int&> codomain_type;
    int& operator()(long const&){ return aValue; }
};
int MyRefFunctionObject::aValue = 0;

struct MyRefFunctionObject2
{
    static int aValue;
    typedef Ref<long const&> input_type_0;
    typedef Ref<int&> codomain_type;
    int& operator()(long const&){ return aValue; }
};
int MyRefFunctionObject2::aValue = 0;

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
};

struct MemberFunctionTest
{
  void voidFun0() const {}
  int intFun0() { return 0; }

  void voidFun1(int) const{}
  int intFun1(int) { return 0; }

  void voidFun2(int, char&) const{}
  int intFun2(int, char&) { return 0; }

  void voidFun3(int, char&, double const&) const{}
  int intFun3(int, char&, double const&) { return 0; }

  void voidFun4(int, char&, double const&, int*&) const{}
  int intFun4(int, char&, double const&, int*&) { return 0; }
};

template<typename ReturnType, typename Input0, typename T>
void testFun0(T)
{
  TEST((typename is_same<typename GetCodomainType<T>::type,ReturnType>::type()));
  TEST((typename is_same<typename DeduceCodomainType<T>::type,ReturnType>::type()));
  TEST((typename FunctionSignatureEnabled<T>::type()));
  TEST((typename HasInputType<T, Integer<0> >::type()));
  TEST(!(typename HasInputType<T, Integer<1> >::type()));
  TEST((typename is_same<Input0, typename GetInputType<T, Integer<0> >::type>::type()));
  TEST((1 == typename GetFunctionArity<T>::type()));
  TEST((typename is_same<Array<Input0>, typename GetInputTypeArray<T>::type>::type()));
}

template<typename ReturnType, typename Input0, typename T>
void testFun1(T)
{
  TEST((typename is_same<typename GetCodomainType<T>::type,ReturnType>::type()));
  TEST((typename is_same<typename DeduceCodomainType<T>::type,ReturnType>::type()));
  TEST((typename FunctionSignatureEnabled<T>::type()));
  TEST((typename HasInputType<T, Integer<0> >::type()));
  TEST((typename HasInputType<T, Integer<1> >::type()));
  TEST(!(typename HasInputType<T, Integer<2> >::type()));
  TEST((typename is_same<Input0, typename GetInputType<T, Integer<0> >::type>::type()));
  TEST((typename is_same<int, typename GetInputType<T, Integer<1> >::type>::type()));
  TEST((2 == typename GetFunctionArity<T>::type()));
  TEST((typename is_same<Array<Input0, int>, typename GetInputTypeArray<T>::type>::type()));
}

template<typename ReturnType, typename Input0, typename T>
void testFun2(T)
{
  TEST((typename is_same<typename GetCodomainType<T>::type,ReturnType>::type()));
  TEST((typename is_same<typename DeduceCodomainType<T>::type,ReturnType>::type()));
  TEST((typename FunctionSignatureEnabled<T>::type()));
  TEST((typename HasInputType<T, Integer<0> >::type()));
  TEST((typename HasInputType<T, Integer<1> >::type()));
  TEST((typename HasInputType<T, Integer<2> >::type()));
  TEST(!(typename HasInputType<T, Integer<3> >::type()));
  TEST((typename is_same<Input0, typename GetInputType<T, Integer<0> >::type>::type()));
  TEST((typename is_same<int, typename GetInputType<T, Integer<1> >::type>::type()));
  TEST((typename is_same<char&, typename GetInputType<T, Integer<2> >::type>::type()));
  TEST((3 == typename GetFunctionArity<T>::type()));
  TEST((typename is_same<Array<Input0, int, char&>, typename GetInputTypeArray<T>::type>::type()));
}

template<typename ReturnType, typename Input0, typename T>
void testFun3(T)
{
  TEST((typename is_same<typename GetCodomainType<T>::type,ReturnType>::type()));
  TEST((typename is_same<typename DeduceCodomainType<T>::type,ReturnType>::type()));
  TEST((typename FunctionSignatureEnabled<T>::type()));
  TEST((typename HasInputType<T, Integer<0> >::type()));
  TEST((typename HasInputType<T, Integer<1> >::type()));
  TEST((typename HasInputType<T, Integer<2> >::type()));
  TEST((typename HasInputType<T, Integer<3> >::type()));
  TEST(!(typename HasInputType<T, Integer<4> >::type()));
  TEST((typename is_same<Input0, typename GetInputType<T, Integer<0> >::type>::type()));
  TEST((typename is_same<int, typename GetInputType<T, Integer<1> >::type>::type()));
  TEST((typename is_same<char&, typename GetInputType<T, Integer<2> >::type>::type()));
  TEST((typename is_same<double const&, typename GetInputType<T, Integer<3> >::type>::type()));
  TEST((4 == typename GetFunctionArity<T>::type()));
  TEST((typename is_same<Array<Input0, int, char&, double const&>, typename GetInputTypeArray<T>::type>::type()));
}

template<typename ReturnType, typename Input0, typename T>
void testFun4(T)
{
  TEST((typename is_same<typename GetCodomainType<T>::type,ReturnType>::type()));
  TEST((typename is_same<typename DeduceCodomainType<T>::type,ReturnType>::type()));
  TEST((typename FunctionSignatureEnabled<T>::type()));
  TEST((typename HasInputType<T, Integer<0> >::type()));
  TEST((typename HasInputType<T, Integer<1> >::type()));
  TEST((typename HasInputType<T, Integer<2> >::type()));
  TEST((typename HasInputType<T, Integer<3> >::type()));
  TEST((typename HasInputType<T, Integer<4> >::type()));
  TEST(!(typename HasInputType<T, Integer<5> >::type()));
  TEST((typename is_same<Input0, typename GetInputType<T, Integer<0> >::type>::type()));
  TEST((typename is_same<int, typename GetInputType<T, Integer<1> >::type>::type()));
  TEST((typename is_same<char&, typename GetInputType<T, Integer<2> >::type>::type()));
  TEST((typename is_same<double const&, typename GetInputType<T, Integer<3> >::type>::type()));
  TEST((typename is_same<int*&, typename GetInputType<T, Integer<4> >::type>::type()));
  TEST((5 == typename GetFunctionArity<T>::type()));
  TEST((typename is_same<Array<Input0, int, char&, double const&, int*&>, typename GetInputTypeArray<T>::type>::type()));
}

void test_function_signatures()
{
  TEST((is_same<GetCodomainType<int(*)()>::type,int>::type()));
  TEST((is_same<DeduceCodomainType<int(*)()>::type,int>::type()));
  TEST((FunctionSignatureEnabled<int(*)()>::type()));
  TEST(!(HasInputType<int(*)(), Integer<0> >::type()));
  TEST((0 == GetFunctionArity<int(*)()>::type()));
  TEST((is_same<Array<>, GetInputTypeArray<int(*)()>::type>::type()));


  TEST((is_same<GetCodomainType<int(*)(long)>::type,int>::type()));
  TEST((is_same<DeduceCodomainType<int(*)(long)>::type,int>::type()));
  TEST((FunctionSignatureEnabled<int(*)(long)>::type()));
  TEST((HasInputType<int(*)(long), Integer<0> >::type()));
  TEST(!(HasInputType<int(*)(long), Integer<1> >::type()));
  TEST((is_same<long, GetInputType<int(*)(long), Integer<0> >::type>::type()));
  TEST((1 == GetFunctionArity<int(*)(long)>::type()));
  TEST((is_same<Array<long>, GetInputTypeArray<int(*)(long)>::type>::type()));


  TEST((is_same<GetCodomainType<int(*)(long, float)>::type,int>::type()));
  TEST((is_same<DeduceCodomainType<int(*)(long, float)>::type,int>::type()));
  TEST((FunctionSignatureEnabled<int(*)(long, float)>::type()));
  TEST((HasInputType<int(*)(long, float), Integer<0> >::type()));
  TEST((HasInputType<int(*)(long, float), Integer<1> >::type()));
  TEST(!(HasInputType<int(*)(long, float), Integer<2> >::type()));
  TEST((is_same<long, GetInputType<int(*)(long, float), Integer<0> >::type>::type()));
  TEST((is_same<float, GetInputType<int(*)(long, float), Integer<1> >::type>::type()));
  TEST((2 == GetFunctionArity<int(*)(long, float)>::type()));
  TEST((is_same<Array<long, float>, GetInputTypeArray<int(*)(long, float)>::type>::type()));

  TEST((is_same<GetCodomainType<int(*)(long, float, short&)>::type,int>::type()));
  TEST((is_same<DeduceCodomainType<int(*)(long, float, short&)>::type,int>::type()));
  TEST((FunctionSignatureEnabled<int(*)(long, float, short&)>::type()));
  TEST((HasInputType<int(*)(long, float, short&), Integer<0> >::type()));
  TEST((HasInputType<int(*)(long, float, short&), Integer<1> >::type()));
  TEST((HasInputType<int(*)(long, float, short&), Integer<2> >::type()));
  TEST(!(HasInputType<int(*)(long, float, short&), Integer<3> >::type()));
  TEST((is_same<long, GetInputType<int(*)(long, float, short&), Integer<0> >::type>::type()));
  TEST((is_same<float, GetInputType<int(*)(long, float, short&), Integer<1> >::type>::type()));
  TEST((is_same<short&, GetInputType<int(*)(long, float, short&), Integer<2> >::type>::type()));
  TEST((3 == GetFunctionArity<int(*)(long, float, short&)>::type()));
  TEST((is_same<Array<long, float, short&>, GetInputTypeArray<int(*)(long, float, short&)>::type>::type()));

  TEST((is_same<GetCodomainType<int(*)(long, float, short&, int const&)>::type,int>::type()));
  TEST((is_same<DeduceCodomainType<int(*)(long, float, short&, int const&)>::type,int>::type()));
  TEST((FunctionSignatureEnabled<int(*)(long, float, short&, int const&)>::type()));
  TEST((HasInputType<int(*)(long, float, short&, int const&), Integer<0> >::type()));
  TEST((HasInputType<int(*)(long, float, short&, int const&), Integer<1> >::type()));
  TEST((HasInputType<int(*)(long, float, short&, int const&), Integer<2> >::type()));
  TEST((HasInputType<int(*)(long, float, short&, int const&), Integer<3> >::type()));
  TEST(!(HasInputType<int(*)(long, float, short&, int const&), Integer<4> >::type()));
  TEST((is_same<long, GetInputType<int(*)(long, float, short&, int const&), Integer<0> >::type>::type()));
  TEST((is_same<float, GetInputType<int(*)(long, float, short&, int const&), Integer<1> >::type>::type()));
  TEST((is_same<short&, GetInputType<int(*)(long, float, short&, int const&), Integer<2> >::type>::type()));
  TEST((is_same<int const&, GetInputType<int(*)(long, float, short&, int const&), Integer<3> >::type>::type()));
  TEST((4 == GetFunctionArity<int(*)(long, float, short&, int const&)>::type()));
  TEST((is_same<Array<long, float, short&, int const&>, GetInputTypeArray<int(*)(long, float, short&, int const&)>::type>::type()));


  TEST((is_same<GetCodomainType<int(*)(long, float, short&, int const&, bool)>::type,int>::type()));
  TEST((is_same<DeduceCodomainType<int(*)(long, float, short&, int const&, bool)>::type,int>::type()));
  TEST((FunctionSignatureEnabled<int(*)(long, float, short&, int const&, bool)>::type()));
  TEST((HasInputType<int(*)(long, float, short&, int const&, bool), Integer<0> >::type()));
  TEST((HasInputType<int(*)(long, float, short&, int const&, bool), Integer<1> >::type()));
  TEST((HasInputType<int(*)(long, float, short&, int const&, bool), Integer<2> >::type()));
  TEST((HasInputType<int(*)(long, float, short&, int const&, bool), Integer<3> >::type()));
  TEST((HasInputType<int(*)(long, float, short&, int const&, bool), Integer<4> >::type()));
  TEST(!(HasInputType<int(*)(long, float, short&, int const&, bool), Integer<5> >::type()));
  TEST((is_same<long, GetInputType<int(*)(long, float, short&, int const&, bool), Integer<0> >::type>::type()));
  TEST((is_same<float, GetInputType<int(*)(long, float, short&, int const&, bool), Integer<1> >::type>::type()));
  TEST((is_same<short&, GetInputType<int(*)(long, float, short&, int const&, bool), Integer<2> >::type>::type()));
  TEST((is_same<int const&, GetInputType<int(*)(long, float, short&, int const&, bool), Integer<3> >::type>::type()));
  TEST((is_same<bool, GetInputType<int(*)(long, float, short&, int const&, bool), Integer<4> >::type>::type()));
  TEST((5 == GetFunctionArity<int(*)(long, float, short&, int const&, bool)>::type()));
  TEST((is_same<Array<long, float, short&, int const&, bool>, GetInputTypeArray<int(*)(long, float, short&, int const&, bool)>::type>::type()));

  TEST((is_same<GetCodomainType<MyFunctionObject>::type,int>::type()));
  TEST((is_same<DeduceCodomainType<MyFunctionObject>::type,int>::type()));
  TEST((FunctionSignatureEnabled<MyFunctionObject>::type()));
  TEST((HasInputType<MyFunctionObject, Integer<0> >::type()));
  TEST(!(HasInputType<MyFunctionObject, Integer<1> >::type()));
  TEST((is_same<long, GetInputType<MyFunctionObject, Integer<0> >::type>::type()));
  TEST((1 == GetFunctionArity<MyFunctionObject>::type()));
  TEST((is_same<Array<long>, GetInputTypeArray<MyFunctionObject>::type>::type()));


  TEST((is_same<GetCodomainType<MyRefFunctionObject>::type,int&>::type()));
  TEST((is_same<DeduceCodomainType<MyRefFunctionObject>::type,int&>::type()));
  TEST((FunctionSignatureEnabled<MyRefFunctionObject>::type()));
  TEST((HasInputType<MyRefFunctionObject, Integer<0> >::type()));
  TEST(!(HasInputType<MyRefFunctionObject, Integer<1> >::type()));
  TEST((is_same<long const&, GetInputType<MyRefFunctionObject, Integer<0> >::type>::type()));
  TEST((1 == GetFunctionArity<MyRefFunctionObject>::type()));
  TEST((is_same<Array<long const&>, GetInputTypeArray<MyRefFunctionObject>::type>::type()));

  TEST((is_same<GetCodomainType<MyRefFunctionObject2>::type,int&>::type()));
  TEST((is_same<DeduceCodomainType<MyRefFunctionObject2>::type,int&>::type()));
  TEST((FunctionSignatureEnabled<MyRefFunctionObject2>::type()));
  TEST((HasInputType<MyRefFunctionObject2, Integer<0> >::type()));
  TEST(!(HasInputType<MyRefFunctionObject2, Integer<1> >::type()));
  TEST((is_same<long const&, GetInputType<MyRefFunctionObject2, Integer<0> >::type>::type()));
  TEST((1 == GetFunctionArity<MyRefFunctionObject2>::type()));
  TEST((is_same<Array<long const&>, GetInputTypeArray<MyRefFunctionObject2>::type>::type()));


  // OK, test out the generic codomain deduction mechanism
  TEST((is_same<GetCodomainType<MyGenericFunctionObject>::type,CodomainDeduction<ReturnFirstValue<placeholders::_0> > >::type()));
  TEST((is_same<DeduceCodomainType<MyGenericFunctionObject, int>::type,int>::type()));
  TEST((FunctionSignatureEnabled<MyGenericFunctionObject>::type()));
  TEST((HasInputType<MyGenericFunctionObject, Integer<0> >::type()));
  TEST(!(HasInputType<MyGenericFunctionObject, Integer<1> >::type()));
  TEST((is_same<template_param, GetInputType<MyGenericFunctionObject, Integer<0> >::type>::type()));
  TEST((1 == GetFunctionArity<MyGenericFunctionObject>::type()));
  TEST((is_same<Array<template_param>, GetInputTypeArray<MyGenericFunctionObject>::type>::type()));



  // OK, test out the generic codomain deduction mechanism with 5 parameters
  TEST((is_same<GetCodomainType<MyGenericFunctionObject2>::type,CodomainDeduction<ReturnThirdValue> >::type()));
  TEST((is_same<DeduceCodomainType<MyGenericFunctionObject2, char, short, int, float, void*>::type,int>::type()));
  TEST((FunctionSignatureEnabled<MyGenericFunctionObject2>::type()));
  TEST((HasInputType<MyGenericFunctionObject2, Integer<0> >::type()));
  TEST((HasInputType<MyGenericFunctionObject2, Integer<1> >::type()));
  TEST((HasInputType<MyGenericFunctionObject2, Integer<2> >::type()));
  TEST((HasInputType<MyGenericFunctionObject2, Integer<3> >::type()));
  TEST((HasInputType<MyGenericFunctionObject2, Integer<4> >::type()));
  TEST(!(HasInputType<MyGenericFunctionObject2, Integer<5> >::type()));
  TEST((is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<0> >::type>::type()));
  TEST((is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<1> >::type>::type()));
  TEST((is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<2> >::type>::type()));
  TEST((is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<3> >::type>::type()));
  TEST((is_same<template_param, GetInputType<MyGenericFunctionObject2, Integer<4> >::type>::type()));
  TEST((5 == GetFunctionArity<MyGenericFunctionObject2>::type()));
  TEST((is_same<Array<template_param, template_param, template_param, template_param, template_param>, GetInputTypeArray<MyGenericFunctionObject2>::type>::type()));

  testFun0<void, MemberFunctionTest const>(&MemberFunctionTest::voidFun0);
  testFun0<int, MemberFunctionTest>(&MemberFunctionTest::intFun0);

  testFun1<void, MemberFunctionTest const>(&MemberFunctionTest::voidFun1);
  testFun1<int, MemberFunctionTest>(&MemberFunctionTest::intFun1);

  testFun2<void, MemberFunctionTest const>(&MemberFunctionTest::voidFun2);
  testFun2<int, MemberFunctionTest>(&MemberFunctionTest::intFun2);

  testFun3<void, MemberFunctionTest const>(&MemberFunctionTest::voidFun3);
  testFun3<int, MemberFunctionTest>(&MemberFunctionTest::intFun3);

  testFun4<void, MemberFunctionTest const>(&MemberFunctionTest::voidFun4);
  testFun4<int, MemberFunctionTest>(&MemberFunctionTest::intFun4);
}

} // unnamed namespace
} // namespace intro

using namespace intro;

int main()
{
    test_metaprogramming();
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
    test_visit();

    test_function_signatures();
}
