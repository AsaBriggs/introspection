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

  template<typename T, typename charT, typename traits>
struct TYPE_HIDDEN_VISIBILITY StreamIn_Visitor
{
    typedef true_type IntrospectionEnabled;
    typedef std::basic_istream<charT, traits>* IntrospectionItem0;
    IntrospectionItem0 is;
    typedef typename std::basic_istream<charT, traits>::sentry Guard;

    template<typename U, int Index>
    ALWAYS_INLINE void operator()(U& x, Integer<Index>)
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
    StreamIn_Visitor<T, charT, traits> visitor = {&is};
    visit(x, visitor);
    return is;
}

} // namespace StreamIn_impl

namespace StreamOut_impl {

struct TYPE_HIDDEN_VISIBILITY default_ostream_traits
{
    template<typename charT>
    struct apply
    {
        typedef default_ostream_traits type;
        static ALWAYS_INLINE_HIDDEN charT const * field_start () { return  ""; }
        static ALWAYS_INLINE_HIDDEN charT const * field_end() { return " "; }
        static ALWAYS_INLINE_HIDDEN charT const * stream_out_start () { return  ""; }
        static ALWAYS_INLINE_HIDDEN charT const * stream_out_end() { return ""; }
        METAPROGRAMMING_ONLY(apply)
    };

    METAPROGRAMMING_ONLY(default_ostream_traits)
};

} // namespace StreamOut_impl

template<typename T, typename enable=void>
struct TYPE_HIDDEN_VISIBILITY obtain_ostream_traits : StreamOut_impl::default_ostream_traits {METAPROGRAMMING_ONLY(obtain_ostream_traits)};

namespace StreamOut_impl {

template<typename T, typename charT, typename traits>
struct TYPE_HIDDEN_VISIBILITY StreamOut_Visitor
{
    typedef true_type IntrospectionEnabled;
    typedef std::basic_ostream<charT, traits>* IntrospectionItem0;
    typedef typename obtain_ostream_traits<T>::template apply<charT> StreamTraits;
    IntrospectionItem0 os; // Requires os is not 0

    template<typename U, int Index>
    ALWAYS_INLINE void operator()(U const& x, Integer<Index>) const
    {
        *os << StreamTraits::field_start() << x << StreamTraits::field_end();
    }

    ALWAYS_INLINE_HIDDEN void operator()(T const&, VisitStart) const
    {
        *os << StreamTraits::stream_out_start();
    }

    ALWAYS_INLINE_HIDDEN void operator()(T const&, VisitEnd) const
    {
        *os << StreamTraits::stream_out_end();
    }
};

// Try and make this function be shared as the single stream in function for T(/charT/traits)
template<typename T, typename charT, typename traits>
INLINE std::basic_ostream<charT, traits>& stream_out(std::basic_ostream<charT, traits>& os, T const& x)
{
    StreamOut_Visitor<T, charT, traits> visitor = {&os};
    visit_with_start_end(x, visitor);
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
