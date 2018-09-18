test: test.o
	g++ -lc -o test -ldl -lm test.o -L../ -ltier0 -L../../vstdlib -lvstdlib

test.o: test.cpp
	g++ -c -fpic -I ../../../sdk/valve/public -D __linux__ test.cpp

clean:
	rm -rf test.o
	rm -rf test
 
