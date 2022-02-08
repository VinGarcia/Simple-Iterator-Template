
test:
	g++ -g -Wall -pedantic -std=c++11 tests.cpp -o tests.exe
	./tests.exe

example1: filter
filter:
	g++ -g -Wall -pedantic -std=c++11 examples/filter.cpp -o filter.exe
	./filter.exe

example2: reverse
reverse:
	g++ -g -Wall -pedantic -std=c++11 examples/reverse.cpp -o reverse.exe
	./reverse.exe

example3: rvalue
rvalue:
	g++ -g -Wall -pedantic -std=c++11 examples/rvalue.cpp -o rvalue.exe
	./rvalue.exe

