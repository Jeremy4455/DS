#include "UFSets.h"

int main() {
	char test[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
	UFSets<char> testSet(test, 10);
	testSet.Union('a', 'c');
	testSet.Union('c', 'e');
	cout << testSet.Differ('a', 'e') << endl;
	return 0;
}