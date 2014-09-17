#ifndef INCLUDED_METAPROGRAMMING_INTEGER
#define INCLUDED_METAPROGRAMMING_INTEGER

#ifndef INCLUDED_CSTDDEF
#include <cstddef>
#define INCLUDED_CSTDDEF
#endif

#ifndef INCLUDED_COMPILER_SPECIFICS
#include "compiler_specifics.h"
#endif

namespace intro {

typedef long IntegerValueType;

template<IntegerValueType num>
struct TYPE_DEFAULT_VISIBILITY Integer
{
    typedef Integer type;
    static const IntegerValueType value = num;
    ALWAYS_INLINE_HIDDEN operator IntegerValueType() const { return value ; }
};

} // namespace intro

#endif
