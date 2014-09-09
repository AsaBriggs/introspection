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

} // namespace intro

#endif
