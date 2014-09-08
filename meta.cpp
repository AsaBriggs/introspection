#include <cassert>
#include <iostream>
#include "storage.h"

#define TEST(x) assert((x))

const char EXPECTED_VALUE = 'a';
const char UNEXPECTED_VALUE = 'b';

template<typename T>
typename enable_if<is_same<T, identity_type<int> >, char>::type enable_if_test() { return EXPECTED_VALUE; }

template<typename T>
typename enable_if<not_<is_same<T, identity_type<int> > >, char>::type enable_if_test() { return UNEXPECTED_VALUE; }

template<typename T>
typename disable_if<is_same<T, identity_type<int> >, char>::type disable_if_test() { return UNEXPECTED_VALUE; }

template<typename T>
typename disable_if<not_<is_same<T, identity_type<int> > >, char>::type disable_if_test() { return EXPECTED_VALUE; }

void test_metaprogramming()
{
  TEST(true_type());
  TEST(!false_type());

  TEST( Integer<1>() == Successor<Integer<0> >::type());
  TEST( Integer<3>() == Successor<Integer<2> >::type());

  TEST( Integer<0>() == Predecessor<Integer<1> >::type());
  TEST( Integer<-2>() == Predecessor<Integer<-1> >::type());

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

  char test = enable_if_test<identity_type<int> >();
  TEST(EXPECTED_VALUE == test);

  char test2 = disable_if_test<identity_type<int> >();
  TEST(EXPECTED_VALUE == test2);

  int x = 0;
  Ref<int, DefaultTag> y = make_ref(x);
  TEST(y.m0 == &x);
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
