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

namespace StreamIn_impl {

template<typename charT, typename traits>
struct TYPE_HIDDEN_VISIBILITY StreamIn_Visitor
{
    typedef true_type IntrospectionEnabled;
    typedef std::basic_istream<charT, traits>* IntrospectionItem0;
    IntrospectionItem0 is;
    typedef typename std::basic_istream<charT, traits>::sentry Guard;

    template<typename T, int Index>
    ALWAYS_INLINE void operator()(T& x, Integer<Index>)
    {
        Guard guard(*is);
        if (INTROSPECTION_LIKELY(guard)) {
            // Requires is is not 0
            *is >> x;
	}
    }
};

// Try and make this function be shared as the single stream out function for T(/charT/traits)
template<typename T, typename charT, typename traits>
INLINE std::basic_istream<charT, traits>& stream_in(std::basic_istream<charT, traits>& is, T& x)
{
    StreamIn_Visitor<charT, traits> visitor = {&is};
    visit(x, visitor);
    return is;
}

} // namespace StreamIn_impl


namespace StreamOut_impl {

template<typename charT, typename traits>
struct TYPE_HIDDEN_VISIBILITY StreamOut_Visitor
{
    typedef true_type IntrospectionEnabled;
    typedef std::basic_ostream<charT, traits>* IntrospectionItem0;
    IntrospectionItem0 os;

    template<typename T, int Index>
    ALWAYS_INLINE void operator()(T const& x, Integer<Index>)
    {
        // Requires os is not 0
        *os << x << ' ' ;
    }
};

// Try and make this function be shared as the single stream in function for T(/charT/traits)
template<typename T, typename charT, typename traits>
INLINE std::basic_ostream<charT, traits>& stream_out(std::basic_ostream<charT, traits>& os, T const& x)
{
    StreamOut_Visitor<charT, traits> visitor = {&os};
    visit(x, visitor);
    return os;
}

} // namespace StreamOut_impl


template<typename T, typename enable=void>
struct TYPE_HIDDEN_VISIBILITY generate_introspected_streaming : IntrospectionEnabled<T> {METAPROGRAMMING_ONLY(generate_introspected_streaming)};


template<typename T, typename charT, typename traits>
ALWAYS_INLINE_HIDDEN typename enable_if<typename generate_introspected_streaming<T>::type, std::basic_istream<charT, traits>& >::type
operator>>(std::basic_istream<charT, traits>& is, T& x)
{
    return StreamIn_impl::stream_in(is, get_storage(x));
}

template<typename T, typename charT, typename traits>
ALWAYS_INLINE_HIDDEN typename enable_if<typename generate_introspected_streaming<T>::type, std::basic_ostream<charT, traits>& >::type
operator<<(std::basic_ostream<charT, traits>& os, T const& x)
{
    return StreamOut_impl::stream_out(os, get_storage(x));
}

} // namespace intro

#endif
