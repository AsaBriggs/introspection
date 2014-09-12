#ifndef INCLUDED_DETECT_TRAITS
#define INCLUDED_DETECT_TRAITS

#ifndef INCLUDED_METAPROGRAMMING
#include "metaprogramming.h"
#endif

namespace intro {

#define GENERATE_GET_MEMBER_TYPE(Type)             \
template<typename T>                               \
struct TYPE_HIDDEN_VISIBILITY GetMemberType_##Type \
{                                                  \
    typedef typename T::Type type;                 \
    METAPROGRAMMING_ONLY(GetMemberType_##Type)     \
};

// See http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Member_Detector
// This uses lookup ambiguity to determine whether the typedef exists. However it relies
// on the fact that one can inherit off T. To work around this requirement we can
// make use of the classic pointer-to-member technique.

#define GENERATE_HAS_MEMBER_TYPE_OF_CLASS(Type)                                  \
namespace detect_traits_impl {                                                   \
template<typename T>                                                             \
struct TYPE_HIDDEN_VISIBILITY HasMemberType_Impl##Type 	                         \
{                                                                                \
private:                                                                         \
    typedef char Yes;				   	                         \
    struct TYPE_HIDDEN_VISIBILITY No { char x[2]; };				 \
    struct TYPE_HIDDEN_VISIBILITY Fallback { struct Type {}; };                  \
    template<typename U>                                                         \
    static HIDDEN No test(typename U::Type*);                                    \
    template<typename U>                                                         \
    static HIDDEN Yes test(U*);                                                  \
    struct TYPE_HIDDEN_VISIBILITY Derived : T, Fallback {};			 \
public:					                                         \
    typedef typename ::intro::ValueToTrueFalse<sizeof(test<Derived>(0)) == 1>::type type; \
    METAPROGRAMMING_ONLY(HasMemberType_Impl##Type)                               \
};                                                                               \
} // namespace detect_traits_impl

#define GENERATE_HAS_MEMBER_TYPE(Type)                   \
GENERATE_HAS_MEMBER_TYPE_OF_CLASS(Type)                  \
template<typename T>                                     \
struct TYPE_HIDDEN_VISIBILITY HasMemberType_##Type :     \
    ::intro::and_< ::intro::is_struct_class_or_union<T>, \
    detect_traits_impl::HasMemberType_Impl##Type<T> >    \
{                                                        \
    METAPROGRAMMING_ONLY(HasMemberType_##Type)           \
};

#define GENERATE_HAS_AND_GET_MEMBER_TYPE(Type) \
GENERATE_HAS_MEMBER_TYPE(Type)		       \
GENERATE_GET_MEMBER_TYPE(Type)

} // namespace intro

#endif
