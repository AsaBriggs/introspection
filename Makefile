CC       = g++
DEBUG    = -O0 -g
CFLAGS   = -Wall 
CXXFLAGS = $(CFLAGS)
LDFLAGS	 = -g

TARGETS=meta
INCLUDES=compiler_specifics.h introspection_assert.h metaprogramming.h detect_traits.h storage.h function_signatures.h storage_io.h

all:$(TARGETS)

meta: meta.o compiler_specifics.o introspection_assert.o metaprogramming.o detect_traits.o storage.o function_signatures.o storage_io.o
	$(CC) $(LDFLAGS) $^ -o $@ 

meta.o: meta.cpp $(INCLUDES)
	$(CC) $(CXXFLAGS) -c $< -o $@

compiler_specifics.o: compiler_specifics.cpp $(INCLUDES)
	$(CC) $(CXXFLAGS) -c $< -o $@

introspection_assert.o: introspection_assert.cpp $(INCLUDES)
	$(CC) $(CXXFLAGS) -c $< -o $@

metaprogramming.o: metaprogramming.cpp $(INCLUDES)
	$(CC) $(CXXFLAGS) -c $< -o $@

detect_traits.o: detect_traits.cpp $(INCLUDES)
	$(CC) $(CXXFLAGS) -c $< -o $@

storage.o: storage.cpp $(INCLUDES)
	$(CC) $(CXXFLAGS) -c $< -o $@

function_signatures.o: function_signatures.cpp $(INCLUDES)
	$(CC) $(CXXFLAGS) -c $< -o $@

storage_io.o: storage_io.cpp $(INCLUDES)
	$(CC) $(CXXFLAGS) -c $< -o $@

.PHONY: clean 

clean :
	rm -rf meta
	rm -rf *.o
