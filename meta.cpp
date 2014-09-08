
#include <cassert>
#include <iostream>
#include "storage.h"

typedef pair<int, float> P;

P x0 = P::make(1, 13.0f);
P x1 = P::make(1, 14.0f);
P x2 = P::make(2, 11.0f);

struct a_type
{
    typedef a_type type;

    typedef true_type IntrospectionEnabled;
    typedef true_type IntrospectionIndirectStorage;
    typedef float IntrospectionItem0;
    typedef long long IntrospectionItem1;
    typedef double IntrospectionItem2;
    typedef bool IntrospectionItem3;
    typedef char IntrospectionItem4;
    typedef pair<int, long long, DefaultTag> IntrospectionItem5;
    typedef GenerateStorage<type>::type Storage;

    Storage m0;
};

struct Identity
{
    template<typename T>
    struct apply
    {
        typedef T type;
    };
};

int main()
{
    a_type::IntrospectionItem5 tmp = {1, 2};
    a_type value = {{1.0f, 1LL, 2.0, false, 'b', tmp}};
    a_type value2 = {a_type::Storage::make(1.0f, 2LL, 3.0, false, 'a', tmp)};

    swap(value, value2);

    empty_type<DefaultTag> a = make_storage<DefaultTag>();
    singleton<int, DefaultTag> b = make_storage<DefaultTag>(1);
    pair<int, double, DefaultTag> c = make_storage<DefaultTag>(1, 2.0);
    triple<int, double, float, DefaultTag> d = make_storage<DefaultTag>(1, 2.0, 3.0f);
    quadruple<int, double, float, char const*, DefaultTag> e = make_storage<DefaultTag>(1, 2.0, 3.0f, "");
    quintuple<int, double, float, char const*, long long, DefaultTag> f = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL);
    sextuple<int, double, float, char const*, long long, char, DefaultTag> g = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL, 'a');
    septuple<int, double, float, char const*, long long, char, unsigned, DefaultTag> h = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL, 'a', 7U);
    octuple<int, double, float, char const*, long long, char, unsigned, unsigned long long, DefaultTag> i = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL, 'a', 7U, 99ULL);
    nonuple<int, double, float, char const*, long long, char, unsigned, unsigned long long, bool, DefaultTag> j = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL, 'a', 7U, 99ULL, false);
    decuple<int, double, float, char const*, long long, char, unsigned, unsigned long long, bool, a_type, DefaultTag> k = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL, 'a', 7U, 99ULL, false, value2);

    swap(a, a);
    swap(b, b);
    swap(c, c);
    swap(d, d);
    swap(e, e);
    swap(f, f);
    swap(g, g);
    swap(h, h);
    swap(i, i);
    swap(j, j);
    swap(k, k);

    assert(a == a && b == b && c == c && d == d && f == f && g == g && h == h && i == i && k == k);

    assert(!(a < a) && !(b < b) && !(c < c) && !(d < d) && !(f < f) && !(g < g) && !(h < h) && !(i < i) && !(k < k));

    std::cout << sizeof(value);
    return x0 < x1 && x1 < x2 && x1 == x1 && value < value2 && !(value == value2);
}

