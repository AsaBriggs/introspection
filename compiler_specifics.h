#ifndef INCLUDED_COMPILER_SPECIFICS
#define INCLUDED_COMPILER_SPECIFICS

#define INLINE inline
#define HIDDEN __attribute__((__visibility__("hidden")))

#define INLINE_HIDDEN INLINE HIDDEN
#define ALWAYS_INLINE INLINE __attribute__((always_inline))
#define ALWAYS_INLINE_HIDDEN ALWAYS_INLINE HIDDEN

#define TYPE_DEFAULT_VISIBILITY __attribute__((__visibility__("default")))
#define TYPE_HIDDEN_VISIBILITY __attribute__((__visibility__("hidden")))

#endif
