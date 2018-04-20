/*
TO-DO:
	- Make a class, maybe two
	- No globals
	- Actual hangman animation
	- Clean-up output function, make more abstact
	- Change unordered_map to set, or something else
*/



#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unordered_map>

using namespace std;

void printHangman();
int checkGameStatus();
void printWord();
void printGuessedLetters();

int attemptsLeft = 6;
string theWord;
vector<char> lettersGuessed;
unordered_map<char, int> correctLetters;
int gameStatus = 0;

int main() {
	string dictionary = "hangmanWords.txt", word;
	vector<string> words;

	fstream readInDict;
	readInDict.open(dictionary);
	while (readInDict >> word) {
		words.push_back(word);
	}

	srand(time(NULL));
	theWord = words[rand() % words.size()];

	while (!gameStatus && attemptsLeft > 0) {
		printHangman();
		cout << string(5, '\n');
	}
	if (attemptsLeft == 0) {
		cout << "\n\t- - - - - - - - - YOU LOSE  - - - - - - - - - " << endl;
		cout << "\tThe word was '" << theWord << "'" << string(5, '\n');
	}

	return 0;
}


void printHangman() {
	char guess;
	cout << "\n\t* * * * * * * * * *";
	cout << " \tYOU HAVE " << attemptsLeft << " ATTEMPTS LEFT:\n";
	cout << "\t*   _________     *" << endl;
	cout << "\t*   |       |     *";
	cout << "\tWord:  ";
	printWord();
	cout << "\t*   |       |     *" << endl;
	cout << "\t*   |             *" << endl;
	cout << "\t*   |             *" << endl;
	cout << "\t*   |             *" << endl;
	cout << "\t*   |             *" << endl;
	cout << "\t*   |             *" << endl;
	cout << "\t*   |             *";
	cout << "\tLetters you've guessed already: ";
	printGuessedLetters();
	cout << "\t* * * * * * * * * *";
	cout << "\tGuess a letter: ";
	cin >> guess;
	if (find(lettersGuessed.begin(), lettersGuessed.end(), guess) != lettersGuessed.end()) {
		cout << string(5, '\n') << "\tYOU'VE ALREADY GUESSED THAT LETTER!!" << endl;
		return;
	}
	lettersGuessed.push_back(guess);

	size_t indexOfLetter = theWord.find_first_of(guess);
	if (indexOfLetter == string::npos) {
		attemptsLeft -= 1;
		return;
	}

	correctLetters[guess] = indexOfLetter;
	if (checkGameStatus()) {
		cout << string(5, '\n') << "\t- - - - - - - - - YOU WON!  - - - - - - - - - " << endl;
		cout << "\tThe word was '" << theWord << "'" << string(5, '\n');
		return;
	}
}

int checkGameStatus() {
	for (int i = 0; i < theWord.size(); ++i) {
		if (correctLetters.find(theWord[i]) == correctLetters.end() && theWord[i] != '-') 
			return 0;
	}
	gameStatus = 1;
	return 1;
}

void printWord() {
	for (int i = 0; i < theWord.size(); ++i) {
		if (theWord[i] == '-')
			cout << "- ";
		else if (correctLetters.find(theWord[i]) == correctLetters.end()) 
			cout << "_ ";
		else
			cout << theWord[i] << " ";
	} 
	cout << "  (" << theWord.size() << " letters)" << endl;
}

void printGuessedLetters() {
	for (int i = 0; i < lettersGuessed.size(); ++i) {
		cout << lettersGuessed[i] << " ";
	} cout << endl;
}

