.PHONY: build clean execute

build:
	g++ -g -O0 -Wall -std=c++11 main.cpp -o prog

clean:
	rm -f prog

execute:
	./prog
