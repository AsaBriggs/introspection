#ifndef INCLUDED_COMPILER_SPECIFICS
#define INCLUDED_COMPILER_SPECIFICS

#define INLINE inline
#define HIDDEN __attribute__((__visibility__("hidden")))

#define INLINE_HIDDEN INLINE HIDDEN
#define ALWAYS_INLINE INLINE __attribute__((always_inline))
#define ALWAYS_INLINE_HIDDEN ALWAYS_INLINE HIDDEN

#define TYPE_DEFAULT_VISIBILITY __attribute__((__visibility__("default")))
#define TYPE_HIDDEN_VISIBILITY __attribute__((__visibility__("hidden")))

// Place this just before the closing brace of the metaprogramming class
// passing in the class name as the parameter. This prevents accidental
// construction of a metaprogramming only class.
// Should be used for all TYPE_HIDDEN_VISIBILITY classes
#define METAPROGRAMMING_ONLY(x) private: x(); ~x();

#endif
