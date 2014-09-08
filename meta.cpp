
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
    a_type value = {1.0f, 1LL, 2.0, false, 'b', tmp};
    a_type value2 = {a_type::Storage::make(1.0f, 2LL, 3.0, false, 'a', tmp)};

    auto a = make_storage<DefaultTag>();
    auto b = make_storage<DefaultTag>(1);
    auto c = make_storage<DefaultTag>(1, 2.0);
    auto d = make_storage<DefaultTag>(1, 2.0, 3.0f);
    auto e = make_storage<DefaultTag>(1, 2.0, 3.0f, "");
    auto f = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL);
    auto g = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL, 'a');
    auto h = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL, 'a', 7U);
    auto i = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL, 'a', 7U, 99ULL);
    auto j = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL, 'a', 7U, 99ULL, false);
    auto k = make_storage<DefaultTag>(1, 2.0, 3.0f, "", 22LL, 'a', 7U, 99ULL, false, value2);

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

    typedef Array<double, int> arr;
    deduce_type<arr, DefaultTag>::type xxxx = {3.0, 1};
    ArrayTransform<arr, DecayRef>::type::M1 xxxxy = 3;

    pair<int, double, DefaultTag> x = make_storage<DefaultTag>(1, 3.0);

    swap(value, value2);

    typedef get_underlying_type<P>::type T;
    T& r0 = reinterpret_cast<T&>( x0 );
    std::cout << sizeof(value);
    return x0 < x1 && x1 < x2 && x1 == x1 && value < value2 && !(value == value2);
}

