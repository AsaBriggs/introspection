#include "introspection_numerics.h"

// Defined simple compile-time assetions here to reduce dependencies.

namespace intro {
namespace {

#define ASSERT_IS_UNSIGNED_TYPE(Type) \
  typedef char (*ERROR_ ## Type ## _MUST_BE_UNSIGNED)[((Type) -1 > 0) ? 1 : -1];

#define ASSERT_IS_SIGNED_TYPE(Type) \
  typedef char (*ERROR_ ## Type ## _MUST_BE_SIGNED)[((Type) -1 < 0) ? 1 : -1];

#ifdef __CHAR_UNSIGNED__
ASSERT_IS_UNSIGNED_TYPE(char)
#else // __CHAR_UNSIGNED__
ASSERT_IS_SIGNED_TYPE(char)
#endif // __CHAR_UNSIGNED__


#ifdef __WCHAR_UNSIGNED__
ASSERT_IS_UNSIGNED_TYPE(wchar_t)
#else // __WCHAR_UNSIGNED__
ASSERT_IS_SIGNED_TYPE(wchar_t)
#endif // __WCHAR_UNSIGNED__

} // unnamed namespace
} // namespace intro
