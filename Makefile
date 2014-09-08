CC       = g++
DEBUG    = -O0 -g
CFLAGS   = -Wall 
CXXFLAGS = $(CFLAGS)
LDFLAGS	 = -g

TARGETS=meta
INCLUDES=metaprogramming.h detect_traits.h storage.h

all:$(TARGETS)

eop: meta.o
	$(CC) $(LDFLAGS) $^ -o $@ 

eop.o: meta.cpp $(INCLUDES)
	$(CC) $(CXXFLAGS) -c $< -o $@

.PHONY: clean 

clean :
	rm -rf 
	rm -rf *.o
