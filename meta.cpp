#include <cassert>
#include "storage.h"

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
{}

void test_array_transform()
{}

void test_metaprogramming()
{
  TEST(true_type());
  TEST(!false_type());

  int x = 0;
  Ref<int, DefaultTag> y = make_ref(x);
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
  TEST((is_same<decay_ref<Ref<int, DefaultTag> >::type, int&>::type()));
  TEST((is_same<decay_ref<Ref<int const, DefaultTag> >::type, int const&>::type()));

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
}
