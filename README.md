C++ introspection mechanism

The idea is to allow the generation of simple container types that allow introspection, and so allows for programmatic generation of more complex behaviour (operator==, operator<, underlying_type in the Stepanov/EoP sense).

Note that the coding convention follows Boost MPL fairly closely, but without actually pulling in this library. This is because MPL is too dependent on the standard library to be used by this low a level component.
  a) Metafunctions have a nested typedef "type"
  b) metafunction classes have template class called apply nested within it. Note that metafunction forwarding (i.e. inheriting off other metafunctions) is used extensively.

To enable introspection

1) include storage.h
2) Within the struct/class to be introspected add the following typedef in publicly visible scope
    typedef true_type IntrospectionEnabled;

e.g.
```cpp
template<typename T>
struct A_Type
{
    typedef true_type IntrospectionEnabled;
};
```

Note that I tend to put a typedef to type as well, to make the struct a (self-evaluating) metafunction.

At this point the introspection will determine that the struct has no introspectable member variables.
There are two ways of specifying (up to 10) member variables, either by adding typedefs for IntrospectionItemN where N=0..9, or adding a typedef IntrospectionItem which typedefs a (metaprogramming) Array :-

e.g.
```cpp
template<typename T>
struct A_Type
{
    typedef true_type IntrospectionEnabled;
    typedef int IntrospectionItem0;
    typedef float IntrospectionItem1;
    typedef bool IntrospectionItem2;
};
```
or equivalently
```cpp
template<typename T>
struct A_Type
{
    typedef true_type IntrospectionEnabled;
    typedef Array<int, float, bool> IntrospectionItems;
};
```

Still, at this point A_Type has no data members; to get a struct containing the data members the GenerateStorage metafunction is provided.

```cpp
template<typename T>
struct A_Type
{
    typedef true_type IntrospectionEnabled;
    typedef Array<int, float, bool> IntrospectionItems;
    typedef A_Type type; // self evaluating metafunction
    typedef typename GenerateStorageFromArray<IntrospectionItems, DefaultTag>::type Storage;

    Storage m0;
};
```

So at this point A_Type<T> contains a single member m0 of type triple<int, float, bool>; given an instance of A_Type<T> x, to access the int one has to call x.m0.m0, and the float x.m0.m1 .

Adding the typedef IntrospectionIndirectStorage, and having the GenerateStorage<type>::type as a member variable with name m0 allows operator< and operator== to be generated correctly.
This IntrospectionIndirectStorage needs looking at some more; need an elegant way of specifying types to generate, functions to operate on values as well as the nature of the storage. Seems awkward that a user defined type has to contain the generated type at (publicly visible) m0 for it to work.

```cpp
template<typename T>
struct A_Type
{
    typedef true_type IntrospectionEnabled;
    typedef Array<int, float, bool> IntrospectionItems;
    typedef A_Type type; // self evaluating metafunction
    typedef true_type IntrospectionIndirectStorage;

    typename GenerateStorageFromArray<IntrospectioItems, DefaultTag>::type m0;
};
```

Note that the storage types empty_type/singleton/pair/triple etc have been designed to be as light-weight as possible; they are all aggregates, and will be PODs if all they contain are PODs. This allows for aggregate initialisation syntax as well as all the default construction/assignment/move operations being defaults.