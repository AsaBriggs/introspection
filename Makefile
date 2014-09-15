CC=g++
CFLAGS=-c -Wall -pedantic -DHAS_NO_LONG_LONG -DHAS_NO_MULTIBYTE_CHAR_T -DHAS_NO_NULL_POINTER
LDFLAGS=
INCLUDES=compiler_specifics.h introspection_assert.h metaprogramming.h detect_traits.h storage.h function_signatures.h storage_io.h introspection_numerics.h function_apply.h
SOURCES=meta.cpp compiler_specifics.cpp introspection_assert.cpp metaprogramming.cpp detect_traits.cpp storage.cpp function_signatures.cpp storage_io.cpp introspection_numerics.cpp function_apply.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=meta

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp $(INCLUDES)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean 

clean :
	rm -rf meta
	rm -rf *.o
