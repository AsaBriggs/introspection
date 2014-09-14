CC=g++
CFLAGS=-c -Wall
LDFLAGS=
INCLUDES=compiler_specifics.h introspection_assert.h metaprogramming.h detect_traits.h storage.h function_signatures.h storage_io.h
SOURCES=meta.cpp compiler_specifics.cpp introspection_assert.cpp metaprogramming.cpp detect_traits.cpp storage.cpp function_signatures.cpp storage_io.cpp
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
