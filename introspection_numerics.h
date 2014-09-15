#ifndef INCLUDED_INTROSPECTION_NUMERICS
#define INCLUDED_INTROSPECTION_NUMERICS

// X Macros

// HAS_NO_LONG_LONG
// HAS_NO_MULTIBYTE_CHAR_T
// X_EXTENDED_SIGNED_INTEGER_TYPES
// X_EXTENDED_UNSIGNED_INTEGER_TYPES
// HAS_NO_NULL_POINTER

// Signed-ness macros automatically used
// __CHAR_UNSIGNED__
// __WCHAR_UNSIGNED__


#ifdef HAS_NO_LONG_LONG

#define X_LONG_LONG_INT
#define X_UNSIGNED_LONG_LONG_INT

#else

#define X_LONG_LONG_INT X(long long int)
#define X_UNSIGNED_LONG_LONG_INT X(unsigned long long int)

#endif


#ifdef HAS_NO_MULTIBYTE_CHAR_T

#define X_CHAR16_T
#define X_CHAR32_T

#else

#define X_CHAR16_T X(char16_t)
#define X_CHAR32_T X(char32_t)

#endif


#ifndef X_EXTENDED_SIGNED_INTEGER_TYPES
#define X_EXTENDED_SIGNED_INTEGER_TYPES
#endif


#ifndef X_EXTENDED_UNSIGNED_INTEGER_TYPES
#define X_EXTENDED_UNSIGNED_INTEGER_TYPES
#endif


// Classification follows C++11 standard section 3.9.1 Fundamental types

// 3.9.1.2
#define STANDARD_SIGNED_INTEGER_TYPES \
X(signed char) \
X(short int) \
X(int) \
X(long int) \
X_LONG_LONG_INT \

#define SIGNED_INTEGER_TYPES \
STANDARD_SIGNED_INTEGER_TYPES \
X_EXTENDED_SIGNED_INTEGER_TYPES

// 3.9.1.3
#define STANDARD_UNSIGNED_INTEGER_TYPES \
X(unsigned char) \
X(unsigned short int) \
X(unsigned int) \
X(unsigned long int) \
X_UNSIGNED_LONG_LONG_INT \

#define UNSIGNED_INTEGER_TYPES \
STANDARD_UNSIGNED_INTEGER_TYPES \
X_EXTENDED_UNSIGNED_INTEGER_TYPES

// 3.9.1.5 ... although this grouping has no explicit name
#define CHARACTER_TYPES \
X(char) \
X(wchar_t) \
X_CHAR16_T \
X_CHAR32_T

// 3.9.1.6
#define BOOL_TYPE X(bool)

// 3.9.1.7
#define INTEGRAL_TYPES \
CHARACTER_TYPES \
SIGNED_INTEGER_TYPES \
UNSIGNED_INTEGER_TYPES \
BOOL_TYPE

// 3.9.1.8
#define FLOATING_POINT_TYPES \
X(float) \
X(double) \
X(long double)

// 3.9.1.9
#define VOID_TYPE X(void)

#ifdef HAS_NO_NULL_POINTER

#define NULL_POINTER_TYPE

#else

#ifndef INCLUDED_CSTDDEF
#include <cstddef>
#define INCLUDED_CSTDDEF
#endif

#define NULL_POINTER_TYPE X(std::nullptr_t)

#endif


#define FUNDAMENTAL_TYPES \
INTEGRAL_TYPES \
FLOATING_POINT_TYPES \
NULL_POINTER_TYPE


#ifdef __CHAR_UNSIGNED__
#ifdef __WCHAR_UNSIGNED__

#define SIGNED_TYPES \
SIGNED_INTEGER_TYPES

#define UNSIGNED_TYPES \
UNSIGNED_INTEGER_TYPES \
X(char) \
X(wchar_t) \
X_CHAR16_T \
X_CHAR32_T

#else // __WCHAR_UNSIGNED__

#define SIGNED_TYPES \
SIGNED_INTEGER_TYPES \
X(wchar_t)

#define UNSIGNED_TYPES \
UNSIGNED_INTEGER_TYPES \
X(char) \
X_CHAR16_T \
X_CHAR32_T

#endif // __WCHAR_UNSIGNED__

#else // __CHAR_USIGNED__

#ifdef __WCHAR_UNSIGNED__

#define SIGNED_TYPES \
SIGNED_INTEGER_TYPES \
X(char)

#define UNSIGNED_TYPES \
UNSIGNED_INTEGER_TYPES \
X_CHAR16_T \
X_CHAR32_T \
X(wchar_t)

#else // __WCHAR_UNSIGNED__

#define SIGNED_TYPES \
SIGNED_INTEGER_TYPES \
X(char) \
X(wchar_t)

#define UNSIGNED_TYPES \
UNSIGNED_INTEGER_TYPES \
X_CHAR16_T \
X_CHAR32_T

#endif // __WCHAR_UNSIGNED__

#endif // __CHAR_UNSIGNED__

#endif
