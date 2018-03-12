src=$(wildcard *.cpp)
dir=$(notdir $(src))
obj=$(patsubst %.cpp,%.o,$(dir) )

test:
	g++ $(CFLAGS) $(src) -o test -lpthread

clean:
	rm test