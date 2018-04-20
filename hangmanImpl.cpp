#include "hangmanImpl.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unordered_map>

using namespace std;

CurrentGame::CurrentGame(string word_in) : chosenWord(word_in), attemptsLeft(6), gameStatus(0) {}

void CurrentGame::playGame() {
	while (!gameStatus && attemptsLeft > 0) {
		printHangman();
		cout << string(3, '\n');
	}
	if (attemptsLeft == 0) {
		printHangman();
		cout << string(3, '\n') << "\t- - - - - - - - - YOU LOSE  - - - - - - - - - " << endl;
		cout << "\tThe word was '" << chosenWord << "'" << string(3, '\n');
	}
}


void CurrentGame::printHangman() {
	cout << "\n\t* * * * * * * * * *";
	if (attemptsLeft)
		cout << " \tYou have " << attemptsLeft << (attemptsLeft == 1 ? " attempt" : " attmepts") << " left\n";
	else {cout << endl;}
	cout << "\t*   _________     *";
	if (attemptsLeft) {
		cout << "\tUsed Letters: [";
		printGuessedLetters();
	}
	else {cout << endl;}
	cout << "\t*   |       |     *" << endl;
	cout << "\t*   |       "; 
	cout << (attemptsLeft < 6 ? "@     *" : "      *") << endl;
	cout << "\t*   |      ";
	if (attemptsLeft == 4)
		cout << " |     *";
	else if (attemptsLeft == 3)
		cout << "/|     *";
	else if (attemptsLeft <= 2)
		cout << "/|\\    *";
	else 
		cout << "       *";
	if (attemptsLeft) {
		cout << "\tWORD:  ";
		printWord();
	} 
	else {cout << endl;}
	cout << "\t*   |      ";
	if (attemptsLeft == 1)
		cout << "/      *" << endl;
	else if (attemptsLeft == 0)
		cout << "/ \\    *" << endl;
	else
		cout << "       *" << endl;
	cout << "\t*   |             *" << endl;
	cout << "\t* * * * * * * * * *";
	cout << (attemptsLeft ? "\tGuess a letter: " : "\n");

	if (attemptsLeft == 0)
		return;

	char guess;
	cin >> guess;
	if (find(lettersGuessed.begin(), lettersGuessed.end(), guess) != lettersGuessed.end()) {
		cout << string(3, '\n') << "\tYOU'VE ALREADY GUESSED THAT LETTER!!";
		return;
	}
	lettersGuessed.push_back(guess);

	size_t indexOfLetter = chosenWord.find_first_of(guess);
	if (indexOfLetter == string::npos) {
		attemptsLeft -= 1;
		return;
	}

	correctLetters.insert(guess);
	if (checkGameStatus()) {
		cout << string(3, '\n') << "\t- - - - - - - - - YOU WON!  - - - - - - - - - " << endl;
		cout << "\tThe word was '" << chosenWord << "'" << string(3, '\n');
		return;
	}
}


int CurrentGame::checkGameStatus() {
	for (int i = 0; i < chosenWord.size(); ++i) {
		if (correctLetters.find(chosenWord[i]) == correctLetters.end() && chosenWord[i] != '-') 
			return 0;
	}
	gameStatus = 1;
	return 1;
}


void CurrentGame::printWord() {
	for (int i = 0; i < chosenWord.size(); ++i) {
		if (chosenWord[i] == '-')
			cout << "- ";
		else if (correctLetters.find(chosenWord[i]) == correctLetters.end()) 
			cout << "_ ";
		else
			cout << chosenWord[i] << " ";
	} 
	cout << "  (" << chosenWord.size() << " letters)" << endl;
}


void CurrentGame::printGuessedLetters() {
	for (int i = 0; i < lettersGuessed.size(); ++i) {
		cout << (i == 0 ? "" : " ") << lettersGuessed[i];
	} cout << "]" << endl;
}
