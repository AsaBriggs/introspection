CC       = g++
DEBUG    = -O0 -g
CFLAGS   = -Wall 
CXXFLAGS = $(CFLAGS)
LDFLAGS	 = -g

TARGETS=meta
INCLUDES=metaprogramming.h detect_traits.h storage.h function_signatures.h

all:$(TARGETS)

meta: meta.o
	$(CC) $(LDFLAGS) $^ -o $@ 

meta.o: meta.cpp $(INCLUDES)
	$(CC) $(CXXFLAGS) -c $< -o $@

.PHONY: clean 

clean :
	rm -rf meta
	rm -rf *.o
