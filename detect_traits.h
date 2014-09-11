#ifndef INCLUDED_DETECT_TRAITS
#define INCLUDED_DETECT_TRAITS

namespace intro {

struct true_type;

struct false_type;

template<bool value>
struct ValueToTrueFalse;

template<>
struct ValueToTrueFalse<0>
{
    typedef false_type type;
};

template<>
struct ValueToTrueFalse<1> 
{
    typedef true_type type;
};

#define GENERATE_HAS_MEMBER_TYPE(Type)                                     \
template<typename T>                                                       \
struct HasMemberType_##Type                                                \
{                                                                          \
private:                                                                   \
    typedef char Yes;                                                      \
    typedef char No[2];                                                    \
    template <typename U>                                                  \
    static No& test(...);                                                  \
    template <typename U>                                                  \
    static Yes& test(typename U::Type*);			           \
public:                                                                    \
    typedef typename ValueToTrueFalse<sizeof(test<T>(0)) == 1>::type type; \
};                                                                         \

#define GENERATE_GET_MEMBER_TYPE(Type) \
template<typename T>                   \
struct GetMemberType_##Type             \
{                                      \
    typedef typename T::Type type;     \
};

#define GENERATE_HAS_AND_GET_MEMBER_TYPE(Type) \
GENERATE_HAS_MEMBER_TYPE(Type) \
GENERATE_GET_MEMBER_TYPE(Type)

// OK GENERATE_HAS_MEMBER_TYPE suffers from the problem that if the nested type
// is a reference then typename U::Type* does not generate a valid type (can't form
// a pointer to a reference).
// Therefore this second typedef detection scheme can be used. This inherits off T
// and uses lookup ambiguity to determine whether the typedef exists. However it relies
// on the fact that one can inherit off T. To work around this requirement we can
// make use of the concept of an enabling metafunction, using inheritance only if this
// is true. Note that users of this scheme need to structure their design carefully
// to take this into account.

#define GENERATE_HAS_MEMBER_TYPE_OF_CLASS(Type)\
namespace detect_traits_impl { \
struct HasMemberType_ImplBase##Type                                        \
{                                                                          \
protected:                                                                 \
    typedef char Yes;				   	                   \
    struct No { char x[2]; };						   \
    struct Fallback { struct Type {}; };                                   \
    template < class U >                                                   \
    static No test ( typename U::Type* );                                  \
    template < typename U >                                                \
    static Yes test ( U* );                                                \
};                                                                         \
template<typename T>                                                       \
struct HasMemberType_Impl##Type : private HasMemberType_ImplBase##Type 	   \
{                                                                          \
private:                                                                   \
    typedef HasMemberType_ImplBase##Type Base ;                            \
    struct Derived : T, Base::Fallback {};				   \
public:					                                   \
    typedef typename ValueToTrueFalse<sizeof(Base::template test<Derived>(0)) == 1>::type type; \
};                                                                         \
} // namespace detect_traits_impl

#define GENERATE_HAS_MEMBER_TYPE2(Type, EnablingMetafunction)              \
GENERATE_HAS_MEMBER_TYPE_OF_CLASS(Type)                                    \
template<typename T>                                                       \
struct HasMemberType_##Type : and_<EnablingMetafunction<T>,                \
    detect_traits_impl::HasMemberType_Impl##Type<T> >			   \
{};

#define GENERATE_HAS_AND_GET_MEMBER_TYPE2(Type, EnablingMetafunction) \
GENERATE_HAS_MEMBER_TYPE2(Type, EnablingMetafunction)		      \
GENERATE_GET_MEMBER_TYPE(Type)

template<typename T>
struct IsStructClassOrUnion
{
private:
    typedef char Yes;
    struct No { char x[2]; };
    template < class U >
    static Yes test (char U::*);
    template < typename U >
    static No test (...);
public:
    typedef typename ValueToTrueFalse<sizeof(test<T>(0)) == 1>::type type;
};

//template<>struct IsStructClassOrUnion<void>{ typedef false_type type; };
//template<typename T>struct IsStructClassOrUnion<T&>{ typedef false_type type; };

#define GENERATE_HAS_MEMBER_TYPE3(Type)              \
GENERATE_HAS_MEMBER_TYPE_OF_CLASS(Type)                                    \
template<typename T>                                                       \
struct HasMemberType_##Type : and_<IsStructClassOrUnion<T>,                \
    detect_traits_impl::HasMemberType_Impl##Type<T> >			   \
{};

#define GENERATE_HAS_AND_GET_MEMBER_TYPE3(Type) \
GENERATE_HAS_MEMBER_TYPE3(Type)		      \
GENERATE_GET_MEMBER_TYPE(Type)

} // namespace intro

#endif
