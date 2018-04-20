/*
TO-DO:
	- Implement play again function
	- Clean-up output function, make more abstact
	- Why does this only work when including .cpp file?
*/

#include "hangmanImpl.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	string dictionary = "hangmanWords.txt", word;
	vector<string> words;

	fstream readInDict;
	readInDict.open(dictionary);
	while (readInDict >> word) {
		words.push_back(word);
	}

	srand(time(NULL));
	string theWord = words[rand() % words.size()];

	CurrentGame game(theWord);
	game.playGame();

	return 0;
}