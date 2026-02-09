all:
	g++ -std=c++17 -o block-parser main.cpp

run: all
	./block-parser

clean:
	rm -f block-parser
