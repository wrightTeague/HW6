all:
	g++ -Wall -g RedBlackTreeTests.cpp RedBlackTree.cpp -o test
	g++ -Wall -g RedBlackTreeTestsFirstStep.cpp RedBlackTree.cpp -o first
clean:
	rm -rf test first *.dSYM
