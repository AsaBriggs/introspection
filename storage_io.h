#ifndef INCLUDED_STORAGE_IO
#define INCLUDED_STORAGE_IO

#ifndef INCLUDED_STORAGE
#include "storage.h"
#endif

#ifndef INCLUDED_COMPILER_SPECIFICS
#include "compiler_specifics.h"
#endif

#ifndef INCLUDED_IOSFWD
#define INCLUDED_IOSFWD
#include <iosfwd>
#endif

namespace intro {
namespace impl {

template<typename charT, typename traits>
struct StreamIn_Visitor
{
    typedef true_type IntrospectionEnabled;
    typedef std::basic_istream<charT, traits>* IntrospectionItem0;
    IntrospectionItem0 is;
    typedef typename std::basic_istream<charT, traits>::sentry Guard;

    template<typename T, int Index>
    void operator()(T& x, Integer<Index>)
    {
        Guard guard(*is);
        if (guard) {
            // Requires is is not 0
            *is >> x;
	}
    }
};

template<typename charT, typename traits>
struct StreamOut_Visitor
{
    typedef true_type IntrospectionEnabled;
    typedef std::basic_ostream<charT, traits>* IntrospectionItem0;
    IntrospectionItem0 os;

    template<typename T, int Index>
    void operator()(T const& x, Integer<Index>)
    {
        // Requires os is not 0
        *os << x << ' ' ;
    }
};

template<typename T, typename charT, typename traits>
std::basic_istream<charT, traits>& stream_in_impl(std::basic_istream<charT, traits>& is, T& x)
{
    StreamIn_Visitor<charT, traits> visitor = {&is};
    visit(x, visitor);
    return is;
}

template<typename T, typename charT, typename traits>
std::basic_ostream<charT, traits>& stream_out_impl(std::basic_ostream<charT, traits>& os, T const& x)
{
    StreamOut_Visitor<charT, traits> visitor = {&os};
    visit(x, visitor);
    return os;
}

} // namespace impl

template<typename T, typename enable=void>
struct TYPE_HIDDEN_VISIBILITY generate_introspected_streaming : IntrospectionEnabled<T> {METAPROGRAMMING_ONLY(generate_introspected_streaming)};

template<typename T, typename charT, typename traits>
typename enable_if<typename generate_introspected_streaming<T>::type, std::basic_istream<charT, traits>& >::type
operator>>(std::basic_istream<charT, traits>& is, T& x)
{
    return impl::stream_in_impl(is, get_storage(x));
}

template<typename T, typename charT, typename traits>
typename enable_if<typename generate_introspected_streaming<T>::type, std::basic_ostream<charT, traits>& >::type
operator<<(std::basic_ostream<charT, traits>& os, T const& x)
{
    return impl::stream_out_impl(os, get_storage(x));
}

} // namespace intro

#endif
